#include <Client/PlayerMovementSystem.hpp>
#include <glm/glm.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/BodyComponent.hpp>

#include <easylogging++.h>

namespace Client
{

    PlayerMovementSystem::PlayerMovementSystem(std::shared_ptr<BombermanMap> bombermanMap)
    	: Base(anax::ComponentFilter().requires<PlayerComponent,
               PositionComponent,
               PlayerInputComponent,
               SpriteComponent,
               BodyComponent>())
    {
		m_bombermanMap = bombermanMap;
    }

    PlayerMovementSystem::~PlayerMovementSystem()
    {

    }

    void PlayerMovementSystem::setMap(std::shared_ptr<BombermanMap> map)
    {
        m_bombermanMap = map;
    }

    void PlayerMovementSystem::update(float frameTime)
    {
        glm::dvec2 dir(0, 0);
		for(auto &entity : getEntities())
        {
            dir.x = 0;
            dir.y = 0;
            auto &pos = entity.getComponent<PositionComponent>();
            auto &player = entity.getComponent<PlayerComponent>();
            auto &input = entity.getComponent<PlayerInputComponent>();
            auto &sprite = entity.getComponent<SpriteComponent>();
            auto &body = entity.getComponent<BodyComponent>();

            bool wasValidInput = false;

            if(input.isActive(PlayerInputEnum::UP))
            {
                dir.y -= player.speed * frameTime;
                wasValidInput = true;
            }
            if(input.isActive(PlayerInputEnum::DOWN))
            {
                dir.y += player.speed * frameTime;
                wasValidInput = true;
            }
            if(input.isActive(PlayerInputEnum::LEFT))
            {
                dir.x -= player.speed * frameTime;
                wasValidInput = true;
            }
            if(input.isActive(PlayerInputEnum::RIGHT))
            {
                dir.x += player.speed * frameTime;
                wasValidInput = true;
            }

            if(wasValidInput)
            {
                glm::ivec2 nextXBodyPos(pos.pos.x + dir.x + body.x, pos.pos.y + body.y);
                glm::ivec2 nextYBodyPos(pos.pos.x + body.x, pos.pos.y + dir.y + body.y);

                glm::ivec2 nextXBodyWidthPos(pos.pos.x + body.x + dir.x + body.w, pos.pos.y + body.y);
                glm::ivec2 nextYBodyWidthPos(pos.pos.x + body.x, pos.pos.y + dir.y + body.y + body.h);

                if(m_bombermanMap->getTileAtPixel(nextXBodyPos).physics == BombermanMapTile::SOLID)
                {
                    dir.x = 0;
                }
                if(m_bombermanMap->getTileAtPixel(nextYBodyPos).physics == BombermanMapTile::SOLID)
                {
                    dir.y = 0;
                }
                if(m_bombermanMap->getTileAtPixel(nextXBodyWidthPos).physics == BombermanMapTile::SOLID)
                {
                    dir.x = 0;
                }
                if(m_bombermanMap->getTileAtPixel(nextYBodyWidthPos).physics == BombermanMapTile::SOLID)
                {
                    dir.y = 0;
                }
            }

            if(wasValidInput && (dir.x != 0 || dir.y != 0))
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
