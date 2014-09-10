#ifndef CLIENT_BOMBPLACESYSTEM_HPP_INCLUDED
#define CLIENT_BOMBPLACESYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

#include <Client/EntityFactory.hpp>

namespace Client
{
    class BombPlaceSystem : public anax::System<BombPlaceSystem>
    {
        public:
            BombPlaceSystem(EntityFactory *entityFactory);
            virtual ~BombPlaceSystem();

            void update();
        private:
            EntityFactory *m_entityFactory;
    };
}

#endif
