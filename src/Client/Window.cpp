#include <Client/Window.hpp>
#include <easylogging++.h>
#include <SDL2/SDL.h>

namespace Client
{
    Window::Window()
    {
	LOG(INFO) << "Creating Window.";
    }
    Window::~Window()
    {
	// Clean the SDL objects.
	if(m_renderer != nullptr)
	    SDL_DestroyRenderer(m_renderer);
	if(m_window != nullptr)
	    SDL_DestroyWindow(m_window);
	
	if(m_SDLInitialized)
	    SDL_Quit();
	
	LOG(INFO) << "Deleted Window." << endl;
    }
    
    int Window::init(const glm::ivec2 &windowSize)
    {
	LOG(INFO) << "Initializing Window (" << windowSize.x << "x" << windowSize.y << ")";
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
	    LOG(FATAL) << "SDL_Init fauled! Error: " << SDL_GetError();
	    return 1;
	}
	
	m_window = SDL_CreateWindow("BomberPi", 100, 100, windowSize.x, windowSize.y, SDL_WINDOW_SHOWN);
	if(m_window == nullptr)
	{
	    LOG(FATAL) << "SDL_CreateWindow failed! Error: " << SDL_GetError();
	    SDL_Quit();
	    return 1;
	}
	
	m_SDLInitialized = true;
    }
}