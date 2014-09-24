#include <Client/BombPlacePositionSystem.hpp>

#include <easylogging++.h>

#include <Client/PositionComponent.hpp>
#include <Client/BombLayerComponent.hpp>

namespace Client
{
    BombPlacePositionSystem::BombPlacePositionSystem(BombermanMap *bombermanMap)
    	: Base(anax::ComponentFilter().requires<BombLayerComponent,
               PositionComponent>())
    {
		m_bombermanMap = bombermanMap;
    }
    BombPlacePositionSystem::~BombPlacePositionSystem()
    {

    }
    void BombPlacePositionSystem::update()
    {
		for(auto &entity : getEntities())
        {
            auto &pos = entity.getComponent<PositionComponent>();
            auto &layer = entity.getComponent<BombLayerComponent>();

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
				if(m_bombermanMap->getTileAtPixel(glm::ivec3(layer.placePos.x, layer.placePos.y, 1)).physics
						== BombermanMapTile::PASSABLE)
				{
					layer.canPlace = true;
				}
				else
				{
					layer.canPlace = false;
					if(m_bombermanMap->getTileAtPixel(glm::ivec3(layer.placePos.x - pos.orientation.x * 32, layer.placePos.y - pos.orientation.y * 32, 1)).physics
							== BombermanMapTile::PASSABLE)
                    {
						layer.canPlace = true;
                        layer.placePos.x -= pos.orientation.x * 32;
                        layer.placePos.y -= pos.orientation.y * 32;
                    }
				}
            }
            catch(std::out_of_range &e)
            {
                //Nothing to do!
				layer.canPlace = false;
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
