#ifndef CLIENT_ANIMATION_HPP_INCLUDED
#define CLIENT_ANIMATION_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <glm/vec2.hpp>

namespace Client
{
    class Animation
    {
        public:
            typedef std::vector<SDL_Rect> StepsVector;
            Animation();
            Animation(const std::string &definitionPath);
            virtual ~Animation();

            void loadDefinition(const std::string &definitionPath);

            void addStep(const SDL_Rect &step);
            const SDL_Rect& getStep(unsigned int step);
            void setRoot(int x, int y);
            void setRoot(glm::ivec2 root);
            unsigned int getStepCount();
            void setStepDuration(float duration);
            float getStepDuration();
            float getTotalDuration();

            StepsVector& getSteps();
        private:
            StepsVector m_steps;
            float m_stepDuration;
            std::string m_definitionPath;
    };
}

#endif
