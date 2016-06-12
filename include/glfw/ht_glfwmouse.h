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

#pragma once

#include <ht_platform.h>
#include <ht_mouse.h>
#include <ht_types.h>
#include <GLFW/glfw3.h>

namespace Hatchit
{
    namespace Game
    {
        struct GLFWMouseState
        {
            uint8_t clicks;
            uint8_t state;
        };

        class HT_API GLFWMouse : public IMouse
        {
            static const int NUM_BUTTONS = 3;
        public:
            GLFWMouse();

            int VMouseX()           override;
            int VMouseY()           override;
            int VPreviousMouseX()   override;
            int VPreviousMouseY()   override;
            int VMouseWheelX()      override;
            int VMouseWheelY()      override;
            int VDeltaX(int val)    override;
            int VDeltaY(int val)    override;

            bool VButtonRelease(MouseButton button)         override;
            bool VButtonPress(MouseButton button)           override;
            bool VSingleButtonPress(MouseButton button)     override;

            void VUpdate() override;


            void RegisterMouseMove(int x, int y);
            void RegisterMouseButtonEvent(int e, int action);
            void RegisterMouseWheelEvent(int xoffset, int yoffset);

        private:
            int             m_x;
            int             m_y;
            int             m_prevX;
            int             m_prevY;
            int             m_wx;
            int             m_wy;
            int             m_prevWX;
            int             m_prevWY;
            GLFWMouseState   m_current[NUM_BUTTONS];
            GLFWMouseState   m_previous[NUM_BUTTONS];
        };
    }
}
