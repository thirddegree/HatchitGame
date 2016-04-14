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

#include <ht_tween_rotation.h>
#include <ht_gameobject.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Creates a new tween rotation component.
         */
        TweenRotation::TweenRotation()
        {
            Math::Float3 empty = {0, 0, 0};

            SetStartRotation(empty);
            SetEndRotation(empty);
        }

        /**
         * \brief Destroys this tween rotation component.
         */
        TweenRotation::~TweenRotation()
        {
        }

        /**
         * \brief Gets the start tween rotation.
         */
        Math::Float3 TweenRotation::GetStartRotation() const
        {
            return m_startValue.GetFloat3();
        }

        /**
         * \brief Gets the end tween rotation.
         */
        Math::Float3 TweenRotation::GetEndRotation() const
        {
            return m_endValue.GetFloat3();
        }

        /**
         * \brief Sets the start tween rotation.
         *
         * \param value The new start rotation.
         */
        void TweenRotation::SetStartRotation(const Math::Float3& value)
        {
            m_startValue.SetValue(value);
        }

        /**
         * \brief Sets the end tween rotation.
         *
         * \param value The new end rotation.
         */
        void TweenRotation::SetEndRotation(const Math::Float3& value)
        {
            m_endValue.SetValue(value);
        }

        /**
         * \brief Called once per frame while the GameObject is enabled.
         *
         * Updates all components first, then all child gameobjects.
         */
        void TweenRotation::VOnUpdate()
        {
            TweenComponent::VOnUpdate();

            Math::Float3 target = m_targetValue.GetFloat3();
            Math::Vector3 rotation(target.m_data);
            m_owner->GetTransform().SetRotation(rotation);
        }

    }

}
