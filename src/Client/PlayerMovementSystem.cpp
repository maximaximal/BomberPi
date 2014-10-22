#include <Client/PlayerMovementSystem.hpp>
#include <glm/glm.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/EntityTypeComponent.hpp>

#include <easylogging++.h>

namespace Client
{

    PlayerMovementSystem::PlayerMovementSystem(BombermanMap *bombermanMap)
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

    void PlayerMovementSystem::setMap(BombermanMap *map)
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

				pos.orientation = glm::normalize(dir);

                body.lastMove = dir;

				pos.pos += dir;
            }
        }
    }
    void PlayerMovementSystem::onPlayerCollision(std::shared_ptr<Collision> collision)
    {
        if(collision->getType() == Collision::EntityWithRect)
        {
			auto &playerPos = collision->getA().getComponent<PositionComponent>();
			auto &playerBody = collision->getA().getComponent<BodyComponent>();
			playerPos.pos = playerPos.pos - playerBody.lastMove;
			//playerPos.pos = playerPos.pos + collision->getPenetrationVec();
        }
        if(collision->getType() == Collision::EntityWithEntity)
        {
            auto &B = collision->getB();
            if(B.hasComponent<EntityTypeComponent>())
            {
                auto &type = B.getComponent<EntityTypeComponent>();
                if(type.type == Type::Bomb)
                {
					auto &playerPos = collision->getA().getComponent<PositionComponent>();
					auto &playerBody = collision->getA().getComponent<BodyComponent>();

                }
            }

        }
    }
    void PlayerMovementSystem::onEntityRemoved(anax::Entity &e)
    {
        if(m_collisionConnections.count(e.getId()) > 0)
        {
            m_collisionConnections.erase(e.getId());
        }
    }
}
