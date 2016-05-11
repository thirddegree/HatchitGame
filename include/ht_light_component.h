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

#include <ht_shadervariablechunk.h>
#include <ht_meshrenderer.h>
#include <ht_component.h>
#include <ht_model.h>


namespace Hatchit {

    namespace Game {

        enum LightType
        {
            POINT_LIGHT,
            SPOT_LIGHT,
            DIRECTIONAL_LIGHT
        };

        class LightComponent : public Component
        {
        public:
            LightComponent();

            virtual Core::JSON VSerialize(void) override;
            virtual bool VDeserialize(const Core::JSON& jsonObject) override;

            void SetType(LightType lightType);

            void VOnInit() override;

            void VOnUpdate() override;

            Component* VClone() const override;

            virtual Core::Guid VGetComponentId(void) const override;
        protected:

            void VOnEnabled() override;

            void VOnDisabled() override;

            void VOnDestroy() override;

        private:

            bool SetMeshAndMaterial(std::string meshFile, std::string materialFile);

            LightType m_lightType;
            Graphics::MeshRenderer* m_meshRenderer;
            Graphics::MeshHandle m_mesh;
            Graphics::MaterialHandle m_material;

            /* Point Light Data */
            Graphics::ShaderVariableChunk* m_data;
            float m_radius;
            Math::Vector4 m_color;
            Math::Vector3 m_attenuation;

        };
    }
}
