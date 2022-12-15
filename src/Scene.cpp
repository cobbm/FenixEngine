#include "Scene.hpp"
#include "Renderer.hpp"

namespace Fenix
{
    Scene::Scene() : Object3D()
    {
        // for FPS counter:
        m_tickRes = sceRtcGetTickResolution();
        m_scene = this;
    }

    Scene::~Scene()
    {
    }

    void Scene::update()
    {

        static int updateCount = 0;
        const int updateN = 30;

        uint64_t updateStartTicks;
        uint64_t updateEndTicks;
        sceRtcGetCurrentTick(&updateStartTicks);

        // benchmark
        Object3D::update();

        // benchmark
        sceRtcGetCurrentTick(&updateEndTicks);
        m_lastUpdateTicks += (updateEndTicks - updateStartTicks);

        if (updateCount % updateN == 0)
        {

            m_computeTime = (m_lastUpdateTicks / updateN);
            m_lastUpdateTicks = 0;
            updateCount = 0;
        }
        updateCount++;
    }

    bool Scene::hasLightingUpdated() const
    {
        return m_lightsAdjusted;
    }

    void Scene::renderUpdateScene(Renderer &r) const
    {
        if (m_lightsAdjusted)
        {
            r.updateLights(m_sceneLights);
            m_lightsAdjusted = false;
        }
    }

    uint32_t Scene::getComputeTime() const
    {
        return m_computeTime;
    }

    int Scene::registerLight(Light &light)
    {
        // Light *l = nullptr;
        int i = 0;
        while (i < FE_MAX_LIGHTS && m_sceneLights[i] != nullptr)
        {
            if (m_sceneLights[i] == &light)
                break;
            i++;
        }
        if (i >= FE_MAX_LIGHTS)
            return -1;

        m_sceneLights[i] = &light;
        m_lightsAdjusted = true;
        return i;
    }

    void Scene::unregisterLight(Light &light)
    {
        // TODO
    }
}