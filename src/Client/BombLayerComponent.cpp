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
        this->speedMultiplicator = 1;
        this->bombTurns = 0;
        this->bombTiles = 1;
        powerupQueue.reset();
    }
    short BombLayerComponent::getBombsRemaining()
    {
        return bombsRemaining + powerupQueue.getCombinedPowerup().getAdditionalBombs();
    }
    float BombLayerComponent::getSpeedMultiplicator()
    {
        return speedMultiplicator + powerupQueue.getCombinedPowerup().getSpeedMultiplicatorBonus();
    }
    int BombLayerComponent::getBombTurns()
    {
        return bombTurns + powerupQueue.getCombinedPowerup().getAdditionalCorners();
    }
    int BombLayerComponent::getBombTiles()
    {
        return bombTiles + powerupQueue.getCombinedPowerup().getAdditionalTiles();
    }
    bool BombLayerComponent::canPlace()
    {
        if(getBombsRemaining() > 0 && lastPlacedBomb >= cooldown && positionOkay)
        {
            return true;
        }
        return false;
    }
}
