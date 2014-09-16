#include <Client/SpreadingComponent.hpp>

namespace Client
{
    SpreadingComponent::SpreadingComponent(int power, int corners, SpreadingComponent::SpreadingFrom from)
    {
        this->power = power;
        this->corners = corners;
        this->from = from;
    }
    SpreadingComponent::SpreadingComponent()
    {

    }
    SpreadingComponent::~SpreadingComponent()
    {

    }
}
