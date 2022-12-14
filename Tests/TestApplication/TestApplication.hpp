#pragma once
#include "Fenix.hpp"

class TestComponent : public Fenix::Component
{
public:
    using Fenix::Component::Component;

    unsigned int t = 0;

    void start() override
    {
    }

    void update() override
    {
        float r = sinf(t / 30.0f);
        ownerObject.transform.setRotationEuler(Fenix::Vector3F{r * 90, 0, 0});
        // ownerObject.transform.setPosition(Fenix::Vector3F{r *2.0f, 0, 0});
        t++;
    }
};

class TestApplication : public Fenix::ApplicationBase
{
private:
    Fenix::Scene m_scene;

public:
    TestApplication();
    ~TestApplication();

    // void begin() override;
    void run() override;

    void drawUI();

    struct vertex_coord
    {
        float x, y, z;
    };

    struct vertex_uv
    {
        float u;
        float v;
    };

    struct vertex
    {
        vertex_uv uv;
        int color;
        vertex_coord pos;
    };

#define B 0xff000000
#define W 0xffffffff

    // checkerboard pattern
    const unsigned int __attribute__((aligned(16))) m_texture[256] = {
#if 1
                W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
                W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
                B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
                B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
                W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
                W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
                B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
                B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
                W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
                W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
                B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
                B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
                W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
                W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
                B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
                B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
#else
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
        W,
        B,
#endif
    };

    const vertex __attribute__((aligned(16))) m_debugVertices[4] = {
        {{-1, -1},
         GU_RGBA(0xff, 0x00, 0x00, 0xff),
         {-1, -1, 0}}, // 0
        {
            {-1, 1},
            GU_RGBA(0x00, 0xff, 0x00, 0xff),
            {-1, 1, 0}}, // 4
        {
            {1, 1},
            GU_RGBA(0x00, 0x00, 0xff, 0xff),
            {1, 1, 0}}, // 5
        {
            {1, -1},
            GU_RGBA(0xff, 0xff, 0xff, 0xff),
            {1, -1, 0}},
    };
    const unsigned short __attribute__((aligned(16))) m_indices[6] = {
        0,
        1,
        2,
        2,
        3,
        0,

    };
};
