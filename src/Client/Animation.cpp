#include <Client/Animation.hpp>
#include <easylogging++.h>

#include <yaml-cpp/yaml.h>

namespace Client
{
    Animation::Animation()
    {

    }

    Animation::Animation(const std::string &definitionPath)
    {

    }
    Animation::~Animation()
    {

    }

    void Animation::loadDefinition(const std::string &definitionPath)
    {
        /**
         * Example Definition File:
         *
         *
         */
		YAML::Node definition = YAML::LoadAllFromFile(definitionPath).front();
        if(definition['step-duration'])
        {
        	m_stepDuration = definition['step-duration'].as<float>();
        }

        if(definition['steps'])
        {
            m_steps.clear();
			SDL_Rect step;
            for(YAML::const_iterator it = definition['steps'].begin(); it != definition['steps'].end(); ++it)
			{
                step.x = 0;
                step.y = 0;
                step.w = 0;
                step.h = 0;

				if((*it)['x'])
                    step.x = (*it)['x'].as<int>();
				if((*it)['y'])
                    step.y = (*it)['y'].as<int>();
				if((*it)['w'])
                    step.w = (*it)['w'].as<int>();
				if((*it)['h'])
                    step.h = (*it)['h'].as<int>();
			}
        }
        if(definition['sequence'])
        {
            YAML::Node sequence = definition['sequence'];

        }
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

    float Animation::getTotalDuration()
    {
        return m_stepDuration * m_steps.size();
    }
    Animation::StepsVector &Animation::getSteps()
    {
		return m_steps;
    }
}
