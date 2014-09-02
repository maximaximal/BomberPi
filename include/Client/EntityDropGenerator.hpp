#ifndef CLIENT_ENTITYDROPGENERATOR_HPP
#define CLIENT_ENTITYDROPGENERATOR_HPP

#include <map>
#include <functional>

namespace Client
{
    class EntityDropGenerator
    {
        public:
            EntityDropGenerator();
         	virtual ~EntityDropGenerator();

           	void run();

            void setChance(float chance);
        protected:
            float m_chance = 90;
            std::map<unsigned int, std::function<void()>> m_entities;
    };
}

#endif
