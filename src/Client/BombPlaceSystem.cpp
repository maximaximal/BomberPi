#include <Client/BombPlaceSystem.hpp>

#include <easylogging++.h>

#include <Client/PlayerInputComponent.hpp>
#include <Client/BombLayerComponent.hpp>

namespace Client
{
    BombPlaceSystem::BombPlaceSystem(EntityFactory *entityFactory)
    	: Base(anax::ComponentFilter().requires<PlayerInputComponent,
               BombLayerComponent>())
    {
        m_entityFactory = entityFactory;
    }
    BombPlaceSystem::~BombPlaceSystem()
    {

    }
    void BombPlaceSystem::update()
    {
        for(auto &entity : getEntities())
        {
            auto &input = entity.getComponent<PlayerInputComponent>();
            auto &bombLayer = entity.getComponent<BombLayerComponent>();

            if(input.isActive(PlayerInputEnum::ACTION))
            {
				if(bombLayer.canPlace())
                {
                    bombLayer.bombsRemaining -= 1;
                    m_entityFactory->createBomb(bombLayer.placePos, entity, bombLayer.getBombTiles(), bombLayer.getBombTurns());
                    bombLayer.lastPlacedBomb = -1;
                    bombLayer.positionOkay = false;
                }
            }
        }
    }
}
