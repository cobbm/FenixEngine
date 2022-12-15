#include "Geometry.hpp"

#include <memory>
#include <malloc.h>
// #include "Object3D.hpp"

namespace Fenix
{

    Geometry::~Geometry()
    {
        if (isManaged)
        {
            if (m_vertexData != nullptr)
            {
                free((void *)m_vertexData);
            }
            if (m_indexData != nullptr)
            {
                free((void *)m_indexData);
            }
        }
    }
    // std::shared_ptr<Geometry> Geometry::createGeometry(const VertexLayout &layout, const void *vertexData, unsigned int vertexCount)
    // {
    //     return std::shared_ptr<Geometry>(new Geometry(layout, vertexData, vertexCount));
    // }
    std::shared_ptr<Geometry> Geometry::createManagedGeometry(const VertexLayout &layout, const void *vertexData, unsigned int vertexCount, unsigned int indexSize, const void *indexData, unsigned int indexCount)
    {
        return std::shared_ptr<Geometry>(new Geometry(layout, vertexData, vertexCount, indexSize, indexData, indexCount, true));
    }
    std::shared_ptr<Geometry> Geometry::createGeometry(const VertexLayout &layout, const void *vertexData, unsigned int vertexCount, unsigned int indexSize, const void *indexData, unsigned int indexCount)
    {
        return std::shared_ptr<Geometry>(new Geometry(layout, vertexData, vertexCount, indexSize, indexData, indexCount, false));
    }

    void Geometry::draw(unsigned int textureSize)
    {
        // renderer.drawGeometry(*this);
        sceGumDrawArray(GU_TRIANGLES, m_vertexType, getCount(), m_indexData, m_vertexData);
    }

    // void Geometry::setTextureRenderSize(unsigned int textureSize)
    // {
    //     switch (textureSize)
    //     {
    //     case 0:
    //         m_textureRenderSize = 0;
    //         break;
    //     case 1:
    //         m_textureRenderSize = GU_TEXTURE_8BIT;
    //         break;
    //     case 2:
    //         m_textureRenderSize = GU_TEXTURE_16BIT;
    //         break;
    //     case 4:
    //         m_textureRenderSize = GU_TEXTURE_32BITF;
    //         break;
    //     }
    // }

    int Geometry::getVType() const
    {
        return m_vertexType;
    }

    // unsigned int Geometry::getCount() const
    // {
    //     return m_indexData != nullptr ? m_indexCount : m_vertexCount;
    // }

    const void *Geometry::getIndices() const
    {
        return m_indexData;
    }

    const void *Geometry::getVertices() const
    {
        return m_vertexData;
    }

    unsigned int Geometry::getIndexCount() const
    {
        return m_indexCount;
    }

    unsigned int Geometry::getVertexCount() const
    {
        return m_vertexCount;
    }

    unsigned int Geometry::getVertexSize() const
    {
        return m_vertexSize;
    }

    Geometry::Geometry(const VertexLayout &vertexLayout, const void *vertexData, unsigned int vertexCount, unsigned int indexSize, const void *indexData, unsigned int indexCount, bool managed) : isManaged(managed)
    {
        // calculate total size of a vertex from the layout data
        // TODO: text weights in this calculation!
        // m_vertexSize = vertexLayout.vertexCount * (3 * (vertexLayout.vertexSize + vertexLayout.normalSize)) + (vertexLayout.weightCount * vertexLayout.weightSize) + (2 * vertexLayout.textureSize) + vertexLayout.colorSize;
        m_vertexSize = vertexLayout.vertexElementSize;
        m_vertexCount = vertexCount;
        m_indexSize = indexSize;
        m_indexCount = indexCount;
        if (managed)
        {
            // do vertex data copy
            const unsigned int vertexBufferSize = m_vertexSize * vertexCount;
            // Allocate space for vertex buffer in RAM. must be aligned by 16 bits?
            // TODO: allow VRAM allocation, too
            // TODO: exceptions?
            m_vertexData = memalign(16, vertexBufferSize);
            if (m_vertexData == nullptr)
            {
                // throw std::runtime_error("Geometry allocation failed!");
                return;
            }
            // copy vertex data:
            memcpy((void *)m_vertexData, vertexData, vertexBufferSize);
        }
        else
        {
            m_vertexData = vertexData;
        }
        // calculate vertex layout info
        m_vertexType = Geometry::calculateVertexTypeForLayout(vertexLayout);
        if (indexData != nullptr)
        {
            if (managed)
            {
                // Allocate space for index buffer in RAM. must be aligned by 16 bits?
                // TODO: allow VRAM allocation, too
                // TODO: exceptions?
                const unsigned int indexBufferSize = indexSize * indexCount;

                m_indexData = memalign(16, indexBufferSize);

                if (m_indexData == nullptr)
                {
                    // throw std::runtime_error("Geometry allocation failed!");
                    return;
                }
                // copy vertex data:
                memcpy((void *)m_indexData, indexData, indexBufferSize);
            }
            else
            {
                m_indexData = indexData;
            }
            // calculate index size:
            m_vertexType |= Geometry::calculateIndexTypeForLayout(indexSize);
        }
    }

