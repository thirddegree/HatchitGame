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

#include <ht_glfwwindow.h>
#include <ht_debug.h>
#include <ht_time_singleton.h>
#include <ht_input_singleton.h>
#include <ht_glfwkeyboard.h>
#include <ht_glfwmouse.h>

#ifdef HT_SYS_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif defined(HT_SYS_WINDOWS)
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GLFW/glfw3native.h>

namespace Hatchit {

    namespace Game {

        GLFWWindow::GLFWWindow(const WindowParams& params)
        {
            m_params = params;
            m_handle = nullptr;
            m_nativeWindowHandle = nullptr;
            m_nativeDisplayHandle = nullptr;
        }

        GLFWWindow::~GLFWWindow()
        {
            glfwTerminate();
        }

        bool GLFWWindow::VInitialize()
        {
            if (!glfwInit()) {
                HT_DEBUG_PRINTF("GLFW Failed to Initialize. Exiting\n");
                return false;
            }

            m_handle = glfwCreateWindow(m_params.width, m_params.height, m_params.title.c_str(),
            nullptr, nullptr);

            #ifdef HT_SYS_LINUX

            m_nativeDisplayHandle = glfwGetX11Display();
            m_nativeWindowHandle = (void*)glfwGetX11Window(m_handle);

            #elif defined(HT_SYS_WINDOWS)

            m_nativeWindowHandle = glfwGetWin32Window(m_handle);
            m_nativeDisplayHandle = nullptr;
            
            #endif

            if ( !m_handle ) {
                HT_DEBUG_PRINTF("Failed to create GLFWwindow handle. Exiting.\n");
                glfwTerminate();
                return false;
            }

            glfwSetKeyCallback(m_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                if ( action == GLFW_PRESS )
                    static_cast<GLFWKeyboard*>(Input::Keyboard())->RegisterKeyDown(key);
                else {
                    if ( action == GLFW_RELEASE )
                        static_cast<GLFWKeyboard*>(Input::Keyboard())->RegisterKeyUp(key);
                }
            });
            
            glfwSetCursorPosCallback(m_handle, [](GLFWwindow* window, double xpos, double ypos) {
                static_cast<GLFWMouse*>(Input::Mouse())->RegisterMouseMove(static_cast<int>(xpos), static_cast<int>(ypos));
            });

            glfwSetMouseButtonCallback(m_handle, [](GLFWwindow* window, int button, int action, int mods) {
                static_cast<GLFWMouse*>(Input::Mouse())->RegisterMouseButtonEvent(button, action);
            });

            glfwSetScrollCallback(m_handle, [](GLFWwindow* window, double xoffset, double yoffset) {
                static_cast<GLFWMouse*>(Input::Mouse())->RegisterMouseWheelEvent(static_cast<int>(xoffset), static_cast<int>(yoffset));
            });
            
            m_running = true;

            return true;
        }

        void GLFWWindow::VPollEvents()
        {
            glfwPollEvents();
        }

        void* GLFWWindow::VNativeWindowHandle()
        {
            return m_nativeWindowHandle;
        }

        void* GLFWWindow::VNativeDisplayHandle()
        {
            return m_nativeDisplayHandle;
        }

        bool GLFWWindow::VIsRunning()
        {
            return m_running;
        }

        void GLFWWindow::VClose()
        {
            glfwTerminate();
            m_running = false;
        }

        void GLFWWindow::VSwapBuffers()
        {
  //          glfwSwapBuffers(m_handle);
        }
    }

}
