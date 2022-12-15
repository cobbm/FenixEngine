#pragma once
#include "Object3D.hpp"
namespace Fenix
{
    class Renderer;
    class Light;

    class Scene : public Object3D
    {
    public:
        Scene();
        ~Scene();

        void update() override;

        bool hasLightingUpdated() const;
        void renderUpdateScene(Renderer &) const;

        uint32_t getComputeTime() const;

        int registerLight(Light &);
        void unregisterLight(Light &);

    private:
        Light *m_sceneLights[FE_MAX_LIGHTS] = {0};
        mutable bool m_lightsAdjusted = false;

        uint32_t m_tickRes = 0;
        uint32_t m_computeTime = 0;
        uint64_t m_lastUpdateTicks = 0;
    };
} // namespace Fenix
