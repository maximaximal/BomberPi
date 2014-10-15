#ifndef CLIENT_PLAYERCOMPONENT_HPP_INCLUDED
#define CLIENT_PLAYERCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>
#include <glm/vec2.hpp>

namespace Client
{
    class PlayerComponent : public anax::Component<PlayerComponent>
    {
        public:
            PlayerComponent();
            PlayerComponent(float speed, const glm::ivec2 &startingPos);
            virtual ~PlayerComponent();

            float speed = 150;
            glm::ivec2 startingPos;
    };
}

#endif
