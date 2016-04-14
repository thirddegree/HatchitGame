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

namespace Hatchit
{
    namespace Game
    {
        enum class MouseButton
        {
            Left,
            Middle,
            Right
        };

        class IMouse
        {
        public:
            virtual ~IMouse() { };

            virtual int     VMouseX() = 0;
            virtual int     VMouseY() = 0;
            virtual int     VPreviousMouseX() = 0;
            virtual int     VPreviousMouseY() = 0;
            virtual int     VMouseWheelX() = 0;
            virtual int     VMouseWheelY() = 0;
            virtual int     VDeltaX(int val) = 0;
            virtual int     VDeltaY(int val) = 0;
            virtual bool    VButtonRelease(MouseButton button) = 0;
            virtual bool    VButtonPress(MouseButton button) = 0;
            virtual bool    VSingleButtonPress(MouseButton button) = 0;
            virtual void    VUpdate() = 0;
        };
    }
}