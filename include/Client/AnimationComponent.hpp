#ifndef CLIENT_ANIMATIONCOMPONENT_HPP_INCLUDED
#define CLIENT_ANIMATIONCOMPONENT_HPP_INCLUDED

#include <memory>
#include <anax/Component.hpp>
#include <Client/Animation.hpp>

namespace Client
{
    class AnimationComponent : public anax::Component
    {
        public:
            AnimationComponent();
            AnimationComponent(std::shared_ptr<Animation> animation, bool killAfterFinish = false);
            virtual ~AnimationComponent();

			void clear();

            bool finished = false;
            std::shared_ptr<Animation> animation;
            unsigned int currentStep = 0;
            float seconds = 0;
            bool killAfterFinish = false;
    };
}

#endif
