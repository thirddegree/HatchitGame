/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
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

#include <ht_window_singleton.h>
#include <ht_debug.h>

#ifdef HT_SYS_LINUX
#include <ht_xcbwindow.h>
#else
    #ifdef HT_WIN32_DESKTOP_APP
    #include <ht_sdlwindow.h>
    #elif defined(HT_WIN32_UNIVERSAL_APP)

    #endif
#endif

namespace Hatchit {

    namespace Game {

        bool Window::Initialize(const WindowParams& params)
        {
            Window& _instance = Window::instance();

#ifdef HT_SYS_LINUX
            _instance.m_window = new XCBWindow(params);
#else
    #ifdef HT_WIN32_DESKTOP_APP
            _instance.m_window = new SDLWindow(params);
    #elif defined(HT_WIN32_UNIVERSAL_APP)
            _instance.m_window = new UWAWindow(params);
    #endif
#endif
            if (!_instance.m_window->VInitialize())
            {
#ifdef _DEBUG
                Core::DebugPrintF("Failed to initialize Window. Exiting. \n");
#endif
                return false;
            }

            return true;
        }

        void Window::DeInitialize()
        {
            Window& _instance = Window::instance();

            delete _instance.m_window;
        }

        void Window::PollEvents()
        {
            Window& _instance = Window::instance();

            _instance.m_window->VPollEvents();
        }

        void Window::Close()
        {
            Window& _instance = Window::instance();

            _instance.m_window->VClose();
        }

        bool Window::IsRunning()
        {
            Window& _instance = Window::instance();
            
            return _instance.m_window->VIsRunning();
        }

        void Window::SwapBuffers()
        {
            Window& _instance = Window::instance();

            _instance.m_window->VSwapBuffers();
        }

        void* Window::NativeWindowHandle()
        {
            Window& _instance = Window::instance();

            return _instance.m_window->VNativeWindowHandle();
        }

        void* Window::NativeDisplayHandle()
        {
            Window& _instance = Window::instance();

            return _instance.m_window->VNativeDisplayHandle();
        }
    }

}
