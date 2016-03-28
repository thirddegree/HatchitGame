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

#include <ht_input_singleton.h>

#ifdef HT_SYS_WINDOWS
    #ifdef HT_WIN32_DESKTOP_APP
        #define SDL_SUPPORT TRUE
        #include <ht_sdlkeyboard.h>
    #endif
#else
    #ifndef VK_SUPPORT
        #define SDL_SUPPORT TRUE
        #include <ht_sdlkeyboard.h>
    #endif
#endif

namespace Hatchit
{
    namespace Game
    {
        void Input::Initialize()
        {
            Input& _instance = Input::instance();
#ifdef SDL_SUPPORT
            _instance.m_keyboard = new SDLKeyboard;
#endif
        }

        void Input::DeInitialize()
        {
            Input& _instance = Input::instance();

            delete _instance.m_keyboard;
        }

        bool Input::KeyPress(Key key)
        {
            Input& _instance = Input::instance();

            return _instance.m_keyboard->VKeyPress(key);
        }

        bool Input::KeyRelease(Key key)
        {
            Input& _instance = Input::instance();

            return _instance.m_keyboard->VKeyRelease(key);
        }

        bool Input::SingleKeyPress(Key key)
        {
            Input& _instance = Input::instance();

            return _instance.m_keyboard->VSingleKeyPress(key);
        }

        IKeyboard* const Input::Keyboard()
        {
            return Input::instance().m_keyboard;
        }

        void Input::Update()
        {
            Input& _instance = Input::instance();

            _instance.m_keyboard->VUpdate();
        }

    }
}