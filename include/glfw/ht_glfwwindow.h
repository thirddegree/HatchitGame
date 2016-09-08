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
#include <ht_window.h>
#include <GLFW/glfw3.h>

namespace Hatchit {

    namespace Game {

        class HT_API GLFWWindow : public IWindow
        {
        public:
            GLFWWindow(const WindowParams& params);

            ~GLFWWindow();

            bool    VInitialize()             override;

            void*   VNativeWindowHandle()     override;

    	    void*   VNativeDisplayHandle()    override;            

            bool    VIsRunning()              override;

            void    VPollEvents()             override;

            void    VClose()                  override;

            void    VSwapBuffers()            override;

        private:
            GLFWwindow*         m_handle;
            void*               m_nativeWindowHandle;
            void*               m_nativeDisplayHandle;
            WindowParams        m_params;
        };

    }

}
