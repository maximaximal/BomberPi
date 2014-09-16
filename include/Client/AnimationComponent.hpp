#ifndef CLIENT_ANIMATIONCOMPONENT_HPP_INCLUDED
#define CLIENT_ANIMATIONCOMPONENT_HPP_INCLUDED

#include <memory>
#include <anax/Component.hpp>
#include <Client/Animation.hpp>

namespace Client
{
    class AnimationComponent : public anax::Component<AnimationComponent>
    {
        public:
            AnimationComponent();
            virtual ~AnimationComponent();

			void clear();
            /**
             * @brief animationFinished checks if the animation is finished for more convenience.
             *
             * This function uses the seconds variable and compares it to the total duration of
             * the animation set.
             *
             * @return True is the animation has finished, false otherwise (or if the animation is not
             * defined)
             */
            bool animationFinished();

            std::shared_ptr<Animation> animation;
            unsigned int currentStep = 0;
            float seconds = 0;
    };
}

#endif
