#ifndef CLIENT_INVINCIBLESYSTEM_HPP_INCLUDED
#define CLIENT_INVINCIBLESYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

namespace Client
{
    class InvincibleSystem : public anax::System<InvincibleSystem>
    {
        public:
            InvincibleSystem();
            virtual ~InvincibleSystem();

            void update(float frametime);
    };
}

#endif
