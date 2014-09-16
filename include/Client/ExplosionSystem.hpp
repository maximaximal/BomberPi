#ifndef CLIENT_EXPLOSIONSYSTEM_HPP_INCLUDED
#define CLIENT_EXPLOSIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/EntityFactory.hpp>
#include <Client/SpreadingComponent.hpp>

namespace Client
{
    class ExplosionSystem : public anax::System<ExplosionSystem>
    {
        public:
            ExplosionSystem(BombermanMap *map, EntityFactory *entityFactory);
            virtual ~ExplosionSystem();

            void update(float frametime);
        private:
            bool spreadTo(glm::ivec2 pos, int power, int turns, Client::SpreadingComponent::SpreadingFrom from);
            bool spreadFrom(glm::ivec2 pos, int power, int turns);
            bool makeTurnFrom(glm::ivec2 pos, int power, int turns, SpreadingComponent::SpreadingFrom from);
            bool spreadFurther(glm::ivec2 pos, int power, int turns, SpreadingComponent::SpreadingFrom from);
            BombermanMap *m_map;
            EntityFactory *m_entityFactory;
    };
}

#endif
