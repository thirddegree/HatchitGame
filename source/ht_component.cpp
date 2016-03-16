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
#include <ht_gameobject.h>

namespace Hatchit {
    namespace Game {
        GameObject* Component::GetOwner(void)
        {
            return m_owner;
        }

        void Component::SetOwner(GameObject *owner)
        {
            m_owner = owner;
        }

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
    }
}