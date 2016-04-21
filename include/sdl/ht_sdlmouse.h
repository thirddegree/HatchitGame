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
#include <ht_sdl.h>

namespace Hatchit
{
    namespace Game
    {
        struct SDLMouseState
        {
            uint8_t clicks;
            uint8_t state;
        };

        class HT_API SDLMouse : public IMouse
        {
            static const int NUM_BUTTONS = 3;
        public:
            SDLMouse();

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
            void RegisterMouseButtonEvent(SDL_MouseButtonEvent e);
            void RegisterMouseWheelEvent(SDL_MouseWheelEvent e);

        private:
            int             m_x;
            int             m_y;
            int             m_prevX;
            int             m_prevY;
            int             m_wx;
            int             m_wy;
            int             m_prevWX;
            int             m_prevWY;
            SDLMouseState   m_current[NUM_BUTTONS];
            SDLMouseState   m_previous[NUM_BUTTONS];
        };
    }
}
