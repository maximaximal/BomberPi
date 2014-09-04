#ifndef CLIENT_TIMERSYSTEM_HPP_INCLUDED
#define CLIENT_TIMERSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

namespace Client
{
    class TimerSystem : public anax::System<TimerSystem>
    {
        public:
            TimerSystem();
            virtual ~TimerSystem();

            void update(float frametime);
    };
}

#endif
