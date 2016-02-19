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

#ifdef HT_SYS_WINDOWS
#include <ht_d3d11renderer.h>
#include <ht_d3d12renderer.h>
#endif

#include <ht_glrenderer.h>
#include <ht_vkrenderer.h>

namespace Hatchit {

    namespace Game {

        using namespace Graphics;

        bool Renderer::Initialize(const RendererParams& params)
        {
            Renderer& _instance = Renderer::instance();
           

#ifdef HT_SYS_LINUX
            if (params.renderer == RendererType::OPENGL)
                _instance.m_renderer = new GLRenderer;
            else if (params.renderer == RendererType::VULKAN)
                _instance.m_renderer = new VKRenderer;
            else
                _instance.m_renderer = nullptr;
#else
            if (params.renderer == RendererType::DIRECTX11)
                _instance.m_renderer = new DirectX::D3D11Renderer;
            else if (params.renderer == RendererType::DIRECTX12)
                _instance.m_renderer = new DirectX::D3D12Renderer;
			else if (params.renderer == RendererType::OPENGL)
				_instance.m_renderer = new OpenGL::GLRenderer;
            else if (params.renderer == RendererType::VULKAN)
                _instance.m_renderer = new Vulkan::VKRenderer;
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
    }

}