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
#include <ht_dxrenderer.h>
#endif
#include <ht_glrenderer.h>

namespace Hatchit {

    namespace Game {

        using namespace Graphics;

        bool Renderer::Initialize(const RendererParams& params)
        {
            Renderer& _instance = Renderer::instance();

#ifdef HT_SYS_LINUX
            _instance.m_renderer = new GLRenderer;
#else
            if (params.renderer == RendererType::DIRECTX)
                _instance.m_renderer = new DXRenderer;
            else
                _instance.m_renderer = new GLRenderer;
#endif
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