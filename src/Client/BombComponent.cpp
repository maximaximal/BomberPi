#include <Client/BombComponent.hpp>

namespace Client
{
    BombComponent::BombComponent(anax::Entity bombThrower, int tiles, int turns)
    {
        thrower = bombThrower;
        this->tiles = tiles;
        this->turns = turns;
    }
    BombComponent::~BombComponent()
    {

    }
}
