#ifndef CLIENT_TIMERCOMPONENT_HPP_INCLUDED
#define CLIENT_TIMERCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class TimerComponent : public anax::Component
    {
        public:
            TimerComponent();
            virtual ~TimerComponent();

            void reset();

            bool complete = false;
            /**
             * @brief The time (in seconds) the timer has to pass to run out.
             */
            float timeToPass = 1;
            float seconds = 0;
    };
}

#endif
