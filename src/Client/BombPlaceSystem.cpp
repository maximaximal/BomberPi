#include <Client/BombPlaceSystem.hpp>

#include <easylogging++.h>

#include <Client/PlayerInputComponent.hpp>
#include <Client/BombLayerComponent.hpp>

namespace Client
{
    BombPlaceSystem::BombPlaceSystem(EntityFactory *entityFactory)
    {
        m_entityFactory = entityFactory;
    }
    BombPlaceSystem::~BombPlaceSystem()
    {

    }
    void BombPlaceSystem::update()
    {
        if(m_noBombPlacing)
        {
            return;
        }
        for(auto &entity : getEntities())
        {
            auto &input = entity.getComponent<PlayerInputComponent>();
            auto &bombLayer = entity.getComponent<BombLayerComponent>();

            if(input.isActive(PlayerInputEnum::ACTION))
            {
				if(bombLayer.canPlace())
                {
                    m_entityFactory->createBomb(bombLayer.placePos, entity, bombLayer.getBombTiles(), bombLayer.getBombTurns());

                    if(bombLayer.bombsRemaining == 0)
                    {
                        bombLayer.powerupQueue.removeOneOfPredefined(Powerup::ADDITIONAL_BOMB);
                    }
                    else
                    {
                        bombLayer.bombsRemaining -= 1;
                    }
                    bombLayer.lastPlacedBomb = -1;

                    bombLayer.positionOkay = false;
                }
            }
        }
    }
    void BombPlaceSystem::lockBombPlacing(bool state)
    {
        m_noBombPlacing = state;
    }
}
