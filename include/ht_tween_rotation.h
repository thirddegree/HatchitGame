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

#include <ht_tween_component.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Defines a tween component that can be used to tween an object's rotation.
         */
        class HT_API TweenRotation : public TweenComponent
        {
        public:
            /**
             * \brief Creates a new tween rotation component.
             */
            TweenRotation();

            /**
             * \brief Destroys this tween rotation component.
             */
            ~TweenRotation();

            virtual Core::JSON VSerialize(void) override;
            virtual bool VDeserialize(const Core::JSON& jsonObject) override;

            /**
             * \brief Gets the start tween rotation.
             */
            Math::Float3 GetStartRotation() const;

            /**
             * \brief Gets the end tween rotation.
             */
            Math::Float3 GetEndRotation() const;

            /**
             * \brief Sets the start tween rotation.
             *
             * \param value The new start rotation.
             */
            void SetStartRotation(const Math::Float3& value);

            /**
             * \brief Sets the end tween rotation.
             *
             * \param value The new end rotation.
             */
            void SetEndRotation(const Math::Float3& value);

            /**
             * \brief Called once per frame while the GameObject is enabled.
             *
             * Updates all components first, then all child gameobjects.
             */
            void VOnUpdate() final override;

            /**
            * \brief Creates a copy of this Component.
            */
            Component* VClone(void) const override;

            virtual Core::Guid VGetComponentId(void) const override;
        };

    }

}
