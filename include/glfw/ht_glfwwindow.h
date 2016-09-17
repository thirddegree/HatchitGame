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
#include <ht_vulkan.h>
#include <GLFW/glfw3.h>

namespace Hatchit {

    namespace Game {

        /**
        * @brief struct defining various window parameters
        */
        struct WindowParams
        {
            std::string title;
            int x;
            int y;
            int width;
            int height;
            bool displayFPS;
            bool displayMouse;
            bool debugWindowEvents;
        };

        class HT_API GLFWWindow
        {
        public:
            GLFWWindow(const WindowParams& params);

            ~GLFWWindow();

            bool    Initialize();

            void*   NativeWindowHandle();

    	    void*   NativeDisplayHandle();            

            bool    IsRunning();

            void    PollEvents();

            void    Close();

            void    SwapBuffers();

            VkSurfaceKHR Surface();

        private:
            GLFWwindow*         m_handle;
            void*               m_nativeWindowHandle;
            void*               m_nativeDisplayHandle;
            

            VkSurfaceKHR        m_surface;
            WindowParams        m_params;
        };

    }

}
