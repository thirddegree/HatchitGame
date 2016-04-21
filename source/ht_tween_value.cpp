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

#include <ht_tween_value.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Creates a new tween value.
         *
         * \param value The initial value.
         */
        TweenValue::TweenValue(float value)
        {
            SetValue(value);
        }

        /**
         * \brief Creates a new tween value.
         *
         * \param value The initial value.
         */
        TweenValue::TweenValue(const Math::Float2& value)
        {
            SetValue(value);
        }

        /**
         * \brief Creates a new tween value.
         *
         * \param value The initial value.
         */
        TweenValue::TweenValue(const Math::Float3& value)
        {
            SetValue(value);
        }

        /**
         * \brief Creates a new tween value.
         *
         * \param value The initial value.
         */
        TweenValue::TweenValue(const Math::Float4& value)
        {
            SetValue(value);
        }

        /**
         * \brief Gets this tween value as a single float.
         */
        float TweenValue::GetFloat() const
        {
            return m_values.x;
        }

        /**
         * \brief Gets this tween value as a single float2.
         */
        Math::Float2 TweenValue::GetFloat2() const
        {
            return Math::Float2(m_values.x, m_values.y);
        }

        /**
         * \brief Gets this tween value as a single float3.
         */
        Math::Float3 TweenValue::GetFloat3() const
        {
            return Math::Float3(m_values.x, m_values.y, m_values.z);
        }

        /**
         * \brief Gets this tween value as a single float4.
         */
        Math::Float4 TweenValue::GetFloat4() const
        {
            return m_values;
        }

        /**
         * \brief Gets this tween value's type.
         */
        TweenValueType TweenValue::GetType() const
        {
            return m_valueType;
        }

        /**
         * \brief Sets this tween value's underlying value.
         *
         * \param value The new value.
         */
        void TweenValue::SetValue(float value)
        {
            m_values = Math::Float4(value, 0, 0, 0);
            m_valueType = TweenValueType::Float;
        }

        /**
         * \brief Sets this tween value's underlying value.
         *
         * \param value The new value.
         */
        void TweenValue::SetValue(const Math::Float2& value)
        {
            m_values = Math::Float4(value.x, value.y, 0, 0);
            m_valueType = TweenValueType::Float2;
        }

        /**
         * \brief Sets this tween value's underlying value.
         *
         * \param value The new value.
         */
        void TweenValue::SetValue(const Math::Float3& value)
        {
            m_values = Math::Float4(value.x, value.y, value.z, 0);
            m_valueType = TweenValueType::Float3;
        }

        /**
         * \brief Sets this tween value's underlying value.
         *
         * \param value The new value.
         */
        void TweenValue::SetValue(const Math::Float4& value)
        {
            m_values = value;
            m_valueType = TweenValueType::Float4;
        }

        /**
         * \brief Checks to see if this tween value is equal to another.
         */
        bool TweenValue::operator==(const TweenValue& other) const
        {
            return m_valueType == other.m_valueType
                && m_values.x == other.m_values.x
                && m_values.y == other.m_values.y
                && m_values.z == other.m_values.z
                && m_values.w == other.m_values.w;
        }

        /**
         * \brief Checks to see if this tween value is equal to another.
         */
        bool TweenValue::operator!=(const TweenValue& other) const
        {
            return !(*this == other);
        }

    }

}
