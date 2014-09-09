#include <Client/BombComponent.hpp>

namespace Client
{
    BombComponent::BombComponent(anax::Entity bombThrower)
    {
		thrower = bombThrower;
    }
    BombComponent::~BombComponent()
    {

    }
}
