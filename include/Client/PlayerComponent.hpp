#ifndef CLIENT_PLAYERCOMPONENT_HPP_INCLUDED
#define CLIENT_PLAYERCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>
#include <glm/vec2.hpp>
#include <memory>

namespace Client
{
    class Player;

    class PlayerComponent : public anax::Component<PlayerComponent>
    {
        public:
            PlayerComponent();
            PlayerComponent(const glm::ivec2 &startingPos);
            PlayerComponent(const glm::ivec2 &startingPos, std::shared_ptr<Player> player);
            virtual ~PlayerComponent();

            glm::ivec2 startingPos;
            std::shared_ptr<Player> player;
    };
}

#endif
