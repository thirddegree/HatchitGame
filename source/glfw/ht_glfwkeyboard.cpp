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

#include <ht_glfwkeyboard.h>
#include <GLFW/glfw3.h>

namespace Hatchit
{
    namespace Game
    {
        GLFWKeyboard::GLFWKeyboard()
        {
        }

        bool GLFWKeyboard::VKeyPress(IKeyboard::Key k)
        {
            return m_current[ConvertFromKey(k)];
        }

        bool GLFWKeyboard::VKeyRelease(IKeyboard::Key k)
        {
            int code = ConvertFromKey(k);

            return m_current[code] && m_previous[code];
        }

        bool GLFWKeyboard::VSingleKeyPress(IKeyboard::Key k)
        {
            int code = ConvertFromKey(k);

            return m_current[code] && !m_previous[code];
        }

        void GLFWKeyboard::VUpdate()
        {
            m_previous = m_current;
        }

        void GLFWKeyboard::RegisterKeyDown(int code)
        {
            m_current[code] = true;
        }

        void GLFWKeyboard::RegisterKeyUp(int code)
        {
            m_current[code] = false;
        }


        int GLFWKeyboard::ConvertFromKey(IKeyboard::Key k)
        {
            switch (k)
            {
            case IKeyboard::Key::A:
                return GLFW_KEY_A;
            case IKeyboard::Key::B:
                return GLFW_KEY_B;
            case IKeyboard::Key::C:
                return GLFW_KEY_C;
            case IKeyboard::Key::D:
                return GLFW_KEY_D;
            case IKeyboard::Key::E:
                return GLFW_KEY_E;
            case IKeyboard::Key::F:
                return GLFW_KEY_F;
            case IKeyboard::Key::G:
                return GLFW_KEY_G;
            case IKeyboard::Key::H:
                return GLFW_KEY_H;
            case IKeyboard::Key::I:
                return GLFW_KEY_I;
            case IKeyboard::Key::J:
                return GLFW_KEY_J;
            case IKeyboard::Key::K:
                return GLFW_KEY_K;
            case IKeyboard::Key::L:
                return GLFW_KEY_L;
            case IKeyboard::Key::M:
                return GLFW_KEY_M;
            case IKeyboard::Key::N:
                return GLFW_KEY_N;
            case IKeyboard::Key::O:
                return GLFW_KEY_O;
            case IKeyboard::Key::P:
                return GLFW_KEY_P;
            case IKeyboard::Key::Q:
                return GLFW_KEY_Q;
            case IKeyboard::Key::R:
                return GLFW_KEY_R;
            case IKeyboard::Key::S:
                return GLFW_KEY_S;
            case IKeyboard::Key::T:
                return GLFW_KEY_T;
            case IKeyboard::Key::U:
                return GLFW_KEY_U;
            case IKeyboard::Key::V:
                return GLFW_KEY_V;
            case IKeyboard::Key::W:
                return GLFW_KEY_W;
            case IKeyboard::Key::X:
                return GLFW_KEY_X;
            case IKeyboard::Key::Y:
                return GLFW_KEY_Y;
            case IKeyboard::Key::Z:
                return GLFW_KEY_Z;
            case IKeyboard::Key::Up:
                return GLFW_KEY_UP;
            case IKeyboard::Key::Down:
                return GLFW_KEY_DOWN;
            case IKeyboard::Key::Left:
                return GLFW_KEY_LEFT;
            case IKeyboard::Key::Right:
                return GLFW_KEY_RIGHT;
            case IKeyboard::Key::Space:
                return GLFW_KEY_SPACE;
            case IKeyboard::Key::F1:
                return GLFW_KEY_F1;
            case IKeyboard::Key::F2:
                return GLFW_KEY_F2;
            case IKeyboard::Key::F3:
                return GLFW_KEY_F3;
            case IKeyboard::Key::F4:
                return GLFW_KEY_F4;
            case IKeyboard::Key::F5:
                return GLFW_KEY_F5;
            case IKeyboard::Key::F6:
                return GLFW_KEY_F6;
            case IKeyboard::Key::F7:
                return GLFW_KEY_F7;
            case IKeyboard::Key::F8:
                return GLFW_KEY_F8;
            case IKeyboard::Key::F9:
                return GLFW_KEY_F9;
            case IKeyboard::Key::F10:
                return GLFW_KEY_F10;
            case IKeyboard::Key::F11:
                return GLFW_KEY_F11;
            case IKeyboard::Key::F12:
                return GLFW_KEY_F12;
            case IKeyboard::Key::Num0:
                return GLFW_KEY_0;
            case IKeyboard::Key::Num1:
                return GLFW_KEY_1;
            case IKeyboard::Key::Num2:
                return GLFW_KEY_2;
            case IKeyboard::Key::Num3:
                return GLFW_KEY_3;
            case IKeyboard::Key::Num4:
                return GLFW_KEY_4;
            case IKeyboard::Key::Num5:
                return GLFW_KEY_5;
            case IKeyboard::Key::Num6:
                return GLFW_KEY_6;
            case IKeyboard::Key::Num7:
                return GLFW_KEY_7;
            case IKeyboard::Key::Num8:
                return GLFW_KEY_8;
            case IKeyboard::Key::Num9:
                return GLFW_KEY_9;
            case IKeyboard::Key::Esc:
                return GLFW_KEY_ESCAPE;
            case IKeyboard::Key::Enter:
                return GLFW_KEY_ENTER;
            case IKeyboard::Key::LShift:
                return GLFW_KEY_LEFT_SHIFT;
            case IKeyboard::Key::RShift:
                return GLFW_KEY_RIGHT_SHIFT;
            case IKeyboard::Key::LAlt:
                return GLFW_KEY_LEFT_ALT;
            case IKeyboard::Key::RAlt:
                return GLFW_KEY_RIGHT_ALT;
            default:
                return GLFW_KEY_0;
                break;
            }
        }
    }
}
