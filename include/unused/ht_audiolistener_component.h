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

#include <ht_component.h> //Component

namespace Hatchit
{
    namespace Game
    {
        class AudioListener : public Component
        {
        public:
            AudioListener();

            virtual Core::JSON VSerialize() override;
            virtual bool VDeserialize(const Core::JSON& jsonObject) override;
            virtual void VOnInit() override;

            virtual void VOnUpdate() override;

            virtual void VOnDestroy() override;

            virtual Component* VClone() const override;

            virtual Core::Guid VGetComponentId() const override;
        protected:
            virtual void VOnEnabled() override;

            virtual void VOnDisabled() override;

        private:


        };
    }
}