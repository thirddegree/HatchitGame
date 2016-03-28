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

        bool SDLKeyboard::VKeyPress(Key k)
        {
            return m_current[ConvertFromKey(k)];
        }

        bool SDLKeyboard::VKeyRelease(Key k)
        {
            SDL_Scancode code = ConvertFromKey(k);

            return m_current[code] && m_previous[code];
        }

        bool SDLKeyboard::VSingleKeyPress(Key k)
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

       
        SDL_Scancode SDLKeyboard::ConvertFromKey(Key k)
        {
            switch (k)
            {
            case Key::A:
                return SDL_SCANCODE_A;
            case Key::B:
                return SDL_SCANCODE_B;
            case Key::C:
                return SDL_SCANCODE_C;
            case Key::D:
                return SDL_SCANCODE_D;
            case Key::E:
                return SDL_SCANCODE_E;
            case Key::F:
                return SDL_SCANCODE_F;
            case Key::G:
                return SDL_SCANCODE_G;
            case Key::H:
                return SDL_SCANCODE_H;
            case Key::I:
                return SDL_SCANCODE_I;
            case Key::J:
                return SDL_SCANCODE_J;
            case Key::K:
                return SDL_SCANCODE_K;
            case Key::L:
                return SDL_SCANCODE_L;
            case Key::M:
                return SDL_SCANCODE_M;
            case Key::N:
                return SDL_SCANCODE_N;
            case Key::O:
                return SDL_SCANCODE_O;
            case Key::P:
                return SDL_SCANCODE_P;
            case Key::Q:
                return SDL_SCANCODE_Q;
            case Key::R:
                return SDL_SCANCODE_R;
            case Key::S:
                return SDL_SCANCODE_S;
            case Key::T:
                return SDL_SCANCODE_T;
            case Key::U:
                return SDL_SCANCODE_U;
            case Key::V:
                return SDL_SCANCODE_V;
            case Key::W:
                return SDL_SCANCODE_W;
            case Key::X:
                return SDL_SCANCODE_X;
            case Key::Y:
                return SDL_SCANCODE_Y;
            case Key::Z:
                return SDL_SCANCODE_Z;
            case Key::Up:
                return SDL_SCANCODE_UP;
            case Key::Down:
                return SDL_SCANCODE_DOWN;
            case Key::Left:
                return SDL_SCANCODE_LEFT;
            case Key::Right:
                return SDL_SCANCODE_RIGHT;
            case Key::Space:
                return SDL_SCANCODE_SPACE;
            case Key::F1:
                return SDL_SCANCODE_F1;
            case Key::F2:
                return SDL_SCANCODE_F2;
            case Key::F3:
                return SDL_SCANCODE_F3;
            case Key::F4:
                return SDL_SCANCODE_F4;
            case Key::F5:
                return SDL_SCANCODE_F5;
            case Key::F6:
                return SDL_SCANCODE_F6;
            case Key::F7:
                return SDL_SCANCODE_F7;
            case Key::F8:
                return SDL_SCANCODE_F8;
            case Key::F9:
                return SDL_SCANCODE_F9;
            case Key::F10:
                return SDL_SCANCODE_F10;
            case Key::F11:
                return SDL_SCANCODE_F11;
            case Key::F12:
                return SDL_SCANCODE_F12;
            case Key::Num0:
                return SDL_SCANCODE_0;
            case Key::Num1:
                return SDL_SCANCODE_1;
            case Key::Num2:
                return SDL_SCANCODE_2;
            case Key::Num3:
                return SDL_SCANCODE_3;
            case Key::Num4:
                return SDL_SCANCODE_4;
            case Key::Num5:
                return SDL_SCANCODE_5;
            case Key::Num6:
                return SDL_SCANCODE_6;
            case Key::Num7:
                return SDL_SCANCODE_7;
            case Key::Num8:
                return SDL_SCANCODE_8;
            case Key::Num9:
                return SDL_SCANCODE_9;
            case Key::Esc:
                return SDL_SCANCODE_ESCAPE;
            case Key::Enter:
                return SDL_SCANCODE_RETURN;
            default:
                return SDL_SCANCODE_0;
                break;
            }
        }
    }
}