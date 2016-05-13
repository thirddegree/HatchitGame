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
#include <ht_path_singleton.h>
#include <ht_window_singleton.h>
#include <ht_renderer_singleton.h>
#include <ht_time_singleton.h>
#include <ht_input_singleton.h>
#include <ht_scenemanager_singleton.h>
#include <ht_audioemitter_singleton.h>

namespace Hatchit {

  namespace Game {

        using namespace Graphics;

        Application::Application(Core::INISettings* settings)
        {
            m_settings = settings;
        }

        int Application::Run()
        {
            if (!Initialize())
            {
                DeInitialize();
                return -1;
            }

            Time::Start();
            while (Window::IsRunning())
            {
                Time::Tick();

                Window::PollEvents();

                SceneManager::Update();

                Renderer::Render();

                Renderer::Present();

                Window::SwapBuffers();

                Time::CalculateFPS();

                Input::Update();
            }

            DeInitialize();

            return 0;
        }

        bool Application::Initialize()
        {
            /*Initialize path manager*/
            Core::Path::Initialize(*m_settings);

            /*Initialize Window with values from settings file*/
            WindowParams wparams;
            try
            {
                wparams.title = m_settings->GetValue<std::string>("WINDOW", "sTitle");
            }
            catch (const std::invalid_argument& e)
            {
                HT_ERROR_PRINTF("Error loading INI File: %s\n", e.what());
                wparams.title = "Hatchit Engine";
            }

            try
            {
                wparams.x = m_settings->GetValue<int>("WINDOW", "iX");
                wparams.y = m_settings->GetValue<int>("WINDOW", "iY");
                wparams.width = m_settings->GetValue<int>("WINDOW", "iWidth");
                wparams.height = m_settings->GetValue<int>("WINDOW", "iHeight");
            }
            catch (const std::invalid_argument& e)
            {
                HT_ERROR_PRINTF("Error loading INI File: %s\n", e.what());
                wparams.x = -1;
                wparams.y = -1;
                wparams.width = 800;
                wparams.height = 600;
            }

            try
            {
                wparams.displayFPS = m_settings->GetValue<bool>("WINDOW", "bFPS");
                wparams.displayMouse = m_settings->GetValue<bool>("WINDOW", "bMouse");
                wparams.debugWindowEvents = m_settings->GetValue<bool>("WINDOW", "bDebugWindowEvents");
            }
            catch (const std::invalid_argument& e)
            {
                HT_ERROR_PRINTF("Error Loading INI File: %s\n", e.what());
                
                wparams.displayFPS = true;
                wparams.displayMouse = true;
                wparams.debugWindowEvents = false;
            }


            /*Initialize Renderer with values from settings file*/
            RendererParams rparams;
            
            std::string renderer;

            try
            {
                renderer = m_settings->GetValue<std::string>("RENDERER", "sRenderer");
            }
            catch (const std::invalid_argument& e)
            {
                HT_ERROR_PRINTF("Error Loading INI File: %s\n", e.what());
                renderer = "DIRECTX12";
            }

#ifdef HT_SYS_LINUX
            if(renderer == "OPENGL")
                rparams.renderer = RendererType::OPENGL;
            else if(renderer == "VULKAN")
                rparams.renderer = RendererType::VULKAN;
#else
            if (renderer == "DIRECTX11")
                rparams.renderer = RendererType::DIRECTX11;
            else if (renderer == "DIRECTX12")
                rparams.renderer = RendererType::DIRECTX12;
            else if (renderer == "VULKAN")
                rparams.renderer = RendererType::VULKAN;
            else if (renderer == "OPENGL")
                rparams.renderer = RendererType::OPENGL;
#endif
            wparams.renderer = rparams.renderer;

            if (!Window::Initialize(wparams))
                return false;

            try
            {
                rparams.validate = m_settings->GetValue<bool>("RENDERER", "bValidate");
            }
            catch (const std::invalid_argument& e)
            {
                HT_ERROR_PRINTF("Error loading INI File: %s\n", e.what());
                rparams.validate = false;
            }

            rparams.window = Window::NativeWindowHandle();
            rparams.viewportWidth = wparams.width;
            rparams.viewportHeight = wparams.height;
            rparams.display = Window::NativeDisplayHandle();

            try
            {
                rparams.clearColor = Color(m_settings->GetValue<float>("RENDERER", "fClearR"),
                    m_settings->GetValue<float>("RENDERER", "fClearG"),
                    m_settings->GetValue<float>("RENDERER", "fClearB"),
                    m_settings->GetValue<float>("RENDERER", "fClearA"));
            }
            catch (const std::invalid_argument& e)
            {
                HT_ERROR_PRINTF("Error loading INI file: %s\n", e.what());
                rparams.clearColor = Color(0.0f, 0.0f, 0.0f, 0.0f);
            }

            if (!Renderer::Initialize(rparams))
                return false;

            if (!AudioEmitter::Initialize())
                return false;

            Input::Initialize();

            if (!SceneManager::Initialize())
                return false;

            SceneManager::LoadScene("testscene.json");

            return true;
        }

        void Application::DeInitialize()
        {
            SceneManager::Deinitialize();
            Input::DeInitialize();
            Renderer::DeInitialize();
            Window::DeInitialize();
            Core::Path::DeInitialize();
        }
  }

}
