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

#include <ht_sdlkeyboard.h>

namespace Hatchit
{
    namespace Game
    {
        SDLKeyboard::SDLKeyboard()
        {

        }

        bool SDLKeyboard::VKeyPress(IKeyboard::Key k)
        {
            return m_current[ConvertFromKey(k)];
        }

        bool SDLKeyboard::VKeyRelease(IKeyboard::Key k)
        {
            SDL_Scancode code = ConvertFromKey(k);

            return m_current[code] && m_previous[code];
        }

        bool SDLKeyboard::VSingleKeyPress(IKeyboard::Key k)
        {
            SDL_Scancode code = ConvertFromKey(k);

            return m_current[code] && !m_previous[code];
        }

        void SDLKeyboard::VUpdate()
        {
            m_previous = m_current;
        }

        void SDLKeyboard::RegisterKeyDown(SDL_Scancode code)
        {
            m_current[code] = true;
        }

        void SDLKeyboard::RegisterKeyUp(SDL_Scancode code)
        {
            m_current[code] = false;
        }


        SDL_Scancode SDLKeyboard::ConvertFromKey(IKeyboard::Key k)
        {
            switch (k)
            {
            case IKeyboard::Key::A:
                return SDL_SCANCODE_A;
            case IKeyboard::Key::B:
                return SDL_SCANCODE_B;
            case IKeyboard::Key::C:
                return SDL_SCANCODE_C;
            case IKeyboard::Key::D:
                return SDL_SCANCODE_D;
            case IKeyboard::Key::E:
                return SDL_SCANCODE_E;
            case IKeyboard::Key::F:
                return SDL_SCANCODE_F;
            case IKeyboard::Key::G:
                return SDL_SCANCODE_G;
            case IKeyboard::Key::H:
                return SDL_SCANCODE_H;
            case IKeyboard::Key::I:
                return SDL_SCANCODE_I;
            case IKeyboard::Key::J:
                return SDL_SCANCODE_J;
            case IKeyboard::Key::K:
                return SDL_SCANCODE_K;
            case IKeyboard::Key::L:
                return SDL_SCANCODE_L;
            case IKeyboard::Key::M:
                return SDL_SCANCODE_M;
            case IKeyboard::Key::N:
                return SDL_SCANCODE_N;
            case IKeyboard::Key::O:
                return SDL_SCANCODE_O;
            case IKeyboard::Key::P:
                return SDL_SCANCODE_P;
            case IKeyboard::Key::Q:
                return SDL_SCANCODE_Q;
            case IKeyboard::Key::R:
                return SDL_SCANCODE_R;
            case IKeyboard::Key::S:
                return SDL_SCANCODE_S;
            case IKeyboard::Key::T:
                return SDL_SCANCODE_T;
            case IKeyboard::Key::U:
                return SDL_SCANCODE_U;
            case IKeyboard::Key::V:
                return SDL_SCANCODE_V;
            case IKeyboard::Key::W:
                return SDL_SCANCODE_W;
            case IKeyboard::Key::X:
                return SDL_SCANCODE_X;
            case IKeyboard::Key::Y:
                return SDL_SCANCODE_Y;
            case IKeyboard::Key::Z:
                return SDL_SCANCODE_Z;
            case IKeyboard::Key::Up:
                return SDL_SCANCODE_UP;
            case IKeyboard::Key::Down:
                return SDL_SCANCODE_DOWN;
            case IKeyboard::Key::Left:
                return SDL_SCANCODE_LEFT;
            case IKeyboard::Key::Right:
                return SDL_SCANCODE_RIGHT;
            case IKeyboard::Key::Space:
                return SDL_SCANCODE_SPACE;
            case IKeyboard::Key::F1:
                return SDL_SCANCODE_F1;
            case IKeyboard::Key::F2:
                return SDL_SCANCODE_F2;
            case IKeyboard::Key::F3:
                return SDL_SCANCODE_F3;
            case IKeyboard::Key::F4:
                return SDL_SCANCODE_F4;
            case IKeyboard::Key::F5:
                return SDL_SCANCODE_F5;
            case IKeyboard::Key::F6:
                return SDL_SCANCODE_F6;
            case IKeyboard::Key::F7:
                return SDL_SCANCODE_F7;
            case IKeyboard::Key::F8:
                return SDL_SCANCODE_F8;
            case IKeyboard::Key::F9:
                return SDL_SCANCODE_F9;
            case IKeyboard::Key::F10:
                return SDL_SCANCODE_F10;
            case IKeyboard::Key::F11:
                return SDL_SCANCODE_F11;
            case IKeyboard::Key::F12:
                return SDL_SCANCODE_F12;
            case IKeyboard::Key::Num0:
                return SDL_SCANCODE_0;
            case IKeyboard::Key::Num1:
                return SDL_SCANCODE_1;
            case IKeyboard::Key::Num2:
                return SDL_SCANCODE_2;
            case IKeyboard::Key::Num3:
                return SDL_SCANCODE_3;
            case IKeyboard::Key::Num4:
                return SDL_SCANCODE_4;
            case IKeyboard::Key::Num5:
                return SDL_SCANCODE_5;
            case IKeyboard::Key::Num6:
                return SDL_SCANCODE_6;
            case IKeyboard::Key::Num7:
                return SDL_SCANCODE_7;
            case IKeyboard::Key::Num8:
                return SDL_SCANCODE_8;
            case IKeyboard::Key::Num9:
                return SDL_SCANCODE_9;
            case IKeyboard::Key::Esc:
                return SDL_SCANCODE_ESCAPE;
            case IKeyboard::Key::Enter:
                return SDL_SCANCODE_RETURN;
            case IKeyboard::Key::LShift:
                return SDL_SCANCODE_LSHIFT;
            case IKeyboard::Key::RShift:
                return SDL_SCANCODE_RSHIFT;
            case IKeyboard::Key::LAlt:
                return SDL_SCANCODE_LALT;
            case IKeyboard::Key::RAlt:
                return SDL_SCANCODE_RALT;
            default:
                return SDL_SCANCODE_0;
                break;
            }
        }
    }
}
