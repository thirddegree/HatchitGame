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
#include <ht_noncopy.h>
#include <ht_string.h>

namespace Hatchit {

    namespace Game {

        struct HT_API WindowParams
        {
            std::string title;
            int x;
            int y;
            int width;
            int height;
        };

        class HT_API IWindow : Core::INonCopy
        {
        public:
            virtual ~IWindow() { };
        
            virtual bool    VInitialize() = 0;
            virtual void*   VNativeHandle() = 0;
            virtual bool    VIsRunning() = 0;
            virtual void    VPollEvents() = 0;
            virtual void    VClose() = 0;
            virtual void    VSwapBuffers() = 0;
        };


    }

}