#ifndef CLIENT_EXPLOSIONSYSTEM_HPP_INCLUDED
#define CLIENT_EXPLOSIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/EntityFactory.hpp>

namespace Client
{
    class ExplosionSystem : public anax::System<ExplosionSystem>
    {
        public:
            ExplosionSystem(BombermanMap *map, EntityFactory *entityFactory);
            virtual ~ExplosionSystem();

            void update(float frametime);
        private:
            BombermanMap *m_map;
            EntityFactory *m_entityFactory;
    };
}

#endif
