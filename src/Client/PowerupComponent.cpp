#include <Client/PowerupComponent.hpp>

namespace Client
{
    PowerupComponent::PowerupComponent(Predefined definition)
    {
		switch(definition)
        {
            case NOT_DEFINED:
                //The powerup was not defined!
                break;
            case _COUNT:
                //This should not be the case.
                break;
            case ADDITIONAL_BOMB:
                additionalBombs = 1;
                break;
            case ADDITIONAL_CORNER:
                additionalTurns = 1;
                break;
            case ADDITIONAL_TILE:
                additionalTiles = 1;
                break;
            case SPEED_MULTIPLICATOR_BONUS:
                speedMultiplicatorBonus = 0.25;
                break;
        }
        this->definition = definition;
    }
    PowerupComponent::~PowerupComponent()
    {

    }
    SDL_Rect PowerupComponent::computeRectFor(PowerupComponent *powerup)
    {
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 32;
        rect.h = 32;
		switch(powerup->definition)
        {
            case NOT_DEFINED:
                rect.y = 128;
                break;
            case _COUNT:
                //This should not be the case.
                break;
            case ADDITIONAL_BOMB:
                rect.y = 0;
                break;
            case ADDITIONAL_CORNER:
                rect.y = 96;
                break;
            case ADDITIONAL_TILE:
                rect.y = 64;
                break;
            case SPEED_MULTIPLICATOR_BONUS:
                rect.y = 32;
                break;
        }
        return rect;
    }
}
