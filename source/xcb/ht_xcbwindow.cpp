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

#include <ht_xcbwindow.h>
#include <ht_debug.h>
#include <ht_time_singleton.h>

namespace Hatchit{

    namespace Game{

        XCBWindow::XCBWindow(const WindowParams& params)
        {
            m_params = params;
            m_connection = nullptr;
            m_window = 0;
            m_nativeWindowHandle = nullptr;
            m_nativeDisplayHandle = nullptr;
        }

        XCBWindow::~XCBWindow()
        {
            if(m_connection != nullptr)
            {
                xcb_destroy_window(m_connection, m_window);
                xcb_disconnect(m_connection);
            }
        }

        bool XCBWindow::VInitialize()
        {
            const xcb_setup_t* setup;
            xcb_screen_iterator_t it;
            int src;

            //Connect to X11
            m_connection = xcb_connect(nullptr, &src);
            if(m_connection == nullptr)
            {
#ifdef _DEBUG
                Core::DebugPrintF("Failed to connect XCB to X11 Server. Exiting.\n");
#endif
                return false;
            }

            setup = xcb_get_setup(m_connection);
            it = xcb_setup_roots_iterator(setup);
        
            while(src-- > 0)
                xcb_screen_next(&it);

            m_screen = it.data;


            //Hook connection to window
    
            uint32_t value_mask, value_list[32];

            m_window = xcb_generate_id(m_connection);

            value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
            value_list[0] = m_screen->black_pixel;
            value_list[1] = 
                XCB_EVENT_MASK_KEY_RELEASE |
                XCB_EVENT_MASK_EXPOSURE |
                XCB_EVENT_MASK_STRUCTURE_NOTIFY |
                XCB_EVENT_MASK_POINTER_MOTION |
                XCB_EVENT_MASK_BUTTON_PRESS |
                XCB_EVENT_MASK_BUTTON_RELEASE;

            xcb_create_window(m_connection,
                XCB_COPY_FROM_PARENT,
                m_window, m_screen->root,
                0, 0, m_params.width, m_params.height, 0,
                XCB_WINDOW_CLASS_INPUT_OUTPUT,
                m_screen->root_visual,
                value_mask, value_list);

            /* Magic code that will send notification when window is destroyed */
            xcb_intern_atom_cookie_t cookie = xcb_intern_atom(m_connection, 1, 12, "WM_PROTOCOLS");
            xcb_intern_atom_reply_t* reply = xcb_intern_atom_reply(m_connection, cookie, 0);

            xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(m_connection, 0, 16, "WM_DELETE_WINDOW");
            m_atomDeleteWindow = xcb_intern_atom_reply(m_connection, cookie2, 0);

            xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE,
                m_window, (*reply).atom, 4, 32, 1,
                &(*m_atomDeleteWindow).atom);

            xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE,
                m_window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
                m_params.title.size(), m_params.title.c_str());

            free(reply);

            xcb_map_window(m_connection, m_window);

            xcb_flush(m_connection);

            m_nativeWindowHandle = &m_window;
            m_nativeDisplayHandle = m_connection;
            
            m_running = true;
            return true;
        }

        void XCBWindow::VPollEvents()
        {
            xcb_generic_event_t* event;
            event = xcb_poll_for_event(m_connection);
            
            if(event != nullptr)
            {
                //TODO: Debug window events               
                switch (event->response_type & 0x7f)
                {
                    case XCB_CLIENT_MESSAGE:
                        if ((*(xcb_client_message_event_t*)event).data.data32[0] ==
                            (*m_atomDeleteWindow).atom)
                            m_running = false;
                        break;
                    default:
                    break;
                }
                 
                free(event);
            }

            if(m_params.displayFPS)
            {
                std::string title = m_params.title + "FSP: " + std::to_string((int) Time::FramesPerSecond());

                xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE,
                    m_window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, 
                    title.length(), title.c_str());

                xcb_flush(m_connection);
            }
            
        }

        void* XCBWindow::VNativeWindowHandle()
        {
            return m_nativeWindowHandle;
        }

        void* XCBWindow::VNativeDisplayHandle()
        {
            return m_nativeDisplayHandle;
        }

        bool XCBWindow::VIsRunning()
        {
            return m_running;
        }

        void XCBWindow::VClose()
        {
            m_running = false;
            
            if(m_connection != nullptr)
            {
                xcb_destroy_window(m_connection, m_window);
                xcb_disconnect(m_connection);
            } 
        }

        void XCBWindow::VSwapBuffers()
        {
            //Do nothing; Vulkan will swap buffers
            //TODO: Swap GL context if GL is ever supported
        }

    }
}

