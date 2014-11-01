#ifndef CLIENT_POWERUPCOMPONENT_HPP_INCLUDED
#define CLIENT_POWERUPCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>
#include <SDL2/SDL_rect.h>

namespace Client
{
    class PowerupComponent : public anax::Component<PowerupComponent>
    {
    	public:
            enum Predefined {
                ADDITIONAL_BOMB,
                ADDITIONAL_CORNER,
                ADDITIONAL_TILE,
                SPEED_MULTIPLICATOR_BONUS,

                _COUNT,
                NOT_DEFINED
            };

            PowerupComponent(Predefined definition = NOT_DEFINED);
            virtual ~PowerupComponent();

            int additionalBombs = 0;
            int additionalTurns = 0;
            int additionalTiles = 0;
            float speedMultiplicatorBonus = 0;

            Predefined definition = NOT_DEFINED;

            static SDL_Rect computeRectFor(PowerupComponent *powerup);
    };
}

#endif
