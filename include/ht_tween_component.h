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

            /**
             * \brief Creates a new tween component.
             */
            TweenComponent();

            /**
             * \brief Destroys this tween component.
             */
            virtual ~TweenComponent();

            /**
             * \brief Gets the duration of the tween.
             */
            float GetDuration() const;

            /**
             * \brief Gets the tween method.
             */
            TweenMethod GetMethod() const;

            /**
             * \brief Gets the tween play mode.
             */
            TweenPlayMode GetPlayMode() const;

            /**
             * \brief Checks to see if this tween is playing.
             */
            bool IsPlaying() const;

            /**
             * \brief Plays the tween.
             *
             * \return True if the tween has begun, false if there was an error.
             */
            bool Play();

            /**
             * \brief Plays the tween.
             *
             * \param duration The duration of the tween.
             * \return True if the tween has begun, false if there was an error.
             */
            bool Play(float duration);

            /**
             * \brief Plays the tween.
             *
             * \param duration The duration of the tween.
             * \param method The tween method.
             * \return True if the tween has begun, false if there was an error.
             */
            bool Play(float duration, TweenMethod method);

            /**
             * \brief Plays the tween.
             *
             * \param duration The duration of the tween.
             * \param method The tween method.
             * \param mode The play mode.
             * \return True if the tween has begun, false if there was an error.
             */
            bool Play(float duration, TweenMethod method, TweenPlayMode mode);

            /**
             * \brief Sets the tween's duration.
             *
             * \param duration The new duration.
             */
            void SetDuration(float duration);

            /**
             * \brief Sets the tween method.
             *
             * \param method The new method.
             */
            void SetMethod(TweenMethod method);

            /**
             * \brief Sets the play mode.
             *
             * \param method The new play mode.
             */
            void SetPlayMode(TweenPlayMode mode);

            /**
             * \brief Stops the tween.
             */
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
            virtual void VOnUpdate() override;

            /**
             * \brief Called when the GameObject is destroyed/deleted.
             *
             * Objects are always disabled before destroyed.
             * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
             */
            void VOnDestroy() override;

            /**
            * \brief Creates a copy of this Component.
            */
            Component* VClone(void) const override;

        protected:
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

        private:
            /**
             * \brief Begins playing the tween by assuming all parameters are set.
             *
             * \return True if the tween has begun, false if there was an error.
             */
            bool BeginPlay();

            /**
             * \brief Called when this tween component stops playing.
             *
             * \param interrupted True if the tween was interrupted, false if not.
             */
            void OnStop(bool interrupted);
        };

    }

}
