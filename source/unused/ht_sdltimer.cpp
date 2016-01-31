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

#include <ht_sdltimer.h>
#include <ht_sdl.h>

namespace Hatchit {

    namespace Game {

        SDLTimer::SDLTimer()
            : ITimer()
        {
            m_startTime = 0;
            m_currentTime = 0;
            m_previousTime = 0;
            m_fps = 0.0f;
            m_deltaTime = 0.0f;
        }

        SDLTimer::~SDLTimer()
        {

        }

        void SDLTimer::VStart()
        {
            m_startTime = SDL_GetTicks();
        }

        void SDLTimer::VTick()
        {
            /*cache current time in previous*/
            m_previousTime = m_currentTime;

            /*update current time*/
            m_currentTime = SDL_GetTicks();

            /*calculate delta time*/
            m_deltaTime = static_cast<float>(m_currentTime - m_previousTime) / 1000.0f;
        }
        
        void SDLTimer::VCalculateFPS()
        {
            static int frameCnt = 0;

            if (m_startTime < (SDL_GetTicks() - 1000.0f))
            {
                m_startTime = SDL_GetTicks();
                m_fps = static_cast<float>(frameCnt);

                frameCnt = 0;
            }

            ++frameCnt;
        }

        float SDLTimer::VDeltaTime()
        {
            return m_deltaTime;
        }

        float SDLTimer::VFramesPerSecond()
        {
            return m_fps;
        }

        float SDLTimer::VTotalTime()
        {
            return static_cast<float>(m_currentTime);
        }
    }

}