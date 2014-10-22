#include <Client/EntityDropGenerator.hpp>
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
            unsigned int randomItem = abs(rand() % 6);

			LOG(INFO) << "Spawn Item: " << randomItem;
        }
    }
    void EntityDropGenerator::setChance(unsigned int chance)
    {
        m_chance = chance;
    }
}
