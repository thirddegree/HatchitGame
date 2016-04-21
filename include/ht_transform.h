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


            Math::Matrix4* GetWorldMatrix();
            Math::Matrix4* GetLocalMatrix();

            void UpdateWorldMatrix();

            void SetDirty();

            void RotateX(float val);
            void RotateY(float val);
            void RotateZ(float val);
            void TranslateX(float val);
            void TranslateY(float val);
            void TranslateZ(float val);
            void Translate(Math::Vector3 val);
            //void Translate(float x, float y, float z);

            Math::Vector3 GetPosition();
            Math::Vector3 GetWorldPosition();
            Math::Vector3 GetRotation();
            Math::Vector3 GetScale();
            Math::Vector3 GetForward();
            Math::Vector3 GetUp();
            Math::Vector3 GetRight();

            Math::Vector3* GetRotationRef();

            void SetPosition(Math::Vector3 val);
            void SetRotation(Math::Vector3 val);
            void SetScale(Math::Vector3 val);

            float X() const;
            float Y() const;
            float Z() const;
            float RotX() const;
            float RotY() const;
            float RotZ() const;
            float ScaleX() const;
            float ScaleY() const;
            float ScaleZ() const;

            void DebugPrint();

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