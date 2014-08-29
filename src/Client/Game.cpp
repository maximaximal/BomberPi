#include <Client/Game.hpp>
#include <iostream>
#include <easylogging++.h>

using std::cout;
using std::endl;

_INITIALIZE_EASYLOGGINGPP

namespace Client
{
    Game::Game()
    {
	
    }
    Game::~Game()
    {
	
    }
    
    void Game::init()
    {
	LOG(INFO) << "Initializing Game!";
	m_window = std::make_shared<Window>();
	m_window->init(glm::ivec2(800, 600));
    }
    void Game::update()
    {
	
    }
    void Game::render()
    {
	
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