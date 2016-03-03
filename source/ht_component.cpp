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

#include <ht_component.h>
#include <ht_debug.h>

namespace Hatchit {
    namespace Game {
        std::uint32_t Component::s_componentIdCounter = 0;

        bool Component::GetEnabled(void) const
        {
            return m_enabled;
        }

        void Component::SetEnabled(bool value)
        {
            if (m_enabled)
            {
                if (m_enabled != value)
                {
                    VOnDisabled();
                }
            }
            else
            {
                if (m_enabled != value)
                {
                    VOnEnabled();
                }
            }

            m_enabled = value;
        }

        void Component::Init(void)
        {
#ifdef _DEBUG
            Core::DebugPrintF("Component Initialized. (not implemented)\n");
#endif
        }

        void Component::Update(void)
        {
#ifdef _DEBUG
            Core::DebugPrintF("Component Updated. (not implemented)\n");
#endif
        }

        void Component::Destroy(void)
        {
#ifdef _DEBUG
            Core::DebugPrintF("Component Destroyed. (not implemented)\n");
#endif
        }
    }
}