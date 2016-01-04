#include <Client/BombPlacePositionSystem.hpp>

#include <easylogging++.h>

#include <Client/CollisionSystem.hpp>
#include <Client/EntityTypeComponent.hpp>
#include <Client/EmbeddedChunk.hpp>

namespace Client
{
    BombPlacePositionSystem::BombPlacePositionSystem(BombermanMap *bombermanMap, CollisionSystem *collisionSystem)
    {
        m_bombermanMap = bombermanMap;
        m_collisionSystem = collisionSystem;
    }
    BombPlacePositionSystem::~BombPlacePositionSystem()
    {

    }
    void BombPlacePositionSystem::update(float frametime)
    {
		for(auto &entity : getEntities())
        {
            auto &pos = entity.getComponent<PositionComponent>();
            auto &layer = entity.getComponent<BombLayerComponent>();

            if(layer.lastPlacedBomb == -1)
            {
                layer.lastPlacedBomb = 0;
            }
            if(layer.lastPlacedBomb >= 0)
            {
				layer.lastPlacedBomb += frametime;
            }

            layer.placePos = pos.pos;
            layer.placePos = ((glm::ivec2) (layer.placePos + 16) / 32) * 32;

            /*           D3
             *
             *           |
             *           |
             * D4 -------+-------   D2
             *           |
             *       360 | 0
             *
             *           D1
             */

            if(pos.orientation.x > 0)
            {
                layer.placePos.x += 1 * 32;
            }
            else if(pos.orientation.x < 0)
            {
                layer.placePos.x -= 1 * 32;
            }
            if(pos.orientation.y > 0)
            {
                layer.placePos.y += 1 * 32;
            }
            else if(pos.orientation.y < 0)
            {
                layer.placePos.y -= 1 * 32;
            }

            try
            {
                if(m_bombermanMap->getCollisionOf(glm::ivec2(layer.placePos.x / EmbeddedChunk::tileWidth,
                                                             layer.placePos.y / EmbeddedChunk::tileWidth)) == EmbeddedTilemap::NoCollision)
				{
					layer.positionOkay = true;
				}
				else
				{
					layer.positionOkay = false;
                    if(m_bombermanMap->getCollisionOf(glm::ivec2(layer.placePos.x / EmbeddedChunk::tileWidth - pos.orientation.x,
                                                                 layer.placePos.y / EmbeddedChunk::tileWidth - pos.orientation.y)) == EmbeddedTilemap::NoCollision)
                    {
						layer.positionOkay = true;
                        layer.placePos.x -= pos.orientation.x * 32;
                        layer.placePos.y -= pos.orientation.y * 32;
                    }
				}

                //Check if there is already an entity and if there is one, check if it is allowed to place a bomb on it.
                bool entityFound = false;
                auto entity = m_collisionSystem->getEntityAt(layer.placePos, entityFound);
                if(entityFound)
                {
                    layer.positionOkay = false;
                    if(entity.hasComponent<EntityTypeComponent>())
                    {
                        auto &type = entity.getComponent<EntityTypeComponent>();
                        switch(type.type)
                        {
                            case Type::Explosion:
                                layer.positionOkay = true;
                                break;
                            case Type::Player:
                                layer.positionOkay = true;
                                break;
                            default:
                                //Nothing to set; it was set previosly.
                                break;
                        }
                    }
                }
            }
            catch(std::out_of_range &e)
            {
                //Nothing to do!
				layer.positionOkay = false;
            }

            /**
              CODE FOR RADIANS (if needed later)
            if((((7 * M_PI) / 4 <= pos.rotation) && pos.rotation < 2 * M_PI)
                    || 0 <= pos.rotation && pos.rotation < M_PI / 4)
            {
                //D1
                layer.placePos.x += 1 * 32;
            }
            else if(M_PI / 4 <= pos.rotation && pos.rotation < (3 * M_PI) / 4)
            {
                //D2
                layer.placePos.y += 1 * 32;
            }
            else if((3 * M_PI) / 4 <= pos.rotation && pos.rotation < (5 * M_PI) / 4)
            {
                //D3
                layer.placePos.x -= 1 * 32;
            }
            else if((5 * M_PI) / 4 <= pos.rotation && pos.rotation < (7 * M_PI) / 4)
            {
                //D4
                layer.placePos.y -= 1 * 32;
            }
            */
        }
    }
}
