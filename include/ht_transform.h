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

#pragma once

#include <ht_platform.h>
#include <ht_math.h>
#include <vector>

namespace Hatchit {

    namespace Game {

        class HT_API Transform
        {
            friend class GameObject;
        public:
            Transform();
            Transform(float posX, float posY, float posZ,
                float rotX, float rotY, float rotZ,
                float scaleX, float scaleY, float scaleZ);
            Transform(Math::Vector3 position, Math::Vector3 rotation, Math::Vector3 scale);
            Transform(const Transform& transform);

            /**
            * \brief Returns world transformation matrix.
            * \return Matrix4* Pointer to world transformation matrix.
            */
            Math::Matrix4* GetWorldMatrix();

            /**
            * \brief Returns local transformation matrix.
            * \return Matrix4* Pointer to local transformation matrix.
            */
            Math::Matrix4* GetLocalMatrix();

            /**
            * \brief Recomputes world matrix.
            */
            void UpdateWorldMatrix();

            /**
            * \brief Flags transformation matrix for recomputation.
            */
            void SetDirty();

            /**
            * \brief Rotates around the local X axis.
            * \param val Amount to rotate around axis.
            */
            void RotateX(float val);

            /**
            * \brief Rotates around the local Y axis.
            * \param val Amount to rotate around axis.
            */
            void RotateY(float val);

            /**
            * \brief Rotates around the local Z axis.
            * \param val Amount to rotate around axis.
            */
            void RotateZ(float val);

            /**
            * \brief Translates on the local X axis.
            * \param val Amount to translate on axis.
            */
            void TranslateX(float val);

            /**
            * \brief Translates on the local Y axis.
            * \param val Amount to translate on axis.
            */
            void TranslateY(float val);

            /**
            * \brief Translates on the local Z axis.
            * \param val Amount to translate on axis.
            */
            void TranslateZ(float val);

            /**
            * \brief Translates by Vector3 val.
            * \param val Amount to translate on each axis.
            */
            void Translate(Math::Vector3 val);

            /**
            * \brief Returns position as a Vector3.
            * \return Vector3 Local position vector.
            */
            Math::Vector3 GetPosition();

            /**
            * \brief Returns world position as a Vector3.
            * \return Vector3 World position vector.
            */
            Math::Vector3 GetWorldPosition();

            /**
            * \brief Returns rotation as a Vector3.
            * \return Vector3 Rotation vector.
            */
            Math::Vector3 GetRotation();

            /**
            * \brief Returns scale as a Vector3.
            * \return Vector3 World position vector.
            */
            Math::Vector3 GetScale();

            /**
            * \brief Returns forward vector as a Vector3.
            * \return Vector3 Forward vector.
            */
            Math::Vector3 GetForward();
            /**
            * \brief Returns up vector as a Vector3.
            * \return Vector3 Up vector.
            */
            Math::Vector3 GetUp();

            /**
            * \brief Returns right vector as a Vector3.
            * \return Vector3 Right vector.
            */
            Math::Vector3 GetRight();

            /**
            * \brief Returns pointer to rotation vector.
            * \return Vector3* Pointer to rotation vector.
            */
            Math::Vector3* GetRotationRef();

            /**
            * \brief Sets position values from a Vector3.
            * \param val New position vector.
            */
            void SetPosition(Math::Vector3 val);

            /**
            * \brief Sets rotation values from a Vector3.
            * \param val New rotation vector.
            */
            void SetRotation(Math::Vector3 val);

            /**
            * \brief Sets scale values from a Vector3.
            * \param val New scale vector.
            */
            void SetScale(Math::Vector3 val);

            /**
            * \brief Returns X value of position.
            * \return float X position.
            */
            float X() const;

            /**
            * \brief Returns Y value of position.
            * \return float Y position.
            */
            float Y() const;

            /**
            * \brief Returns Z value of position.
            * \return float Z position.
            */
            float Z() const;

            /**
            * \brief Returns X value of rotation.
            * \return float Rotation around X.
            */
            float RotX() const;

            /**
            * \brief Returns Y value of rotation.
            * \return float Rotation around Y.
            */
            float RotY() const;

            /**
            * \brief Returns Z value of rotation.
            * \return float Rotation around Z.
            */
            float RotZ() const;

            /**
            * \brief Returns X value of scale.
            * \return float Scale on X axis.
            */
            float ScaleX() const;

            /**
            * \brief Returns Y value of scale.
            * \return float Scale on Y axis.
            */
            float ScaleY() const;

            /**
            * \brief Returns Z value of scale.
            * \return float Scale on Z axis.
            */
            float ScaleZ() const;

            /**
            * \brief Prints transform data.
            */
            void DebugPrint();

            /**
            * \brief Returns whether or not transformation matrices are dirty.
            * \return bool Value of dirty flag of transformation matrics.
            */
            bool IsDirty();

        private:
            Math::Vector3 m_position;
            Math::Vector3 m_rotation;
            Math::Vector3 m_scale;

            Math::Vector3 m_worldPosition;


            Math::Vector3 m_forward;
            Math::Vector3 m_up;
            Math::Vector3 m_right;

            Math::Matrix4  m_world;
            Math::Matrix4  m_local;

            bool	m_localDirty;
            bool    m_worldDirty;
            bool    m_test;

            std::vector<Transform*> m_childTransforms;
            Transform*              m_parent;
        };
    };

};