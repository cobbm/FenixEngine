#include "TestApplication.hpp"

#include "TextRenderer.hpp"

using namespace Fenix;

TestApplication::TestApplication() : Fenix::ApplicationBase(), m_scene()
{
}

TestApplication::~TestApplication()
{
}

void TestApplication::run()
{
    Fenix::PerspectiveCamera cam(75.0f, ((float)SCR_WIDTH / SCR_HEIGHT), 0.5f, 1000.0f);

    cam.transform.setPosition(Vector3F{0, 5, -5});
    cam.transform.setRotationEuler(Vector3F{-30, 0, 0});

    std::shared_ptr<Texture> tex = Texture::createTexture(ColorType::COLOR_8888, m_texture, 16, 16);

    std::shared_ptr<Material> mat = Material::createMaterial(tex);
    std::shared_ptr<Material> mat1 = Material::createMaterial(FE_RGB(0xff, 0x00, 0x00));

    VertexLayout layout = {
        .vertexElementSize = sizeof(vertex),
        .vertexCount = 1,
        .vertexSize = sizeof(float),
        .weightCount = 0,
        .weightSize = 0,
        .textureSize = sizeof(float),
        .colorType = ColorType::COLOR_8888,
        .colorSize = sizeof(int),
        .normalSize = 0,
    };

    std::shared_ptr<Geometry> plane = Geometry::createManagedGeometry(layout, m_debugVertices, 4, sizeof(unsigned short), m_indices, 6);

    std::shared_ptr<Mesh> mesh = Mesh::createMesh(plane, mat1);

    std::shared_ptr<Mesh> mesh2 = Mesh::createMesh(plane, mat);
    mesh2->transform.setPosition(Vector3F{2.0f, 0, 0});

    std::shared_ptr<Mesh> mesh3 = Mesh::createMesh(plane, mat1);
    mesh3->transform.setPosition(Vector3F{2.0f, 0, 0});

    mesh->addChild(mesh2);
    mesh2->addChild(mesh3);
    m_scene.addChild(mesh);

    // add a behaviour !
    mesh2->addComponent<TestComponent>();

    // cam.addComponent<TestComponent>();

    while (!shouldQuit())
    {

        cam.update();
        m_scene.update();
        m_renderer->beginFrame();
        m_renderer->render(m_scene, cam);
        drawUI();
        m_renderer->endFrame();
    }
}

void TestApplication::drawUI()
{

    char buff[256];
    // print render info
    snprintf(buff, 255, "%0.0f FPS. Render: %lu, Update: %lu\n(%u objects, %u vertices)", m_renderer->getFramerate(), m_renderer->getDebugRenderTime(), m_scene.getComputeTime(), m_renderer->getDebugObjectCount(), m_renderer->getDebugVerticesCount());
    drawString(buff, 0, 0, FE_RGBA(0xff, 0xff, 0xff, 0xff));
    // print used memory:
    struct mallinfo mi;
    mi = mallinfo();
    snprintf(buff, 255, "Mem: %ub", (mi.uordblks));
    drawString(buff, SCR_WIDTH - measureString(buff), 0, FE_RGBA(0xff, 0xff, 0xff, 0xff));
}
