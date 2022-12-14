

#include "PSPRenderer.hpp"
// #include "TextRenderer.hpp"

// #include "FenixMath.hpp"
// #include "Scene.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
// #include "Geometry.hpp"
// #include "Texture.hpp"
// #include "Material.hpp"
#include "Mesh.hpp"
#include "Light.hpp"

#include <malloc.h>

namespace Fenix
{
    unsigned int __attribute__((aligned(16))) PSPRenderer::drawList[262144] = {0};

    PSPRenderer::PSPRenderer()
    {

        fbp0 = getStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888);
        fbp1 = getStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888);
        zbp = getStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_4444);

        sceGuInit();
        {
            sceGuStart(GU_DIRECT, Fenix::PSPRenderer::drawList);

            sceGuDrawBuffer(GU_PSM_8888, fbp0, BUF_WIDTH);
            sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, fbp1, BUF_WIDTH);
            sceGuDepthBuffer(zbp, BUF_WIDTH);
            sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
            sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
            sceGuDepthRange(65535, 0);
            sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);

            sceGuEnable(GU_SCISSOR_TEST);
            sceGuDepthFunc(GU_GEQUAL);
            sceGuEnable(GU_DEPTH_TEST);

            sceGuShadeModel(GU_SMOOTH);

            sceGuEnable(GU_CULL_FACE);
            sceGuFrontFace(GU_CW);

            // sceGuEnable(GU_TEXTURE_2D);

            sceGuEnable(GU_CLIP_PLANES);

            // sceGuEnable(GU_LIGHTING);

            sceGuEnable(GU_BLEND);
            sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);

            sceGuClearColor(0xff554433);

            sceGuAmbientColor(FE_RGBA(0xff, 0xff, 0xff, 0xff)); // ? in texture?
            sceGuAmbient(FE_RGBA(0x00, 0x00, 0x00, 0xff));

            sceGuFinish();
            sceGuSync(0, 0);
        }
        sceDisplayWaitVblankStart();
        sceGuDisplay(GU_TRUE);

        // sceKernelDcacheWritebackAll();
        // for FPS counter:
        m_tickRes = sceRtcGetTickResolution();
    }

    PSPRenderer::~PSPRenderer()
    {
        sceGuTerm();
    }

    void PSPRenderer::beginFrame()
    {
        sceGuStart(GU_DIRECT, Fenix::PSPRenderer::drawList);
        clear();
    }

    void PSPRenderer::render(const Scene &scene, const PerspectiveCamera &camera)
    {
        // benchmark
        uint64_t render_start_tick;
        uint64_t render_end_tick;
        sceRtcGetCurrentTick(&render_start_tick);

        m_debugObjects = 0;
        m_debugVertices = 0;

        // update lighting
        if (scene.hasLightingUpdated())
        {
            scene.renderUpdateScene(*this);
        }

        // sceGumMatrixMode(GU_PROJECTION);
        // {
        //     sceGumLoadIdentity();
        //     sceGumPerspective(camera.fovy, camera.aspect, camera.near, camera.far);
        // }
        if (m_lastCamera != &camera || camera.isProjectionUpdated())
        {
            camera.renderProjectionMatrix();
            m_lastCamera = (PerspectiveCamera *)&camera;
        }

        sceGumMatrixMode(GU_VIEW);
        {
            sceGumLoadIdentity();
            // apply rotation
            Matrix4F rot __attribute__((aligned(16)));
            vfpu_quaternion_to_matrix((QuaternionF *)&camera.transform.getRotation(), &rot);
            //  sceGumRotateZYX(&rot);
            sceGumMultMatrix(&rot);
            // translate
            Vector3F pos = camera.transform.getPosition();
            pos.x = -pos.x;
            pos.y = -pos.y;
            sceGumTranslate(&pos);
        }

        sceGumMatrixMode(GU_MODEL);
        {
            sceGumLoadIdentity();
            renderObject(scene);
        }

        updateDebugStats();
        // render UI
        // renderUI();

        // benchmark render duration
        sceRtcGetCurrentTick(&render_end_tick);
        m_lastRenderTicks += (render_end_tick - render_start_tick);

        m_frameCount++;
    }

    void PSPRenderer::updateLights(Light *const lights[])
    {
        sceGuEnable(GU_LIGHTING);
        sceGuLightMode(GU_SEPARATE_SPECULAR_COLOR);
        int i = 0;
        while (i < FE_MAX_LIGHTS)
        {
            if (lights[i] == nullptr)
            {
                sceGuDisable(Light::LIGHTS[i]);
            }
            else
            {
                sceGuEnable(Light::LIGHTS[i]);
            }
            i++;
        }
    }

    void PSPRenderer::endFrame()
    {
        sceGuFinish();
        sceGuSync(0, 0);

        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    float PSPRenderer::getFramerate() const
    {
        return m_fps;
    }

    uint32_t PSPRenderer::getDebugRenderTime() const
    {
        return m_renderTime;
    }

    unsigned int PSPRenderer::getDebugObjectCount() const
    {
        return m_debugObjects;
    }

    unsigned int PSPRenderer::getDebugVerticesCount() const
    {
        return m_debugVertices;
    }

    void PSPRenderer::clear()
    {
        // sceGuClearColor(0xff554433);
        sceGuClearDepth(0);
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
    }

    void PSPRenderer::renderObject(const Object3D &object)
    {
        // trs
        sceGumTranslate(&object.transform.getPosition());
        // apply rotation
        Matrix4F rot __attribute__((aligned(16)));
        vfpu_quaternion_to_matrix((QuaternionF *)&object.transform.getRotation(), &rot);
        //  sceGumRotateZYX(&rot);
        sceGumMultMatrix(&rot);
        sceGumScale(&object.transform.getScale());

        // now render the object
        object.render();
        if (Mesh *mesh = object.getMesh())
        {
            if (Geometry *geom = mesh->getGeometry())
                m_debugVertices += geom->getCount();
        }
        // now render the children
        for (auto &child : object.getChildren())
        {
            if (child->isEnabled())
            {
                sceGumPushMatrix();
                renderObject(*child);
                sceGumPopMatrix();
            }
        }
        m_debugObjects++;
    }

    // void PSPRenderer::renderUI()
    //{
    //  calculate FPS:
    //  float curr_fps = 1.0f / curr_ms;

    // char buff[256];
    // snprintf(buff, 255, "%0.0f FPS. Render: %llu\n(%u objects, %u vertices)", m_fps, m_renderTime, m_debugObjects, m_debugVertices);
    // drawString(buff, 0, 0, FE_RGBA(0xff, 0xff, 0xff, 0xff));

    // sceGumMatrixMode(GU_VIEW);
    // {
    //     // ScePspFVector3 pos = {0.0f, 0.0f, -2.5f};
    //     Matrix4F cameraWorld;
    //     sceGumStoreMatrix(&cameraWorld);
    //     const char *v4_fmt = "(%0.2f, %0.2f, %0.2f, %0.2f)\n"
    //                          "(%0.2f, %0.2f, %0.2f, %0.2f)\n"
    //                          "(%0.2f, %0.2f, %0.2f, %0.2f)\n"
    //                          "(%0.2f, %0.2f, %0.2f, %0.2f)";

    //     snprintf(buff, 255, v4_fmt,
    //              cameraWorld.x.x, cameraWorld.x.y, cameraWorld.x.z, cameraWorld.x.w,
    //              cameraWorld.y.x, cameraWorld.y.y, cameraWorld.y.z, cameraWorld.y.w,
    //              cameraWorld.z.x, cameraWorld.z.y, cameraWorld.z.z, cameraWorld.z.w,
    //              cameraWorld.w.x, cameraWorld.w.y, cameraWorld.w.z, cameraWorld.w.w);
    //     drawString(buff, 0, 28, 0xffffffff);
    // }
    //}

    void PSPRenderer::updateDebugStats()
    {
        const unsigned int updateNFrames = 30;
        if (m_frameCount % updateNFrames == 0 && m_frameCount > 0)
        {
            float tickRes = (float)m_tickRes;
            // update fps
            uint64_t curr_tick;
            sceRtcGetCurrentTick(&curr_tick);

            double time_span = ((curr_tick - m_lastFpsTick)) / tickRes;
            // double curr_ms = time_span / updateNFrames;
            // m_fps = 1 / curr_ms;
            m_fps = updateNFrames / time_span;
            m_lastFpsTick = curr_tick;
            // update render duration
            m_renderTime = (m_lastRenderTicks / updateNFrames);
            m_lastRenderTicks = 0;
        }
    }
} // namespace Fenix