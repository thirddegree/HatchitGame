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
* \class Component
* \ingroup HatchitGame
*
* \brief The base Component class which all Components should derive from.
*
* Components are attached to/removed from GameObjects.
* Components are updated during the GameObject's update.
*/

#pragma once

#include <cstdint>
#include <type_traits>
#include <ht_transform.h>
#include <ht_guid.h>
#include <ht_jsonhelper.h>


namespace Hatchit {

    namespace Game {

        class GameObject;

        using JSON = Core::JSON;

        class HT_API Component
        {
        public:
            /**
            * \brief Returns the unique id associated with a Component of type T.
            * \tparam T A sub-class of Component.
            * \return A Guid which is this Component's unique ID.
            */
            template <typename T>
            static Core::Guid GetComponentId(void);

            Component(void) = default;
            virtual ~Component(void) = default;
            Component(const Component& rhs) = default;
            Component(Component&& rhs) = default;
            Component& operator=(const Component& rhs) = default;
            Component& operator=(Component&& rhs) = default;

            virtual Core::JSON VSerialize(void) = 0;
            virtual bool VDeserialize(const Core::JSON& jsonObject) = 0;


            /**
            * \brief Getter which returns the GameObject to which this Component is attached.
            * \return Pointer to the GameObject.
            */
            GameObject* GetOwner(void);

            /**
            * \brief Getter that returns that value of m_enabled.
            * \return true if this Component is enabled.
            */
            bool GetEnabled(void);

            /**
            * \brief Setter that sets the value of m_enabled.
            * \param value  The new value of m_enabled.
            */
            void SetEnabled(bool value);


            /**
            * \brief Called when the GameObject is created to initialize all values
            */
            virtual void VOnInit(void) = 0;

            /**
            * \brief Called once per frame while the GameObject is enabled.
            * Updates all components first, then all child gameobjects.
            */
            virtual void VOnUpdate(void) = 0;


            /**
            * \brief Called when the GameObject is destroyed/deleted.
            * Objects are always disabled before destroyed.
            * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
            */
            virtual void VOnDestroy(void) = 0;

            /**
            * \brief Creates a copy of this Component.
            * This is used by GameObject to create a copy of a class extending Component without knowledge of its underlying type.
            */
            virtual Component* VClone(void) const = 0;

            /**
            * \brief Setter that sets which GameObject this Component is attached to.
            * \param owner  The GameObject to which this Component is attached.
            */
            void SetOwner(GameObject *owner);

        protected:
            /**
            * \brief Called when the Component is enabled.
            * This happens when a scene has finished loading, or immediately after creation if the scene is already loaded.
            */
            virtual void VOnEnabled(void) = 0;

            /**
            * \brief Called when the Component is disabled.
            * Components are always disabled before destroyed.
            * When a scene is destroyed, all Components are disabled before any are destroyed.
            */
            virtual void VOnDisabled(void) = 0;

            bool m_enabled{true}; /**< bool indicating if this Component is enabled. */
            GameObject *m_owner; /**< The GameObject to which this Component is attached. */
        };

        template <typename T>
        Core::Guid Component::GetComponentId(void)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");
            static Core::Guid id = Core::Guid(); /**< This value is set once when the template is instantiated. */
            return id;
        }
    }
}
