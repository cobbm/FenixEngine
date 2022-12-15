#pragma once
#include "Object3D.hpp"

namespace Fenix
{
    class PerspectiveCamera : public Object3D
    {
    public:
        PerspectiveCamera(float fovy, float aspect, float near, float far);

        void renderProjectionMatrix() const;
        bool isProjectionUpdated() const;

        void setFOV(float fov);
        void setAspectRation(float aspect);
        void setNearPlane(float near);
        void setFarPlane(float far);

    private:
        float m_fovy;
        float m_aspect;
        float m_near;
        float m_far;

        mutable bool m_projectionUpdated;
    };
} // namespace Fenix
