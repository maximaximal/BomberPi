#include <Client/BombLayerComponent.hpp>

namespace Client
{
    BombLayerComponent::BombLayerComponent()
    {

    }
    BombLayerComponent::~BombLayerComponent()
    {

    }

    bool BombLayerComponent::canBomb()
    {
        if(bombsRemaining > 0)
            return true;
        return false;
    }
    void BombLayerComponent::triggerBomb()
    {
        if(bombsRemaining > 0)
			bombsRemaining--;
    }
    void BombLayerComponent::bombRemoved()
    {
        bombsRemaining++;
    }
}
