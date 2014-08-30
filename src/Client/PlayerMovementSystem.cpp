#include <Client/PlayerMovementSystem.hpp>
#include <glm/glm.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/SpriteComponent.hpp>

#include <easylogging++.h>

namespace Client
{

    PlayerMovementSystem::PlayerMovementSystem()
    	: Base(anax::ComponentFilter().requires<PlayerComponent,
               PositionComponent,
               PlayerInputComponent,
               SpriteComponent>())
    {

    }

    PlayerMovementSystem::~PlayerMovementSystem()
    {

    }

    void PlayerMovementSystem::update(float frameTime)
    {
        glm::dvec2 dir(0, 0);
		for(auto &entity : getEntities())
        {
            auto &pos = entity.getComponent<PositionComponent>();
            auto &player = entity.getComponent<PlayerComponent>();
            auto &input = entity.getComponent<PlayerInputComponent>();
            auto &sprite = entity.getComponent<SpriteComponent>();

            bool wasInput = false;

            if(input.isActive(PlayerInputEnum::UP))
            {
                dir.y -= player.speed * frameTime;
                wasInput = true;
            }
            if(input.isActive(PlayerInputEnum::DOWN))
            {
                dir.y += player.speed * frameTime;
                wasInput = true;
            }
            if(input.isActive(PlayerInputEnum::LEFT))
            {
                dir.x -= player.speed * frameTime;
                wasInput = true;
            }
            if(input.isActive(PlayerInputEnum::RIGHT))
            {
                dir.x += player.speed * frameTime;
                wasInput = true;
            }

            if(wasInput)
            {
                glm::dvec2 normal(0, -1);
				float alpha = glm::acos((glm::dot(normal, dir)) / (glm::length(normal) * glm::length(dir)));

                if(dir.x >= 0)
                {
                    alpha = (M_PI - alpha) * (-1);
                }
                else
                {
                    alpha = M_PI - alpha;
                }

				sprite.rotation = alpha * (180 / M_PI);

				pos.pos += dir;
            }
        }
    }

}
