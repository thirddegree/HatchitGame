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

#pragma once

#include <ht_platform.h>
#include <ht_window.h>
#include <ht_sdl.h>


namespace Hatchit {

    namespace Game {

        class HT_API SDLWindow : public IWindow
        {
        public:
            SDLWindow(const WindowParams& params);

            ~SDLWindow();

            bool    VInitialize()             override;

            void*   VNativeWindowHandle()     override;

    	    void*   VNativeDisplayHandle()    override;            

	        bool    VIsRunning()              override;

            void    VPollEvents()             override;

            void    VClose()                  override;

            void    VSwapBuffers()            override;

        private:
            SDL_Window*         m_handle;
            SDL_GLContext       m_glcontext;
        };

    }

}
