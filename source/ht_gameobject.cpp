/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#include <ht_gameobject.h>

#if defined(DEBUG) || defined(_DEBUG)
    #include <ht_debug.h>
#endif

namespace Hatchit {

    namespace Game {
        GameObject::GameObject(void)
        {
            m_enabled = false;
            m_parent = nullptr;
            m_components = std::vector<Component*>();
            m_children = std::vector<GameObject*>();
            m_componentMap = std::unordered_map<Guid, std::vector<Component*>::size_type>();
        }

        GameObject::GameObject(const Guid& guid, const std::string& name, Transform& t)
            : GameObject()
        {
            m_guid = guid;
            m_name = name;
            m_transform = t;
        }

        GameObject::~GameObject(void)
        {
            for (GameObject* child : m_children)
            {
                delete child;
            }
            for (Component *component: m_components)
            {
                delete component;
            }
        }

        const Guid& GameObject::GetGuid(void) const
        {
            return m_guid;
        }

        const std::string& GameObject::GetName(void) const
        {
            return m_name;
        }

        Transform& GameObject::GetTransform(void)
        {
            return m_transform;
        }

        bool GameObject::GetEnabled(void) const
        {
            return m_enabled;
        }

        void GameObject::SetEnabled(bool value)
        {
            m_enabled = value;
        }

        GameObject* GameObject::GetParent(void)
        {
            return m_parent;
        }

        void GameObject::SetParent(GameObject *parent)
        {
            HT_DEBUG_PRINTF("GameObject SetParent. (not implemented)\n");
        }

        void GameObject::Update(void)
        {
            for (Component *component : m_components)
            {
                    if(component->GetEnabled())
                        component->VOnUpdate();
            }

            for (std::size_t i = 0; i < m_children.size(); ++i)
            {
                GameObject *child = m_children[i];
                if (child->GetEnabled())
                    child->Update();
            }
        }

        void GameObject::OnInit(void)
        {
            HT_DEBUG_PRINTF("GameObject OnInit. (not implemented)\n");
        }

        void GameObject::OnDestroy(void)
        {
            Disable();

            for (Component *component : m_components)
            {
                if (component->GetEnabled())
                    component->SetEnabled(false);
                component->VOnDestroy();
            }

            for (std::size_t i = 0; i < m_children.size(); ++i)
            {
                GameObject *child = m_children[i];
                if (child)
                    child->OnDestroy();
            }
        }

        GameObject* GameObject::GetChildAtIndex(std::size_t index)
        {
            if (index >= m_children.size())
                return nullptr;

            return m_children[index];
        }

        void GameObject::AddChild(GameObject *child)
        {
            m_transform.AddChild(&child->GetTransform());
        }

        void GameObject::RemoveChild(GameObject* child)
        {
            m_transform.RemoveChild(&child->GetTransform());
        }

        void GameObject::RemoveChildAtIndex(std::size_t index)
        {
            m_transform.RemoveChildAtIndex(index);
        }
    }
}
