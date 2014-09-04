#include <Client/TimerSystem.hpp>

#include <Client/TimerComponent.hpp>

namespace Client
{
    TimerSystem::TimerSystem()
    	: Base(anax::ComponentFilter().requires<TimerComponent>())
    {

    }
    TimerSystem::~TimerSystem()
    {

    }
    void TimerSystem::update(float frametime)
    {
        for(auto &entity: getEntities())
        {
            auto &timer = entity.getComponent<TimerComponent>();
            if(!timer.complete)
            {
				timer.seconds += frametime;
				if(timer.seconds > timer.timeToPass)
				{
					timer.complete = true;
				}
            }
        }
    }
}
