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
        #define GLFW_SUPPORT TRUE
        #include <ht_glfwkeyboard.h>
        #include <ht_glfwmouse.h>
    #endif
#else
        #include <ht_glfwkeyboard.h>
        #include <ht_glfwmouse.h>
#endif

namespace Hatchit
{
    namespace Game
    {
        void Input::Initialize()
        {
            Input& _instance = Input::instance();

            _instance.m_keyboard = new GLFWKeyboard;
            _instance.m_mouse = new GLFWMouse;
        }

        void Input::DeInitialize()
        {
            Input& _instance = Input::instance();

            delete _instance.m_keyboard;
        }

        bool Input::KeyPressed(IKeyboard::Key key)
        {
            Input& _instance = Input::instance();

            return _instance.m_keyboard->VKeyPress(key);
        }

        bool Input::KeyReleased(IKeyboard::Key key)
        {
            Input& _instance = Input::instance();

            return _instance.m_keyboard->VKeyRelease(key);
        }

        bool Input::KeySinglePressed(IKeyboard::Key key)
        {
            Input& _instance = Input::instance();

            return _instance.m_keyboard->VSingleKeyPress(key);
        }

        Math::Vector2 Input::MousePos()
        {
            return Math::Vector2(MouseX(), MouseY());
        }

        Math::Vector2 Input::PreviousMousePos()
        {
            return Math::Vector2(PreviousMouseX(), PreviousMouseY());
        }

        int Input::MouseX()
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VMouseX();
        }

        int Input::MouseY()
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VMouseY();
        }

        int Input::PreviousMouseX()
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VPreviousMouseX();
        }

        int Input::PreviousMouseY()
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VPreviousMouseY();
        }

        int Input::MouseWheelX()
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VMouseWheelX();
        }

        int Input::MouseWheelY()
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VMouseWheelY();
        }

        int Input::DeltaX(int val)
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VDeltaX(val);
        }

        int Input::DeltaY(int val)
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VDeltaY(val);
        }

        bool Input::MouseButtonPress(MouseButton button)
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VButtonPress(button);
        }

        bool Input::MouseButtonRelease(MouseButton button)
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VButtonRelease(button);
        }

        bool Input::MouseButtonSinglePress(MouseButton button)
        {
            Input& _instance = Input::instance();

            return _instance.m_mouse->VSingleButtonPress(button);
        }

        IKeyboard* const Input::Keyboard()
        {
            return Input::instance().m_keyboard;
        }

        IMouse* const Input::Mouse()
        {
            return Input::instance().m_mouse;
        }

        void Input::Update()
        {
            Input& _instance = Input::instance();

            _instance.m_keyboard->VUpdate();
            _instance.m_mouse->VUpdate();
        }

    }
}
