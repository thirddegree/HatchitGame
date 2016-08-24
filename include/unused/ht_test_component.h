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

#include <ht_component.h>

namespace Hatchit {
    namespace Game {

        class TestComponent : public Component
        {
        public:
            TestComponent(void) = default;

            virtual Core::JSON VSerialize(void) override;
            virtual bool VDeserialize(const Core::JSON& jsonObject) override;

            void VOnInit() override;
            void VOnUpdate() override;
            Component* VClone(void) const override;
            virtual Core::Guid VGetComponentId(void) const override;
        protected:
            void VOnEnabled() override;
            void VOnDisabled() override;
            void VOnDestroy() override;

        private:
            GameObject* testObject;

        };
    }
}
