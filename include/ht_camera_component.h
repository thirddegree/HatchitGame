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

#include <ht_math.h>
#include <ht_component.h>
#include <ht_camera.h>

namespace Hatchit {

    namespace Game {

        class Camera : public Component
        {
        public:
            Camera();

            /**
            * \brief Called when the GameObject is created to initialize all values
            */
            virtual Core::JSON VSerialize(void) override;
            virtual bool VDeserialize(const Core::JSON& jsonObject) override;
            void VOnInit() override;

            /**
            * \brief Called once per frame while the GameObject is enabled.
            * Updates all components first, then all child gameobjects.
            */
            void VOnUpdate() override;

            /**
            * \brief Called when the GameObject is destroyed/deleted.
            * Objects are always disabled before destroyed.
            * When a scene is destroyed, all gameobjects are disabled before any are destroyed.
            */
            void VOnDestroy() override;

            /**
            * \brief Creates a copy of this Component.
            */
            Component* VClone(void) const override;

            virtual Core::Guid VGetComponentId(void) const override;
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

        private:
            bool  m_useWindowScale;
            float m_height;
            float m_width;

            float m_fov;
            float m_near;
            float m_far;
            uint32_t m_layer;

            float m_speed;
            
            Graphics::Camera m_camera;
            Graphics::Renderer* m_renderer;
        };

    }

}
