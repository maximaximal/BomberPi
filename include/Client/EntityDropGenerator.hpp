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
            EntityDropGenerator(std::shared_ptr<EntityFactory> factory);
         	virtual ~EntityDropGenerator();

           	void run(glm::ivec3 tilePos);

            void setChance(unsigned int chance);
        protected:
            unsigned int m_chance = 900;
            std::shared_ptr<EntityFactory> m_entityFactory;
    };
}

#endif
