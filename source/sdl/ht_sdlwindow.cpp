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
#include <ht_time_singleton.h>
#include <ht_input_singleton.h>
#include <ht_sdlkeyboard.h>
#include <ht_sdlmouse.h>
#include <ht_renderer_singleton.h>

namespace Hatchit {

    namespace Game {

        SDLWindow::SDLWindow(const WindowParams& params)
        {
            m_params = params;
            m_handle = nullptr;
            m_nativeWindowHandle = nullptr;
            m_nativeDisplayHandle = nullptr;
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
            {
                m_nativeWindowHandle = info.info.win.window;
                m_nativeDisplayHandle = nullptr;
            }
#elif defined(HT_SYS_LINUX)
            SDL_SysWMinfo info;
            SDL_VERSION(&info.version);
            if (SDL_GetWindowWMInfo(m_handle, &info))
            {
                m_nativeWindowHandle = (void*)info.info.x11.window;
                m_nativeDisplayHandle = info.info.x11.display;
            }
#endif
            if (m_params.renderer == Graphics::RendererType::OPENGL)
            {
                m_glcontext = SDL_GL_CreateContext(m_handle);
                if (!m_glcontext)
                {
#ifdef _DEBUG
                    Core::DebugPrintF("Failed to create SDL_GL_Context handle. Exiting.\n");
#endif
                    SDL_Quit();
                    return false;
                }
            }
           

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

                case SDL_KEYDOWN:
                {
                    static_cast<SDLKeyboard*>(Input::Keyboard())->RegisterKeyDown(event.key.keysym.scancode);
                } break;

                case SDL_KEYUP:
                {
                    static_cast<SDLKeyboard*>(Input::Keyboard())->RegisterKeyUp(event.key.keysym.scancode);
                } break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                {
                    static_cast<SDLMouse*>(Input::Mouse())->RegisterMouseButtonEvent(event.button);
                } break;

                case SDL_MOUSEWHEEL:
                {
                    static_cast<SDLMouse*>(Input::Mouse())->RegisterMouseWheelEvent(event.wheel);
                } break;

                case SDL_MOUSEMOTION:
                {
                    static_cast<SDLMouse*>(Input::Mouse())->RegisterMouseMove(event.motion.x, event.motion.y);
                } break;

                case SDL_WINDOWEVENT:
                {
                    switch (event.window.event)
                    {
                    case SDL_WINDOWEVENT_SHOWN:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d shown", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_HIDDEN:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d hidden", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_EXPOSED:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d exposed", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_MOVED:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d moved to %d,%d",
                                event.window.windowID, event.window.data1,
                                event.window.data2);
                        break;
                    case SDL_WINDOWEVENT_RESIZED:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d resized to %dx%d",
                                event.window.windowID, event.window.data1,
                                event.window.data2);
                        Renderer::ResizeBuffers(event.window.data1, event.window.data2);
                        break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d size changed to %dx%d",
                                event.window.windowID, event.window.data1,
                                event.window.data2);
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d minimized", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d maximized", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_RESTORED:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d restored", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Mouse entered window %d",
                                event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_LEAVE:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Mouse left window %d", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d gained keyboard focus",
                                event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d lost keyboard focus",
                                event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d closed", event.window.windowID);
                        break;
                    default:
                        if (m_params.debugWindowEvents)
                            HT_DEBUG_PRINTF("Window %d got unknown event %d",
                                event.window.windowID, event.window.event);
                    }
                } break;

                default:
                    break;
                }
            }

            
        
            std::string title = m_params.title + (m_params.displayFPS ? (" FPS: " + std::to_string((int)Time::FramesPerSecond())) : "")
                                                + (m_params.displayMouse ? (" [" + std::to_string(Input::MouseX()) + "," +
                                                    std::to_string(Input::MouseY()) + "]") : "");
            SDL_SetWindowTitle(m_handle, title.c_str());
            
        }

        void* SDLWindow::VNativeWindowHandle()
        {
            return m_nativeWindowHandle;
        }
        void* SDLWindow::VNativeDisplayHandle()
        {
            return m_nativeDisplayHandle;
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
            if (m_params.renderer == Graphics::RendererType::OPENGL)
                SDL_GL_SwapWindow(m_handle);
        }
    }

}
