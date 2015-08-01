#include <Client/PlayerMovementSystem.hpp>
#include <glm/glm.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/EntityTypeComponent.hpp>
#include <Client/BombLayerComponent.hpp>
#include <Client/EmbeddedChunk.hpp>

#include <easylogging++.h>

namespace Client
{

    PlayerMovementSystem::PlayerMovementSystem(BombermanMap *bombermanMap, CollisionSystem *collisionSystem)
    	: Base(anax::ComponentFilter().requires<PlayerComponent,
               PositionComponent,
               PlayerInputComponent,
               SpriteComponent,
               BodyComponent,
               BombLayerComponent>())
    {
		m_bombermanMap = bombermanMap;
        m_collisionSystem = collisionSystem;
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
		for(auto &entity : getEntities())
        {
            auto &pos = entity.getComponent<PositionComponent>();
            auto &player = entity.getComponent<PlayerComponent>();
            auto &input = entity.getComponent<PlayerInputComponent>();
            auto &sprite = entity.getComponent<SpriteComponent>();
            auto &body = entity.getComponent<BodyComponent>();
            auto &bombLayer = entity.getComponent<BombLayerComponent>();

            //Check if the target has been reached.
            if(std::abs(pos.pos.x - body.targetPos.x) <= player.speed * frameTime * 2
                    && std::abs(pos.pos.y - body.targetPos.y) <= player.speed * frameTime * 2)
            {
                pos.pos.x = body.targetPos.x;
                pos.pos.y = body.targetPos.y;
                body.movementDirection = BodyComponent::NOT_MOVING;
            }

            //Assign new movement
            if(!body.currentlyMoving())
            {
                BodyComponent::MovementDirection dir = BodyComponent::NOT_MOVING;
                glm::ivec2 target;

                for(auto &in : input.inputs)
                {
                    if(in.second)
                    {
                        if(in.first == PlayerInputEnum::UP
                                || in.first == PlayerInputEnum::DOWN
                                || in.first == PlayerInputEnum::LEFT
                                || in.first == PlayerInputEnum::RIGHT)
                        {
                            target = body.targetPos;
                            dir = body.movementDirection;
                            calculateTarget(in.first, body, pos);

                            //Direction-Detection level entity detection.
                            bool found = false;
                            bool blockedByEntity = false;

                            anax::Entity e = m_collisionSystem->getEntityAt(glm::ivec2(body.targetPos.x, body.targetPos.y), found);

                            if(found)
                            {
                                if(e.hasComponent<EntityTypeComponent>())
                                {
                                    auto &type = e.getComponent<EntityTypeComponent>();
                                    if(type.type == Type::Bomb)
                                    {
                                        blockedByEntity = true;
                                    }
                                }
                            }

                            if(m_bombermanMap->getCollisionOf(glm::ivec2(body.targetPos.x / EmbeddedChunk::tileWidth,
                                                                         body.targetPos.y / EmbeddedChunk::tileWidth))
                                                              == static_cast<uint8_t>(EmbeddedTilemap::CollideFully)
                                    || blockedByEntity)
                            {
                                //If the new target is not a valid one (obstructed), set the old one instead.
                                body.movementDirection = dir;
                                body.targetPos = target;
                            }
                        }
                    }
                }

                //Final entity detection

                bool found = false;
                bool blockedByEntity = false;

                anax::Entity e = m_collisionSystem->getEntityAt(glm::ivec2(body.targetPos.x, body.targetPos.y), found);

                if(found)
                {
                    if(e.hasComponent<EntityTypeComponent>())
                    {
                        auto &type = e.getComponent<EntityTypeComponent>();
                        if(type.type == Type::Bomb)
                        {
                            blockedByEntity = true;
                        }
                    }
                }

                if(m_bombermanMap->getCollisionOf(glm::ivec2(body.targetPos.x / EmbeddedChunk::tileWidth,
                                                             body.targetPos.y / EmbeddedChunk::tileWidth))
                                                  == static_cast<uint8_t>(EmbeddedTilemap::CollideFully)
                        || blockedByEntity)
                {
                    body.movementDirection = BodyComponent::NOT_MOVING;
                }
            }

            //Move the character
            switch(body.movementDirection)
            {
                case BodyComponent::UP:
                    pos.pos.y -= player.speed * frameTime;
                    break;
                case BodyComponent::DOWN:
                    pos.pos.y += player.speed * frameTime;
                    break;
                case BodyComponent::LEFT:
                    pos.pos.x -= player.speed * frameTime;
                    break;
                case BodyComponent::RIGHT:
                    pos.pos.x += player.speed * frameTime;
                    break;
                default:
                    break;
            }
        }
    }
    void PlayerMovementSystem::onPlayerCollision(std::shared_ptr<Collision> collision)
    {
        if(collision->getType() == Collision::EntityWithRect)
        {
			auto &playerPos = collision->getA().getComponent<PositionComponent>();
			auto &playerBody = collision->getA().getComponent<BodyComponent>();
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
    void PlayerMovementSystem::calculateTarget(PlayerInputEnum dir, BodyComponent &body, PositionComponent &pos)
    {
        switch(dir)
        {
            case PlayerInputEnum::UP:
                body.targetPos.x = pos.pos.x;
                body.targetPos.y = pos.pos.y - EmbeddedChunk::tileWidth;
                body.movementDirection = BodyComponent::UP;
                break;
            case PlayerInputEnum::DOWN:
                body.movementDirection = BodyComponent::DOWN;
                body.targetPos.x = pos.pos.x;
                body.targetPos.y = pos.pos.y + EmbeddedChunk::tileWidth;
                break;
            case PlayerInputEnum::LEFT:
                body.movementDirection = BodyComponent::LEFT;
                body.targetPos.x = pos.pos.x - EmbeddedChunk::tileWidth;
                body.targetPos.y = pos.pos.y;
                break;
            case PlayerInputEnum::RIGHT:
                body.movementDirection = BodyComponent::RIGHT;
                body.targetPos.x = pos.pos.x + EmbeddedChunk::tileWidth;
                body.targetPos.y = pos.pos.y;
                break;
            default:
                break;
        }
    }
}
