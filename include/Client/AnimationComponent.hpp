#ifndef CLIENT_ANIMATIONCOMPONENT_HPP_INCLUDED
#define CLIENT_ANIMATIONCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>
#include <Client/Animation.hpp>

namespace Client
{
    class AnimationComponent : anax::Component<AnimationComponent>
    {
        public:
            AnimationComponent();
            virtual ~AnimationComponent();

			void clear();

            std::shared_ptr<Animation> animation;
    };
}

#endif
