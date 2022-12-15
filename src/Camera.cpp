#include "Camera.hpp"

namespace Fenix
{
    PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far) : Object3D(), m_fovy(fovy), m_aspect(aspect), m_near(near), m_far(far), m_projectionUpdated(true) {}

    void PerspectiveCamera::renderProjectionMatrix() const
    {
        sceGumMatrixMode(GU_PROJECTION);
        {
            sceGumLoadIdentity();
            // sceGumPerspective(75.0f, 16.0f / 9.0f, 0.5f, 1000.0f);
            sceGumPerspective(m_fovy, m_aspect, m_near, m_far);
            m_projectionUpdated = false;
        }
    }

    bool PerspectiveCamera::isProjectionUpdated() const
    {
        return m_projectionUpdated;
    }

    void PerspectiveCamera::setFOV(float fov)
    {
        m_fovy = fov;
        m_projectionUpdated = true;
    }

    void PerspectiveCamera::setAspectRation(float aspect)
    {
        m_aspect = aspect;
        m_projectionUpdated = true;
    }

    void PerspectiveCamera::setNearPlane(float near)
    {
        m_near = near;
        m_projectionUpdated = true;
    }

    void PerspectiveCamera::setFarPlane(float far)
    {
        m_far = far;
        m_projectionUpdated = true;
    }

} // namespace Fenix
