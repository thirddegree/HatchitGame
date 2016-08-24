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

#include <ht_camera_component.h>
#include <ht_renderer_singleton.h>
#include <ht_input_singleton.h>
#include <ht_swapchain.h>
#include <ht_jsonhelper.h>
#include <ht_gameobject.h>

namespace Hatchit {

    namespace Game {

        Camera::Camera()
        {
            m_useWindowScale = false;
            m_fov = Math::MMDegreesToRadians(90.0f);
            m_width = 1280;
            m_height = 720;
            m_near = 1.0f;
            m_far = 100.0f;
            m_layer = 1;

            m_speed = 0.01f;
            m_yaw = 0.0f;
            m_pitch = 0.0f;
            
            m_camera = Graphics::Camera(Math::Matrix4(), Math::MMMatrixPerspProj(m_fov, m_width, m_height, m_near, m_far));
            m_renderer = Renderer::instance().GetRenderer();
        }

        Core::JSON Camera::VSerialize(void)
        {
            return Core::JSON();
        }

        bool Camera::VDeserialize(const Core::JSON& jsonObject)
        {
            if (!Core::JsonExtract<bool>(jsonObject, "UseWindowScale", m_useWindowScale))
                HT_WARNING_PRINTF("Camera::VDeserialize: Failed to load window scale preference; defaulting to false\n");

            if (!Core::JsonExtract<float>(jsonObject, "FOV", m_fov))
                HT_WARNING_PRINTF("Camera::VDeserialize: Failed to load FOV; defaulting to 90 degrees\n");
            else
                m_fov = Math::MMDegreesToRadians(m_fov); //Convert FOV to radians if we loaded properly

            if (!Core::JsonExtract<float>(jsonObject, "Width", m_width))
                HT_WARNING_PRINTF("Camera::VDeserialize: Failed to load width; defaulting to 1280\n");

            if (!Core::JsonExtract<float>(jsonObject, "Height", m_height))
                HT_WARNING_PRINTF("Camera::VDeserialize: Failed to load height; defaulting to 720\n");

            if (!Core::JsonExtract<float>(jsonObject, "Near", m_near))
                HT_WARNING_PRINTF("Camera::VDeserialize: Failed to load near plane; defaulting to 0.1\n");

            if (!Core::JsonExtract<float>(jsonObject, "Far", m_far))
                HT_WARNING_PRINTF("Camera::VDeserialize: Failed to load far plane; defaulting to 100\n");

            if (!Core::JsonExtract<uint32_t>(jsonObject, "Layer", m_layer))
                HT_WARNING_PRINTF("Camera::VDeserialize: Failed to load layer; defaulting to 1\n");

            //If we want to use window scale lets make m_width and m_height relative to the renderer's swapchain size
            if (m_useWindowScale)
            {
                Graphics::SwapChain* swapchain = m_renderer->GetSwapChain();

                //m_width and m_height should be "percentage" values until this step if m_useWindowScale is defined
                m_width = m_width * swapchain->GetWidth();
                m_height = m_height * swapchain->GetHeight();

                //Now m_width and m_height should be relative to the swapchain's screen size
            }

            m_camera = Graphics::Camera(Math::Matrix4(), Math::MMMatrixPerspProj(m_fov, m_width, m_height, m_near, m_far));
            m_camera.SetLayerFlags(m_layer);
            return true;
        }

        void Camera::VOnInit()
        {

        }

        void Camera::VOnUpdate()
        {
            Transform& t = m_owner->GetTransform();

            Move();
            Rotate();

            //Send transform data to the GPU by registering the camera with the renderer
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

        /**
        * \brief Retrieves the id associated with this class of Component.
        * \return The Core::Guid associated with this Component type.
        * \sa Component(), GameObject()
        */
        Core::Guid Camera::VGetComponentId(void) const
        {
            return Component::GetComponentId<Camera>();
        }

        void Camera::Move()
        {
            Transform& t = m_owner->GetTransform();

            if (Input::KeyPressed(IKeyboard::Key::W) || Input::KeyPressed(IKeyboard::Key::Up))
                t.SetPosition(t.GetPosition() + (t.GetForward() * m_speed));
            if (Input::KeyPressed(IKeyboard::Key::A) || Input::KeyPressed(IKeyboard::Key::Left))
                t.SetPosition(t.GetPosition() - (t.GetRight() * m_speed));
            if (Input::KeyPressed(IKeyboard::Key::S) || Input::KeyPressed(IKeyboard::Key::Down))
                t.SetPosition(t.GetPosition() - (t.GetForward() * m_speed));
            if (Input::KeyPressed(IKeyboard::Key::D) || Input::KeyPressed(IKeyboard::Key::Right))
                t.SetPosition(t.GetPosition() + (t.GetRight() * m_speed));
            if (Input::KeyPressed(IKeyboard::Key::E))
                t.SetPosition(t.GetPosition() + (Math::Vector3(0.0f, 1.0f, 0.0f) * m_speed));
            if (Input::KeyPressed(IKeyboard::Key::Q))
                t.SetPosition(t.GetPosition() + (Math::Vector3(0.0f, -1.0f, 0.0f) * m_speed));
        }

        void Camera::Rotate()
        {
            if (Input::MouseButtonPress(MouseButton::Left)) 
            {
                Transform& t = m_owner->GetTransform();

                float xOffset = static_cast<float>(Input::PreviousMouseX() - Input::MouseX());
                float yOffset = static_cast<float>(Input::PreviousMouseY() - Input::MouseY());
                float sensitivity = 0.1f;

                xOffset *= sensitivity;
                yOffset *= sensitivity;

                m_yaw += xOffset;
                m_pitch += yOffset;

                if (m_pitch > 89.9f)
                    m_pitch = 89.9f;
                if (m_pitch < -89.9f)
                    m_pitch = -89.9f;

                if (xOffset != 0 && yOffset != 0)
                {
                    float yawRad = Math::MMDegreesToRadians(m_yaw);
                    float pitchRad = Math::MMDegreesToRadians(m_pitch);

                    Math::Vector3 camFront = Math::Vector3();
                    camFront.x = cosf(yawRad) * cosf(pitchRad);
                    camFront.y = sinf(pitchRad);
                    camFront.z = sinf(yawRad) * cosf(pitchRad);

                    t.SetRotation(Math::Vector3(-pitchRad, -yawRad, 0.0f));
                }
            }
        }
    }

}
