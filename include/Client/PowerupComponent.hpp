#ifndef CLIENT_POWERUPCOMPONENT_HPP_INCLUDED
#define CLIENT_POWERUPCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class PowerupComponent : public anax::Component<PowerupComponent>
    {
    	public:
            PowerupComponent();
            virtual ~PowerupComponent();

            int additionalBombs = 0;
            int additionalTurns = 0;
            int additionalTiles = 0;
            float speedMultiplicator = 0;
    };
}

#endif
