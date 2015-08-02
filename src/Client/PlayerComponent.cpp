#include <Client/PlayerComponent.hpp>

namespace Client
{
    PlayerComponent::PlayerComponent()
    {

    }

    PlayerComponent::PlayerComponent(const glm::ivec2 &startingPos)
    {
        this->startingPos = startingPos;
    }
    PlayerComponent::PlayerComponent(const glm::ivec2 &startingPos, std::shared_ptr<Player> player)
    {
        this->startingPos = startingPos;
        this->player = player;
    }
    PlayerComponent::~PlayerComponent()
    {

    }
}
