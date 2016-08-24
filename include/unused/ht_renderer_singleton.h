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
#include <ht_singleton.h>
#include <ht_renderer.h>

namespace Hatchit {

    namespace Game {

        class HT_API Renderer : public Core::Singleton<Renderer>
        {
        public:

            static bool Initialize(const Graphics::RendererParams& params);

            static void DeInitialize();

            static void Render();

            static void Present();

            static void ResizeBuffers(uint32_t width, uint32_t height);

            static Graphics::RendererType GetRendererType();

            static Graphics::Renderer* GetRenderer();

        private:
            Graphics::Renderer*     m_renderer;
            Graphics::RendererType  m_rendererType;
            bool                    m_initialized;
        };

    }

}
