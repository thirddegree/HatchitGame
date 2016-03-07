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

/**
* \class GameObject
* \ingroup HatchitGame
*
* \brief Basic Hatchit GameObject.
*
* Components can be attached to/removed from a GameObject.
* GameObjects can be attached to/removed from themselves.
* Updating a GameObject will update it, its components, and its children.
*/

#pragma once

#include <vector>
#include <bitset>
#include <tuple>
#include <utility>

#include <ht_platform.h>
#include <ht_component.h>
#include <ht_transform.h>
#include <ht_guid.h>

#ifdef HT_SYS_LINUX
    #include <cstdlib>
#endif

namespace Hatchit {

    namespace Game {

        class HT_API GameObject
        {
        public:
            static constexpr std::uint32_t MAX_COMPONENTS{50}; /**< The maximum number of Components that can be attached to a GameObject. */

            GameObject(const GameObject& rhs) = default;
            GameObject(GameObject&& rhs) = default;
            GameObject& operator=(const GameObject& rhs) = default;
            GameObject& operator=(GameObject&& rhs) = default;

            /**
            * \brief The constructor for GameObject.
            *
            * Responsible for initializing the Component vector, Component bitmask, and child vector.
            */
            GameObject(void);

			/**
			* \brief The constructor for GameObject read from scene file.
			*
			* Responsible for initializing the Component vector, Component bitmask, and child vector.
			* Sets the GameObject's guid to an existing value.
			*/
			GameObject::GameObject(uint8_t uuid[]);

            /**
            * \brief The destructor for GameObject.
            *
            * Responsible for deleting all currently attached components.
            */
            ~GameObject(void);

            Transform* GetTransform();

            /**
            * \brief Indicates whether or not this GameObject is enabled.
            * \return bool indicating if this GameObject is enabled.
            */
            bool GetEnabled(void) const;

            /**
            * \brief Enables/Disables the GameObject based on the provided value
            * \param value The new value of m_enabled.
            */
            void SetEnabled(bool value);

            /**
            * \brief An inline for SetEnabled(true);
            */
            inline void Enable(void)
            {
                SetEnabled(true);
            }

            /**
            * \brief An inline for SetEnabled(false);
            */
            inline void Disable(void)
            {
                SetEnabled(false);
            }

            /**
            * \brief Returns this GameObject's parent.
            * \return A pointer to the parent GameObject.
            */
            GameObject* GetParent(void);

            /**
            * \brief Sets the parent of this GameObject.
            * \param parent The new GameObject parent pointer.
            */
            void SetParent(GameObject *parent);

            /**
            * \brief Returns a child GameObject located at the provided index.
            * \param index  The index of the particular GameObject to locate.
            * \return The pointer to the child GameObject, or a nullptr if it could not located.
            */
            GameObject* GetChildAtIndex(std::size_t index);

            /**
            * \brief Adds the provided GameObject as a child of this GameObject.
            * \param child  The GameObject to child.
            */
            void AddChild(GameObject *child);

            /**
            * \brief Attempts to remove the GameObject child at the provided index.
            * \param index  The index of the GameObject to remove.
            */
            void RemoveChildAtIndex(std::size_t index);

            /**
            * \brief Called when the gameobject is created to initialize all values.
            */
            void OnInit(void);

            /**
            * \brief Called once per frame while the gameobject is enabled
            *
            * Updates all components first, then all child gameobjects.
            */
            void Update(void);

            /**
            * \brief Called when the gameobject is destroyed/deleted.
            *
            * Objects are always disabled before destroyed.
            * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
            */
            void OnDestroy(void);

            /**
            * \brief Attempts to attach a Component of type T.
            * \param component  The new Component of type T to attach.
            * \tparam T A sub-class of Component.
            * \return bool indicating if the component could be attached.
            * \sa AddComponent(Args&&... args)
            *
            * If the component can be attached, its VOnInit and VOnEnabled will be invoked.
            */
            template <typename T>
            bool AddComponent(T *component);

