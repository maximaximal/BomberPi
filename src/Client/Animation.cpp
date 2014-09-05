#include <Client/Animation.hpp>
#include <easylogging++.h>

namespace Client
{
    Animation::Animation()
    {

    }
    Animation::~Animation()
    {

    }
    void Animation::addStep(const SDL_Rect &step)
    {
     	m_steps.push_back(step);
    }
    const SDL_Rect &Animation::getStep(unsigned int step)
    {
        if(step < m_steps.size())
			return m_steps[step];
        else
        {
            LOG(WARNING) << "Invalid step ID: " << step << " on animation!";
        }
    }

    unsigned int Animation::getStepCount()
    {
        return m_steps.size();
    }

    void Animation::setStepDuration(float duration)
    {
        m_stepDuration = duration;
    }

    float Animation::getStepDuration()
    {
        return m_stepDuration;
    }
    Animation::StepsVector &Animation::getSteps()
    {
		return m_steps;
    }
}
