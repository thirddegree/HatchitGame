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

#include <ht_window.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

namespace Hatchit {

    namespace Game {

        class HT_API XCBWindow : public IWindow
        {
        public:
            XCBWindow(const WindowParams& params); 
            
            ~XCBWindow();
        
            bool    VInitialize()           override;

            void*   VNativeWindowHandle()   override;
            
            void*   VNativeDisplayHandle()  override;

            bool    VIsRunning()            override;

            void    VPollEvents()           override;

            void    VClose()                override;

            void    VSwapBuffers()          override;

        private:
            xcb_connection_t*           m_connection;
            xcb_screen_t*               m_screen;
            xcb_screen_iterator_t       m_iter;
            uint32_t                    m_window;
            xcb_intern_atom_reply_t*    m_atomDeleteWindow; 
        };


    }

}
