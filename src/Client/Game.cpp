#include <Client/Game.hpp>
#include <iostream>
#include <easylogging++.h>
#include <Timer.hpp>
#include <Client/StateBomberman.hpp>
#include <Client/StateMainMenu.hpp>
#include <Client/KeyboardInputMethod.hpp>
#include <Client/PlayerInputSystem.hpp>
#include <pihud/pihud.hpp>
#include <piga/PlayerManager.hpp>

_INITIALIZE_EASYLOGGINGPP

namespace Client
{
    Game::Game(bool getCommandsFromSharedMemory, bool quickStart)
    {
        m_getCommandsFromSharedMemory = getCommandsFromSharedMemory;
        m_pigaInterface = new piga::Interface(!getCommandsFromSharedMemory);
        m_quickStart = quickStart;

        m_config = new Config();
        m_config->setDefaultValues();
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
        if(m_pigaInterface != nullptr)
            delete m_pigaInterface;
    }
    
    int Game::init(bool fullscreen)
    {
		LOG(INFO) << "Initializing Game!";

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
        m_sdlEventHandler = std::make_shared<SDLEventHandler>();
        m_fontManager = new PiH::FontManager();

        if(!m_getCommandsFromSharedMemory)
        {
            //Add 2 players if the game is selfhosted.

            InputMap inputMap;
            inputMap.set(SDL_SCANCODE_W, PlayerInputEnum::UP);
            inputMap.set(SDL_SCANCODE_A, PlayerInputEnum::LEFT);
            inputMap.set(SDL_SCANCODE_S, PlayerInputEnum::DOWN);
            inputMap.set(SDL_SCANCODE_D, PlayerInputEnum::RIGHT);
            inputMap.set(SDL_SCANCODE_SPACE, PlayerInputEnum::ACTION);

            std::shared_ptr<piga::PlayerInput> playerInput = std::make_shared<piga::PlayerInput>();
            playerInput->setPlayerID(0);
            for(auto &input : inputMap.getMaps())
            {
                playerInput->setInputMethod(new piga::KeyboardInputMethod(input.first, m_sdlEventHandler),
                                            PlayerInputSystem::getPigaGameControlFromPlayerInputEnum(input.second));
            }
            m_pigaInterface->addPlayerInput(playerInput);

            inputMap.clear();

            inputMap.set(SDL_SCANCODE_UP, PlayerInputEnum::UP);
            inputMap.set(SDL_SCANCODE_LEFT, PlayerInputEnum::LEFT);
            inputMap.set(SDL_SCANCODE_DOWN, PlayerInputEnum::DOWN);
            inputMap.set(SDL_SCANCODE_RIGHT, PlayerInputEnum::RIGHT);
            inputMap.set(SDL_SCANCODE_L, PlayerInputEnum::ACTION);

            playerInput = std::make_shared<piga::PlayerInput>();
            playerInput->setPlayerID(1);
            for(auto &input : inputMap.getMaps())
            {
                playerInput->setInputMethod(new piga::KeyboardInputMethod(input.first, m_sdlEventHandler),
                                            PlayerInputSystem::getPigaGameControlFromPlayerInputEnum(input.second));
            }
            m_pigaInterface->addPlayerInput(playerInput);
        }

        m_playerManager = m_pigaInterface->getPlayerManager();

        if(!m_getCommandsFromSharedMemory)
        {
            m_playerManager->getPlayer(0)->setName("Player 1");
            m_playerManager->getPlayer(0)->setActive(true);
            m_playerManager->getPlayer(1)->setName("Player 2");
            m_playerManager->getPlayer(1)->setActive(true);
        }

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

        if(m_quickStart)
        {
            std::shared_ptr<StateBomberman> stateBomberman = std::make_shared<StateBomberman>();
            m_stateManager->push(stateBomberman);
            stateBomberman->init();
            stateBomberman.reset();
        }
        else
        {
            std::shared_ptr<StateMainMenu> stateMainMenu = std::make_shared<StateMainMenu>();
            m_stateManager->push(stateMainMenu);
            stateMainMenu->init();
            stateMainMenu.reset();
        }

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
            while(m_pigaInterface->pollEvent(&gameEvent))
            {
                m_stateManager->sendGameEvent(gameEvent, frametime);
            }

            update(frametime);

            render();

            if(m_stateManager->hasBeenQuitted())
                end = true;

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
        m_sdlEventHandler->sendEvent(e, frametime);
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

    Config *Game::getConfig()
    {
        return m_config;
    }
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char* argv[])
{
    bool getCommandsFromSharedMemory = false;
    bool fullscreen = false;
    bool quickStart = false;
    bool localDir = false;

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
    if(cmdOptionExists(argv, argv + argc, "-quickStart"))
    {
        quickStart = true;
        LOG(INFO) << "BomberPi quick start actvated!";
    }
    if(cmdOptionExists(argv, argv + argc, "-local"))
    {
        localDir = true;
        LOG(INFO) << "Using a local (.) data directory!";
    }
    if(cmdOptionExists(argv, argv + argc, "-help"))
    {
        std::cout << "BomberPi - Program Arguments Help" << std::endl;
        std::cout << "  -c\t\tLaunches BomberPi in shared input mode." << std::endl;
        std::cout << "  -f\t\tLaunches BomberPi in fullscreen mode." << std::endl;
        std::cout << "  -quickStart\tLaunches BomberPi directly into the game instead of the main menu." << std::endl;
        std::cout << "  -help\t\tDisplays this menu." << std::endl;
        std::cout << "  -local\tRuns bomberpi with a local (.) data directory." << std::endl;
        return 0;
    }
    LOG(INFO) << "Starting BomberPi.";

    Client::Game *game = new Client::Game(getCommandsFromSharedMemory, quickStart);

    if(localDir)
    {
        game->getConfig()->setStringValue(Client::Config::DATA_DIRECTORY, ".");
        game->getConfig()->setStringValue(Client::Config::STANDARD_FONT,
                                          game->getConfig()->getStringValue(Client::Config::DATA_DIRECTORY) + "/xolonium-fonts/fonts/Xolonium-Bold.otf");
    }

    game->init(fullscreen);
    
    delete game;
    game = nullptr;
    
    LOG(INFO) << "Exiting BomberPi.";
    return 0;
}
