#pragma once
#include <memory>
#include "FenixPlatform.hpp"
#include "Renderer.hpp"

namespace Fenix
{
    class Texture
    {
    public:
        static std::shared_ptr<Texture> createTexture(ColorType textureFormat, const void *textureData, unsigned int width, unsigned int height, bool swizzle = false);

        // inline unsigned int getTextureRenderSize();

        void bind();
        void unbind();

    private:
        Texture(ColorType textureFormat, const void *textureData, unsigned int width, unsigned int height, bool swizzle);

        int m_texturePixelFormat;
        unsigned int m_texturePixelSize;

        const void *m_textureData; // make array of struct for 8 mipmap levels
        unsigned int m_width;
        unsigned int m_height;

        bool m_swizzle;

        float m_offsetU;
        float m_offsetV;

        float m_scaleU;
        float m_scaleV;

        ColorRGBA8 m_envColor;

        int m_filterMin;
        int m_filterMag;

        int m_filterApplyMode;
        int m_filterComponentMode;
    };

} // namespace Fenix