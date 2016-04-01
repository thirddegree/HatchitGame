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

#pragma once

#include <ht_meshrenderer.h>

#ifdef HT_SYS_WINDOWS
#ifdef DX11_SUPPORT
#include <ht_d3d11meshrenderer.h>
#endif
#ifdef DX12_SUPPORT
#include <ht_d3d12meshrenderer.h>
#endif
#endif

#ifdef GL_SUPPORT
#include <ht_glmeshrenderer.h>
#endif

#ifdef VK_SUPPORT
#include <ht_vkmeshrenderer.h>
#endif

#include <ht_component.h>

namespace Hatchit {

    namespace Game {

        class MeshRenderer : public Component
        {
        public:
            MeshRenderer(void);

            void SetRenderable(Graphics::IMesh* mesh, 
                Graphics::IMaterial* material, 
                Graphics::IRenderPass* renderPass);

            void VOnInit() override;
            void VOnUpdate() override;
            void VOnDestroy() override;

        protected:
            void VOnEnabled() override;
            void VOnDisabled() override;

        private:
            Graphics::IMeshRenderer* m_meshRenderer;
        };

    }

}
