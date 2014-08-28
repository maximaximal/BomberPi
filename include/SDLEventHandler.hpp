#ifndef SDLEVENTHANDLER_HPP_INCLUDED
#define SDLEVENTHANDLER_HPP_INCLUDED

#include <map>
#include <sigc++/sigc++.h>
#include <SDL2/SDL.h>

/**
 * @brief The SDLEventHandler class fires SDL events in a signal/slot form.
 */
class SDLEventHandler
{
    public:
        typedef sigc::signal<void, const SDL_Event&, float> SDLEventSignal;
       	void sendEvent(const SDL_Event &e, float frametime);

        SDLEventSignal getSignal(uint8_t type);
    protected:
        virtual void onSDLEvent(const SDL_Event &e, float frametime);
    private:
		std::map<uint8_t, SDLEventSignal> m_signals;
};

#endif
