#include "Texture.hpp"

namespace Fenix
{
    std::shared_ptr<Texture> Texture::createTexture(ColorType textureFormat, const void *textureData, unsigned int width, unsigned int height, bool swizzle)
    {
        return std::shared_ptr<Texture>(new Texture(textureFormat, textureData, width, height, swizzle));
    }

    // unsigned int Texture::getTextureRenderSize()
    // {
    //     return m_texturePixelSize;
    // }

    void Texture::bind()
    {
        sceGuEnable(GU_TEXTURE_2D);
        // renderer.bindTexture(*this);
        sceGuTexMode(m_texturePixelFormat, /*mipmaps: */ 0, 0, m_swizzle);
        // TODO: check buffer width = texture width?:
        sceGuTexImage(/*mipmap level:*/ 0, m_width, m_height, m_width, m_textureData);
        sceGuTexFunc(m_filterApplyMode, m_filterComponentMode);
        sceGuTexEnvColor(m_envColor);
        sceGuTexFilter(m_filterMin, m_filterMag);
        sceGuTexScale(m_scaleU, m_scaleV);
        sceGuTexOffset(m_offsetU, m_offsetV);
    }

    void Texture::unbind()
    {
        sceGuDisable(GU_TEXTURE_2D);
    }

    Texture::Texture(ColorType textureFormat, const void *textureData, unsigned int width, unsigned int height, bool swizzle)
        : m_textureData(textureData),
          m_width(width),
          m_height(height),
          m_swizzle(swizzle),
          m_offsetU(0.0),
          m_offsetV(0.0),
          m_scaleU(1.0),
          m_scaleV(1.0),
          m_envColor(GU_RGBA(0xff, 0xff, 0xff, 0xff)), // affects GU_TFX_BLEND mode
          m_filterMin(GU_LINEAR),
          m_filterMag(GU_LINEAR),
          m_filterApplyMode(GU_TFX_MODULATE),
          m_filterComponentMode(GU_TCC_RGB)
    {
        // calculate platform specific texture mode
        // TODO: indexed mode
        switch (textureFormat)
        {
        case ColorType::COLOR_5650:
            m_texturePixelFormat = GU_PSM_5650;
            m_texturePixelSize = sizeof(unsigned short);
            break;
        case ColorType::COLOR_5551:
            m_texturePixelFormat = GU_PSM_5551;
            m_texturePixelSize = sizeof(unsigned short);
            break;
        case ColorType::COLOR_4444:
            m_texturePixelFormat = GU_PSM_4444;
            m_texturePixelSize = sizeof(unsigned short);
            break;
        case ColorType::COLOR_8888:
            m_texturePixelFormat = GU_PSM_8888;
            m_texturePixelSize = sizeof(unsigned int);
            break;
        default:
            // error
            m_texturePixelFormat = 0;
            break;
        }
    }
}