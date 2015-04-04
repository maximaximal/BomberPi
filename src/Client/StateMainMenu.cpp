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
        if(m_menuContainer != nullptr)
            delete m_menuContainer;
        if(m_mapCustomizer != nullptr)
            delete m_mapCustomizer;

		LOG(INFO) << "StateMainMenu deleted.";
    }
    void StateMainMenu::init()
    {
		m_menuContainer = new PiH::MenuContainer(nullptr);
        m_mapCustomizer = new BombermanMap();
        m_mapCustomizer->setTexture(getTextureManager()->get("tilemap_proto.png"));
        m_mapCustomizer->init();
        m_mapCustomizer->createOuterWall();
        m_mapCustomizer->createInnerStamps();
        m_mapCustomizer->createFillerWalls();

        getGameEventHandler()->getGameEventSignal().connect(sigc::mem_fun(this, &StateMainMenu::onGameEvent));

        // MainMenu
        // --------

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

        std::shared_ptr<PiH::PushButton> customizeMap = std::make_shared<PiH::PushButton>(nullptr);
        customizeMap->setText("Customize Map Size");
        customizeMap->getButtonPressedSignal().connect(sigc::mem_fun(this, &StateMainMenu::customizeMap));
        addButton(customizeMap);

        std::shared_ptr<PiH::PushButton> quitGame = std::make_shared<PiH::PushButton>(nullptr);
        quitGame->setText("Quit Game");
        quitGame->getButtonPressedSignal().connect(sigc::mem_fun(this, &StateMainMenu::quitGame));
        addButton(quitGame);

        buttons->setBoundingBox(getWindow()->getSize().x / 4, getWindow()->getSize().y / 2,
                                getWindow()->getSize().x / 2, getWindow()->getSize().y / 2);

        // Map-Size Selection Menu
        // -----------------------

        std::shared_ptr<PiH::HudContainer> mapMenu = std::make_shared<PiH::HudContainer>(m_menuContainer);
        m_menuContainer->addPage(mapMenu, "MapMenu");

        std::shared_ptr<PiH::Label> mapMenuTitle(new PiH::Label(nullptr));
        mapMenuTitle->setFont(getFontManager()->get(getConfig()->getStringValue(Config::STANDARD_FONT) + ":20"));
        mapMenuTitle->setText("Mapsize Settings");
        mapMenuTitle->setPosition(getWindow()->getSize().x / 2 - mapMenuTitle->getTextWidth() / 2, 10);
        mapMenuTitle->setColor(120, 120, 120);
        mapMenu->addWidget(mapMenuTitle, "Title");

        getSDLEventHandler()->getSignal(SDL_KEYDOWN).connect(sigc::mem_fun(this, &StateMainMenu::onSDLEvent));

		LOG(INFO) << "StateMainMenu initialized";
    }
    void StateMainMenu::update(float frametime)
    {
        m_menuContainer->onUpdate(frametime);
    }
    void StateMainMenu::onGameEvent(const piga::GameEvent &gameEvent, float frametime)
    {
        if(m_menuContainer->getCurrentPageName() == "MapMenu")
        {
            if(gameEvent.type() == piga::GameEvent::GameEventType::GameInput)
            {
                if(gameEvent.gameInput.state())
                {
                    glm::ivec2 mapSize = m_mapCustomizer->getMapSize();
                    switch(gameEvent.gameInput.control())
                    {
                        case piga::UP:
                            if(mapSize.y > 4)
                                mapSize.y -= 1;
                            break;
                        case piga::DOWN:
                            mapSize.y += 1;
                            break;
                        case piga::LEFT:
                            if(mapSize.x > 4)
                                mapSize.x -= 1;
                            break;
                        case piga::RIGHT:
                            mapSize.x += 1;
                            break;
                        case piga::ACTION:
                            m_menuContainer->setCurrentPage("MainMenu");
                            break;
                        default:
                            //Nothing to do
                            break;
                    }
                    if(mapSize != m_mapCustomizer->getMapSize())
                    {
                        m_mapCustomizer->clearTilemap();
                        m_mapCustomizer->setMapSize(mapSize);
                        m_mapCustomizer->createInnerStamps();
                        m_mapCustomizer->createOuterWall();
                        m_mapCustomizer->createFillerWalls();
                    }
                }
            }
        }
        m_menuContainer->onEvent(PiH::Event(gameEvent, true));
        m_menuContainer->onEvent(PiH::Event(gameEvent, false));
    }
    void StateMainMenu::onSDLEvent(const SDL_Event &e, float frametime)
    {

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
        stateBomberman->setMapSize(m_mapCustomizer->getMapSize());
        stateBomberman->init();
    }
    void StateMainMenu::quitGame(int playerID)
    {
        getStateManager()->quit();
    }
    void StateMainMenu::customizeMap(int playerID)
    {
        m_menuContainer->setCurrentPage("MapMenu");
    }
    void StateMainMenu::render(Client::Window *window)
    {
        if(m_menuContainer->getCurrentPageName() == "MapMenu")
        {
            m_mapCustomizer->render(window, glm::ivec2(50, 50));
        }

        PiH::FloatRect offset(0, 0, window->getSize().x, window->getSize().y);
		m_menuContainer->onRender(window->getSDLRenderer(), offset);
    }
}
