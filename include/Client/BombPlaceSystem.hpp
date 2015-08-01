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

            void lockBombPlacing(bool state);
        private:
            EntityFactory *m_entityFactory;
            bool m_noBombPlacing = false;
    };
}

#endif
