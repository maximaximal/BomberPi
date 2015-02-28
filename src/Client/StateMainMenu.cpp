#include <Client/StateMainMenu.hpp>
#include <Client/Window.hpp>

namespace Client
{
	StateMainMenu::StateMainMenu()
    {

    }
    StateMainMenu::~StateMainMenu()
    {
		delete m_menuContainer;
    }

    void StateMainMenu::init()
    {
		m_menuContainer = new PiH::MenuContainer(nullptr);
    }
    void StateMainMenu::update(float frametime)
    {
		m_menuContainer->onUpdate(frametime);
    }
    void StateMainMenu::render(Client::Window *window)
    {
        PiH::FloatRect offset(0, 0, window->getSize().x, window->getSize().y);
		m_menuContainer->onRender(window->getSDLRenderer(), offset);
    }
}
