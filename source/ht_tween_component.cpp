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

#include <ht_tween_component.h>
#include <ht_time_singleton.h>
#include <ht_debug.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Creates a new tween component.
         */
        TweenComponent::TweenComponent()
            : m_targetValue(0.0f)
            , m_startValue(0.0f)
            , m_endValue(0.0f)
            , m_tweenFunction(nullptr)
            , m_tweenMethod(TweenMethod::Linear)
            , m_tweenPlayMode(TweenPlayMode::Once)
            , m_startTime(0.0f)
            , m_duration(0.0f)
            , m_isPlaying(false)
        {
            CreateTweenFunctions();
            SetMethod(TweenMethod::Linear);
        }

        /**
         * \brief Destroys this tween component.
         */
        TweenComponent::~TweenComponent()
        {
            m_tweenFunction = nullptr;
            m_startTime     = 0.0f;
            m_duration      = 0.0f;
            m_isPlaying     = 0;
        }

        /**
         * \brief Checks to see if the start and end values are compatible.
         */
        bool TweenComponent::AreValuesCompatible() const
        {
            return m_startValue.GetType() == m_endValue.GetType();
        }

        /**
         * \brief Begins playing the tween by assuming all parameters are set.
         *
         * \return True if the tween has begun, false if there was an error.
         */
        bool TweenComponent::BeginPlay()
        {
            m_startTime = Time::instance().TotalTime();
            m_isPlaying = AreValuesCompatible();

            SetEnabled(m_isPlaying);

#if defined(_DEBUG) || defined(DEBUG)
            HT_DEBUG_PRINTF("[TweenComponent] Start value and end value are of incompatible types\n");
#endif

            return m_isPlaying;
        }

        /**
         * \brief Gets the duration of the tween.
         */
        float TweenComponent::GetDuration() const
        {
            return m_duration;
        }

        /**
         * \brief Gets the tween method.
         */
        TweenMethod TweenComponent::GetMethod() const
        {
            return m_tweenMethod;
        }

        /**
         * \brief Gets the tween play mode.
         */
        TweenPlayMode TweenComponent::GetPlayMode() const
        {
            return m_tweenPlayMode;
        }

        /**
         * \brief Checks to see if this tween is playing.
         */
        bool TweenComponent::IsPlaying() const
        {
            return m_isPlaying;
        }

        /**
         * \brief Called when this tween component stops playing.
         *
         * \param interrupted True if the tween was interrupted, false if not.
         */
        void TweenComponent::OnStop(bool interrupted)
        {
            if (interrupted)
            {
                m_isPlaying = false;
                return;
            }

            switch (m_tweenPlayMode)
            {
                case TweenPlayMode::Loop:
                {
                    Play();
                }
                break;

                case TweenPlayMode::PingPong:
                {
                    // Swap the start and end values
                    TweenValue end = m_endValue;
                    m_endValue = m_startValue;
                    m_startValue = end;

                    // Begin again
                    this->Play();
                }
                break;

                case TweenPlayMode::Once:
                default:
                {
                    SetEnabled(false);
                }
                break;
            }
        }

        /**
         * \brief Plays the tween.
         *
         * \return True if the tween has begun, false if there was an error.
         */
        bool TweenComponent::Play()
        {
            return BeginPlay();
        }

        /**
         * \brief Plays the tween.
         *
         * \param duration The duration of the tween.
         * \return True if the tween has begun, false if there was an error.
         */
        bool TweenComponent::Play(float duration)
        {
            SetDuration(duration);
            return BeginPlay();
        }

        /**
         * \brief Plays the tween.
         *
         * \param duration The duration of the tween.
         * \param method The tween method.
         * \return True if the tween has begun, false if there was an error.
         */
        bool TweenComponent::Play(float duration, TweenMethod method)
        {
            SetDuration(duration);
            SetMethod(method);
            return BeginPlay();
        }

        /**
         * \brief Plays the tween.
         *
         * \param duration The duration of the tween.
         * \param method The tween method.
         * \param mode The play mode.
         * \return True if the tween has begun, false if there was an error.
         */
        bool TweenComponent::Play(float duration, TweenMethod method, TweenPlayMode mode)
        {
            SetDuration(duration);
            SetMethod(method);
            SetPlayMode(mode);
            return BeginPlay();
        }

        /**
         * \brief Sets the tween's duration.
         *
         * \param duration The new duration.
         */
        void TweenComponent::SetDuration(float duration)
        {
            m_duration = duration;
        }

        /**
         * \brief Sets the tween method.
         *
         * \param method The new method.
         */
        void TweenComponent::SetMethod(TweenMethod method)
        {
            m_tweenMethod = method;
            m_tweenFunction = s_tweenFunctions[static_cast<size_t>(method)];
        }

        /**
         * \brief Sets the play mode.
         *
         * \param method The new play mode.
         */
        void TweenComponent::SetPlayMode(TweenPlayMode mode)
        {
            m_tweenPlayMode = mode;
        }

        /**
         * \brief Stops the tween.
         */
        void TweenComponent::Stop()
        {
            float currentTime = Time::instance().TotalTime();
            
            OnStop(currentTime - m_startTime < m_duration);
        }

        /**
         * \brief Called when the Component is enabled.
         *
         * This happens when a scene has finished loading, or immediately after creation if the scene is already loaded.
         */
        void TweenComponent::VOnEnabled()
        {
            if (!m_isPlaying)
            {
                SetEnabled(false);
            }
        }

        /**
         * \brief Called when the Component is disabled.
         *
         * Components are always disabled before destroyed.
         * When a scene is destroyed, all Components are disabled before any are destroyed.
         */
        void TweenComponent::VOnDisabled()
        {
        }

        /**
         * \brief Called when the GameObject is created to initialize all values
         */
        void TweenComponent::VOnInit()
        {
            // TODO - Is there anything we need to do here?
        }

        /**
         * \brief Called once per frame while the GameObject is enabled.
         *
         * Updates all components first, then all child gameobjects.
         */
        void TweenComponent::VOnUpdate()
        {
            // Get the time, and make sure it doesn't go higher than the duration
            float time = Time::instance().TotalTime() - m_startTime;
            if (time >= m_duration)
            {
                time = m_duration;
                OnStop(false);
            }

            switch (m_targetValue.GetType())
            {
                case TweenValueType::Float:
                {
                    float src = m_startValue.GetFloat();
                    float dst = m_endValue.GetFloat();

                    float value = m_tweenFunction(src, dst, time, m_duration);
                    m_targetValue.SetValue(value);
                }
                break;

                case TweenValueType::Float2:
                {
                    Math::Float2 src = m_startValue.GetFloat2();
                    Math::Float2 dst = m_endValue.GetFloat2();

                    Math::Float2 value;
                    value.x = m_tweenFunction(src.x, dst.x, time, m_duration);
                    value.y = m_tweenFunction(src.y, dst.y, time, m_duration);

                    m_targetValue.SetValue(value);
                }
                break;

                case TweenValueType::Float3:
                {
                    Math::Float3 src = m_startValue.GetFloat3();
                    Math::Float3 dst = m_endValue.GetFloat3();

                    Math::Float3 value;
                    value.x = m_tweenFunction(src.x, dst.x, time, m_duration);
                    value.y = m_tweenFunction(src.y, dst.y, time, m_duration);
                    value.z = m_tweenFunction(src.z, dst.z, time, m_duration);

                    m_targetValue.SetValue(value);
                }
                break;

                case TweenValueType::Float4:
                {
                    Math::Float4 src = m_startValue.GetFloat4();
                    Math::Float4 dst = m_endValue.GetFloat4();

                    Math::Float4 value;
                    value.x = m_tweenFunction(src.x, dst.x, time, m_duration);
                    value.y = m_tweenFunction(src.y, dst.y, time, m_duration);
                    value.z = m_tweenFunction(src.z, dst.z, time, m_duration);
                    value.w = m_tweenFunction(src.w, dst.w, time, m_duration);

                    m_targetValue.SetValue(value);
                }
                break;
            }

        }

        /**
         * \brief Called when the GameObject is destroyed/deleted.
         *
         * Objects are always disabled before destroyed.
         * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
         */
        void TweenComponent::VOnDestroy()
        {
            Stop();
        }

    }

}
