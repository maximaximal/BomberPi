#ifndef CLIENT_GAME_HPP_INCLUDED
#define CLIENT_GAME_HPP_INCLUDED

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
	    
    };
}


#endif