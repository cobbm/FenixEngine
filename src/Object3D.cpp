
// #include "FenixPlatform.hpp"

#include "Object3D.hpp"
#include "FenixMath.hpp"
// #include <vector>
// #include <typeinfo>

namespace Fenix
{

    Object3D::Object3D() : transform(), m_worldPositionNeedsUpdate(false), m_isEnabled(true), m_parent(nullptr){
                                                                                                  // if (parent == nullptr)
                                                                                                  //{
                                                                                                  // gumLoadIdentity(&m_worldMatrix);

                                                                                                  //}
                                                                                              };

    bool Object3D::isEnabled() const
    {
        return m_isEnabled;
    };

    void Object3D::setEnabled(bool state)
    {
        m_isEnabled = state;
    };

    const Object3D *Object3D::getParent()
    {
        return m_parent;
    }

    Scene *Object3D::getScene()
    {
        return m_scene;
    }

    void Object3D::addChild(std::shared_ptr<Object3D> child)
    {
        child->_setParent(*this);
        m_children.push_back(child);
    }

    const std::vector<std::shared_ptr<Object3D>> &Object3D::getChildren() const
    {
        return m_children;
    }

    void Object3D::addedToScene(Scene &scene)
    {
        m_scene = &scene;
        for (const auto &ch : m_children)
        {
            ch->addedToScene(scene);
        }
    }

    void Object3D::_setParent(Object3D &parent)
    {
        m_parent = &parent;
        if (m_scene != parent.m_scene)
        {
            addedToScene(*(parent.m_scene));
        }
    }

    void Object3D::update()
    {
        // update all components in this object
        for (const auto &cmpnt_ptr : m_components)
        {
            // check if we need to call start()
            if (!cmpnt_ptr->hasStarted())
                cmpnt_ptr->init();
            cmpnt_ptr->update();
        }
        for (const auto &ch : m_children)
        {
            ch->update();
        }
    }

    bool Object3D::hasWorldPositionChanged()
    {
        return m_worldPositionNeedsUpdate || (m_parent != nullptr ? m_parent->hasWorldPositionChanged() : false);
    }

} // namespace Fenix