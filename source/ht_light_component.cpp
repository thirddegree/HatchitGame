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

#ifdef VK_SUPPORT
#include <ht_vkmaterial.h>
#include <ht_vkmesh.h>
#endif

#ifdef HT_SYS_WINDOWS
#ifdef DX12_SUPPORT
#include <ht_d3d12material.h>
#endif
#endif

#include <unordered_map>
#include <ht_gameobject.h>
#include <ht_light_component.h>
#include <ht_shadervariablechunk.h>
#include <ht_renderer_singleton.h>
#include <ht_debug.h>

namespace Hatchit {

    namespace Game {

        LightComponent::LightComponent()
        {

        }

        /**
        * \brief Saves light as JSON.
        */
        Core::JSON LightComponent::VSerialize(void)
        {
            return Core::JSON();
        }

        /**
        * \brief Constructs light from JSON.
        */
        bool LightComponent::VDeserialize(const Core::JSON& jsonObject)
        {
            int lightType;
            if (Core::JsonExtract<int32_t>(jsonObject, "LightType", lightType)) 
            {
                if (lightType == LightType::POINT_LIGHT)
                {
                    if (!Core::JsonExtract<float>(jsonObject, "Radius", m_radius))
                        return false;

                    Core::JSON attenuationJSON = jsonObject["Attenuation"];
                    if (attenuationJSON.size() <= 0)
                        return false;

                    for (size_t i = 0; i < attenuationJSON.size(); i++)
                        m_attenuation[i] = attenuationJSON[i];
                    
                    Core::JSON colorJSON = jsonObject["Color"];
                    if (colorJSON.size() <= 0)
                        return false;

                    for (size_t i = 0; i < colorJSON.size(); i++)
                        m_color[i] = colorJSON[i];

                }
                m_lightType = LightType(lightType);
            }

            return true;
        }

        /**
        * \brief Sets the light to the specified type with proper data.
        * \param lightType enum value of light
        */
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

        /**
        * \brief Called when the GameObject is created to initialize all values
        */
        void LightComponent::VOnInit()
        {
            m_meshRenderer = new Graphics::MeshRenderer(Renderer::GetRenderer());

            std::vector<Resource::ShaderVariable*> variables;
            Resource::Matrix4Variable* transform = new Resource::Matrix4Variable(Math::Matrix4());
            Resource::Float4Variable* color = new Resource::Float4Variable(m_color);
            Resource::FloatVariable* radius = new Resource::FloatVariable(m_radius);
            Resource::Float3Variable* atten = new Resource::Float3Variable(m_attenuation);

            variables.push_back(transform);
            variables.push_back(color);
            variables.push_back(radius);
            variables.push_back(atten);

            m_data = new Graphics::ShaderVariableChunk(variables);

            delete transform, color, radius, atten;

            SetType(m_lightType);
            
            HT_DEBUG_PRINTF("Initialized Light Component.\n");
        }

        /**
        * \brief Called once per frame while the GameObject is enabled.
        * Updates all components first, then all child gameobjects.
        */
        void LightComponent::VOnUpdate()
        {
            //0 is the beginning of the instance data array
            m_data->SetMatrix4(0, Hatchit::Math::MMMatrixTranspose(*m_owner->GetTransform().GetWorldMatrix()));
            m_meshRenderer->SetInstanceData(m_data);
            m_meshRenderer->Render();
        }

        /**
        * \brief Creates a copy of this Component.
        */
        Component* LightComponent::VClone(void) const
        {
            HT_DEBUG_PRINTF("Cloned LightComponent.\n");
            return new LightComponent(*this);
        }

        /**
        * \brief Called when the Component is enabled.
        * This happens when a scene has finished loading, or immediately after creation if the scene is already loaded.
        */
        void LightComponent::VOnEnabled()
        {
            HT_DEBUG_PRINTF("Enabled LightComponent Component.\n");
        }

        /**
        * \brief Called when the Component is disabled.
        * Components are always disabled before destroyed.
        * When a scene is destroyed, all Components are disabled before any are destroyed.
        */
        void LightComponent::VOnDisabled()
        {
            HT_DEBUG_PRINTF("Disabled LightComponent Component.\n");
        }

        /**
        * \brief Called when the GameObject is destroyed/deleted.
        * Objects are always disabled before destroyed.
        * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
        */
        void LightComponent::VOnDestroy()
        {
            delete m_meshRenderer;
            HT_DEBUG_PRINTF("Destroyed LightComponent Component.\n");
        }

        /**
        * \brief Sets the light mesh with the appropriate type for current renderer.
        * \param meshFile File name of mesh to load
        * \param meshFile File name of material to load
        */
        bool LightComponent::SetMeshAndMaterial(std::string meshFile, std::string materialFile)
        {
            m_mesh = Graphics::Mesh::GetHandle(meshFile, meshFile);
            m_material = Graphics::Material::GetHandle(materialFile, materialFile);

            return true;
        }
    }
}