            /**
            * \brief Attempts to attach a Component of type T.
            * \param args   The arguments to pass to the constructor for T.
            * \tparam T A sub-class of Component.
            * \tparam Args... The arguments to provide to T's constructor.
            * \return bool indicating if the Component could be attached.
            * \sa AddComponent(T *component)
            *
            * This method constructs the Component of type T using the provided args.
            * If the Component can be attached, its VOnInit and VOnEnabled will be invoked.
            */
            template <typename T, typename... Args>
            bool AddComponent(Args&&... args);

            /**
            * \brief Attempts to remove a Component of type T.
            * \tparam T A sub-class of Component.
            * \return bool indicating if the Component could be removed.
            *
            * This method will invoke the VOnDisabled and VOnDestroy methods of the Component before deleting it.
            */
            template <typename T>
            bool RemoveComponent(void);

            /**
            * \brief Test if a Component of type T is attached to this GameObject.
            * \tparam T A sub-class of Component.
            * \return true if there is a Component of type T attached.
            */
            template <typename T>
            bool HasComponent(void) const;

            /**
            * \brief Test if Components of types T1, T2, and Args... are attached to this GameObject.
            * \tparam T1 A sub-class of Component.
            * \tparam T2 A sub-class of Component.
            * \tparam Args... Sub-classes of Component.
            * \return true if all Components are present.
            */
            template <typename T1, typename T2, typename... Args>
            bool HasComponent(void) const;

            /**
            * \brief Return a Component of type T attached to this GameObject.
            * \tparam T A sub-class of Component.
            * \return Pointer to the Component, or nullptr if the Component was not present.
            * \sa GetComponents()
            */
            template <typename T>
            T* GetComponent(void);

            /**
            * \brief Returns Components of type Args... attached to this GameObject.
            * \tparam Args... Sub-classes of Component.
            * \return A std::tuple of Component pointers, or nullptr if a Component was not present.
            * \sa GetComponent()
            */
            template <typename... Args>
            std::tuple<Args*...> GetComponents(void);

            /**
            * \brief Enable a Component of type T attached to this GameObject.
            * \tparam T A sub-class of Component.
            * \return true if the Component was successfully enabled.
            * \sa EnableComponents()
            */
            template <typename T>
            bool EnableComponent(void);

            /**
            * \brief Enable Components of type Args... attached to this GameObject.
            * \tparam Args... Sub-classes of Component.
            * \return A std::tuple of bools indicating if a Component was successfully enabled.
            * \sa EnableComponent()
            */
            template <typename... Args>
            auto EnableComponents(void) -> decltype(std::make_tuple(EnableComponent<Args>()...))
            {
                return std::make_tuple(EnableComponent<Args>()...);
            }

            /**
            * \brief Disable a Component of type T attached to this GameObject.
            * \tparam T A sub-class of Component.
            * \return true if the Component was successfully disabled.
            * \sa DisableCompenents()
            */
            template <typename T>
            bool DisableComponent(void);

            /**
            * \brief Disable Components of type Args... attached to this GameObject.
            * \tparam Args... Sub-classes of Component.
            * \return A std::tuple of bools indicating if a Component was successfully disabled.
            */
            template <typename... Args>
            auto DisableComponents(void) -> decltype(std::make_tuple(DisableComponent<Args>()...))
            {
                return std::make_tuple(DisableComponent<Args>()...);
            }

        private:
            bool m_enabled; /**< bool indicating if this GameObject is enabled. */
            GameObject *m_parent; /**< The parent of this GameObject. */
            std::vector<GameObject*> m_children; /**< All the GameObjects which are children of this GameObject. */
            std::bitset<MAX_COMPONENTS> m_componentMask; /**< Bitmask indicating which Components are attached. */
            std::vector<Component*> m_components; /**< std::vector of all attached Components. */
            Transform m_transform;
			Guid guid;
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

            component->VOnInit();

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

            component->VOnInit();

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
            if(component->GetEnabled())
                component->Disable();
            component->VOnDestroy();

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
