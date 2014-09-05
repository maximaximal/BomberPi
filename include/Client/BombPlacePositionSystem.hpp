#ifndef CLIENT_BOMBPLACEPOSITIONSYSTEM_HPP_INCLUDED
#define CLIENT_BOMBPLACEPOSITIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>

namespace Client
{
    class BombPlacePositionSystem : public anax::System<BombPlacePositionSystem>
    {
        public:
            BombPlacePositionSystem(std::shared_ptr<BombermanMap> bombermanMap);
            virtual ~BombPlacePositionSystem();

            void update();
        private:
            std::shared_ptr<BombermanMap> m_bombermanMap;
    };
}

#endif
