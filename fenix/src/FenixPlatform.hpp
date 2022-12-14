#pragma once

#ifdef PSP
#include "../../src/psphdr.hpp"
#include <psptypes.h>

/* PI, float-sized */
#define FE_PI (3.141593f)

/* Color Macros, maps 8 bit unsigned channels into one 32-bit value */
#define FE_ABGR(a, b, g, r) (((a) << 24) | ((b) << 16) | ((g) << 8) | (r))
#define FE_ARGB(a, r, g, b) FE_ABGR((a), (b), (g), (r))
#define FE_RGBA(r, g, b, a) FE_ARGB((a), (r), (g), (b))
#define FE_RGB(r, g, b) FE_ABGR(0xff, b, g, r)

#define FE_MAX_LIGHTS 4
#endif
/**
 * @brief Define generic types from platform specific ones
 */
namespace Fenix
{
#ifdef PSP
    typedef ScePspFVector2 _Vector2F;
    typedef ScePspFVector3 _Vector3F;
    typedef ScePspFVector4 _Vector4F;

    typedef ScePspFMatrix2 _Matrix2F;
    typedef ScePspFMatrix3 _Matrix3F;
    typedef ScePspFMatrix4 _Matrix4F;

    // typedef ScePspFQuaternion _Quaternion;
    typedef ScePspQuatMatrix _QuaternionF;

    typedef ScePspRGBA8888 ColorRGBA8;
    typedef ScePspRGBA4444 ColorRGBA4;
    typedef ScePspRGBA5551 ColorRGBA5;
    typedef ScePspRGB565 ColorRGB565;

    typedef ScePspFColor ColorF;

#endif
    typedef struct alignas(32) Vector2F : public _Vector2F
    {
        void add(const Vector2F &other)
        {
            x += other.x;
            y += other.y;
        }
    } Vector2F;

    typedef struct alignas(32) Vector3F : public _Vector3F
    {
        // Vector3F(float _x, float _y, float _z)
        // {
        //     x = _x;
        //     y = _y;
        //     z = _z;
        // };
        void add(const Vector3F &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
        }
        void subtract(const Vector3F &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
        }

        static const Vector3F Front;
    } Vector3F;

    typedef struct alignas(32) Vector4F : public _Vector4F
    {
        void add(const Vector4F &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
        }
        void subtract(const Vector4F &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
        }
    } Vector4F;

    typedef struct alignas(32) Matrix2F : public _Matrix2F
    {
    } Matrix2F;
    typedef struct alignas(32) Matrix3F : public _Matrix3F
    {
    } Matrix3F;
    typedef struct alignas(32) Matrix4F : public _Matrix4F
    {
    } Matrix4F;

    typedef struct alignas(32) QuaternionF : public _QuaternionF
    {
    } QuaternionF;

    enum class ColorType
    {
        COLOR_5650,
        COLOR_5551,
        COLOR_4444,
        COLOR_8888
    };

} // namespace Fenix
