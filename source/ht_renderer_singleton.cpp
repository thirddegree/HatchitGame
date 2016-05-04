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

#include <ht_gpuresourcepool.h>

#include <ht_time_singleton.h>

namespace Hatchit {

    namespace Game {

        using namespace Graphics;

        bool Renderer::Initialize(const RendererParams& params)
        {
            Renderer& _instance = Renderer::instance();
            _instance.m_rendererType = params.renderer;
            _instance.m_renderer = new Graphics::Renderer;
            if (!_instance.m_renderer->Initialize(params))
                return false;

            TextureHandle def = Texture::GetHandle("raptor.png", "raptor.png");
            MaterialHandle m = Material::GetHandle("DeferredMaterial.json", "DeferredMaterial.json");
            PipelineHandle pipe = Pipeline::GetHandle("DeferredPipeline.json", "DeferredPipeline.json");

            
            _instance.m_initialized = true;

            return true;
        }

        void Renderer::DeInitialize()
        {
            Renderer& _instance = Renderer::instance();

            if (!_instance.m_initialized)
                return;


            /*Release GPUResourcePool*/
            GPUResourcePool::DeInitialize();

            delete _instance.m_renderer;

            
            _instance.m_initialized = false;
        }

       
        void Renderer::Render()
        {
            Renderer& _instance = Renderer::instance();
            if (!_instance.m_initialized)
                return;

            _instance.m_renderer->Render();
        }

        void Renderer::Present()
        {
            Renderer& _instance = Renderer::instance();
            if (!_instance.m_initialized)
                return;

            _instance.m_renderer->Present();
        }

        void Renderer::ResizeBuffers(uint32_t width, uint32_t height)
        {
            Renderer& _instance = Renderer::instance();
            if (!_instance.m_initialized)
                return;

            _instance.m_renderer->ResizeBuffers(width, height);
        }
        

        RendererType Renderer::GetRendererType()
        {
            Renderer& _instance = Renderer::instance();

            return _instance.m_rendererType;
        }

        Graphics::Renderer* Renderer::GetRenderer()
        {
            return m_renderer;
        }
    }

}
