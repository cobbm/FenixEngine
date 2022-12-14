#pragma once

#include "FenixPlatform.hpp"

#include "Renderer.hpp"

#include "Object3D.hpp"

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

namespace Fenix
{
    class PSPRenderer : public Renderer
    {
    public:
        PSPRenderer();
        ~PSPRenderer();

        void beginFrame() override;

        void render(const Scene &, const PerspectiveCamera &) override;

        void updateLights(Light *const[]) override;

        void endFrame() override;

        // void drawGeometry(const Geometry &) override;
        // void bindTexture(const Texture &) override;

        inline float getFramerate() const;
        inline uint32_t getDebugRenderTime() const;
        inline unsigned int getDebugObjectCount() const;
        inline unsigned int getDebugVerticesCount() const;

    protected:
        void clear() override;

        void renderObject(const Object3D &) override;

    private:
        void *fbp0;
        void *fbp1;
        void *zbp;

        static unsigned int __attribute__((aligned(16))) drawList[262144];

        PerspectiveCamera *m_lastCamera = nullptr;

        uint32_t m_tickRes = 0;
        float m_fps = 0;
        uint64_t m_lastFpsTick = 0;
        uint64_t m_renderTime = 0;
        uint64_t m_lastRenderTicks = 0;

        unsigned int m_debugVertices = 0;
        unsigned int m_debugObjects = 0;
        unsigned long m_frameCount = 0;

        void renderUI();

        void updateDebugStats();
    };

    typedef PSPRenderer PlatformRenderer;
} // namespace Fenix
