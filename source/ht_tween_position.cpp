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

#include <ht_tween_position.h>
#include <ht_gameobject.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Creates a new tween position component.
         */
        TweenPosition::TweenPosition()
        {
            Math::Float3 empty = {0, 0, 0};

            SetStartPosition(empty);
            SetEndPosition(empty);
        }

        /**
         * \brief Destroys this tween position component.
         */
        TweenPosition::~TweenPosition()
        {
        }

        /**
         * \brief Gets the start tween position.
         */
        Math::Float3 TweenPosition::GetStartPosition() const
        {
            return m_startValue.GetFloat3();
        }

        /**
         * \brief Gets the end tween position.
         */
        Math::Float3 TweenPosition::GetEndPosition() const
        {
            return m_endValue.GetFloat3();
        }

        /**
         * \brief Sets the start tween position.
         *
         * \param value The new start position.
         */
        void TweenPosition::SetStartPosition(const Math::Float3& value)
        {
            m_startValue.SetValue(value);
        }

        /**
         * \brief Sets the end tween position.
         *
         * \param value The new end position.
         */
        void TweenPosition::SetEndPosition(const Math::Float3& value)
        {
            m_endValue.SetValue(value);
        }

        /**
         * \brief Called once per frame while the GameObject is enabled.
         *
         * Updates all components first, then all child gameobjects.
         */
        void TweenPosition::VOnUpdate()
        {
            TweenComponent::VOnUpdate();

            Math::Float3 target = m_targetValue.GetFloat3();
            Math::Vector3 position(target.m_data);
            m_owner->GetTransform().SetPosition(position);
        }

        /**
        * \brief Creates a copy of this Component.
        */
        Component* TweenPosition::VClone(void) const
        {
            return new TweenPosition(*this);
        }

    }

}
