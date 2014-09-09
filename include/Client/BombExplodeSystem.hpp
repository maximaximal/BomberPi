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
            BombExplodeSystem(std::shared_ptr<EntityFactory> entityFactory);
            virtual ~BombExplodeSystem();

            void update();
        private:
			std::shared_ptr<EntityFactory> m_entityFactory;
    };
}

#endif
