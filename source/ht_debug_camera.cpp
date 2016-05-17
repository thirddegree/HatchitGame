#include <ht_debug_camera.h>
#include <ht_time_singleton.h>
#include <ht_input_singleton.h>
#include <ht_renderer_singleton.h>
#include <ht_swapchain.h>

namespace Hatchit {

    namespace Game {

        DebugCamera::DebugCamera() :
            m_yaw(90.0f),
            m_pitch(0.0f),
            m_moveSpeed(3.0f),
            m_zoomSpeed(4.0f),
            m_dragSpeed(3.0f),
            m_scrollSpeed(10.0f),
            m_shiftSpeed(2.0f),
            m_position(Math::Vector3(0, 0, -5)),
            m_forward(Math::Vector3(0, 0, 1)),
            m_up(Math::Vector3(0, 1, 0)),
            m_right(Math::Vector3(1, 0, 0)),
            m_camera(Graphics::Camera(Math::MMMatrixLookAt(m_position, m_forward, m_up), Math::MMMatrixPerspProj(60, 1280, 720, 1, 100))),
            m_controlType(CameraControlType::Unity)
        {
        }

        /**
        * \fn void Update()
        * \brief Updates camera position/rotation based on user input
        */
        void DebugCamera::Update()
        {
            LeftMousePress();
            RightMousePress();
            MiddleMousePress();
            MouseScroll();

            m_camera.SetView(Math::MMMatrixLookAt(m_position, m_position + m_forward, m_up));
        }

        /**
        * \fn void LeftMousePress()
        * \brief Called when the left mouse button is pressed
        */
        void DebugCamera::LeftMousePress()
        {
            if (Input::MouseButtonPress(MouseButton::Left))
            {
                if (m_controlType == CameraControlType::Unity)
                {
                    Orbit();
                }
            }
        }

        /**
        * \fn void RightMousePress()
        * \brief Called when the right mouse button is pressed
        */
        void DebugCamera::RightMousePress()
        {
            if (Input::MouseButtonPress(MouseButton::Right))
            {
                if (m_controlType == CameraControlType::Unity)
                {
                    if (Input::KeyPressed(IKeyboard::Key::LAlt))
                    {
                        Zoom();
                    }
                    else
                    {
                        Move();
                        Rotate();
                    }
                }
            }
        }

        /**
        * \fn void MiddleMousePress()
        * \brief Called when the mouse wheel is pressed
        */
        void DebugCamera::MiddleMousePress()
        {
            if (Input::MouseButtonPress(MouseButton::Middle))
            {
                if (m_controlType == CameraControlType::Unity)
                {
                    Drag();
                }
            }
        }

        /**
        * \fn void MouseScroll()
        * \brief Called when the mouse wheel is scrolled
        */
        void DebugCamera::MouseScroll()
        {
            int mouseWheelY = Input::MouseWheelY();

            if (mouseWheelY != 0)
            {
                float speed = ShiftPressed(m_scrollSpeed);

                m_position += m_forward * speed * mouseWheelY * Time::DeltaTime();
            }
        }

        /**
        * \fn void Move()
        * \brief Moves camera based off of user input
        *
        *   W -> forward
        *   A -> right
        *   S -> backward
        *   D -> right
        *   Q -> down
        *   E -> up
        *
        */
        void DebugCamera::Move()
        {
            float dt = Time::DeltaTime();
            float speed = ShiftPressed(m_moveSpeed);

            if (Input::KeyPressed(IKeyboard::Key::W))
                m_position += m_forward * speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::A))
                m_position += m_right * -speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::S))
                m_position += m_forward * -speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::D))
                m_position += m_right * speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::Q))
                m_position += m_up * -speed * dt;
            if (Input::KeyPressed(IKeyboard::Key::E))
                m_position += m_up * speed * dt;
        }

        /**
        * \fn void Zoom()
        * \brief Moves the camera towards/away from focal point
        */
        void DebugCamera::Zoom()
        {
            Graphics::SwapChain* chain = Renderer::instance().GetRenderer()->GetSwapChain();
            Math::Vector2 windowCenter = Math::Vector2(chain->GetWidth() / 2, chain->GetHeight() / 2);

            float distanceFromCenter = Math::MMVector2Distance(Input::MousePos(), windowCenter);
            float prevDistanceFromCenter = Math::MMVector2Distance(Input::PreviousMousePos(), windowCenter);
            float direction = Math::Clampf(distanceFromCenter - prevDistanceFromCenter, -1.0f, 1.0f);
            float speed = ShiftPressed(m_zoomSpeed);
            int deltaX = Input::MouseX() < windowCenter.x ? -1 : 1;

            m_position += m_forward * speed * direction * deltaX * Time::DeltaTime() * 3.0f;
        }

        /**
        * \fn void Drag()
        * \brief Moves the camera relative to mouse movement in the viewport
        */
        void DebugCamera::Drag()
        {
            if (Input::MousePos() != Input::PreviousMousePos()) 
            {
                Math::Vector2 direction = Math::MMVector2Normalized(Input::MousePos() - Input::PreviousMousePos());
                float speed = ShiftPressed(m_dragSpeed);

                if (direction.MagnitudeSquared() > 0)
                {
                    m_position += Math::MMVector3Cross(m_forward, m_right).Normalize() * -direction.y * speed * Time::DeltaTime() * 3.0f;
                    m_position += m_right * direction.x * speed * Time::DeltaTime() * 5.0f;
                }
            }
        }

        /**
        * \fn void Rotate()
        * \brief Rotates camera based off of user input
        */
        void DebugCamera::Rotate()
        {
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

            float yawRad = Math::MMDegreesToRadians(m_yaw);
            float pitchRad = Math::MMDegreesToRadians(m_pitch);

            Math::Vector3 camFront = Math::Vector3();
            camFront.x = cosf(yawRad) * cosf(pitchRad);
            camFront.y = sinf(pitchRad);
            camFront.z = sinf(yawRad) * cosf(pitchRad);

            m_forward = Math::MMVector3Normalized(camFront);
            m_right = Math::MMVector3Cross(m_up, m_forward);
        }

        void DebugCamera::Orbit()
        {
            // TO-DO: Figure out how to orbit around specific points in space (linecasting)
        }

        /**
        * \fn float ShiftPress(float speed)
        * \brief Increases the speed of the camera if shift held
        *
        * \param speed The speed to augment (move, zoom, drag, etc.)
        *
        * \return Increased speed if shift is held
        */
        float DebugCamera::ShiftPressed(float speed)
        {
            return (Input::KeyPressed(IKeyboard::Key::LShift)) ? speed * m_shiftSpeed : speed;
        }

        /**
        * \fn const Math::Matrix4 GetView()
        * \brief Returns cameras view matrix
        *
        * \return Cameras view matrix
        */
        const Math::Matrix4 DebugCamera::GetView()
        {
            return m_camera.GetView();
        }

        /**
        * \fn const Math::Matrix4 GetProjection()
        * \brief Returns cameras projection matrix
        *
        * \return Cameras projection matrix
        */
        const Math::Matrix4 DebugCamera::GetProjection()
        {
            return m_camera.GetProjection();
        }
    }
}