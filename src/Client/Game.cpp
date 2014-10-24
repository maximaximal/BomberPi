#include <Client/Game.hpp>
#include <iostream>
#include <easylogging++.h>
#include <Timer.hpp>
#include <Client/StateBomberman.hpp>
#include <pihud/pihud.hpp>

_INITIALIZE_EASYLOGGINGPP

namespace Client
{
    Game::Game()
    {
	
    }
    Game::~Game()
    {
        if(m_stateManager != nullptr)
            delete m_stateManager;
        if(m_textureManager != nullptr)
            delete m_textureManager;
        if(m_fontManager != nullptr)
            delete m_fontManager;
        if(m_window != nullptr)
            delete m_window;
        if(m_config != nullptr)
            delete m_config;

        PiH::exit();
    }
    
    int Game::init()
    {
		LOG(INFO) << "Initializing Game!";

        m_config = new Config();
        m_config->setDefaultValues();

		m_window = new Window();
		if(m_window->init(glm::ivec2(m_config->getIntValue(Config::WINDOW_SIZE_X),
                                     m_config->getIntValue(Config::WINDOW_SIZE_Y)),
                          m_config->getBooleanValue(Config::FULLSCREEN)) != 0)
        {
            LOG(FATAL) << "Window did not initialize correctly. Exiting.";
            return 1;
        }

        m_textureManager = new TextureManager(m_window);

        m_fontManager = new PiH::FontManager();

        m_stateManager = new StateManager();
        m_stateManager->setTextureManager(m_textureManager);
        m_stateManager->setFontManager(m_fontManager);
        m_stateManager->setWindow(m_window);
        m_stateManager->setConfig(m_config);


        //Initialize PiHUD
        PiH::Config *pihudConfig = new PiH::Config(m_window->getSDLRenderer());
        pihudConfig->setupDefaultConfig();
        PiH::initialize(pihudConfig);

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
