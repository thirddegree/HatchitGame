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

#include <ht_time_singleton.h>

namespace Hatchit {

    namespace Game {

        Time::Time()
        {
            m_timer = new Core::Timer;
            m_fps = 0.0f;
            m_mspf = 0.0f;
        }

        void Time::Start()
        {
            Time& _instance = Time::instance();

            _instance.m_timer->Reset();
            _instance.m_timer->Start();
        }

        void Time::Tick()
        {
            Time& _instance = Time::instance();

            _instance.m_timer->Tick();
        }

        void Time::CalculateFPS()
        {
            Time& _instance = Time::instance();

            static int frameCnt = 0;
            static float timeElapsed = 0.0f;

            frameCnt++;

            // Compute averages over one second period.
            if ((_instance.TotalTime() - timeElapsed) >= 1.0f)
            {
                _instance.m_fps = static_cast<float>(frameCnt);
                _instance.m_mspf = 1000.0f / _instance.m_fps;

                // Reset for next average.
                frameCnt = 0;
                timeElapsed += 1.0f;
            }
        }

        float Time::DeltaTime()
        {
            Time& _instance = Time::instance();

            return _instance.m_timer->DeltaTime();
        }

        float Time::FramesPerSecond()
        {
            Time& _instance = Time::instance();

            return _instance.m_fps;
        }

        float Time::FrameTime()
        {
            Time& _instance = Time::instance();

            return _instance.m_mspf;
        }

        float Time::TotalTime()
        {
            Time& _instance = Time::instance();

            return _instance.m_timer->TotalTime();
        }
    }

}