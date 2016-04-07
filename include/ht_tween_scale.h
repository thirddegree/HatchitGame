#include <ht_tween_component.h>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Defines a tween component that can be used to tween an object's scale.
         */
        class TweenScale : public TweenComponent
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
        };

    }

}
