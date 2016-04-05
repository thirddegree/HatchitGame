#pragma once

namespace Hatchit {
    namespace Game {

        /**
         * \brief An enumeration of possible tween methods.
         */
        enum class TweenMethod
        {
            Linear,
            QuadraticEaseOut,
            QuadraticEaseIn,
            QuadraticEaseInOut,
            QuadraticEaseOutIn,
            ExponentialEaseOut,
            ExponentialEaseIn,
            ExponentialEaseInOut,
            ExponentialEaseOutIn,
            CubicEaseOut,
            CubicEaseIn,
            CubicEaseInOut,
            CubicEaseOutIn,
            QuarticEaseOut,
            QuarticEaseIn,
            QuarticEaseInOut,
            QuarticEaseOutIn,
            QuinticEaseOut,
            QuinticEaseIn,
            QuinticEaseInOut,
            QuinticEaseOutIn,
            CircularEaseOut,
            CircularEaseIn,
            CircularEaseInOut,
            CircularEaseOutIn,
            SineEaseOut,
            SineEaseIn,
            SineEaseInOut,
            SineEaseOutIn,
            ElasticEaseOut,
            ElasticEaseIn,
            ElasticEaseInOut,
            ElasticEaseOutIn,
            /*
            BounceEaseOut,
            BounceEaseIn,
            BounceEaseInOut,
            BounceEaseOutIn,
            */
            BackEaseOut,
            BackEaseIn,
            BackEaseInOut,
            BackEaseOutIn,

            TweenMethodCount
        };

    }
}
