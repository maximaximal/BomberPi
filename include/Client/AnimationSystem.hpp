#ifndef CLIENT_ANIMATIONSYSTEM_HPP_INCLUDED
#define CLIENT_ANIMATIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

namespace Client
{
    class AnimationSystem : public anax::System<AnimationSystem>
    {
        public:
            AnimationSystem();
            virtual ~AnimationSystem();

            void update(float frametime);
    };
}

#endif
