#include <Client/PlayerComponent.hpp>

namespace Client
{
    PlayerComponent::PlayerComponent()
    {

    }

    PlayerComponent::PlayerComponent(float speed, const glm::ivec2 &startingPos)
    {
        this->speed = speed;
        this->startingPos = startingPos;
    }
    PlayerComponent::PlayerComponent(float speed, const glm::ivec2 &startingPos, std::shared_ptr<Player> player)
    {
        this->speed = speed;
        this->startingPos = startingPos;
        this->player = player;
    }
    PlayerComponent::~PlayerComponent()
    {

    }
}
