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
#ifdef VK_SUPPORT
#include <ht_vkmaterial.h>
#include <ht_vkmesh.h>
#include <ht_vkmaterial.h>
#include <ht_vkmesh.h>
#endif
#else
//#include <ht_d3d12material.h>
#include <ht_vkmaterial.h>
#include <ht_vkmesh.h>
#endif

#include <ht_meshrenderer_component.h>
#include <ht_renderer_singleton.h>
#include <ht_debug.h>
#include <ht_gameobject.h>

namespace Hatchit {

    namespace Game {

     
        MeshRenderer::MeshRenderer()
        {
            m_meshRenderer = new Graphics::MeshRenderer();
            m_worldMatrix = new Resource::Matrix4Variable();
        }

        Core::JSON MeshRenderer::VSerialize(void)
        {
            return Core::JSON();
        }



        bool MeshRenderer::VDeserialize(const Core::JSON& jsonObject)
        {
            std::string materialFile;
            std::string meshFile;
            //attempt to read all data from json object, if it fails, return false
            if (!(Core::JsonExtract<std::string>(jsonObject, "Material", materialFile)
                && Core::JsonExtract<std::string>(jsonObject, "Mesh", meshFile)))
            {
                return false;
            }
            //all data has been successfully parsed, attempt to set it all up...

            //get appropriate resource handles
            Graphics::IMeshHandle mesh;
            Graphics::IMaterialHandle mat;

#ifdef HT_SYS_LINUX
            if (Renderer::GetRendererType() == Graphics::OPENGL)
                return false;
#ifdef VK_SUPPORT
            else if (Renderer::GetRendererType() == Graphics::VULKAN)
                mat = Graphics::Vulkan::VKMaterial::GetHandle(materialFile, materialFile).StaticCastHandle<Graphics::IMaterial>();
#endif
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
                mesh = Graphics::Vulkan::VKMesh::GetHandle(meshFile, meshes[0]).StaticCastHandle<Graphics::IMesh>();

                mat = Graphics::Vulkan::VKMaterial::GetHandle(materialFile, materialFile).StaticCastHandle<Graphics::IMaterial>();

                
            }
            else if (Renderer::GetRendererType() == Graphics::OPENGL)
                return false;
#endif
            SetRenderable(mesh, mat);

            return true;
        }





        void MeshRenderer::SetRenderable(Graphics::IMeshHandle mesh,
            Graphics::IMaterialHandle material)
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
            m_worldMatrix->SetData(Hatchit::Math::MMMatrixTranspose(*m_owner->GetTransform().GetWorldMatrix()));

            std::vector<Resource::ShaderVariable*> data;
            data.push_back(m_worldMatrix);

            m_meshRenderer->SetInstanceData(data);
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
            delete m_meshRenderer;
            HT_DEBUG_PRINTF("Destroyed MeshRenderer Component.\n");
        }

    }

}
