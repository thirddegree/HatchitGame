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
#include <ht_renderer_singleton.h>
#include <ht_time_singleton.h>

namespace Hatchit {

  namespace Game {

        using namespace Graphics;

        Application::Application(Core::INIReader* settings)
        {
            m_settings = settings;
        }

        int Application::Run()
        {
            /*Initialize Window with values from settings file*/
            WindowParams wparams;
            wparams.title = m_settings->GetValue("WINDOW", "sTitle", std::string("Hatchit Engine"));
            wparams.x = m_settings->GetValue("WINDOW", "iX", -1);
            wparams.y = m_settings->GetValue("WINDOW", "iY", -1);
            wparams.width = m_settings->GetValue("WINDOW", "iWidth", 800);
            wparams.height = m_settings->GetValue("WINDOW", "iHeight", 600);
            if (!Window::Initialize(wparams))
            {
#ifdef _DEBUG
                Core::DebugPrintF("Game Error: Failed to initialize Window. Exiting.\n");
#endif
                return -1;
            }

            /*Initialize Renderer with values from settings file*/
            RendererParams rparams;
#ifdef HT_SYS_LINUX
            rparams.renderer = RendererType::OPENGL;
#else
            std::string rendererStr = m_settings->GetValue("RENDERER", "sRenderer", std::string("DIRECTX"));
            rparams.renderer = (rendererStr == "DIRECTX") ? RendererType::DIRECTX : RendererType::OPENGL;
#endif
            rparams.window = Window::NativeHandle();
            if (!Renderer::Initialize(rparams))
            {
#ifdef _DEBUG
                Core::DebugPrintF("Game Error: Failed to initialize Renderer. Exiting.\n");
#endif
                Window::DeInitialize();
                Renderer::DeInitialize();
                return -1;
            }

            Renderer::SetClearColor(Colors::CornflowerBlue);

            Time::Start();
            while (Window::IsRunning())
            {
                Time::Tick();

                Window::PollEvents();

                Renderer::ClearBuffer(ClearArgs::ColorDepthStencil);

                Renderer::Present();

                Window::SwapBuffers();

                Time::CalculateFPS();
            }

            Renderer::DeInitialize();
            Window::DeInitialize();

            return 0;
        }
  }

}
