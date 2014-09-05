#ifndef CLIENT_BOMBPLACEPOSITIONSYSTEM_HPP_INCLUDED
#define CLIENT_BOMBPLACEPOSITIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

namespace Client
{
    class BombPlacePositionSystem : public anax::System<BombPlacePositionSystem>
    {
        public:
            BombPlacePositionSystem();
            virtual ~BombPlacePositionSystem();

            void update();
    };
}

#endif
