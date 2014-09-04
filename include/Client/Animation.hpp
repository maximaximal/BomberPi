#ifndef CLIENT_ANIMATION_HPP_INCLUDED
#define CLIENT_ANIMATION_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <vector>

namespace Client
{
    class Animation
    {
        public:
            typedef std::vector<SDL_Rect> StepsVector;
            Animation();
            virtual ~Animation();

            void addStep(const SDL_Rect &step);
            const SDL_Rect& getStep(unsigned int step);
            unsigned int getStepCount();

            StepsVector& getSteps();
        private:
            StepsVector m_steps;
    };
}

#endif
