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

            /*Keyboard*/
            static bool KeyPressed(IKeyboard::Key key);
            static bool KeySinglePressed(IKeyboard::Key key);
            static bool KeyReleased(IKeyboard::Key key);

            /*Mouse*/
            static int  MouseX();
            static int  MouseY();
            static int  PreviousMouseX();
            static int  PreviousMouseY();
            static int  MouseWheelX();
            static int  MouseWheelY();
            static int  DeltaX(int val);
            static int  DeltaY(int val);
            static bool MouseButtonPress(MouseButton button);
            static bool MouseButtonSinglePress(MouseButton button);
            static bool MouseButtonRelease(MouseButton button);

            static void Update();

            static IKeyboard* const Keyboard();
            static IMouse*    const Mouse();
            
        private:
            IKeyboard* m_keyboard;
            IMouse*    m_mouse;
        };
    }
}
