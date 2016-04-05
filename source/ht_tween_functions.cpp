#include <ht_tween_component.h>

// Defines a tween function
#define DefineTweenFunction(name) \
    static float name##Tween(float start, float end, float time, float duration)

// Registers a tween function
#define RegisterTweenFunction(name) \
    s_tweenFunctions[static_cast<size_t>(TweenMethod::##name)] = name##Tween

// Registers a mixed tween function
#define RegisterMixedFunction(mixed, name1, name2) \
    s_tweenFunctions[static_cast<size_t>(TweenMethod::##mixed)] = \
    MixTweenFunctions<name1##Tween, name2##Tween>

namespace Hatchit {

    namespace Game {

        std::vector<TweenComponent::TweenFunction> TweenComponent::s_tweenFunctions;

        DefineTweenFunction(Linear)
        {
            return (end - start) * time / duration + start;
        }

        DefineTweenFunction(QuadraticEaseOut)
        {
            return (start - end) * (time /= duration) * (time - 2.0f) + start;
        }
        
        DefineTweenFunction(QuadraticEaseIn)
        {
            return (end - start) * (time /= duration) * time + start;
        }
        
        DefineTweenFunction(ExponentialEaseOut)
        {
            return (time == duration)
                 ? end
                 : (end - start) * (-powf(2.0f, -10.0f * time / duration) + 1.0f) + start;
        }
        
        DefineTweenFunction(ExponentialEaseIn)
        {
            return (time == 0.0f)
                 ? start
                 : (end - start) * powf(2.0f, 10.0f * (time / duration - 1)) + start;
        }
        
        DefineTweenFunction(CubicEaseOut)
        {
            return (end - start) * ((time = time / duration - 1.0f) * time * time + 1.0f) + start;
        }
        
        DefineTweenFunction(CubicEaseIn)
        {
            return (end - start) * (time /= duration) * time * time + start;
        }
        
        DefineTweenFunction(QuarticEaseOut)
        {
            return (start - end) * ((time = time / duration - 1.0f) * time * time * time - 1.0f) + start;
        }
        
        DefineTweenFunction(QuarticEaseIn)
        {
            return (end - start) * (time /= duration) * time * time * time + start;
        }
        
        DefineTweenFunction(QuinticEaseOut)
        {
            return (end - start) * ((time = time / duration - 1.0f) * time * time * time * time + 1.0f) + start;
        }
        
        DefineTweenFunction(QuinticEaseIn)
        {
            return (end - start) * (time /= duration) * time * time * time * time + start;
        }
        
        DefineTweenFunction(CircularEaseOut)
        {
            return (end - start) * sqrtf(1.0f - (time = time / duration - 1.0f) * time) + start;
        }
        
        DefineTweenFunction(CircularEaseIn)
        {
            return (start - end) * (sqrtf(1.0f - (time /= duration) * time) - 1.0f) + start;
        }
        
        DefineTweenFunction(SineEaseOut)
        {
            return (end - start) * sinf(time / duration * Math::HalfPi) + start;
        }
        
        DefineTweenFunction(SineEaseIn)
        {
            return (start - end) * cosf(time / duration * Math::HalfPi) + (end - start) + start;
        }
        
        DefineTweenFunction(ElasticEaseOut)
        {
            if ((time /= duration) == 1.0f)
            {
                return end;
            }

            float p = duration * 0.3f;
            float s = p * 0.25f;

            return (end - start)
                 * powf(2.0f, -10.0f * time)
                 * sinf((time * duration - s) * Math::TwoPi / p) + (end - start) + start;
        }
        
        DefineTweenFunction(ElasticEaseIn)
        {
            if ((time /= duration) == 1.0f)
            {
                return end;
            }

            float p = duration * 0.3f;
            float s = p * 0.25f;

            return -((end - start)
                 * powf(2.0f, 10.0f * (time -= 1.0f))
                 * sinf((time * duration - s) * Math::TwoPi / p)) + start;
        }
        
        DefineTweenFunction(BackEaseOut)
        {
            return (end - start) * ((time = time / duration - 1.0f) * time * (2.70158f * time + 1.70158f) + 1.0f) + start;
        }
        
        DefineTweenFunction(BackEaseIn)
        {
            return (end - start) * (time /= duration) * time * (2.70158f * time - 1.70158f) + start;
        }
        
        /**
         * \brief Mixes two tween functions.
         */
        template<TweenComponent::TweenFunction TFunc1, TweenComponent::TweenFunction TFunc2>
        static float MixTweenFunctions(float start, float end, float time, float duration)
        {
            if (time < duration * 0.5f)
            {
                return TFunc1(start,
                              start + (end - start) * 0.5f,
                              time * 2.0f,
                              duration);
            }
            else
            {
                return TFunc2(start + (end - start) * 0.5f,
                              end,
                              time * 2.0f - duration,
                              duration);
            }
        }

        /**
         * \brief Creates the global list of tween functions.
         */
        void TweenComponent::CreateTweenFunctions()
        {
            // Ensure we're not initializing the functions more than once
            if (s_tweenFunctions.size() > 0)
            {
                return;
            }

            s_tweenFunctions.resize(static_cast<size_t>(TweenMethod::TweenMethodCount));

            RegisterTweenFunction(Linear);
            RegisterTweenFunction(QuadraticEaseOut);
            RegisterTweenFunction(QuadraticEaseIn);
            RegisterMixedFunction(QuadraticEaseInOut, QuadraticEaseIn, QuadraticEaseOut);
            RegisterMixedFunction(QuadraticEaseOutIn, QuadraticEaseOut, QuadraticEaseIn);
            RegisterTweenFunction(ExponentialEaseOut);
            RegisterTweenFunction(ExponentialEaseIn);
            RegisterMixedFunction(ExponentialEaseInOut, ExponentialEaseIn, ExponentialEaseOut);
            RegisterMixedFunction(ExponentialEaseOutIn, ExponentialEaseOut, ExponentialEaseIn);
            RegisterTweenFunction(CubicEaseOut);
            RegisterTweenFunction(CubicEaseIn);
            RegisterMixedFunction(CubicEaseInOut, CubicEaseIn, CubicEaseOut);
            RegisterMixedFunction(CubicEaseOutIn, CubicEaseOut, CubicEaseIn);
            RegisterTweenFunction(QuarticEaseOut);
            RegisterTweenFunction(QuarticEaseIn);
            RegisterMixedFunction(QuarticEaseInOut, QuarticEaseIn, QuarticEaseOut);
            RegisterMixedFunction(QuarticEaseOutIn, QuarticEaseOut, QuarticEaseIn);
            RegisterTweenFunction(QuinticEaseOut);
            RegisterTweenFunction(QuinticEaseIn);
            RegisterMixedFunction(QuinticEaseInOut, QuinticEaseIn, QuinticEaseOut);
            RegisterMixedFunction(QuinticEaseOutIn, QuinticEaseOut, QuinticEaseIn);
            RegisterTweenFunction(CircularEaseOut);
            RegisterTweenFunction(CircularEaseIn);
            RegisterMixedFunction(CircularEaseInOut, CircularEaseIn, CircularEaseOut);
            RegisterMixedFunction(CircularEaseOutIn, CircularEaseOut, CircularEaseIn);
            RegisterTweenFunction(SineEaseOut);
            RegisterTweenFunction(SineEaseIn);
            RegisterMixedFunction(SineEaseInOut, SineEaseIn, SineEaseOut);
            RegisterMixedFunction(SineEaseOutIn, SineEaseOut, SineEaseIn);
            RegisterTweenFunction(ElasticEaseOut);
            RegisterTweenFunction(ElasticEaseIn);
            RegisterMixedFunction(ElasticEaseInOut, ElasticEaseIn, ElasticEaseOut);
            RegisterMixedFunction(ElasticEaseOutIn, ElasticEaseOut, ElasticEaseIn);
            RegisterTweenFunction(BackEaseOut);
            RegisterTweenFunction(BackEaseIn);
            RegisterMixedFunction(BackEaseInOut, BackEaseIn, BackEaseOut);
            RegisterMixedFunction(BackEaseOutIn, BackEaseOut, BackEaseIn);
        }

    }

}
