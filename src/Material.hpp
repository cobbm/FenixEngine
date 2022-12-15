#pragma once
#include <memory>
#include "Texture.hpp"

namespace Fenix
{
    class Material
    {

    public:
        // constructor for textured materials
        static std::shared_ptr<Material> createMaterial(std::shared_ptr<Texture> &texture);
        // constructor for single color materials
        static std::shared_ptr<Material> createMaterial(ColorRGBA8 color);

        void bind();
        void unbind();

    private:
        Material(std::shared_ptr<Texture> &texture);
        Material(ColorRGBA8 color);

        std::shared_ptr<Texture> m_texture = nullptr;
        ColorRGBA8 m_color = FE_RGBA(0x0, 0x0, 0x0, 0x0);

        float m_specularPower = 1.5f;
    };
} // namespace Fenix