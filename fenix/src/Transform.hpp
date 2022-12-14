#pragma once
#include "FenixPlatform.hpp"

namespace Fenix
{
    class Transform
    {
    public:
        Transform();
        Transform(Vector3F position, QuaternionF rotation, Vector3F scale);
        ~Transform() = default;
        void setPosition(const Vector3F &newPosition);

        const Vector3F &getPosition() const;
        void _setWorldPositionMatrix(const Matrix4F &worldPosition);

        const QuaternionF &getRotation() const;
        /**
         * @brief Get the objects local rotation in Euler angles
         *
         * @return Vector3F euler angles
         */
        Vector3F getRotationEuler() const;

        /**
         * @brief Set the local Rotation of the object using Euler angles
         *
         * @param euler euler rotation angles in local space
         */
        void setRotationEuler(const Vector3F &);

        /**
         * @brief Get the position in World space of the object
         *
         * @return Vector3F world position as a 3 component vector
         */
        Vector3F getWorldPosition() const;

        const Vector3F &getScale() const;

        void lookAt(const Vector3F &);

        bool hasWorldPositionChanged();

    protected:
        Vector3F m_position;
        QuaternionF m_rotation;
        Vector3F m_scale;

        Matrix4F m_worldMatrix;
    };
} // namespace Fenix
