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
        SDLEventHandler();
        virtual ~SDLEventHandler();

        typedef sigc::signal2<void, const SDL_Event&, float> SDLEventSignal;
       	void sendEvent(const SDL_Event &e, float frametime);

        SDLEventSignal& getSignal(int32_t type);
    protected:
        virtual void onSDLEvent(const SDL_Event &e, float frametime);
    private:
        std::map<uint32_t, SDLEventSignal> m_signals;
};

#endif
