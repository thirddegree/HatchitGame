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

#include <ht_platform.h>

namespace Hatchit {

    namespace Game {

        class HT_API Component
        {
        public:
            /**
            * \brief Returns the unique id associated with a Component of type T.
            * \tparam T A sub-class of Component.
            * \return A std::uint32_t which is this Component's unique ID.
            */
            template <typename T>
            static std::uint32_t GetComponentId(void);

            static std::uint32_t s_componentIdCounter; /**< A static counter that is incremented once with each instantiation of GetComponentID(). */

            virtual ~Component(void) = default;

            /**
            * \brief Getter that returns that value of m_enabled.
            * \return true if this Component is enabled.
            */
            bool GetEnabled(void) const;

            /**
            * \brief Setter that sets the value of m_enabled.
            * \param value  The new value of m_enabled.
            */
            void SetEnabled(bool value);

            /**
            * \brief inline for SetEnabled(true);
            */
            inline void Enable(void)
            {
                SetEnabled(true);
            }

            /**
            * \brief inline for SetEnabled(false);
            */
            inline void Disable(void)
            {
                SetEnabled(false);
            }

            /**
            * \brief Called when the GameObject is created to initialize all values
            */
            virtual void VOnInit() = 0;

            /**
            * \brief Called once per frame while the GameObject is enabled.
            * Updates all components first, then all child gameobjects.
            */
            virtual void VOnUpdate() = 0;

            /**
            * \brief Called when the GameObject is destroyed/deleted.
            * Objects are always disabled before destroyed.
            * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
            */
            virtual void VOnDestroy() = 0;

        protected:
            /**
            * \brief Called when the Component is enabled.
            * This happens when a scene has finished loading, or immediately after creation if the scene is already loaded.
            */
            virtual void VOnEnabled() = 0;

            /**
            * \brief Called when the Component is disabled.
            * Components are always disabled before destroyed.
            * When a scene is destroyed, all Components are disabled before any are destroyed.
            */
            virtual void VOnDisabled() = 0;

            bool m_enabled{false}; /**< bool indicating if this Component is enabled. */
        };

        template <typename T>
        std::uint32_t Component::GetComponentId(void)
        {
            static_assert(std::is_base_of<Component, T>::value, "Must be a sub-class of Hatchit::Game::Component!");
            static std::uint32_t id = s_componentIdCounter++; /**< This value is set once when the template is instantiated. */
            return id;
        }
    }
}
