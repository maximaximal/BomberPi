#include <Client/Game.hpp>
#include <iostream>

using std::cout;
using std::endl;

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
	cout << "Initializing Game!" << endl;
    }
    void Game::update()
    {
	
    }
    void Game::render()
    {
	
    }
}

int main()
{
    cout << "Starting BomberPi." << endl;
    Client::Game *game = new Client::Game();
    
    game->init();
    
    delete game;
    
    cout << "Exiting BomberPi." << endl;
    return 0;
}