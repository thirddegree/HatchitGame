#pragma once

#include <ht_math.h>

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
        class TweenValue
        {
            Math::Float4 m_values;
            TweenValueType m_valueType;

        public:

        };

    }
}
