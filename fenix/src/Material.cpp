#include "Material.hpp"

namespace Fenix
{
    std::shared_ptr<Material> Material::createMaterial(std::shared_ptr<Texture> &texture)
    {
        return std::shared_ptr<Material>(new Material(texture));
    }

    std::shared_ptr<Material> Material::createMaterial(ColorRGBA8 color)
    {
        return std::shared_ptr<Material>(new Material(color));
    }

    void Material::bind()
    {
        if (m_texture != nullptr)
        {
            m_texture->bind();
        }
        else
        {
            sceGuColor(m_color);
        }
        sceGuSpecular(m_specularPower);
        // sceGuModelColor();
    }

    void Material::unbind()
    {
        if (m_texture != nullptr)
        {
            m_texture->unbind();
        }
        else
        {
            // sceGuColor(m_color);
        }
    }

    Material::Material(std::shared_ptr<Texture> &texture) : m_texture(texture)
    {
    }

    Material::Material(ColorRGBA8 color) : m_color(color)
    {
    }
}