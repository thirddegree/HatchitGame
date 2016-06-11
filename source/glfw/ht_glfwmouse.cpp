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

#include <ht_glfwmouse.h>
#include <cstring>

#define MOUSE_LMB 0
#define MOUSE_MMB 1
#define MOUSE_RMB 2 

namespace Hatchit
{
    namespace Game
    {
        GLFWMouse::GLFWMouse()
            : m_x(0), m_y(0), m_prevX(0), m_prevY(0), m_wx(0), m_wy(0),
              m_prevWX(0), m_prevWY(0)
        {
            m_current[MOUSE_LMB].state = GLFW_RELEASE;
            m_current[MOUSE_MMB].state = GLFW_RELEASE;
            m_current[MOUSE_RMB].state = GLFW_RELEASE;

            m_previous[MOUSE_LMB].state = GLFW_RELEASE;
            m_previous[MOUSE_MMB].state = GLFW_RELEASE;
            m_previous[MOUSE_RMB].state = GLFW_RELEASE;
        }

        int GLFWMouse::VMouseX()
        {
            return m_x;
        }

        int GLFWMouse::VMouseY()
        {
            return m_y;
        }

        int GLFWMouse::VPreviousMouseX()
        {
            return m_prevX;
        }

        int GLFWMouse::VPreviousMouseY()
        {
            return m_prevY;
        }

        int GLFWMouse::VMouseWheelX()
        {
            return m_wx;
        }

        int GLFWMouse::VMouseWheelY()
        {
            return m_wy;
        }

        int GLFWMouse::VDeltaX(int val)
        {
            if (m_x != m_prevX)
                return m_x - val;
            else
                return 0;
        }

        int GLFWMouse::VDeltaY(int val)
        {
            if (m_y != m_prevY)
                return m_y - val;
            else
                return 0;
        }

        bool GLFWMouse::VButtonPress(MouseButton button)
        {
            switch (button)
            {
            case MouseButton::Left:
                return m_current[MOUSE_LMB].state == GLFW_PRESS;
            case MouseButton::Middle:
                return m_current[MOUSE_MMB].state == GLFW_PRESS;
            case MouseButton::Right:
                return m_current[MOUSE_RMB].state == GLFW_PRESS;
            default:
                return false;
            }
        }

        bool GLFWMouse::VButtonRelease(MouseButton button)
        {
            switch (button)
            {
            case MouseButton::Left:
                return m_current[MOUSE_LMB].state == GLFW_RELEASE && m_previous[MOUSE_LMB].state == GLFW_PRESS;
            case MouseButton::Middle:
                return m_current[MOUSE_MMB].state == GLFW_RELEASE && m_previous[MOUSE_MMB].state == GLFW_PRESS;
            case MouseButton::Right:
                return m_current[MOUSE_RMB].state == GLFW_RELEASE && m_previous[MOUSE_RMB].state == GLFW_PRESS;
            default:
                return false;
            }
        }

        bool GLFWMouse::VSingleButtonPress(MouseButton button)
        {
            switch (button)
            {
            case MouseButton::Left:
                return m_current[MOUSE_LMB].state == GLFW_PRESS && m_previous[MOUSE_LMB].state == GLFW_RELEASE;
            case MouseButton::Middle:
                return m_current[MOUSE_MMB].state == GLFW_PRESS && m_previous[MOUSE_MMB].state == GLFW_RELEASE;
            case MouseButton::Right:
                return m_current[MOUSE_RMB].state == GLFW_PRESS && m_previous[MOUSE_RMB].state == GLFW_RELEASE;
            default:
                return false;
            }
        }

        void GLFWMouse::VUpdate()
        {
            m_prevWX = m_wx;
            m_prevWY = m_wy;
            m_prevX = m_x;
            m_prevY = m_y;
            m_wy = 0;
            memcpy(m_previous, m_current, sizeof(m_current));
        }

        void GLFWMouse::RegisterMouseMove(int x, int y)
        {
            m_x = x;
            m_y = y;
        }

        void GLFWMouse::RegisterMouseButtonEvent(int e, int action)
        {
            switch (e)
            {
                case GLFW_MOUSE_BUTTON_LEFT:
                {
                    m_current[MOUSE_LMB].state = static_cast<uint8_t>(action);
                    m_current[MOUSE_LMB].clicks = 1;
                } break;

                case GLFW_MOUSE_BUTTON_MIDDLE:
                {
                    m_current[MOUSE_MMB].state = static_cast<uint8_t>(action);
                    m_current[MOUSE_MMB].clicks = 1;
                } break;

                case GLFW_MOUSE_BUTTON_RIGHT:
                {
                    m_current[MOUSE_RMB].state = static_cast<uint8_t>(action);
                    m_current[MOUSE_RMB].clicks = 1;
                } break;
            }
        }

        void GLFWMouse::RegisterMouseWheelEvent(double xoffset, double yoffset)
        {
            m_wx = (int)xoffset;
            m_wy = (int)yoffset;
        }
    }
}
