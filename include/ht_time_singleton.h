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

#include <ht_platform.h>
#include <ht_singleton.h>
#include <ht_timer.h>

namespace Hatchit {

    namespace Game {

        class HT_API Time : public Core::Singleton<Time>
        {
        public:
            Time();

            static void Start();

            static void Tick();

            static void CalculateFPS();

            static float DeltaTime();

            static float FramesPerSecond();

            static float FrameTime();

            static float TotalTime();

            static float PausedTime();

        private:
            Core::Timer* m_timer;
            float        m_fps;
            float        m_mspf;
        };

    }

}