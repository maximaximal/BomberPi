#ifndef CLIENT_PLAYERCOMPONENT_HPP_INCLUDED
#define CLIENT_PLAYERCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class PlayerComponent : public anax::Component<PlayerComponent>
    {
        public:
            PlayerComponent();
            virtual ~PlayerComponent();

            float speed = 100;
    };
}

#endif
