#include <Client/Window.hpp>
#include <easylogging++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Client
{
    Window::Window()
    {
		LOG(INFO) << "Creating Window.";
        m_renderer = nullptr;
    }
    Window::~Window()
    {
		// Clean the SDL objects.
		if(m_renderer != nullptr)
        {
			SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }
		if(m_window != nullptr)
        {
			SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
		if(m_SDLInitialized)
			SDL_Quit();
        if(m_SDLImageInitialized)
            IMG_Quit();

		LOG(INFO) << "Deleted Window.";
    }
    
    int Window::init(const glm::ivec2 &windowSize)
    {
		LOG(INFO) << "Initializing Window (" << windowSize.x << "x" << windowSize.y << ")";
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			LOG(FATAL) << "SDL_Init fauled! Error: " << SDL_GetError();
			return 1;
		}
		m_SDLInitialized = true;

        if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            LOG(FATAL) << "IMG_Init failed! Error: " << IMG_GetError();
            return 1;
        }
        m_SDLImageInitialized = true;

		m_window = SDL_CreateWindow("BomberPi", 100, 100, windowSize.x, windowSize.y, SDL_WINDOW_SHOWN);
		if(m_window == nullptr)
		{
			LOG(FATAL) << "SDL_CreateWindow failed! Error: " << SDL_GetError();
			return 1;
		}

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        if(m_renderer == nullptr)
        {
            LOG(FATAL) << "SDL_CreateRenderer failed! Error: " << SDL_GetError();
            return 1;
        }

        return 0;
    }

    void Window::onEvent(const SDL_Event &e)
    {

    }

    SDL_Renderer *Window::getSDLRenderer()
    {
        return m_renderer;
    }

    SDL_Window *Window::getSDLWindow()
    {
        return m_window;
    }
}
