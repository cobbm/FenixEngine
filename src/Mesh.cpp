#include "Mesh.hpp"

namespace Fenix
{
    std::shared_ptr<Mesh> Mesh::createMesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material)
    {
        return std::shared_ptr<Mesh>(new Mesh(geometry, material));
    }

    void Mesh::render() const
    {
        if (m_material != nullptr && m_geometry != nullptr)
        {
            m_material->bind();
            m_geometry->draw();
            // now unbind
            m_material->unbind();
        }
        // return 0;
    }

    Mesh *Mesh::getMesh() const
    {
        return (Mesh *)this;
    }

    Geometry *Mesh::getGeometry() const
    {
        return m_geometry.get();
    }

    Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material) : Object3D(), m_geometry(geometry), m_material(material)
    {
    }
}