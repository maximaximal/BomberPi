#ifndef CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED
#define CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

namespace Client
{
    class PlayerMovementSystem : public anax::System<PlayerMovementSystem>
    {
        public:
            PlayerMovementSystem();
            virtual ~PlayerMovementSystem();

            void update(float frameTime);
    };
}

#endif
