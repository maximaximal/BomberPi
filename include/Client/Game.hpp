#ifndef CLIENT_GAME_HPP_INCLUDED
#define CLIENT_GAME_HPP_INCLUDED

#include <memory>
#include <Client/Window.hpp>

namespace Client 
{
    class Game 
    {
	public:
	    Game();
	    virtual ~Game();
	    
	    void init();
	    
	    void update();
	    
	    void render();
	private:
	    std::shared_ptr<Window> m_window;
    };
}


#endif