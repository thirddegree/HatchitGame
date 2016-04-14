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

            void VOnInit() override;
            void VOnUpdate() override;
            void VOnDestroy() override;
            Component* VClone(void) const override;

        protected:
            void VOnEnabled() override;
            void VOnDisabled() override;

        private:
            bool  m_useWindowScale;
            float m_height;
            float m_width;

            float m_fov;
            float m_near;
            float m_far;
            Graphics::Camera m_camera;
        };

    }

}
