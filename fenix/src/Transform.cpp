#include "Transform.hpp"
#include "FenixMath.hpp"
namespace Fenix
{
    Transform::Transform() : Transform(Vector3F{0, 0, 0}, QuaternionF{0, 0, 0, 1}, Vector3F{1, 1, 1})
    {
        // loadIdentity(&m_rotation);
    }

    Transform::Transform(Vector3F position, QuaternionF rotation, Vector3F scale) : m_position(position), m_rotation(rotation), m_scale(scale)
    {
        // loadIdentity(&m_worldMatrix);
    }

    void Transform::setPosition(const Vector3F &newPosition)
    {
        m_position = newPosition;
        // m_worldPositionNeedsUpdate = true;
    }

    const Vector3F &Transform::getPosition() const
    {
        return m_position;
    }

    void Transform::_setWorldPositionMatrix(const Matrix4F &worldPosition)
    {
        m_worldMatrix = worldPosition;
    }

    const QuaternionF &Transform::getRotation() const
    {
        return m_rotation;
    };

    Vector3F Transform::getRotationEuler() const
    {
        return quaternionToEuler(m_rotation);
    };

    void Transform::setRotationEuler(const Vector3F &euler)
    {
        // Vector3F eulerAl = euler;
        m_rotation = eulerToQuaternion(euler);
    };

    Vector3F Transform::getWorldPosition() const
    {
        // TODO
        return Vector3F{0, 0, 0};
    };

    const Vector3F &Transform::getScale() const
    {
        return m_scale;
    }

    void Transform::lookAt(const Vector3F &target)
    {
        m_rotation = Fenix::lookAt(m_position, target, Vector3F::Front, Vector3F{0, 1, 0});
    }

}