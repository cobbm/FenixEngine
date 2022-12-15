#pragma once

// #include "Camera.hpp"
// #include "Geometry.hpp"

namespace Fenix
{
    class PerspectiveCamera;
    class Geometry;
    class Texture;
    class Scene;
    class Object3D;
    class Light;

    class Renderer
    {
    public:
        Renderer(){};
        virtual ~Renderer() = default;

        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;

        virtual void render(const Scene &, const PerspectiveCamera &) = 0;
        // virtual bool shouldClose() = 0;

        // virtual void drawGeometry(const Geometry &) = 0;
        // virtual void bindTexture(const Texture &) = 0;

        virtual void updateLights(Light *const[]) = 0;

        virtual inline float getFramerate() const = 0;
        virtual inline uint32_t getDebugRenderTime() const = 0;
        virtual inline unsigned int getDebugObjectCount() const = 0;
        virtual inline unsigned int getDebugVerticesCount() const = 0;

    protected:
        virtual void clear() = 0;

        virtual void renderObject(const Object3D &) = 0;
    };

} // namespace Fenix