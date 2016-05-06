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
#include <ht_gameobject.h>

namespace Hatchit {

    namespace Game {

        Camera::Camera()
        {
            m_fov = 3.14f/4.0f;
            m_width = 1280;
            m_height = 720;
            m_near = 0.1f;
            m_far = 100.0f;
            
            m_camera = Graphics::Camera(Math::Matrix4(), Math::MMMatrixPerspProj(m_fov, m_width, m_height, m_near, m_far));
            m_renderer = Renderer::instance().GetRenderer();
        }

        Core::JSON Camera::VSerialize(void)
        {
            return Core::JSON();
        }

        bool Camera::VDeserialize(const Core::JSON& jsonObject)
        {
            m_camera.SetLayerFlags(1);
            return true;
        }

        void Camera::VOnInit()
        {

        }

        void Camera::VOnUpdate()
        {
            Transform t = m_owner->GetTransform();
            m_camera.SetView(Math::MMMatrixLookAt(t.GetPosition(), t.GetPosition() + t.GetForward(), t.GetUp()));
            m_camera.SetProjection(Math::MMMatrixPerspProj(m_fov, m_width, m_height, m_near, m_far));
            m_renderer->RegisterCamera(m_camera);
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
