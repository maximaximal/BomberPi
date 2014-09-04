#include <Client/BombPlaceSystem.hpp>

#include <Client/PlayerInputComponent.hpp>
#include <Client/PositionComponent.hpp>

namespace Client
{
    BombPlaceSystem::BombPlaceSystem(std::shared_ptr<EntityFactory> entityFactory)
    	: Base(anax::ComponentFilter().requires<PlayerInputComponent, PositionComponent>())
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
            auto input = entity.getComponent<PlayerInputComponent>();
            auto pos = entity.getComponent<PositionComponent>();

            if(input.isActive(PlayerInputEnum::ACTION))
            {
                m_entityFactory->createBomb(pos.pos, entity);
            }
        }
    }
}
