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

#include <ht_tween_scale.h>
#include <ht_gameobject.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Creates a new tween scale component.
         */
        TweenScale::TweenScale()
        {
            Math::Float3 empty = {0, 0, 0};

            SetStartScale(empty);
            SetEndScale(empty);
        }

        /**
         * \brief Destroys this tween scale component.
         */
        TweenScale::~TweenScale()
        {
        }

        JSON TweenScale::VSerialize(void)
        {
            return Core::JSON();
        }

        bool TweenScale::VDeserialize(const JSON& jsonObject)
        {
            return false;
        }

        /**
         * \brief Gets the start tween scale.
         */
        Math::Float3 TweenScale::GetStartScale() const
        {
            return m_startValue.GetFloat3();
        }

        /**
         * \brief Gets the end tween scale.
         */
        Math::Float3 TweenScale::GetEndScale() const
        {
            return m_endValue.GetFloat3();
        }

        /**
         * \brief Sets the start tween scale.
         *
         * \param value The new start scale.
         */
        void TweenScale::SetStartScale(const Math::Float3& value)
        {
            m_startValue.SetValue(value);
        }

        /**
         * \brief Sets the end tween scale.
         *
         * \param value The new end scale.
         */
        void TweenScale::SetEndScale(const Math::Float3& value)
        {
            m_endValue.SetValue(value);
        }

        /**
         * \brief Called once per frame while the GameObject is enabled.
         *
         * Updates all components first, then all child gameobjects.
         */
        void TweenScale::VOnUpdate()
        {
            TweenComponent::VOnUpdate();

            Math::Float3 target = m_targetValue.GetFloat3();
            Math::Vector3 scale(target.m_data);
            m_owner->GetTransform().SetScale(scale);
        }

        /**
        * \brief Creates a copy of this Component.
        */
        Component* TweenScale::VClone(void) const
        {
            return new TweenScale(*this);
        }

    }

}
