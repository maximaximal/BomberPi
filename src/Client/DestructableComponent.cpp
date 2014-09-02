#include <Client/DestructableComponent.hpp>

namespace Client
{
    DestructableComponent::DestructableComponent()
    {

    }
    DestructableComponent::DestructableComponent(unsigned int health)
    {
     	this->health = health;
        this->resistance = health;
    }
    DestructableComponent::DestructableComponent(unsigned int health, unsigned int resistance)
    {
        this->health = health;
        this->resistance = resistance;
    }
    DestructableComponent::~DestructableComponent()
    {

    }
}
