#pragma once
#include "Object3D.hpp"

namespace Fenix
{

    class Light : public Object3D
    {
    public:
        Light(ColorRGBA8 diffuse = FE_RGBA(0xff, 0xff, 0xff, 0xff), ColorRGBA8 specular = FE_RGBA(0xff, 0xff, 0xff, 0xff));

        static const int LIGHTS[FE_MAX_LIGHTS];

        void render() const override;

        void setDiffuseColor(ColorRGBA8 diffuse);
        void setSpecularColor(ColorRGBA8 specular);

    protected:
        void _setLightId(int);

        void addedToScene(Scene &) override;

    private:
        int m_lightId;

        mutable bool m_lightParamsUpdated;
        ColorRGBA8 m_diffuse;
        ColorRGBA8 m_specular;

        float m_atten0;
        float m_atten1;
        float m_atten2;
    };
} // namespace Fenix
