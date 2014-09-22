#include <Client/Animation.hpp>
#include <easylogging++.h>
#include <glm/vec2.hpp>
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
        if(definition["step-duration"])
        {
            m_stepDuration = definition["step-duration"].as<float>();
        }

        if(definition["steps"])
        {
            m_steps.clear();
			SDL_Rect step;
            for(YAML::const_iterator it = definition["steps"].begin(); it != definition["steps"].end(); ++it)
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

                this->addStep(step);
			}
        }
        if(definition["sequence"])
        {
            YAML::Node sequence = definition["sequence"];

            glm::ivec2 sequenceRoot;
            glm::ivec2 textureSize;
            int count;

            if(sequence["x"])
                sequenceRoot.x = sequence["x"].as<int>();
            if(sequence["y"])
                sequenceRoot.y = sequence["y"].as<int>();

            if(sequence["w"])
                textureSize.x = sequence["w"].as<int>();
            if(sequence["h"])
                textureSize.y = sequence["h"].as<int>();

            if(sequence["count"])
                count = sequence["count"].as<int>();

            SDL_Rect step;

            for(int i = 0; i < count; ++i)
            {
                step.x = 0;
                step.y = 0;
                step.w = 0;
                step.h = 0;

                step.x = sequenceRoot.x + i * textureSize.x;
                step.y = sequenceRoot.y;
                step.w = textureSize.x;
                step.h = textureSize.y;

                addStep(step);
            }
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
            return getStep(0);
        }
    }

    void Animation::setRoot(int x, int y)
    {
        setRoot(glm::ivec2(x, y));
    }

    void Animation::setRoot(glm::ivec2 root)
    {
        for(unsigned int i = 0; i < m_steps.size(); ++i)
        {
            m_steps[i].x = root.x + m_steps[0].w * i;
            m_steps[i].y = root.y;
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
