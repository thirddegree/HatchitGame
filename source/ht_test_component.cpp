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

#include <ht_test_component.h>
#include <ht_debug.h>
#include <ht_scene.h>

namespace Hatchit {
    namespace Game {
        Core::JSON TestComponent::VSerialize(void)
        {
            return nlohmann::json::object_t();
        }
        bool TestComponent::VDeserialize(Core::JSON& jsonObject)
        {
            return false;
        }
        void TestComponent::VOnInit()
        {
            HT_DEBUG_PRINTF("Initialized Test Component.\n");
        }

        void TestComponent::VOnUpdate()
        {
            HT_DEBUG_PRINTF("Updated Test Component.\n");
        }

        Component* TestComponent::VClone(void) const
        {
            HT_DEBUG_PRINTF("Cloned Test Component.\n");
            return new TestComponent(*this);
        }

        void TestComponent::VOnEnabled()
        {
            HT_DEBUG_PRINTF("Enabled Test Component.\n");
        }

        void TestComponent::VOnDisabled()
        {
            HT_DEBUG_PRINTF("Disabled Test Component.\n");
        }

        void TestComponent::VOnDestroy()
        {
            HT_DEBUG_PRINTF("Destroyed Test Component.\n");
        }
    }
}
