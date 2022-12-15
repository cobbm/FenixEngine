#include "FenixMath.hpp"
// #include <math.h>
#include <cmath>
#include <pspmath.h>
namespace Fenix
{

    /**
     * @brief Shameless borrowed and adapted from Wikipedia: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
     */

    // Vector3F quaternionToEuler(const QuaternionF &q)
    // {

    //     Vector3F angles;

    //     // roll (x-axis rotation)
    //     double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    //     double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    //     angles.x = std::atan2(sinr_cosp, cosr_cosp);

    //     // pitch (y-axis rotation)
    //     double sinp = 2 * (q.w * q.y - q.z * q.x);
    //     if (std::abs(sinp) >= 1)
    //         angles.y = std::copysign(FE_PI / 2, sinp); // use 90 degrees if out of range
    //     else
    //         angles.y = std::asin(sinp);

    //     // yaw (z-axis rotation)
    //     double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    //     double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    //     angles.z = std::atan2(siny_cosp, cosy_cosp);

    //     return angles;
    // }
    Vector3F quaternionToEuler(const QuaternionF &q)
    {

        Vector3F angles;

        // roll (x-axis rotation)
        float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
        float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
        angles.x = std::atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        float sinp = 2 * (q.w * q.y - q.z * q.x);
        if (std::abs(sinp) >= 1)
            angles.y = std::copysign(FE_PI / 2, sinp); // use 90 degrees if out of range
        else
            angles.y = std::asin(sinp);

        // yaw (z-axis rotation)
        float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
        float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
        angles.z = std::atan2(siny_cosp, cosy_cosp);

        return angles;
    }

    /*
    QuaternionF eulerToQuaternion(const Vector3F &euler)
    {
        // Abbreviations for the various angular functions
        double cy = cos(euler.z * 0.5);
        double sy = sin(euler.z * 0.5);
        double cp = cos(euler.y * 0.5);
        double sp = sin(euler.y * 0.5);
        double cr = cos(euler.x * 0.5);
        double sr = sin(euler.x * 0.5);

        QuaternionF q;
        q.w = cr * cp * cy + sr * sp * sy;
        q.x = sr * cp * cy - cr * sp * sy;
        q.y = cr * sp * cy + sr * cp * sy;
        q.z = cr * cp * sy - sr * sp * cy;

        return q;
    }
    */

#ifdef PSP
    QuaternionF eulerToQuaternion(const Vector3F &euler)
    {
        // Vector3F eulerAl __attribute__((aligned(16))) = euler;
        // QuaternionF out __attribute__((aligned(16))); //= QuaternionF{0, 0, 0, 1};
        QuaternionF out;
        // x and y are swapped?
        vfpu_quaternion_from_euler(&out, euler.x, euler.y, euler.z);
        return out;
    }

    void loadIdentity(Matrix4F *matrix)
    {
        gumLoadIdentity(matrix);
    }
    void loadIdentity(QuaternionF *quat)
    {
        // vfpu_quaternion_identity(quat);
    }

    // Matrix4F lookAt(Vector3F &position, Vector3F &target, Vector3F &up)
    // {
    //     Matrix4F out;
    //     gumLookAt(&out, &position, &target, &up);
    //     return out;
    // }

    QuaternionF lookAt(const Vector3F &sourcePoint, const Vector3F &destPoint, const Vector3F &front, const Vector3F &up)
    {
        Vector3F toVector = destPoint;
        toVector.subtract(sourcePoint);
        gumNormalize(&toVector); // = (destPoint - sourcePoint).normalized();

        // compute rotation axis
        Vector3F rotAxis;
        gumCrossProduct(&rotAxis, &front, &toVector);
        gumNormalize(&rotAxis); // = front.cross(toVector).normalized();

        // calculate squaredNorm
        float rot_sqrNorm = gumDotProduct(&rotAxis, &rotAxis);
        if (rot_sqrNorm == 0)
            rotAxis = up;

        // find the angle around rotation axis
        // float dot = VectorMath::front().dot(toVector);
        float dot = gumDotProduct(&Vector3F::Front, &toVector);

        float ang = std::acos(dot);

        // convert axis angle to quaternion
        return angleAxisf(rotAxis, ang);
        // return QuaternionF{};
    }

    // Angle-Axis to Quaternion
    QuaternionF angleAxisf(const Vector3F &axis, float angle)
    {

        float s = std::sin(angle / 2);
        Vector3F u = axis;
        gumNormalize(&u);
        return QuaternionF{u.x * s, u.y * s, u.z * s, std::cos(angle / 2)};
    }
#endif
} // namespace Fenix