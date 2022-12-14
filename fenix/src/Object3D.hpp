#pragma once
#include "FenixPlatform.hpp"
#include <vector>
#include <memory>

#include "Transform.hpp"
#include "Component.hpp"

namespace Fenix
{
    class Scene;
    class Mesh;

    class Object3D
    {
    public:
        Object3D();
        virtual ~Object3D() = default;
        /**
         * @brief is this object a physically renderable object?
         *
         * @return bool true if the object is rendered, false otherwise
         */
        bool isEnabled() const;
        void setEnabled(bool state);

        Transform transform;
        const Object3D *getParent();

        void addChild(std::shared_ptr<Object3D> child);
        const std::vector<std::shared_ptr<Object3D>> &getChildren() const;

        virtual void render() const {};

        virtual Mesh *getMesh() const { return nullptr; };

        // component system
        template <typename T>
        Component *addComponent()
        {
            Component *component = new T(*this);
            m_components.push_back(std::unique_ptr<Component>(component));
            return component;
        }

        template <typename T>
        T *getComponentOfType()
        {
            for (const auto &cmpnt_ptr : m_components)
            {
                Component *b = cmpnt_ptr.get();
                if (typeid(*b) == typeid(T))
                {
                    return static_cast<T *>(b);
                }
            }
            return nullptr;
        }

        virtual void update();

        bool hasWorldPositionChanged();

        Scene *getScene();

    protected:
        // trs
        /**
         * @brief Local transformations
         */

        bool m_worldPositionNeedsUpdate;

        bool m_isEnabled;

        Object3D *m_parent = nullptr;
        Scene *m_scene = nullptr;
        std::vector<std::shared_ptr<Object3D>> m_children;

        std::vector<std::unique_ptr<Component>> m_components;

        virtual void addedToScene(Scene &scene);
        void _setParent(Object3D &);
    };

} // namespace Fenix