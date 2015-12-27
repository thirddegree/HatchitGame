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

#include <ht_time_singleton.h>

#include <ht_sdltimer.h>

namespace Hatchit {

    namespace Game {

        Time::Time()
        {
            m_timer = new SDLTimer;
        }

        void Time::Start()
        {
            Time& _instance = Time::instance();

            _instance.m_timer->VStart();
        }

        void Time::Tick()
        {
            Time& _instance = Time::instance();

            _instance.m_timer->VTick();
        }

        void Time::CalculateFPS()
        {
            Time& _instance = Time::instance();

            _instance.m_timer->VCalculateFPS();
        }

        float Time::DeltaTime()
        {
            Time& _instance = Time::instance();

            return _instance.m_timer->VDeltaTime();
        }

        float Time::FramesPerSecond()
        {
            Time& _instance = Time::instance();

            return _instance.m_timer->VFramesPerSecond();
        }

        float Time::TotalTime()
        {
            Time& _instance = Time::instance();

            return _instance.m_timer->VTotalTime();
        }
    }

}