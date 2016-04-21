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
#include <ht_component.h>

namespace Hatchit {

    namespace Game {

        class MeshRenderer : public Component
        {
        public:
            MeshRenderer(void);

            virtual Core::JSON VSerialize(void) override;
            virtual bool VDeserialize(Core::JSON& jsonObject) override;

            void SetRenderable(Graphics::IMeshHandle mesh, 
                Graphics::IMaterialHandle material);

            void VOnInit() override;
            void VOnUpdate() override;
            Component* VClone() const override;

        protected:
            void VOnEnabled() override;
            void VOnDisabled() override;
            void VOnDestroy() override;

        private:
            Graphics::MeshRenderer* m_meshRenderer;
            Resource::Matrix4Variable* m_worldMatrix;
        };

    }

}
