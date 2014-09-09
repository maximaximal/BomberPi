#ifndef CLIENT_BOMBCOMPONENT_HPP_INCLUDED
#define CLIENT_BOMBCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>
#include <anax/Entity.hpp>

namespace Client
{
    class BombComponent : public anax::Component<BombComponent>
    {
        public:
            BombComponent(anax::Entity bombThrower);
            virtual ~BombComponent();

            anax::Entity thrower;

            //TODO add bomb modifiers.
    };
}

#endif
