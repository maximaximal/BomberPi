#ifndef CLIENT_BOMBCOMPONENT_HPP_INCLUDED
#define CLIENT_BOMBCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>
#include <anax/Entity.hpp>

namespace Client
{
    class BombComponent : public anax::Component<BombComponent>
    {
        public:
            BombComponent(anax::Entity bombThrower, int tiles = 1, int turns = 0);
            virtual ~BombComponent();

            anax::Entity thrower;
            int turns = 0;
            int tiles = 1;
    };
}

#endif
