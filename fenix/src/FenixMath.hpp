#pragma once

#include "FenixPlatform.hpp"

namespace Fenix
{
    Vector3F quaternionToEuler(const QuaternionF &q);

    QuaternionF eulerToQuaternion(const Vector3F &euler);

    void loadIdentity(Matrix4F *matrix);

    void loadIdentity(QuaternionF *quat);

    QuaternionF lookAt(const Vector3F &sourcePoint, const Vector3F &destPoint, const Vector3F &front, const Vector3F &up);

    QuaternionF angleAxisf(const Vector3F &axis, float angle);

} // namespace Fenix