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

#include <ht_sdlwindow.h>
#include <ht_debug.h>

namespace Hatchit {

    namespace Game {

        SDLWindow::SDLWindow(const WindowParams& params)
        {
            m_params = params;
            m_handle = nullptr;
            m_nativeHandle = nullptr;
        }

        SDLWindow::~SDLWindow()
        {
            SDL_Quit();
        }

        bool SDLWindow::VInitialize()
        {
            if (SDL_Init(SDL_INIT_TIMER) != 0) {
#ifdef _DEBUG
                Core::DebugPrintF("SDL Failed to Initialize. Exiting\n");
#endif
                return false;
            }

            m_handle = SDL_CreateWindow(m_params.title.c_str(),
                m_params.x <= 0 ? SDL_WINDOWPOS_CENTERED : m_params.x,
                m_params.y <= 0 ? SDL_WINDOWPOS_CENTERED : m_params.y,
                m_params.width,
                m_params.height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if (!m_handle)
            {
#ifdef _DEBUG
                Core::DebugPrintF("Failed to create SDL_Window handle. Exiting.\n");
#endif 
                SDL_Quit();
                return false;
            }

#ifdef HT_SYS_WINDOWS
            SDL_SysWMinfo info;
            SDL_VERSION(&info.version);
            if (SDL_GetWindowWMInfo(m_handle, &info))
                m_nativeHandle = info.info.win.window;
#endif

#ifdef HT_SYS_LINUX
            m_glcontext = SDL_GL_CreateContext(m_handle);
            if (!m_glcontext)
            {
#ifdef _DEBUG
                Core::DebugPrintF("Failed to create SDL_GL_Context handle. Exiting.\n");
#endif
                SDL_Quit();
                return false;
            }
#endif

            m_running = true;

            return true;
        }

        void SDLWindow::VPollEvents()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    VClose();
                    break;

                default:
                    break;
                }
            }
        }

        void* SDLWindow::VNativeHandle()
        {
            return m_nativeHandle;
        }

        bool SDLWindow::VIsRunning()
        {
            return m_running;
        }

        void SDLWindow::VClose()
        {
            m_running = false;
            SDL_GL_DeleteContext(m_glcontext);
            SDL_Quit();
        }

        void SDLWindow::VSwapBuffers()
        {
            SDL_GL_SwapWindow(m_handle);
        }
    }

}