    int Geometry::calculateVertexTypeForLayout(const VertexLayout &layout)
    {
        // TODO: include weights in this! (done?)
        int weight = 0;
        int texture = 0;
        int color = 0;
        int normal = 0;
        int vertex = 0;

        // weight
        if (layout.weightSize == sizeof(signed char))
            weight = GU_WEIGHT_8BIT;
        else if (layout.weightSize == sizeof(signed short))
            weight = GU_WEIGHT_16BIT;
        else if (layout.weightSize == sizeof(float))
            weight = GU_WEIGHT_32BITF;
        // else if (layout.weightSize != 0) error

        // texture
        if (layout.textureSize == sizeof(signed char))
            texture = GU_TEXTURE_8BIT;
        else if (layout.textureSize == sizeof(signed short))
            texture = GU_TEXTURE_16BIT;
        else if (layout.textureSize == sizeof(float))
            texture = GU_TEXTURE_32BITF;
        // else if (layout.textureSize != 0) error

        // color
        if (layout.colorSize == sizeof(unsigned short))
        {
            if (layout.colorType == ColorType::COLOR_5650)
                color = GU_COLOR_5650;
            else if (layout.colorType == ColorType::COLOR_5551)
                color = GU_COLOR_5551;
            else if (layout.colorType == ColorType::COLOR_4444)
                color = GU_COLOR_4444;
        }
        else if (layout.colorSize == sizeof(unsigned int) && layout.colorType == ColorType::COLOR_8888)
            color = GU_COLOR_8888;
        // else if (layout.colorSize != 0) error

        // normal
        if (layout.normalSize == sizeof(signed char))
            normal = GU_NORMAL_8BIT;
        else if (layout.normalSize == sizeof(signed short))
            normal = GU_NORMAL_16BIT;
        else if (layout.normalSize == sizeof(float))
            normal = GU_NORMAL_32BITF;
        // else if (layout.normalSize != 0) error

        // vertex
        if (layout.vertexSize == sizeof(signed char))
            vertex = GU_VERTEX_8BIT;
        else if (layout.vertexSize == sizeof(signed short))
            vertex = GU_VERTEX_16BIT;
        else if (layout.vertexSize == sizeof(float))
            vertex = GU_VERTEX_32BITF;
        // else error

        int vertices_n = 0;
        if (layout.vertexCount > 0)
            vertices_n = GU_VERTICES(layout.vertexCount);
        int weights_n = 0;
        if (layout.weightCount > 0)
            weights_n = GU_WEIGHTS(layout.weightCount);

        return GU_TRANSFORM_3D | vertices_n | weights_n | weight | texture | color | normal | vertex;
    }

    int Geometry::calculateIndexTypeForLayout(unsigned int indexSize)
    {
        int indices = 0;
        if (indexSize == sizeof(unsigned char))
            indices = GU_INDEX_8BIT;
        else if (indexSize == sizeof(unsigned short))
            indices = GU_INDEX_16BIT;
        // else error

        return indices;
    }

} // namespace Fenix
