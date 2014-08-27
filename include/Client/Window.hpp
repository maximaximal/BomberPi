#ifndef CLIENT_WINDOW_HPP_INCLUDED
#define CLIENT_WINDOW_HPP_INCLUDED

#include <glm/vec2.hpp>
#include <SDL2/SDL.h>

namespace Client 
{
    class Window 
    {
	public:
	    Window();
	    virtual ~Window();
	    
	    /**
	     * @brief Initialize the window.
	     * 
	     * Creates the SDL_Window and all required SDL structs. 
	     * 
	     * @param windowSize The size the SDL Window should have. 
	     */
	    int init(const glm::ivec2 &windowSize);
	    
	    SDL_Renderer* getSDLRenderer();
	private:
	    SDL_Window *m_window = nullptr;
	    SDL_Renderer *m_renderer = nullptr;
	    
	    bool m_SDLInitialized = false;
    };
}

#endif