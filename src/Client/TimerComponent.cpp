#include <Client/TimerComponent.hpp>

namespace Client
{
    TimerComponent::TimerComponent()
    {
        reset();
    }
    TimerComponent::~TimerComponent()
    {

    }
    void TimerComponent::reset()
    {
        seconds = 0;
        complete = false;
        timeToPass = 1;
    }
}
