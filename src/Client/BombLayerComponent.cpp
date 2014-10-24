#include <Client/BombLayerComponent.hpp>
#include <Client/Config.hpp>

namespace Client
{
    BombLayerComponent::BombLayerComponent()
    {
        this->lastPlacedBomb = cooldown;
    }

    BombLayerComponent::BombLayerComponent(float cooldown)
    {
        this->cooldown = cooldown;
        this->lastPlacedBomb = cooldown;
    }
    BombLayerComponent::~BombLayerComponent()
    {

    }
    void BombLayerComponent::reset()
    {
        this->lastPlacedBomb = cooldown;
        this->bombsRemaining = 1;
        this->bombsRemainingMax = 1;
        this->speedBonus = 0;
    }
    bool BombLayerComponent::canPlace()
    {
        if(bombsRemaining > 0 && lastPlacedBomb >= cooldown && positionOkay)
        {
            return true;
        }
        return false;
    }
}
