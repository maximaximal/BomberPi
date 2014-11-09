#include <Client/PowerupComponent.hpp>

namespace Client
{
    PowerupComponent::PowerupComponent(Powerup::Predefined definition)
    {
        powerup = std::make_shared<Powerup>(definition);
    }
    PowerupComponent::~PowerupComponent()
    {

    }
}
