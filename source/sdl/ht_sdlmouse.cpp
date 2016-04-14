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

#include <ht_sdlmouse.h>

#define MOUSE_LMB 0
#define MOUSE_MMB 1
#define MOUSE_RMB 2 

namespace Hatchit
{
    namespace Game
    {
        SDLMouse::SDLMouse()
            : m_x(0), m_y(0), m_wx(0), m_wy(0),
              m_prevWX(0), m_prevWY(0), m_prevX(0), m_prevY(0)
        {
            m_current[MOUSE_LMB].state = SDL_RELEASED;
            m_current[MOUSE_MMB].state = SDL_RELEASED;
            m_current[MOUSE_RMB].state = SDL_RELEASED;

            m_previous[MOUSE_LMB].state = SDL_RELEASED;
            m_previous[MOUSE_MMB].state = SDL_RELEASED;
            m_previous[MOUSE_RMB].state = SDL_RELEASED;
        }

        int SDLMouse::VMouseX()
        {
            return m_x;
        }

        int SDLMouse::VMouseY()
        {
            return m_y;
        }

        int SDLMouse::VPreviousMouseX()
        {
            return m_prevX;
        }

        int SDLMouse::VPreviousMouseY()
        {
            return m_prevY;
        }

        int SDLMouse::VMouseWheelX()
        {
            return m_wx;
        }

        int SDLMouse::VMouseWheelY()
        {
            return m_wy;
        }

        int SDLMouse::VDeltaX(int val)
        {
            if (m_x != m_prevX)
                return m_x - val;
            else
                return 0;
        }

        int SDLMouse::VDeltaY(int val)
        {
            if (m_y != m_prevY)
                return m_y - val;
            else
                return 0;
        }

        bool SDLMouse::VButtonPress(MouseButton button)
        {
            switch (button)
            {
            case MouseButton::Left:
                return m_current[MOUSE_LMB].state == SDL_PRESSED;
            case MouseButton::Middle:
                return m_current[MOUSE_MMB].state == SDL_PRESSED;
            case MouseButton::Right:
                return m_current[MOUSE_RMB].state == SDL_PRESSED;
            default:
                return false;
            }
        }

        bool SDLMouse::VButtonRelease(MouseButton button)
        {
            switch (button)
            {
            case MouseButton::Left:
                return m_current[MOUSE_LMB].state == SDL_RELEASED && m_previous[MOUSE_LMB].state == SDL_PRESSED;
            case MouseButton::Middle:
                return m_current[MOUSE_MMB].state == SDL_RELEASED && m_previous[MOUSE_MMB].state == SDL_PRESSED;
            case MouseButton::Right:
                return m_current[MOUSE_RMB].state == SDL_RELEASED && m_previous[MOUSE_RMB].state == SDL_PRESSED;
            default:
                return false;
            }
        }

        bool SDLMouse::VSingleButtonPress(MouseButton button)
        {
            switch (button)
            {
            case MouseButton::Left:
                return m_current[MOUSE_LMB].state == SDL_PRESSED && m_previous[MOUSE_LMB].state == SDL_RELEASED;
            case MouseButton::Middle:
                return m_current[MOUSE_MMB].state == SDL_PRESSED && m_previous[MOUSE_MMB].state == SDL_RELEASED;
            case MouseButton::Right:
                return m_current[MOUSE_RMB].state == SDL_PRESSED && m_previous[MOUSE_RMB].state == SDL_RELEASED;
            default:
                return false;
            }
        }

        void SDLMouse::VUpdate()
        {
            m_prevWX = m_wx;
            m_prevWY = m_wy;
            m_prevX = m_x;
            m_prevY = m_y;
            m_wy = 0;
            memcpy(m_previous, m_current, sizeof(m_current));
        }

        void SDLMouse::RegisterMouseMove(int x, int y)
        {
            m_x = x;
            m_y = y;
        }

        void SDLMouse::RegisterMouseButtonEvent(SDL_MouseButtonEvent e)
        {
            switch (e.button)
            {
                case SDL_BUTTON_LEFT:
                {
                    m_current[MOUSE_LMB].state = e.state;
                    m_current[MOUSE_LMB].clicks = e.clicks;
                } break;

                case SDL_BUTTON_MIDDLE:
                {
                    m_current[MOUSE_MMB].state = e.state;
                    m_current[MOUSE_MMB].clicks = e.state;
                } break;

                case SDL_BUTTON_RIGHT:
                {
                    m_current[MOUSE_RMB].state = e.state;
                    m_current[MOUSE_RMB].clicks = e.clicks;
                } break;
            }
        }

        void SDLMouse::RegisterMouseWheelEvent(SDL_MouseWheelEvent e)
        {
            m_wx = e.x;
            m_wy = e.y;
        }
    }
}