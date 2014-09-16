#include <Client/ExplosionSystem.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/SpreadingComponent.hpp>

#include <easylogging++.h>

namespace Client
{
    ExplosionSystem::ExplosionSystem(BombermanMap *map, EntityFactory *entityFactory)
    	: Base(anax::ComponentFilter().requires<PositionComponent, SpreadingComponent>())
    {
		m_entityFactory = entityFactory;
        m_map = map;
    }
    ExplosionSystem::~ExplosionSystem()
    {

    }
    void ExplosionSystem::update(float frametime)
    {
        bool spreaded = false;
        for(auto &entity : getEntities())
        {
			auto &pos = entity.getComponent<PositionComponent>();
            auto &spread = entity.getComponent<SpreadingComponent>();

            if(!spread.spread)
            {
                spread.spread = true;
				if(spread.power > 0)
				{
					spread.power -= 1;

					if(spread.from == SpreadingComponent::NOWHERE)
					{
						spreadFrom(pos.pos, spread.power, spread.corners);
					}
					else
					{
						spreaded = spreadFurther(pos.pos, spread.power, spread.corners, spread.from);

						if(!spreaded)
						{
							if(spread.corners > 0)
							{
								//No spread possible; try a turn.
								spread.corners -= 1;
								makeTurnFrom(pos.pos, spread.power, spread.corners, spread.from);
							}
						}
					}
				}
            }
        }
    }
    bool ExplosionSystem::spreadTo(glm::ivec2 pos, int power, int turns, SpreadingComponent::SpreadingFrom from)
    {
		if(m_map->getTileAtPixel(glm::ivec3(pos.x, pos.y, 1)).physics == BombermanMapTile::PASSABLE
                || m_map->getTileAtPixel(glm::ivec3(pos.x, pos.y, 1)).bombable)
		{
			if(m_map->getTileAtPixel(glm::ivec3(pos.x, pos.y, 1)).bombable)
				m_map->clearTile(glm::ivec3(pos.x / 32, pos.y / 32, 1));

			m_entityFactory->createExplosion(glm::ivec2(pos.x, pos.y),
											 power,
											 turns,
                                             from);
            return true;
		}
        return false;
    }
    bool ExplosionSystem::spreadFrom(glm::ivec2 pos, int power, int turns)
    {
        bool spreaded = false;

        if(spreadTo(glm::ivec2(pos.x, pos.y - 1 * 32), power, turns, SpreadingComponent::SpreadingFrom::BOTTOM))
            spreaded = true;
        if(spreadTo(glm::ivec2(pos.x, pos.y + 1 * 32), power, turns, SpreadingComponent::SpreadingFrom::TOP))
            spreaded = true;
        if(spreadTo(glm::ivec2(pos.x + 1 * 32, pos.y), power, turns, SpreadingComponent::SpreadingFrom::LEFT))
            spreaded = true;
        if(spreadTo(glm::ivec2(pos.x - 1 * 32, pos.y), power, turns, SpreadingComponent::SpreadingFrom::RIGHT))
            spreaded = true;
        return spreaded;
    }
    bool ExplosionSystem::makeTurnFrom(glm::ivec2 pos, int power, int turns, SpreadingComponent::SpreadingFrom from)
    {
        bool spreaded = false;

        if(from != SpreadingComponent::BOTTOM)
			if(spreadTo(glm::ivec2(pos.x, pos.y - 1 * 32), power, turns, SpreadingComponent::SpreadingFrom::BOTTOM))
				spreaded = true;
        if(from != SpreadingComponent::TOP)
			if(spreadTo(glm::ivec2(pos.x, pos.y + 1 * 32), power, turns, SpreadingComponent::SpreadingFrom::TOP))
				spreaded = true;
        if(from != SpreadingComponent::LEFT)
			if(spreadTo(glm::ivec2(pos.x + 1 * 32, pos.y), power, turns, SpreadingComponent::SpreadingFrom::LEFT))
				spreaded = true;
        if(from != SpreadingComponent::RIGHT)
			if(spreadTo(glm::ivec2(pos.x - 1 * 32, pos.y), power, turns, SpreadingComponent::SpreadingFrom::RIGHT))
				spreaded = true;

        return spreaded;
    }

    bool ExplosionSystem::spreadFurther(glm::ivec2 pos, int power, int turns, SpreadingComponent::SpreadingFrom from)
    {
        bool spreaded = false;

        if(from == SpreadingComponent::BOTTOM)
			if(spreadTo(glm::ivec2(pos.x, pos.y - 1 * 32), power, turns, SpreadingComponent::SpreadingFrom::BOTTOM))
				spreaded = true;
        if(from == SpreadingComponent::TOP)
			if(spreadTo(glm::ivec2(pos.x, pos.y + 1 * 32), power, turns, SpreadingComponent::SpreadingFrom::TOP))
				spreaded = true;
        if(from == SpreadingComponent::LEFT)
			if(spreadTo(glm::ivec2(pos.x + 1 * 32, pos.y), power, turns, SpreadingComponent::SpreadingFrom::LEFT))
				spreaded = true;
        if(from == SpreadingComponent::RIGHT)
			if(spreadTo(glm::ivec2(pos.x - 1 * 32, pos.y), power, turns, SpreadingComponent::SpreadingFrom::RIGHT))
				spreaded = true;

        return spreaded;
    }
}
