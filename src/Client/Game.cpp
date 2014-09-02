#include <Client/Game.hpp>
#include <iostream>
#include <easylogging++.h>
#include <Timer.hpp>
#include <Client/StateBomberman.hpp>

_INITIALIZE_EASYLOGGINGPP

namespace Client
{
    Game::Game()
    {
	
    }
    Game::~Game()
    {
        m_stateManager.reset();
		m_textureManager->destroy();
        m_textureManager->clear();

        m_textureManager.reset();
        m_window.reset();
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

        m_textureManager = std::make_shared<TextureManager>(m_window);

        m_stateManager = std::make_shared<StateManager>();
        m_stateManager->setTextureManager(m_textureManager);

        //Start the game loop!

        bool end = false;
        Timer timer;
        SDL_Event e;
        float frametime = 0;

        std::shared_ptr<StateBomberman> stateBomberman = std::make_shared<StateBomberman>();
        m_stateManager->push(stateBomberman);
        stateBomberman->init();
		stateBomberman.reset();

        while(!end)
        {
			timer.restart();

            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    end = true;
                }
				onEvent(e, frametime);
            }

            update(frametime);

            render();

            int delay = (1000 / 60) - timer.getMilliseconds();
			if(delay > 0)
				SDL_Delay(delay);
			frametime = timer.getMilliseconds() / 1000.0;
        }

        return 0;
    }
    void Game::update(float frametime)
    {
		m_stateManager->update(frametime);
    }

    void Game::onEvent(const SDL_Event &e, float frametime)
    {
        m_window->onEvent(e);
        m_stateManager->sendEvent(e, frametime);
    }
    void Game::render()
    {
        SDL_RenderClear(m_window->getSDLRenderer());
		m_stateManager->render(m_window);
        SDL_RenderPresent(m_window->getSDLRenderer());
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
