#ifndef CLIENT_TIMERSYSTEM_HPP_INCLUDED
#define CLIENT_TIMERSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/TimerComponent.hpp>

namespace Client
{
    class TimerSystem : public anax::System<anax::Requires<TimerComponent>>
    {
        public:
            TimerSystem();
            virtual ~TimerSystem();

            void update(float frametime);
    };
}

#endif
