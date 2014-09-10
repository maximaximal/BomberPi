#ifndef CLIENT_BOMBEXPLODESYSTEM_HPP_INCLUDED
#define CLIENT_BOMBEXPLODESYSTEM_HPP_INCLUDED

#include <memory>
#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>

namespace Client
{
    class BombExplodeSystem : public anax::System<BombExplodeSystem>
    {
        public:
            BombExplodeSystem(EntityFactory *entityFactory);
            virtual ~BombExplodeSystem();

            void update();
        private:
			EntityFactory *m_entityFactory;
    };
}

#endif
