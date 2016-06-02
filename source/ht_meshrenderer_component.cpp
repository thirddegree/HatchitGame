/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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
#include <ht_vkmaterial.h>
#include <ht_vkmesh.h>
#else
//#include <ht_d3d12material.h>
#endif

#include <ht_meshrenderer_component.h>
#include <ht_shadervariablechunk.h>
#include <ht_renderer_singleton.h>
#include <ht_debug.h>
#include <ht_gameobject.h>

#include <ht_gpuresourcepool.h>

namespace Hatchit {

    namespace Game {

     
        MeshRenderer::MeshRenderer()
        {
            m_meshRenderer = new Graphics::MeshRenderer(Renderer::GetRenderer());
        }

        Core::JSON MeshRenderer::VSerialize(void)
        {
            return Core::JSON();
        }



        bool MeshRenderer::VDeserialize(const Core::JSON& jsonObject)
        {
            using namespace Graphics;

            std::string materialFile;
            std::string meshFile;
            //attempt to read all data from json object, if it fails, return false
            if (!(Core::JsonExtract<std::string>(jsonObject, "Material", materialFile)
                && Core::JsonExtract<std::string>(jsonObject, "Mesh", meshFile)))
            {
                return false;
            }
            
            MaterialHandle material = Material::GetHandle(materialFile, materialFile);

            //all data has been successfully parsed, attempt to set it all up...

            //get appropriate resource handles
            Graphics::MeshHandle mesh;
            Graphics::MaterialHandle mat;

            //auto rendererType = Renderer::GetRendererType();
            //switch (rendererType)
            //{
            //    case Graphics::DIRECTX12:
            //    {
            //        //mat = Graphics::DX::D3D12Material::GetHandle(material);
            //    } return false;

            //    case Graphics::VULKAN:
            //    {
            //        Graphics::Vulkan::VKRenderer* renderer = dynamic_cast<Graphics::Vulkan::VKRenderer*>(Renderer::instance().GetRenderer());
                    mesh = Graphics::Mesh::GetHandle(meshFile, meshFile);
                    mat = Graphics::Material::GetHandle(materialFile, materialFile);
            //    } break;

            //    default:
            //        return false;
            //}
            //
            SetRenderable(mesh, mat);



            //setup instance data
            Resource::Matrix4Variable* temp = new Resource::Matrix4Variable(Math::Matrix4());
            std::vector<Resource::ShaderVariable*> variables;
            variables.push_back(temp);
            m_instanceData = new ShaderVariableChunk(variables);
            delete temp;



            return true;
        }

        void MeshRenderer::SetRenderable(Graphics::MeshHandle mesh,
            Graphics::MaterialHandle material)
        {
            m_meshRenderer->SetMesh(mesh);
            m_meshRenderer->SetMaterial(material);
        }

        void MeshRenderer::VOnInit()
        {
            //Graphics::RendererType rendererType = Renderer::GetRendererType();
            //m_meshRenderer = new Graphics::MeshRenderer();

            HT_DEBUG_PRINTF("Initialized Mesh Renderer Component.\n");
        }

        void MeshRenderer::VOnUpdate()
        {
            //TODO: send actual transform data
            m_instanceData->SetMatrix4(0, Hatchit::Math::MMMatrixTranspose(*m_owner->GetTransform().GetWorldMatrix()));
            m_meshRenderer->SetInstanceData(m_instanceData);
            m_meshRenderer->Render();
        }

        Component* MeshRenderer::VClone(void) const
        {
            HT_DEBUG_PRINTF("Cloned MeshRenderer.\n");
            return new MeshRenderer(*this);
        }

        /**
        * \brief Retrieves the id associated with this class of Component.
        * \return The Core::Guid associated with this Component type.
        * \sa Component(), GameObject()
        */
        Core::Guid MeshRenderer::VGetComponentId(void) const
        {
            return Component::GetComponentId<MeshRenderer>();
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
            delete m_meshRenderer;
            HT_DEBUG_PRINTF("Destroyed MeshRenderer Component.\n");
        }

    }

}
