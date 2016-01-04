#ifndef CLIENT_ANIMATIONSYSTEM_HPP_INCLUDED
#define CLIENT_ANIMATIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/AnimationComponent.hpp>
#include <Client/SpriteComponent.hpp>

namespace Client
{
    class AnimationSystem : public anax::System<anax::Requires<AnimationComponent, SpriteComponent>>
    {
        public:
            AnimationSystem();
            virtual ~AnimationSystem();

            void update(float frametime);
    };
}

#endif
