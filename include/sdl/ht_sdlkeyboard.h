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

#pragma once

#include <ht_platform.h>
#include <ht_keyboard.h>
#include <ht_sdl.h>
#include <map>

namespace Hatchit
{
    namespace Game
    {
        class HT_API SDLKeyboard : public IKeyboard
        {
            typedef std::map<SDL_Scancode, bool> KeyState;
        public:
            SDLKeyboard();

            void RegisterKeyDown(SDL_Scancode code);
            void RegisterKeyUp(SDL_Scancode code);
            

            bool VKeyPress(IKeyboard::Key k)            override;
            bool VKeyRelease(IKeyboard::Key k)          override;
            bool VSingleKeyPress(IKeyboard::Key k)      override;
            void VUpdate()                              override;

        private:
            KeyState m_current;
            KeyState m_previous;

            SDL_Scancode ConvertFromKey(IKeyboard::Key k);
        };
    }
}
