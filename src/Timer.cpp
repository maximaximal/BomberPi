#include <Timer.hpp>

Timer::Timer()
{
	m_startedTicks = 0;
	m_pausedTicks = 0;
	m_paused = false;
	m_started = false;
}
void Timer::restart()
{
	m_started = true;
	m_paused = false;
	m_startedTicks = SDL_GetTicks();
}
void Timer::stop()
{
	m_started = false;
	m_paused = false;
}
void Timer::pause()
{
	if(isStarted() && !isPaused())
	{
		m_paused = true;
		m_pausedTicks = SDL_GetTicks() - m_startedTicks;
	}
}
void Timer::resume()
{
	if(isPaused())
	{
		m_paused = false;
		m_startedTicks = SDL_GetTicks() - m_pausedTicks;
		m_pausedTicks = 0;
	}
}
int Timer::getMilliseconds()
{
	if(isStarted())
	{
		if(isPaused())
		{
			return m_pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - m_startedTicks;
		}
	}
	else
	{
		return 0;
	}
}

bool Timer::isPaused()
{
	return m_paused;
}
bool Timer::isStarted()
{
	return m_started;
}
