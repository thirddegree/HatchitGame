#pragma once

#include <ht_component.h>
#include <ht_tween_value.h>
#include <stdint.h>
#include <vector>

namespace Hatchit {

    namespace Game {

        /**
         * \brief An enumeration of tweener play modes.
         */
        enum class TweenPlayMode : uint8_t
        {
            Once,
            Loop,
            PingPong
        };

        /**
        * \brief An enumeration of possible tween methods.
        */
        enum class TweenMethod : uint8_t
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

        /**
         * \brief Defines the base for tween-based components.
         */
        class HT_API TweenComponent : public Component
        {
        public:
            TweenComponent(GameObject* owner);

            virtual ~TweenComponent();

            float GetDuration() const;

            TweenMethod GetMethod() const;

            TweenPlayMode GetPlayMode() const;

            bool IsPlaying() const;

            void Play();

            void Play(float duration);

            void Play(float duration, TweenMethod method);

            void Play(float duration, TweenMethod method, TweenPlayMode mode);

            void SetDuration(float duration);

            void SetMethod(TweenMethod method);

            void SetPlayMode(TweenPlayMode mode);

            void Stop();

            /**
             * \brief Called when the GameObject is created to initialize all values
             */
            void VOnInit() override;

            /**
             * \brief Called once per frame while the GameObject is enabled.
             *
             * Updates all components first, then all child gameobjects.
             */
            void VOnUpdate() override;

            /**
             * \brief Called when the GameObject is destroyed/deleted.
             *
             * Objects are always disabled before destroyed.
             * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
             */
            void VOnDestroy() override;

        protected:
            /**
             * \brief The type for tween function pointers.
             *
             * \param start The start value.
             * \param end The end value.
             * \param time The current time in the tween.
             * \param duration The duration of the tween.
             * \return The resulting tween value.
             */
            typedef float(*TweenFunction)(float start, float end, float time, float duration);

            static std::vector<TweenFunction> s_tweenFunctions;

            TweenValue    m_targetValue;
            TweenValue    m_startValue;
            TweenValue    m_endValue;
            TweenFunction m_tweenFunction;
            TweenMethod   m_tweenMethod;
            TweenPlayMode m_tweenPlayMode;
            float         m_startTime;
            float         m_duration;
            bool          m_isPlaying;

            /**
             * \brief Creates the global list of tween functions.
             */
            static void CreateTweenFunctions();

            /**
             * \brief Checks to see if the start and end values are compatible.
             */
            bool AreValuesCompatible() const;

            /**
             * \brief Called when this tween component begins playing.
             */
            virtual void VOnPlay() = 0;

            /**
             * \brief Called when this tween component stops playing.
             *
             * \param interrupted True if the tween was interrupted, false if not.
             */
            virtual void VOnStop(bool interrupted) = 0;

            /**
             * \brief Called when the Component is enabled.
             *
             * This happens when a scene has finished loading, or immediately after creation if the scene is already loaded.
             */
            void VOnEnabled() override;

            /**
             * \brief Called when the Component is disabled.
             *
             * Components are always disabled before destroyed.
             * When a scene is destroyed, all Components are disabled before any are destroyed.
             */
            void VOnDisabled() override;
        };

    }

}
