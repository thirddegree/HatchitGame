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

#include <ht_camera_component.h>
#include <ht_renderer_singleton.h>
#include <ht_jsonhelper.h>

namespace Hatchit {

    namespace Game {

        Camera::Camera()
        {
            m_camera = Graphics::Camera(Math::Matrix4(), Math::MMMatrixPerspProj(60, 1280, 720, 1, 100));
        }

        Core::JSON Camera::VSerialize(void)
        {
            return Core::JSON();
        }

        bool Camera::VDeserialize(const Core::JSON& jsonObject)
        {
            return false;
        }

        void Camera::VOnInit()
        {

        }

        void Camera::VOnUpdate()
        {
            Transform t; //m_owner->GetTransform();
            m_camera.SetView(Math::MMMatrixLookAt(t.GetPosition(), t.GetPosition() + t.GetForward(), t.GetUp()));
            m_camera.SetProjection(Math::MMMatrixPerspProj(m_fov, m_width, m_height, m_near, m_far));
            m_camera.RegisterCamera();
        }

        void Camera::VOnEnabled()
        {

        }

        void Camera::VOnDisabled()
        {

        }

        void Camera::VOnDestroy()
        {

        }

        Component* Camera::VClone(void) const
        {
            HT_DEBUG_PRINTF("Cloned Camera Component.\n");
            return new Camera(*this);
        }

    }

}
