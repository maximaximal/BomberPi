#include <Client/Game.hpp>
#include <iostream>
#include <easylogging++.h>
#include <Timer.hpp>
#include <Client/StateBomberman.hpp>
#include <pihud/pihud.hpp>

_INITIALIZE_EASYLOGGINGPP

namespace Client
{
    Game::Game(bool getCommandsFromSharedMemory)
    {
        m_getCommandsFromSharedMemory = getCommandsFromSharedMemory;
        m_pigaInterface = new piga::Interface(!getCommandsFromSharedMemory);

        if(getCommandsFromSharedMemory)
        {
            if(!el::Helpers::installLogDispatchCallback<InterfaceLogger>("InterfaceLogger"))
                LOG(WARNING) << "Cannot install the InterfaceLogger callback!";
            m_interfaceLogger = el::Helpers::logDispatchCallback<InterfaceLogger>("InterfaceLogger");
            m_interfaceLogger->setInterface(m_pigaInterface);
            m_interfaceLogger->setEnabled(true);
        }
    }
    Game::~Game()
    {
        if(m_stateManager != nullptr)
            delete m_stateManager;
        if(m_fontManager != nullptr)
            delete m_fontManager;
        if(m_textureManager != nullptr)
            delete m_textureManager;
        if(m_config != nullptr)
            delete m_config;
        PiH::exit();
        if(m_window != nullptr)
            delete m_window;
        if(m_getCommandsFromSharedMemory)
        {
            m_interfaceLogger->setInterface(nullptr);
            m_interfaceLogger->setEnabled(false);
        }
        if(m_pigaInterface != nullptr)
            delete m_pigaInterface;
    }
    
    int Game::init(bool fullscreen)
    {
		LOG(INFO) << "Initializing Game!";

        m_config = new Config();
        m_config->setDefaultValues();

        m_config->setBooleanValue(Config::FULLSCREEN, fullscreen);

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
        m_stateManager->setPigaInterface(m_pigaInterface);


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

        //The parameters are only temporary and will be set when the event is polled.
        piga::GameEvent gameEvent(0);

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
            m_pigaInterface->update();
            while(m_pigaInterface->pollEvent(gameEvent))
            {
                m_stateManager->sendGameEvent(gameEvent, frametime);
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
        m_window->glClear();
        SDL_SetRenderDrawColor(m_window->getSDLRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(m_window->getSDLRenderer());
        m_stateManager->render(m_window);
        SDL_RenderPresent(m_window->getSDLRenderer());
        SDL_GL_SwapWindow(m_window->getSDLWindow());
    }
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char* argv[])
{
    LOG(INFO) << "Starting BomberPi.";

    bool getCommandsFromSharedMemory = false;
    bool fullscreen = false;

    if(cmdOptionExists(argv, argv + argc, "-c"))
    {
        getCommandsFromSharedMemory = true;
        LOG(INFO) << "Getting Commands from shared memory! No keyboard state will be processed by this application.";
    }
    if(cmdOptionExists(argv, argv + argc, "-f"))
    {
        fullscreen = true;
        LOG(INFO) << "Launching BomberPi in fullscreen mode!";
    }

    Client::Game *game = new Client::Game(getCommandsFromSharedMemory);
    
    game->init(fullscreen);
    
    delete game;
    game = nullptr;
    
    LOG(INFO) << "Exiting BomberPi.";
    return 0;
}
