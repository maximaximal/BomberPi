#ifndef CLIENT_BOMBLAYERCOMPONENT_HPP_INCLUDED
#define CLIENT_BOMBLAYERCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class BombLayerComponent : public anax::Component<BombLayerComponent>
    {
        public:
            BombLayerComponent();
            virtual ~BombLayerComponent();

            bool canBomb();
           	void triggerBomb();
            void bombRemoved();

            short bombsRemaining = 1;

            //TODO Bomb modifiers.
    };
}

#endif
