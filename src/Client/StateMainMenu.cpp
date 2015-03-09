#include <Client/StateMainMenu.hpp>
#include <Client/Window.hpp>

#include <pihud/Label.hpp>
#include <pihud/FontManager.hpp>

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

        std::shared_ptr<PiH::HudContainer> mainMenu = std::make_shared<PiH::HudContainer>(m_menuContainer);
        m_menuContainer->addPage(mainMenu, "MainMenu");
        m_menuContainer->setCurrentPage("MainMenu");

        std::shared_ptr<PiH::Label> title(new PiH::Label(m_menuContainer));
        title->setFont(getFontManager()->get("xolonium-fonts/fonts/Xolonium-Bold.otf:128"));
        title->setText("BomberPi");
        title->setPosition(getWindow()->getSize().x / 2 - title->getBoundingBox().w / 2,
                           getWindow()->getSize().y / 5);
        title->setColor(120, 120, 120);

        mainMenu->addWidget(title, "Title");
    }
    void StateMainMenu::update(float frametime)
    {
        m_menuContainer->onUpdate(frametime);
    }
    void StateMainMenu::onGameEvent(const piga::GameEvent &gameEvent, float frametime)
    {
        m_menuContainer->onEvent(gameEvent);
    }
    void StateMainMenu::render(Client::Window *window)
    {
        PiH::FloatRect offset(0, 0, window->getSize().x, window->getSize().y);
		m_menuContainer->onRender(window->getSDLRenderer(), offset);
    }
}
