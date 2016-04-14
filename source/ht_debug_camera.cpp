#include <ht_debug_camera.h>

namespace Hatchit {

    namespace Game {

        DebugCamera::DebugCamera() :
            m_yaw(90.0f),
            m_pitch(0.0f),
            m_speed(2.5f),
            m_position(Math::Vector3(0, 0, -5)),
            m_forward(Math::Vector3(0, 0, 1)),
            m_up(Math::Vector3(0, 1, 0)),
            m_right(Math::Vector3(1, 0, 0)),
            m_camera(Graphics::Camera(Math::MMMatrixLookAt(m_position, m_forward, m_up), Math::MMMatrixPerspProj(60, 1280, 720, 1, 100)))
        {
        }

        void DebugCamera::Update()
        {
            Rotate();
            Move();

            m_camera.SetView(Math::MMMatrixLookAt(m_position, m_position + m_forward, m_up));
        }

        Math::Matrix4 DebugCamera::GetView()
        {
            return m_camera.GetView();
        }

        Math::Matrix4 DebugCamera::GetProjection()
        {
            return m_camera.GetProjection();
        }

        void DebugCamera::Rotate()
        {
            if (Input::MouseButtonPress(MouseButton::Left))
            {
                float xOffset = Input::PreviousMouseX() - Input::MouseX();
                float yOffset = Input::PreviousMouseY() - Input::MouseY();
                float sensitivity = 0.1f;

                xOffset *= sensitivity;
                yOffset *= sensitivity;
                m_yaw += xOffset;
                m_pitch += yOffset;

                if (m_pitch > 89.9f)
                    m_pitch = 89.9f;
                if (m_pitch < -89.9f)
                    m_pitch = -89.9f;

                float yawRad = Math::MMDegreesToRadians(m_yaw);
                float pitchRad = Math::MMDegreesToRadians(m_pitch);

                Math::Vector3 camFront = Math::Vector3();
                camFront.x = cosf(yawRad) * cosf(pitchRad);
                camFront.y = sinf(pitchRad);
                camFront.z = sinf(yawRad) * cosf(pitchRad);

                m_forward = Math::MMVector3Normalized(camFront);
                m_right = Math::MMVector3Cross(m_up, m_forward);
            }
        }

        void DebugCamera::Move()
        {
            float dt = Time::DeltaTime();

            if (Input::KeyPressed(IKeyboard::Key::W))
                m_position += m_forward * m_speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::A))
                m_position += m_right * -m_speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::S))
                m_position += m_forward * -m_speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::D))
                m_position += m_right * m_speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::Q))
                m_position += m_up * -m_speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::E))
                m_position += m_up * m_speed * dt;
        }
    }
}