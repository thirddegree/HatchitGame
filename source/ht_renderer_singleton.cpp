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

#include <ht_renderer_singleton.h>
#include <ht_time_singleton.h>
#include <ht_debug.h>
#ifdef HT_SYS_WINDOWS
#ifdef DX11_SUPPORT
#include <ht_d3d11renderer.h>
#endif
#ifdef DX12_SUPPORT
#include <ht_d3d12renderer.h>
#endif
#endif

#ifdef GL_SUPPORT
#include <ht_glrenderer.h>
#endif

#ifdef VK_SUPPORT
#include <ht_vkrenderer.h>
#endif

#include <ht_time_singleton.h>

namespace Hatchit {

    namespace Game {

        using namespace Graphics;

        bool Renderer::Initialize(const RendererParams& params)
        {
            Renderer& _instance = Renderer::instance();
            _instance.m_rendererType = params.renderer;

#ifdef HT_SYS_LINUX
            if (params.renderer == RendererType::OPENGL)
	    {            
#ifdef GL_SUPPORT
    		_instance.m_renderer = new OpenGL::GLRenderer;
#endif
	    }
	    else if (params.renderer == RendererType::VULKAN)
	    {
#ifdef VK_SUPPORT
                _instance.m_renderer = new Vulkan::VKRenderer;
#endif
	    }
	    else
                _instance.m_renderer = nullptr;
#else
            if (params.renderer == RendererType::DIRECTX11)
            {
#ifdef DX11_SUPPORT
                _instance.m_renderer = new DirectX::D3D11Renderer;
#else
                Core::DebugPrintF("DirectX11 Renderer requested when engine not compiled with DirectX11 support!\n");
                return false;
#endif
            }
            else if (params.renderer == RendererType::DIRECTX12)
            {

#ifdef DX12_SUPPORT
                _instance.m_renderer = new DX::D3D12Renderer;
#else
                Core::DebugPrintF("DirectX12 Renderer requested when engine not compiled with DirectX12 support!\n");
                return false;
#endif
            }
            else if (params.renderer == RendererType::OPENGL)
            {
#ifdef GL_SUPPORT
                _instance.m_renderer = new OpenGL::GLRenderer;
#else
                Core::DebugPrintF("OpenGL Renderer requested when engine not compiled with OpenGL support!\n");
                return false;
#endif
            }
            else if (params.renderer == RendererType::VULKAN)
            {
#ifdef VK_SUPPORT
                _instance.m_renderer = new Vulkan::VKRenderer;
#else
                Core::DebugPrintF("Vulkan Renderer requested when engine not compiled with Vulkan support!\n");
                return false;
#endif
            }
            else
                _instance.m_renderer = nullptr;
#endif
            if (!_instance.m_renderer)
                return false;

            if (!_instance.m_renderer->VInitialize(params))
                return false;

            return true;
        }

        void Renderer::DeInitialize()
        {
            Renderer& _instance = Renderer::instance();

            _instance.m_renderer->VDeInitialize();

            delete _instance.m_renderer;
        }

        void Renderer::SetClearColor(const Color& color)
        {
            Renderer& _instance = Renderer::instance();

            _instance.m_renderer->VSetClearColor(color);
        }

        void Renderer::Render() 
        {
            Renderer& _instance = Renderer::instance();

            _instance.m_renderer->VRender(Time::DeltaTime());
        }

        void Renderer::Present()
        {
            Renderer& _instance = Renderer::instance();

            _instance.m_renderer->VPresent();
        }

        void Renderer::ClearBuffer(ClearArgs args)
        {
            Renderer& _instance = Renderer::instance();

            _instance.m_renderer->VClearBuffer(args);
        }

        void Renderer::ResizeBuffers(uint32_t width, uint32_t height)
        {
            Renderer& _instance = Renderer::instance();

            _instance.m_renderer->VResizeBuffers(width, height);
        }

        RendererType Renderer::GetRendererType()
        {
            Renderer& _instance = Renderer::instance();

            return _instance.m_rendererType;
        }
    }

}
