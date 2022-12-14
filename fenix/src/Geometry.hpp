#pragma once

#include <memory>
#include <malloc.h>

#include "FenixPlatform.hpp"
#include "Renderer.hpp"
// #include "Object3D.hpp"

namespace Fenix
{
    struct VertexF32
    {
        float x, y, z;
    };
    struct NormalF32
    {
        float x, y, z;
    };

    struct TextureF32
    {
        float x, y;
    };

    /*
    // temp:
    typedef struct
    {
        unsigned char a;
        unsigned char b;
        unsigned char g;
        unsigned char r;
    } Color8888;

    struct VF32_TF32
    {
        VertexF32 vert;
        TextureF32 tex;
    };

    struct VF32_C8888_TF32
    {
        TextureF32 tex;
        Color8888 color;
        VertexF32 vert;
    };
    */

    struct VertexLayout
    {
        unsigned int vertexElementSize;
        unsigned int vertexCount;
        unsigned int vertexSize;
        unsigned int weightCount;
        unsigned int weightSize;
        unsigned int textureSize;
        ColorType colorType;
        unsigned int colorSize;
        unsigned int normalSize;
    };

    class Geometry
    {
    public:
        ~Geometry();
        // static std::shared_ptr<Geometry> createGeometry(const VertexLayout &layout, const void *vertexData, unsigned int vertexCount);
        static std::shared_ptr<Geometry> createManagedGeometry(const VertexLayout &layout, const void *vertexData, unsigned int vertexCount, unsigned int indexSize = 0, const void *indexData = nullptr, unsigned int indexCount = 0);
        static std::shared_ptr<Geometry> createGeometry(const VertexLayout &layout, const void *vertexData, unsigned int vertexCount, unsigned int indexSize = 0, const void *indexData = nullptr, unsigned int indexCount = 0);

        void draw(unsigned int textureSize = 0);

        // void setTextureRenderSize(unsigned int textureSize);

        int getVType() const;
        inline unsigned int getCount() const
        {
            return m_indexData != nullptr ? m_indexCount : m_vertexCount;
        };
        const void *getIndices() const;
        const void *getVertices() const;
        unsigned int getIndexCount() const;
        unsigned int getVertexCount() const;

        unsigned int getVertexSize() const;

    private:
        // Geometry(const VertexLayout &vertexLayout, const void *vertexData, unsigned int vertexCount);
        Geometry(const VertexLayout &vertexLayout, const void *vertexData, unsigned int vertexCount, unsigned int indexSize, const void *indexData, unsigned int indexCount, bool managed);

        static int calculateVertexTypeForLayout(const VertexLayout &layout);

        static int calculateIndexTypeForLayout(unsigned int indexSize);

        const void *m_vertexData = nullptr;
        const void *m_indexData = nullptr;

        int m_vertexType = 0;

        unsigned int m_vertexCount = 0;
        unsigned int m_indexCount = 0;

        unsigned int m_vertexSize = 0;
        unsigned int m_indexSize = 0;

        // int m_textureRenderSize = 0;

        bool isManaged;
    };
} // namespace Fenix
