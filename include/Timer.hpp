#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

#include <SDL2/SDL.h>

class Timer
{
    public:
        Timer();

        void restart();
        void pause();
        void resume();
        void stop();

        int getMilliseconds();

        bool isStarted();
        bool isPaused();
    private:
        int m_pausedTicks;
        int m_startedTicks;

        bool m_started;
        bool m_paused;

};

#endif
