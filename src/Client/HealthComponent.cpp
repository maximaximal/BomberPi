#include <Client/HealthComponent.hpp>

namespace Client
{
    HealthComponent::HealthComponent()
    {

    }
    HealthComponent::HealthComponent(int health, PiH::HealthAndNameDisplay *display)
    {
        this->health = health;
        this->display = display;
    }
    HealthComponent::~HealthComponent()
    {

    }
}
