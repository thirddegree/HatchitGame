/**
 **    Hatchit Engine
 **    Copyright(c) 2015-2016 Third-Degree
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

#include <ht_math.h>
#include <ht_platform.h>

namespace Hatchit {

    namespace Game {
        
        /**
         * \brief An enumeration of possible tween value types.
         */
        enum class TweenValueType
        {
            Float,
            Float2,
            Float3,
            Float4
        };

        /**
         * \brief Defines a tween value.
         */
        class HT_API TweenValue
        {
        public:
            /**
             * \brief Creates a new tween value.
             *
             * \param value The initial value.
             */
            TweenValue(float value);

            /**
             * \brief Creates a new tween value.
             *
             * \param value The initial value.
             */
            TweenValue(const Math::Float2& value);

            /**
             * \brief Creates a new tween value.
             *
             * \param value The initial value.
             */
            TweenValue(const Math::Float3& value);

            /**
             * \brief Creates a new tween value.
             *
             * \param value The initial value.
             */
            TweenValue(const Math::Float4& value);

            /**
             * \brief Gets this tween value as a single float.
             */
            float GetFloat() const;

            /**
             * \brief Gets this tween value as a single float2.
             */
            Math::Float2 GetFloat2() const;

            /**
             * \brief Gets this tween value as a single float3.
             */
            Math::Float3 GetFloat3() const;

            /**
             * \brief Gets this tween value as a single float4.
             */
            Math::Float4 GetFloat4() const;

            /**
             * \brief Gets this tween value's type.
             */
            TweenValueType GetType() const;

            /**
             * \brief Sets this tween value's underlying value.
             *
             * \param value The new value.
             */
            void SetValue(float value);
            
            /**
             * \brief Sets this tween value's underlying value.
             *
             * \param value The new value.
             */
            void SetValue(const Math::Float2& value);
            
            /**
             * \brief Sets this tween value's underlying value.
             *
             * \param value The new value.
             */
            void SetValue(const Math::Float3& value);

            /**
             * \brief Sets this tween value's underlying value.
             *
             * \param value The new value.
             */
            void SetValue(const Math::Float4& value);

            /**
             * \brief Checks to see if this tween value is equal to another.
             */
            bool operator==(const TweenValue& other) const;

            /**
             * \brief Checks to see if this tween value is equal to another.
             */
            bool operator!=(const TweenValue& other) const;

        private:
            Math::Float4 m_values;
            TweenValueType m_valueType;
        };

    }
}
