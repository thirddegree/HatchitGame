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

#include <ht_camera.h>
#include <ht_math.h>

namespace Hatchit {

    namespace Game {

        class HT_API DebugCamera
        {
        public:
            DebugCamera();
            ~DebugCamera() = default;

           void Update();

           const Math::Matrix4 GetView();
           const Math::Matrix4 GetProjection();

        private:
            void Rotate();
            void Move();

            float            m_yaw;
            float            m_pitch;
            float            m_speed;

            Math::Vector3    m_position;
            Math::Vector3    m_forward;
            Math::Vector3    m_up;
            Math::Vector3    m_right;
            Graphics::Camera m_camera;
        };
    }
}