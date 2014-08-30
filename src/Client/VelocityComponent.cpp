#include <Client/VelocityComponent.hpp>

namespace Client
{

    VelocityComponent::VelocityComponent()
    {
		clear();
    }
    VelocityComponent::VelocityComponent(glm::dvec2 vel)
    {
		velocity.x = vel.x;
		velocity.y = vel.y;
    }
    VelocityComponent::VelocityComponent(double x, double y)
    {
		velocity.x = x;
		velocity.y = y;
    }
    VelocityComponent::VelocityComponent(int x, int y)
    {
        velocity.x = x;
        velocity.y = y;
    }
    VelocityComponent::~VelocityComponent()
    {

    }

    void VelocityComponent::clear()
    {
        velocity.x = 0;
        velocity.y = 0;
    }
}
