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
#include <ht_debug.h>

namespace Hatchit {

	namespace Game {
        GameObject::GameObject(void)
        {
            m_components = std::vector<Component*>(GameObject::MAX_COMPONENTS, nullptr);
        }

        GameObject::~GameObject(void)
        {
            for (std::size_t i = 0; i < GameObject::MAX_COMPONENTS; ++i)
            {
                if(m_componentMask.test(i))
                {
                    delete m_components[i];
                }
            }
        }

        bool GameObject::GetEnabled(void) const
        {
            return m_enabled;
        }

        void GameObject::SetEnabled(bool value)
        {
#ifdef _DEBUG
            Core::DebugPrintF("GameObject SetEnabled. (not implemented)\n");
#endif
        }

        GameObject* GameObject::GetParent(void)
        {
            return m_parent;
        }

        void GameObject::SetParent(GameObject *parent)
        {
#ifdef _DEBUG
            Core::DebugPrintF("GameObject SetParent. (not implemented)\n");
#endif
        }

        void GameObject::Init(void)
        {
#ifdef _DEBUG
            Core::DebugPrintF("GameObject initialized. (not implemented)\n");
#endif
        }

        void GameObject::Update()
        {
#ifdef _DEBUG
            Core::DebugPrintF("GameObject updated. (not implemented)\n");
#endif
        }

        void GameObject::Destroy()
        {
#ifdef _DEBUG
            Core::DebugPrintF("GameObject destroyed. (not implemented)\n");
#endif
        }

		void GameObject::OnInit()
		{
#ifdef _DEBUG
            Core::DebugPrintF("GameObject OnInit. (not implemented)\n");
#endif
		}

		void GameObject::OnEnabled()
		{
#ifdef _DEBUG
            Core::DebugPrintF("GameObject OnEnabled. (not implemented)\n");
#endif
		}

		void GameObject::OnDisabled()
		{
#ifdef _DEBUG
            Core::DebugPrintF("GameObject OnDisabled. (not implemented)\n");
#endif
		}

		void GameObject::OnDestroy()
		{
#ifdef _DEBUG
            Core::DebugPrintF("GameObject OnDestroy. (not implemented)\n");
#endif
		}

        void GameObject::AddChild(GameObject *child)
        {
#ifdef _DEBUG
            Core::DebugPrintF("GameObject AddChild. (not implemented)\n");
#endif
        }

        GameObject* GameObject::GetChildAtIndex(std::size_t index)
        {
#ifdef _DEBUG
            Core::DebugPrintF("GameObject GetChildAtIndex. (not implemented)\n");
#endif
            return nullptr;
        }

        void GameObject::RemoveChildAtIndex(std::size_t index)
        {
#ifdef _DEBUG
            Core::DebugPrintF("GameObject RemoveChildAtIndex. (not implemented)\n");
#endif
        }
	}
}
