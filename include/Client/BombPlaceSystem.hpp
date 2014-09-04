#ifndef CLIENT_BOMBPLACESYSTEM_HPP_INCLUDED
#define CLIENT_BOMBPLACESYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

#include <Client/EntityFactory.hpp>

namespace Client
{
    class BombPlaceSystem : public anax::System<BombPlaceSystem>
    {
        public:
            BombPlaceSystem(std::shared_ptr<EntityFactory> entityFactory);
            virtual ~BombPlaceSystem();

            void update();
        private:
            std::shared_ptr<EntityFactory> m_entityFactory;
    };
}

#endif
