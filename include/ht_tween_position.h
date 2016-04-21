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
         * \brief Defines a tween component that can be used to tween an object's position.
         */
        class HT_API TweenPosition : public TweenComponent
        {
        public:
            /**
             * \brief Creates a new tween position component.
             */
            TweenPosition();

            /**
             * \brief Destroys this tween position component.
             */
            ~TweenPosition();

            virtual Core::JSON VSerialize(void) override;
            virtual bool VDeserialize(Core::JSON& jsonObject) override;

            /**
             * \brief Gets the start tween position.
             */
            Math::Float3 GetStartPosition() const;

            /**
             * \brief Gets the end tween position.
             */
            Math::Float3 GetEndPosition() const;

            /**
             * \brief Sets the start tween position.
             *
             * \param value The new start position.
             */
            void SetStartPosition(const Math::Float3& value);

            /**
             * \brief Sets the end tween position.
             *
             * \param value The new end position.
             */
            void SetEndPosition(const Math::Float3& value);

            /**
             * \brief Called once per frame while the GameObject is enabled.
             *
             * Updates all components first, then all child gameobjects.
             */
            void VOnUpdate() final override;
        };

    }

}
