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

#include <ht_meshrenderer_component.h>
#include <ht_renderer_singleton.h>
#include <ht_debug.h>

namespace Hatchit {

    namespace Game {

        using namespace Graphics;

        MeshRenderer::MeshRenderer()
        {
        }

        void MeshRenderer::SetRenderable(Graphics::IMesh * mesh,
            Graphics::IMaterialHandle material,
            Graphics::IRenderPass* renderPass)
        {
            m_meshRenderer->VSetMesh(mesh);
            m_meshRenderer->VSetMaterial(material);
            m_meshRenderer->VSetRenderPass(renderPass);
        }

        void MeshRenderer::VOnInit()
        {
            RendererType rendererType = Renderer::GetRendererType();
            switch (rendererType)
            {
#ifdef HT_SYS_WINDOWS
#ifdef DX11_SUPPORT
            case Hatchit::Graphics::DIRECTX11:
                m_meshRenderer = new DX::DX11MeshRenderer();
                break;
#endif
#ifdef DX12_SUPPORT
            case Hatchit::Graphics::DIRECTX12:
                m_meshRenderer = new DX::D3D12MeshRenderer();
                break;
#endif
#endif
#ifdef GL_SUPPORT
            case Hatchit::Graphics::OPENGL:
//                m_meshRenderer = new GL::GLMeshRenderer();
                break;
#endif
#ifdef VK_SUPPORT
            case Hatchit::Graphics::VULKAN:
                m_meshRenderer = new Vulkan::VKMeshRenderer();
                break;
#endif
            }

            HT_DEBUG_PRINTF("Initialized Mesh Renderer Component.\n");
        }

        void MeshRenderer::VOnUpdate()
        {
            HT_DEBUG_PRINTF("Updated MeshRenderer Component.\n");
            m_meshRenderer->VRender();
        }

        void MeshRenderer::VOnEnabled()
        {
            HT_DEBUG_PRINTF("Enabled MeshRenderer Component.\n");
        }

        void MeshRenderer::VOnDisabled()
        {
            HT_DEBUG_PRINTF("Disabled MeshRenderer Component.\n");
        }

        void MeshRenderer::VOnDestroy()
        {
            HT_DEBUG_PRINTF("Destroyed Test Component.\n");
        }

    }

}
