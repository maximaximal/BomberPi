#ifndef CLIENT_BOMBCOMPONENT_HPP_INCLUDED
#define CLIENT_BOMBCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class BombComponent : public anax::Component<BombComponent>
    {
        public:
            BombComponent();
            virtual ~BombComponent();

            //TODO add bomb modifiers.
    };
}

#endif
