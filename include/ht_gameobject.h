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
#include <unordered_map>
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
        class Scene;
        class HT_API GameObject
        {
        friend class Scene;
        public:
            GameObject(const GameObject& rhs) = default;
            GameObject(GameObject&& rhs) = default;
            GameObject& operator=(const GameObject& rhs) = default;
            GameObject& operator=(GameObject&& rhs) = default;


            /**
            * \brief The destructor for GameObject.
            *
            * Responsible for deleting all currently attached components.
            */
            ~GameObject(void);

            /**
            * \brief Retrieve this GameObject's Guid.
            */
            const Core::Guid& GetGuid(void) const;

            /**
            * \brief Retrieve this GameObject's name.
            */
            const std::string& GetName(void) const;

            /**
            * \brief Retrieve this GameObject's Transform.
            */
            Transform& GetTransform(void);

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
            * \brief Attempts to remove provided GameObject from this GameObject.
            * \param child  The GameObject to remove.
            */
            void RemoveChild(GameObject *child);

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
            * \brief Destroys the GameObject.
            *
            * Objects are always disabled before destroyed.
            * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
            */
            void Destroy(void);

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
            *
            * \param guid       The Guid for this GameObject.
            * \param name       The name of this GameObject.
            * \param t          The Transform for this GameObject.
            * \param enabled    Whether or not this GameObject is enabled
            * \sa Guid(), Transform()
            */
            GameObject::GameObject(const Core::Guid& guid, const std::string& name, Transform& t, bool enabled);

            /**
            * \brief Called when the gameobject is enabled.
            */
            void OnEnabled(void);

            /**
            * \brief Called when the gameobject is disabled.
            */
            void OnDisabled(void);

            /**
            * \brief Called when the gameobject is destroyed/deleted.
            *
            * Objects are always disabled before destroyed.
            * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
            */
            void OnDestroy(void);

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
            bool AddUninitializedComponent(Args&&... args);

            bool m_enabled; /**< bool indicating if this GameObject is enabled. */
            std::string m_name; /**< The name associated with this GameObject. */
            Core::Guid m_guid; /**< The Guid associated with this GameObject. */
            Transform m_transform; /**< The Transform representing the position/orientation of this GameObject. */
            GameObject *m_parent; /**< The parent of this GameObject. */
            std::vector<GameObject*> m_children; /**< All the GameObjects which are children of this GameObject. */
            std::vector<Component*> m_components; /**< std::vector of all attached Components. */
            std::unordered_map<Core::Guid, std::vector<Component*>::size_type> m_componentMap; /**< Unique mapping of Component to Guid. */
        };

        template <typename T>
        bool GameObject::AddComponent(T *component)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            Guid component_id = Component::GetComponentId<T>();
            std::unordered_map<Guid, std::vector<Component*>::size_type>::const_iterator iter = m_componentMap.find(component_id);
            if (iter != m_componentMap.cend())
                return false;

            m_componentMap.insert(std::make_pair(component_id, m_components.size()));
            m_components.push_back(component);

            component->SetOwner(this);

            component->VOnInit();

            component->Enable();

            return true;
        }

        template <typename T, typename... Args>
        bool GameObject::AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            Guid component_id = Component::GetComponentId<T>();
            std::unordered_map<Guid, std::vector<Component*>::size_type>::const_iterator iter = m_componentMap.find(component_id);
            if (iter != m_componentMap.cend())
                return false;

            T *component = new T(std::forward<Args>(args)...);
            m_componentMap.insert(std::make_pair(component_id, m_components.size()));
            m_components.push_back(component);

            component->SetOwner(this);

            component->VOnInit();

            if (m_enabled)
                component->Enable();

            return true;
        }

        template <typename T>
        bool GameObject::RemoveComponent(void)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            Guid component_id = Component::GetComponentId<T>();
            std::unordered_map<Guid, std::vector<Component*>::size_type>::const_iterator iter = m_componentMap.find(component_id);
            if (iter == m_componentMap.cend())
                return false;

            std::vector<Component*>::size_type index = m_componentMap[component_id];
            Component *component = m_components[index];
            if(component->GetEnabled())
                component->Disable();
            component->VOnDestroy();

            m_components[index] = nullptr;
            m_componentMap.erase(component_id);
            delete component;

            return true;
        }

        template <typename T>
        bool GameObject::HasComponent(void) const
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");
            Guid component_id = Component::GetComponentId<T>();
            return (m_componentMap.find(component_id) != m_componentMap.cend());
        }

        template <typename T1, typename T2, typename... Args>
        bool GameObject::HasComponent(void) const
        {
            static_assert(std::is_base_of<Component, T1>::value, "Must be a sub-class of Hatchit::Game::Component!");
            return HasComponent<T1>() && HasComponent<T2, Args...>();
        }

        template <typename T>
        T* GameObject::GetComponent(void)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            Guid component_id = Component::GetComponentId<T>();
            std::unordered_map<Guid, std::vector<Component*>::size_type>::const_iterator iter = m_componentMap.find(component_id);
            if (iter == m_componentMap.cend())
                return nullptr;

            std::vector<Component*>::size_type index = m_componentMap[component_id];
            return dynamic_cast<T*>(m_components[index]);
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

            Guid component_id = Component::GetComponentId<T>();
            std::vector<Component*>::size_type index = m_componentMap[component_id];
            Component *component = m_components[index];
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

            Guid component_id = Component::GetComponentId<T>();
            std::vector<Component*>::size_type index = m_componentMap[component_id];
            Component *component = m_components[index];
            if (!component->GetEnabled())
                return false;

            component->Disable();

            return true;
        }

        template<typename T, typename ...Args>
        inline bool Hatchit::Game::GameObject::AddUninitializedComponent(Args && ...args)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");

            Guid component_id = Component::GetComponentId<T>();
            std::unordered_map<Guid, std::vector<Component*>::size_type>::const_iterator iter = m_componentMap.find(component_id);
            if (iter != m_componentMap.cend())
                return false;

            T *component = new T(std::forward<Args>(args)...);
            m_componentMap.insert(std::make_pair(component_id, m_components.size()));
            m_components.push_back(component);

            component->SetOwner(this);

            return true;
        }
    }
}
