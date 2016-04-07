#include <ht_tween_component.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Defines a tween component that can be used to tween an object's position.
         */
        class TweenPosition : public TweenComponent
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
