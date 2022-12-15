#include "Light.hpp"
#include "Scene.hpp"

namespace Fenix
{
    const int Light::LIGHTS[] = {GU_LIGHT0, GU_LIGHT1, GU_LIGHT2, GU_LIGHT3};

    Light::Light(ColorRGBA8 diffuse, ColorRGBA8 specular) : Object3D(), m_lightId(-1), m_lightParamsUpdated(true), m_diffuse(diffuse), m_specular(specular), m_atten0(0.0f), m_atten1(1.0f), m_atten2(0.0f)
    {
    }

    void Light::render() const
    {
        if (m_lightId >= 0)
        {
            sceGuLight(m_lightId, GU_DIRECTIONAL, GU_DIFFUSE_AND_SPECULAR, &transform.getPosition());
            if (m_lightParamsUpdated)
            {
                sceGuLightColor(m_lightId, GU_DIFFUSE, m_diffuse);
                sceGuLightColor(m_lightId, GU_SPECULAR, m_specular);
                sceGuLightAtt(m_lightId, m_atten0, m_atten1, m_atten2);
                m_lightParamsUpdated = false;
            }
        }
    }

    void Light::setDiffuseColor(ColorRGBA8 diffuse)
    {
        m_diffuse = diffuse;
        m_lightParamsUpdated = true;
    }

    void Light::setSpecularColor(ColorRGBA8 specular)
    {
        m_specular = specular;
        m_lightParamsUpdated = true;
    }

    void Light::_setLightId(int lightId)
    {
        m_lightId = lightId;
        m_lightParamsUpdated = true;
    }

    void Light::addedToScene(Scene &scene)
    {
        _setLightId(scene.registerLight(*this));
        Object3D::addedToScene(scene);
    }
}