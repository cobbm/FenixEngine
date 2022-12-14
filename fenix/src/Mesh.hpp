#pragma once
#include <memory>
#include "Object3D.hpp"
#include "Geometry.hpp"
#include "Material.hpp"

namespace Fenix
{
    class Mesh : public Object3D
    {
    public:
        static std::shared_ptr<Mesh> createMesh(std::shared_ptr<Geometry> geometry = nullptr, std::shared_ptr<Material> material = nullptr);

        void render() const override;

        Mesh *getMesh() const override;

        Geometry *getGeometry() const;

    private:
        Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);

        std::shared_ptr<Geometry> m_geometry = nullptr;
        std::shared_ptr<Material> m_material = nullptr;
    };
} // namespace Fenix
