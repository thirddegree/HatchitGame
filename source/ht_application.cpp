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

#include <ht_application.h>
#include <ht_debug.h>
#include <ht_window_singleton.h>
#include <ht_time_singleton.h>

namespace Hatchit {

  namespace Game {

        Application::Application(Core::INIReader* settings)
        {
            m_settings = settings;
        }

        int Application::Run()
        {
            /*Initialize Window with values from settings file*/
            WindowParams params;
            params.title = m_settings->GetValue("WINDOW", "sTitle", std::string("Hatchit Engine"));
            params.x = m_settings->GetValue("WINDOW", "iX", -1);
            params.y = m_settings->GetValue("WINDOW", "iY", -1);
            params.width = m_settings->GetValue("WINDOW", "iWidth", 800);
            params.height = m_settings->GetValue("WINDOW", "iHeight", 600);
            if (!Window::Initialize(params))
            {
#ifdef _DEBUG
                Core::DebugPrintF("Game Error: Failed to initialize Window. Exiting.\n");
#endif
                return -1;
            }

            Time::Start();
            while (Window::IsRunning())
            {
                Time::Tick();

                Window::PollEvents();

                Window::SwapBuffers();

                Time::CalculateFPS();
            }

            return 0;
        }
  }

}
