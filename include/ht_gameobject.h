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

#pragma once

#include <vector>
#include <bitset>
#include <tuple>
#include <utility>

#include <ht_platform.h>
#include <ht_component.h>

namespace Hatchit {

	namespace Game {

		class HT_API GameObject
		{
		public:
            static constexpr std::uint32_t MAX_COMPONENTS{50};

            GameObject(const GameObject& rhs) = default;
            GameObject(GameObject&& rhs) = default;
            GameObject& operator=(const GameObject& rhs) = default;
            GameObject& operator=(GameObject&& rhs) = default;

            GameObject(void);
            ~GameObject(void);

            bool GetEnabled(void) const;
            void SetEnabled(bool value);

            inline void Enable(void)
            {
                SetEnabled(true);
            }

            inline void Disable(void)
            {
                SetEnabled(false);
            }

            GameObject* GetParent(void);
            void SetParent(GameObject *parent);

            GameObject* GetChildAtIndex(std::size_t index);

            void AddChild(GameObject *child);

            void RemoveChildAtIndex(std::size_t index);

            /**
            * Called when the gameobject is created to initialize all values
            */
            void OnInit(void);

			/** Called once per frame while the gameobject is enabled
			* Updates all components first, then all child gameobjects
			*/
			void Update(void);

            /** Called when the gameobject is destroyed/deleted.
            * Objects are always disabled before destroyed.
            * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
            */
            void OnDestroy(void);

            template <typename T>
            bool AddComponent(T *component);

            template <typename T, typename... Args>
            bool AddComponent(Args&&... args);

            template <typename T>
            bool RemoveComponent(void);

            template <typename T>
            bool HasComponent(void) const;

            template <typename T1, typename T2, typename... Args>
            bool HasComponent(void) const;

            template <typename T>
            T* GetComponent(void);

            template <typename... Args>
            std::tuple<Args*...> GetComponents(void);

            template <typename T>
            bool EnableComponent(void);

            template <typename... Args>
            auto EnableComponents(void) -> decltype(std::make_tuple(EnableComponent<Args>()...))
            {
                return std::make_tuple(EnableComponent<Args>()...);
            }

            template <typename T>
            bool DisableComponent(void);

            template <typename... Args>
            auto DisableComponents(void) -> decltype(std::make_tuple(DisableComponent<Args>()...))
            {
                return std::make_tuple(DisableComponent<Args>()...);
            }

		private:
            bool m_enabled;
            GameObject *m_parent;
            std::vector<GameObject*> m_children;
            std::bitset<MAX_COMPONENTS> m_componentMask;
            std::vector<Component*> m_components;
		};

        template <typename T>
        bool GameObject::AddComponent(T *component)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            std::uint32_t component_id = Component::GetComponentId<T>();
            if (component_id >= MAX_COMPONENTS)
                return false;

            if (m_componentMask.test(component_id))
                return false;

            m_componentMask.set(component_id);

            m_components[component_id] = component;

            component->Init();

            if (m_enabled)
                component->Enable();

            return true;
        }

        template <typename T, typename... Args>
        bool GameObject::AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            std::uint32_t component_id = Component::GetComponentId<T>();
            if (component_id >= MAX_COMPONENTS)
                return false;

            if (m_componentMask.test(component_id))
                return false;

            m_componentMask.set(component_id);

            T *component = new T(std::forward<Args>(args)...);

            m_components[component_id] = component;

            component->Init();

            if (m_enabled)
                component->Enable();

            return true;
        }

        template <typename T>
        bool GameObject::RemoveComponent(void)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            std::uint32_t component_id = Component::GetComponentId<T>();
            if (component_id >= GameObject::MAX_COMPONENTS)
                return false;

            if (!m_componentMask.test(component_id))
                return false;

            Component *component = m_components[component_id];
            component->Disable();
            component->Destroy();

            m_componentMask.reset(component_id);
            m_components[component_id] = nullptr;
            delete component;

            return true;
        }

        template <typename T>
        bool GameObject::HasComponent(void) const
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            std::uint32_t component_id = Component::GetComponentId<T>();
            if (component_id >= GameObject::MAX_COMPONENTS)
                return false;

            return m_componentMask.test(component_id);
        }

        template <typename T1, typename T2, typename... Args>
        bool GameObject::HasComponent(void) const
        {
            static_assert(std::is_base_of<Component, T1>::value, "Must be a sub-class of Hatchit::Game::Component!");

            std::uint32_t component_id = Component::GetComponentId<T1>();
            if (component_id >= GameObject::MAX_COMPONENTS)
                return false;

            return HasComponent<T1>() && HasComponent<T2, Args...>();
        }

        template <typename T>
        T* GameObject::GetComponent(void)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            std::uint32_t component_id = Component::GetComponentId<T>();
            if (component_id >= GameObject::MAX_COMPONENTS)
                return nullptr;

            if (!m_componentMask.test(component_id))
                return nullptr;

            return dynamic_cast<T*>(m_components[component_id]);
        }

        template <typename... Args>
        std::tuple<Args*...> GameObject::GetComponents(void)
        {
            return std::make_tuple(GetComponent<Args>()...);
        }

        template <typename T>
        bool GameObject::EnableComponent(void)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            if (!HasComponent<T>())
                return false;

            std::uint32_t component_id = Component::GetComponentId<T>();
            if (component_id >= MAX_COMPONENTS)
                return false;

            Component *component = m_components[component_id];
            if (component->GetEnabled())
                return false;

            component->Enable();

            return true;
        }

        template <typename T>
        bool GameObject::DisableComponent(void)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            if (!HasComponent<T>())
                return false;

            std::uint32_t component_id = Component::GetComponentId<T>();
            if (component_id >= MAX_COMPONENTS)
                return false;

            Component *component = m_components[component_id];
            if (!component->GetEnabled())
                return false;

            component->Disable();

            return true;
        }
	}
}
