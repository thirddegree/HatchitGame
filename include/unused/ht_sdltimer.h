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
#include <ht_timer.h>
#include <ht_types.h>

namespace Hatchit {

    namespace Game {

        class HT_API SDLTimer : public ITimer
        {
        public:
            SDLTimer();

            ~SDLTimer();

            void    VStart()           override;
            void    VTick()            override;
            void    VCalculateFPS()    override;
            
            float   VDeltaTime()       override;
            float   VFramesPerSecond() override;
            float   VTotalTime()       override;

        private:
            uint32_t m_startTime;
            uint32_t m_currentTime;
            uint32_t m_previousTime;
            float    m_fps;
            float    m_deltaTime;
        };

    }

}