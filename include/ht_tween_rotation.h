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
        };

    }

}
