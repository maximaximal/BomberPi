#ifndef CLIENT_BOMBPLACESYSTEM_HPP_INCLUDED
#define CLIENT_BOMBPLACESYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

#include <Client/EntityFactory.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/BombLayerComponent.hpp>

namespace Client
{
    class BombPlaceSystem : public anax::System<anax::Requires<PlayerInputComponent, BombLayerComponent>>
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
