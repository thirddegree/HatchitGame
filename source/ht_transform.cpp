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

#include <ht_transform.h>

namespace Hatchit {
    namespace Game {
        Transform::Transform()
        {
            m_position = Math::Vector3(0.0f, 0.0f, 0.0f);
            m_rotation = Math::Vector3(0.0f, 0.0f, 0.0f);
            m_scale = Math::Vector3(1.0f, 1.0f, 1.0f);

            m_forward = Math::Vector3(0.0f, 0.0f, 1.0f);
            m_up = Math::Vector3(0.0f, 1.0f, 0.0f);
            m_right = Math::Vector3(1.0f, 0.0f, 0.0f);
            m_parent = nullptr;
            SetDirty();
        }

        Transform::Transform(float posX, float posY, float posZ,
            float rotX, float rotY, float rotZ,
            float scaleX, float scaleY, float scaleZ)
        {
            m_position = Math::Vector3(posX, posY, posZ);
            m_rotation = Math::Vector3(rotX, rotY, rotZ);
            m_scale = Math::Vector3(scaleX, scaleY, scaleZ);

            m_forward = Math::Vector3(0.0f, 0.0f, 1.0f);
            m_up = Math::Vector3(0.0f, 1.0f, 0.0f);
            m_right = Math::Vector3(1.0f, 0.0f, 0.0f);
            m_parent = nullptr;
            SetDirty();
        }

        Transform::Transform(Math::Vector3 position, Math::Vector3 rotation, Math::Vector3 scale) :
            m_position(position),
            m_rotation(rotation),
            m_scale(scale)
        {
            m_forward = Math::Vector3(0.0f, 0.0f, 1.0f);
            m_up = Math::Vector3(0.0f, 1.0f, 0.0f);
            m_right = Math::Vector3(1.0f, 0.0f, 0.0f);
            m_parent = nullptr;
            SetDirty();
        }

        Transform::Transform(const Transform& transform) : 
            m_position(transform.m_position),
            m_rotation(transform.m_rotation),
            m_scale(transform.m_scale),
            m_forward(transform.m_forward),
            m_up(transform.m_up),
            m_right(transform.m_right)
        {
            m_parent = nullptr;
            SetDirty();
        }

        void Transform::SetDirty()
        {
            if (!m_worldDirty) {
                m_worldDirty = true;

                for (auto& transform : m_childTransforms)
                {
                    transform->SetDirty();
                }
            }

            if (!m_localDirty)
                m_localDirty = true;
        }

        void Transform::TranslateX(float val)
        {
            SetDirty();
            m_position.x += val;
        }

        void Transform::TranslateY(float val)
        {
            SetDirty();
            m_position.y += val;
        }

        void Transform::TranslateZ(float val)
        {
            SetDirty();
            m_position.z += val;
        }

        void Transform::Translate(Math::Vector3 val)
        {
            SetDirty();
            m_position.x += val.x;
            m_position.y += val.y;
            m_position.z += val.z;
        }

        /*void Transform::Translate(float x, float y, float z)
        {
        SetDirty();
        m_position.x += x;
        m_position.y += y;
        m_position.z += z;
        }*/

        Math::Vector3 Transform::GetPosition()
        {
            this->GetWorldMatrix();
            return m_position;
        }

        Math::Vector3 Transform::GetWorldPosition()
        {
            this->GetWorldMatrix();
            return m_worldPosition;
        }

        Math::Vector3 Transform::GetRotation()
        {
            this->GetWorldMatrix();
            return m_rotation;
        }

        Math::Vector3 Transform::GetScale()
        {
            this->GetWorldMatrix();
            return m_scale;
        }

        Math::Vector3 Transform::GetForward()
        {
            this->GetWorldMatrix();
            return m_forward;
        }

        Math::Vector3 Transform::GetUp()
        {
            this->GetWorldMatrix();
            return m_up;
        }

        Math::Vector3 Transform::GetRight()
        {
            this->GetWorldMatrix();
            return m_right;
        }

        void Transform::SetPosition(Math::Vector3 val)
        {
            SetDirty();
            m_position = val;
        }

        void Transform::SetRotation(Math::Vector3 val)
        {
            SetDirty();
            m_rotation = val;
        }

        void Transform::SetScale(Math::Vector3 val)
        {
            SetDirty();
            m_scale = val;
        }

        void Transform::SetForward(Math::Vector3 val)
        {
            SetDirty();
            m_forward = Math::MMVector3Normalized(val);
        }

        void Transform::RotateX(float val)
        {
            SetDirty();
            m_rotation.x += val;
        }

        void Transform::RotateY(float val)
        {
            SetDirty();
            m_rotation.y += val;
        }

        void Transform::RotateZ(float val)
        {
            SetDirty();
            m_rotation.z += val;
        }

        Math::Vector3* Transform::GetRotationRef()
        {
            return &m_rotation;
        }

        float Transform::X() const
        {
            return m_position.x;
        }

        float Transform::Y() const
        {
            return m_position.y;
        }

        float Transform::Z() const
        {
            return m_position.z;
        }

        float Transform::RotX() const
        {
            return m_rotation.x;
        }

        float Transform::RotY() const
        {
            return m_rotation.y;
        }

        float Transform::RotZ() const
        {
            return m_rotation.z;
        }

        float Transform::ScaleX() const
        {
            return m_scale.x;
        }

        float Transform::ScaleY() const
        {
            return m_scale.y;
        }

        float Transform::ScaleZ() const
        {
            return m_scale.z;
        }

        bool Transform::IsDirty()
        {
            return m_worldDirty || m_localDirty;
        }

        Math::Matrix4* Transform::GetWorldMatrix()
        {
            UpdateWorldMatrix();

            return &m_world;
        }

        Math::Matrix4* Transform::GetLocalMatrix()
        {
            if (m_localDirty) {
                m_local = Math::MMMatrixTranslation(m_position) *
                    Math::MMMatrixRotationXYZ(m_rotation) *
                    Math::MMMatrixScale(m_scale);
                m_localDirty = false;
            }

            return &m_local;
        }

        void Transform::UpdateWorldMatrix()
        {
            if (m_worldDirty)
            {
                m_worldDirty = false;
                if (m_parent)
                    m_world = (*GetLocalMatrix()) * (*m_parent->GetWorldMatrix());
                else
                    m_world = *GetLocalMatrix();

                m_worldPosition = m_world * Math::Vector4(0, 0, 0, 0);

                //recalculate basis vectors (right, forward, up)
                m_forward = m_world * Math::Vector4(0, 0, 1, 0);
                m_forward = Math::MMVector3Normalized(m_forward);

                m_up = m_world * Math::Vector4(0, 1, 0, 0);
                m_up = Math::MMVector3Normalized(m_up);

                m_right = Math::MMVector3Cross(m_up, m_forward);
            }
        }

        void Transform::DebugPrint()
        {
            //DebugPrintF(VTEXT("Transform [X: %.3f, Y: %.3f, Z: %.3f]\n"), m_position.x, m_position.y, m_position.z);
        }
    }
}
