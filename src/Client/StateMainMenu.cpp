#include <Client/StateMainMenu.hpp>
#include <Client/Window.hpp>
#include <Client/Config.hpp>
#include <StateManager.hpp>

#include <Client/StateBomberman.hpp>

#include <pihud/Label.hpp>
#include <pihud/PushButton.hpp>
#include <pihud/FontManager.hpp>
#include <pihud/VerticalListLayout.hpp>
#include <pihud/Layout.hpp>
#include <pihud/pihud.hpp>

#include <easylogging++.h>

namespace Client
{
	StateMainMenu::StateMainMenu()
    {

    }
    StateMainMenu::~StateMainMenu()
    {
		delete m_menuContainer;
		LOG(INFO) << "StateMainMenu deleted.";
    }

    void StateMainMenu::init()
    {
		m_menuContainer = new PiH::MenuContainer(nullptr);

        std::shared_ptr<PiH::HudContainer> mainMenu = std::make_shared<PiH::HudContainer>(m_menuContainer);
        m_menuContainer->addPage(mainMenu, "MainMenu");
        m_menuContainer->setCurrentPage("MainMenu");

        std::shared_ptr<PiH::Label> title(new PiH::Label(nullptr));
        title->setFont(getFontManager()->get(getConfig()->getStringValue(Config::STANDARD_FONT) + ":128"));
        title->setText("BomberPi");
        title->setPosition(getWindow()->getSize().x / 2 - title->getTextWidth() / 2,
                           getWindow()->getSize().y / 5);
        title->setColor(120, 120, 120);
        mainMenu->addWidget(title, "Title");

        std::shared_ptr<PiH::Layout> buttons = std::make_shared<PiH::Layout>(nullptr);
		PiH::VerticalListLayout *buttonsLayout = new PiH::VerticalListLayout;

        buttonsLayout->setCentered(true);

        buttons->setLayouter(buttonsLayout);

        mainMenu->addWidget(buttons, "Buttons");

        std::shared_ptr<PiH::PushButton> startGame = std::make_shared<PiH::PushButton>(nullptr);
        startGame->setText("Start Game");
        startGame->getButtonPressedSignal().connect(sigc::mem_fun(this, &StateMainMenu::startGame));

        PiH::getGlobalConfig()->getFocusManager()->setFocused(startGame, 0);

        addButton(startGame);

        std::shared_ptr<PiH::PushButton> quitGame = std::make_shared<PiH::PushButton>(nullptr);
        quitGame->setText("Quit Game");
        addButton(quitGame);

        buttons->setBoundingBox(getWindow()->getSize().x / 4, getWindow()->getSize().y / 2,
                                getWindow()->getSize().x / 2, getWindow()->getSize().y / 2);

        getSDLEventHandler()->getSignal(SDL_KEYDOWN).connect(sigc::mem_fun(this, &StateMainMenu::onSDLEvent));

		LOG(INFO) << "StateMainMenu initialized";
    }
    void StateMainMenu::update(float frametime)
    {
        m_menuContainer->onUpdate(frametime);
    }
    void StateMainMenu::onGameEvent(const piga::GameEvent &gameEvent, float frametime)
    {
        m_menuContainer->onEvent(gameEvent);
    }
    void StateMainMenu::onSDLEvent(const SDL_Event &e, float frametime)
    {
        if(e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                onGameEvent(piga::GameEvent(0, piga::event::GameInput(piga::ACTION, true)), frametime);
            }
        }
    }
    void StateMainMenu::addButton(std::shared_ptr<PiH::PushButton> button)
    {
        PiH::IntRect normalRect(6, 162, 250, 21);
        PiH::IntRect pressedRect(6, 185, 250, 21);
        PiH::IntRect focusedRect(6, 209, 250, 21);

        button->setTextColor(170, 170, 170);
        button->setFont(getFontManager()->get(getConfig()->getStringValue(Config::STANDARD_FONT) + ":18"));
        button->setBackgroundTexture(getTextureManager()->get("hud.png"));
        button->setNormalTextureRect(normalRect);
        button->setFocusedTextureRect(focusedRect);
        button->setPressedTextureRect(pressedRect);

        std::shared_ptr<PiH::Layout> buttons = std::static_pointer_cast<PiH::Layout>(m_menuContainer->getCurrentPage()->getWidget("Buttons"));

        buttons->addWidget(button);
    }
    void StateMainMenu::startGame(int playerID)
    {
        std::shared_ptr<StateBomberman> stateBomberman = std::make_shared<StateBomberman>();
        getStateManager()->push(stateBomberman);
        stateBomberman->init();
    }
    void StateMainMenu::render(Client::Window *window)
    {
        PiH::FloatRect offset(0, 0, window->getSize().x, window->getSize().y);
		m_menuContainer->onRender(window->getSDLRenderer(), offset);
    }
}
