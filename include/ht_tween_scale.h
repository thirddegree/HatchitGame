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

#include <ht_tween_component.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Defines a tween component that can be used to tween an object's scale.
         */
        class HT_API TweenScale : public TweenComponent
        {
        public:
            /**
             * \brief Creates a new tween scale component.
             */
            TweenScale();

            /**
             * \brief Destroys this tween scale component.
             */
            ~TweenScale();


            virtual JSON VSerialize(void) override;
            virtual bool VDeserialize(const JSON& jsonObject) override;

            /**
             * \brief Gets the start tween scale.
             */
            Math::Float3 GetStartScale() const;

            /**
             * \brief Gets the end tween scale.
             */
            Math::Float3 GetEndScale() const;

            /**
             * \brief Sets the start tween scale.
             *
             * \param value The new start scale.
             */
            void SetStartScale(const Math::Float3& value);

            /**
             * \brief Sets the end tween scale.
             *
             * \param value The new end scale.
             */
            void SetEndScale(const Math::Float3& value);

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
        };

    }

}
