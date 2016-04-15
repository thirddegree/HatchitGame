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

     
        MeshRenderer::MeshRenderer()
        {
        }

        Core::JSON MeshRenderer::VSerialize(void)
        {
            return Core::JSON();
        }

        bool MeshRenderer::VDeserialize(Core::JSON& jsonObject)
        {
            std::string material;
            /*if (JsonExtractString(jsonObject, "Material", material)) 
            {
            }*/
            return false;
        }

        void MeshRenderer::SetRenderable(Graphics::IMeshHandle mesh,
            Graphics::IMaterialHandle material,
            Graphics::IRenderPassHandle renderPass)
        {
            m_meshRenderer->SetMesh(mesh);
            m_meshRenderer->SetMaterial(material);
            m_meshRenderer->SetRenderPass(renderPass);
        }

        void MeshRenderer::VOnInit()
        {
            Graphics::RendererType rendererType = Renderer::GetRendererType();
            m_meshRenderer = new Graphics::MeshRenderer();

            HT_DEBUG_PRINTF("Initialized Mesh Renderer Component.\n");
        }

        void MeshRenderer::VOnUpdate()
        {
            HT_DEBUG_PRINTF("Updated MeshRenderer Component.\n");
            m_meshRenderer->Render();
        }

        Component* MeshRenderer::VClone(void) const
        {
            HT_DEBUG_PRINTF("Cloned MeshRenderer.\n");
            return new MeshRenderer(*this);
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
            HT_DEBUG_PRINTF("Destroyed MeshRenderer Component.\n");
        }

    }

}
