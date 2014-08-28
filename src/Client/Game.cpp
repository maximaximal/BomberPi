#include <Client/Game.hpp>
#include <iostream>
#include <easylogging++.h>
#include <Timer.hpp>

_INITIALIZE_EASYLOGGINGPP

namespace Client
{
    Game::Game()
    {
	
    }
    Game::~Game()
    {
	
    }
    
    int Game::init()
    {
		LOG(INFO) << "Initializing Game!";
		m_window = std::make_shared<Window>();
		if(m_window->init(glm::ivec2(800, 600)) != 0)
        {
            LOG(FATAL) << "Window did not initialize correctly. Exiting.";
            return 1;
        }


        //Start the game loop!

        bool end = false;
        Timer timer;
        SDL_Event e;
        float frametime = 0;

        while(!end)
        {
			timer.restart();

            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    end = true;
                }
				onEvent(e);
            }
        }

        return 0;
    }
    void Game::update(float frametime)
    {

    }

    void Game::onEvent(const SDL_Event &e)
    {
        m_window->onEvent(e);
    }
    void Game::render()
    {
		m_stateManager->render(m_window);
    }
}

int main(int argv, const char** argc)
{
    LOG(INFO) << "Starting BomberPi.";
    Client::Game *game = new Client::Game();
    
    game->init();
    
    delete game;
    
    LOG(INFO) << "Exiting BomberPi.";
    return 0;
}
