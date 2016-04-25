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

#ifdef HT_SYS_LINUX
#include <ht_vkmaterial.h>
#include <ht_vkmesh.h>
#else
//#include <ht_d3d12material.h>
#include <ht_vkmaterial.h>
#include <ht_vkmesh.h>
#endif
#include <ht_gameobject.h>
#include <ht_model.h>
#include <ht_light_component.h>
#include <ht_renderer_singleton.h>
#include <ht_debug.h>

namespace Hatchit {

    namespace Game {

        LightComponent::LightComponent()
        {

        }

        Core::JSON LightComponent::VSerialize(void)
        {
            return Core::JSON();
        }

        bool LightComponent::VDeserialize(const Core::JSON& jsonObject)
        {
            int lightType;
            if (Core::JsonExtract<int32_t>(jsonObject, "LightType", lightType)) 
            {
                if (lightType == LightType::POINT_LIGHT)
                {
                    std::vector<float> attenuation;
                    std::vector<float> color;
                    if (!Core::JsonExtract<float>(jsonObject, "Radius", m_radius) 
                        || !Core::JsonExtractContainer(jsonObject, "Attenuation", attenuation)
                        || !Core::JsonExtractContainer(jsonObject, "Color", color))
                        return false;
                    m_attenuation = { attenuation[0], attenuation[1], attenuation[2] };
                    m_color = { color[0], color[1], color[2], color[3] };
                }
                m_lightType = LightType(lightType);
            }
            return true;
        }

        void LightComponent::SetType(LightType lightType)
        {
            m_lightType = lightType;
            switch (lightType)
            {
                case LightType::POINT_LIGHT:
                {
                    SetMeshAndMaterial("Icosphere.dae", "PointLightMaterial.json");
                    break;
                }
            }
            m_meshRenderer->SetMesh(m_mesh);
            m_meshRenderer->SetMaterial(m_material);
        }

        void LightComponent::VOnInit()
        {
            m_meshRenderer = new Graphics::MeshRenderer();

            SetType(m_lightType);
            
            HT_DEBUG_PRINTF("Initialized Light Component.\n");
        }

        void LightComponent::VOnUpdate()
        {
            std::vector<Resource::ShaderVariable*> data;

            //this will need to use the Object's transform, but it currently does not read in correctly
            data.push_back(new Resource::Matrix4Variable(Math::MMMatrixTranspose(Math::MMMatrixTranslation(Math::Vector3(-1, 5, 1)))));

            data.push_back(new Resource::Float4Variable(m_color));
            data.push_back(new Resource::FloatVariable(m_radius));
            data.push_back(new Resource::Float3Variable(m_attenuation));

            m_meshRenderer->SetInstanceData(data);
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

        bool LightComponent::SetMeshAndMaterial(std::string meshFile, std::string materialFile)
        {
#ifdef HT_SYS_LINUX
            if (renderer == "OPENGL")
                return false;
            else if (renderer == "VULKAN")
                mat = Graphics::Vulkan::VKMaterial::GetHandle(materialFile, materialFile).StaticCastHandle<Graphics::IMaterial>();
#else
            if (Renderer::GetRendererType() == Graphics::DIRECTX11)
                return false;
            else if (Renderer::GetRendererType() == Graphics::DIRECTX12)
                //mat = Graphics::DX::D3D12Material::GetHandle(material);
                return false;
            else if (Renderer::GetRendererType() == Graphics::VULKAN)
            {
                Resource::ModelHandle model = Resource::Model::GetHandleFromFileName(meshFile);
                std::vector<Resource::Mesh*> meshes = model->GetMeshes();
                m_mesh = Graphics::Vulkan::VKMesh::GetHandle(meshFile, meshes[0]).StaticCastHandle<Graphics::IMesh>();

                m_material = Graphics::Vulkan::VKMaterial::GetHandle(materialFile, materialFile).StaticCastHandle<Graphics::IMaterial>();
            }
            else if (Renderer::GetRendererType() == Graphics::OPENGL)
                return false;
#endif      
            return true;
        }
    }
}
