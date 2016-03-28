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
#include <ht_singleton.h>
#include <ht_keyboard.h>
#include <ht_mouse.h>

namespace Hatchit
{
    namespace Game
    {
        class HT_API Input : public Core::Singleton<Input>
        {
        public:
            static void Initialize();

            static void DeInitialize();

            /*Keyboard functions*/
            static bool KeyPress(Key key);
            static bool SingleKeyPress(Key key);
            static bool KeyRelease(Key key);

            static void Update();

            static IKeyboard* const Keyboard();
            
        private:
            IKeyboard* m_keyboard;
        };
    }
}