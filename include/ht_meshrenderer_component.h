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

            /**
            * \brief Called when the GameObject is created to initialize all values
            */
            void VOnInit() override;

            /**
            * \brief Called once per frame while the GameObject is enabled.
            * Updates all components first, then all child gameobjects.
            */
            void VOnUpdate() override;

            /**
            * \brief Creates a copy of this Component.
            */
            Component* VClone() const override;

        protected:

            /**
            * \brief Called when the Component is enabled.
            * This happens when a scene has finished loading, or immediately after creation if the scene is already loaded.
            */
            void VOnEnabled() override;


            /**
            * \brief Called when the Component is disabled.
            * Components are always disabled before destroyed.
            * When a scene is destroyed, all Components are disabled before any are destroyed.
            */
            void VOnDisabled() override;

            /**
            * \brief Called when the GameObject is destroyed/deleted.
            * Objects are always disabled before destroyed.
            * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
            */
            void VOnDestroy() override;

        private:
            Graphics::MeshRenderer* m_meshRenderer;
            Resource::Matrix4Variable* m_worldMatrix;
        };

    }

}
