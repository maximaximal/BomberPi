#include <Client/EntityDropGenerator.hpp>
#include <Client/PowerupComponent.hpp>
#include <easylogging++.h>

namespace Client
{
    EntityDropGenerator::EntityDropGenerator(EntityFactory *factory)
    {
		m_entityFactory = factory;
    }
    EntityDropGenerator::~EntityDropGenerator()
    {

    }

    void EntityDropGenerator::run(glm::ivec3 tilePos)
    {
        unsigned int randomValue = abs(rand() % 1000);
        if(randomValue <= m_chance)
        {
            //Spawn something!
            unsigned int randomItem = abs(rand() % PowerupComponent::_COUNT);
            PowerupComponent::Predefined def = static_cast<PowerupComponent::Predefined>(randomItem);

            PowerupComponent *powerup = new PowerupComponent(def);
            m_entityFactory->createPowerup(glm::ivec2(tilePos.x * 32, tilePos.y * 32), powerup,
                                           "powerups.png", PowerupComponent::computeRectFor(powerup));
        }
    }
    void EntityDropGenerator::setChance(unsigned int chance)
    {
        m_chance = chance;
    }
}
