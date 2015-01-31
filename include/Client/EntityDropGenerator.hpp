#ifndef CLIENT_ENTITYDROPGENERATOR_HPP
#define CLIENT_ENTITYDROPGENERATOR_HPP

#include <map>
#include <functional>
#include <memory>
#include <Client/EntityFactory.hpp>
#include <glm/vec3.hpp>

namespace Client
{
    class EntityDropGenerator
    {
        public:
            EntityDropGenerator(EntityFactory *factory);
         	virtual ~EntityDropGenerator();

           	void run(const glm::ivec3 &tilePos);

            void setChance(unsigned int chance);
        protected:
            unsigned int m_chance = 900;
            EntityFactory *m_entityFactory;
    };
}

#endif
