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

#include <ht_light_component.h>

#include <ht_renderer_singleton.h>
#include <ht_debug.h>

namespace Hatchit {

    namespace Game {

        LightComponent::LightComponent()
        {

        }

        void LightComponent::SetType(LightType lightType)
        {
            m_lightType = lightType;
            switch (lightType)
            {
                case LightType::SPOT_LIGHT:
                {
                    //m_meshRenderer->SetMesh(mesh);
                    //m_meshRenderer->SetMaterial(material);
                    //m_meshRenderer->SetRenderPass(renderPass);
                    break;
                }
            }
        }

        void LightComponent::VOnInit()
        {

            m_pointLightModel = Resource::Model::GetHandleFromFileName("IcoSphere.dae");

            Graphics::RendererType rendererType = Renderer::GetRendererType();
            m_meshRenderer = new Graphics::MeshRenderer();
            
            HT_DEBUG_PRINTF("Initialized Light Component.\n");
        }

        void LightComponent::VOnUpdate()
        {
            HT_DEBUG_PRINTF("Updated Light Component.\n");
            m_meshRenderer->Render();
        }

        Component* LightComponent::VClone(void) const
        {
            HT_DEBUG_PRINTF("Cloned LightComponent.\n");
            return new LightComponent(*this);
        }

        void LightComponent::VOnEnabled()
        {
            HT_DEBUG_PRINTF("Enabled LightComponent Component.\n");
        }

        void LightComponent::VOnDisabled()
        {
            HT_DEBUG_PRINTF("Disabled LightComponent Component.\n");
        }

        void LightComponent::VOnDestroy()
        {
            delete m_meshRenderer;
            HT_DEBUG_PRINTF("Destroyed LightComponent Component.\n");
        }
    }
}