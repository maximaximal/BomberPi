#include <Client/StateBomberman.hpp>
#include <easylogging++.h>
#include <Client/TextureManager.hpp>
#include <easylogging++.h>

#include <Client/SpriteRenderingSystem.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/PlayerInputSystem.hpp>
#include <Client/TimerSystem.hpp>
#include <Client/PlayerMovementSystem.hpp>
#include <Client/BombPlaceSystem.hpp>
#include <Client/BombPlacePositionSystem.hpp>
#include <Client/AnimationSystem.hpp>
#include <Client/BombExplodeSystem.hpp>
#include <Client/ExplosionSystem.hpp>
#include <Client/ExplosionManagementSystem.hpp>
#include <Client/KillEntityTypeSystem.hpp>
#include <Client/CollisionSystem.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/VelocityComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/DamageSystem.hpp>
#include <Client/HealthSystem.hpp>
#include <Client/Config.hpp>
#include <Client/KeyboardInputMethod.hpp>

#include <Client/UI/PowerupQueue.hpp>

#include <pihud/FontManager.hpp>
#include <pihud/Label.hpp>
#include <pihud/WeHaveAWinnerWidget.hpp>

#include <piga/Interface.hpp>

namespace Client
{

    StateBomberman::StateBomberman()
    {
		m_hudContainer = new PiH::HudContainer(nullptr);

        m_offset.x = 50;
        m_offset.y = 50;
    }
    StateBomberman::~StateBomberman()
    {
        delete m_hudContainer;

        if(m_world != nullptr)
            delete m_world;
        if(m_spriteRenderingSystem != nullptr)
        	delete m_spriteRenderingSystem;
        if(m_animationSystem != nullptr)
            delete m_animationSystem;
        if(m_bombExplodeSystem != nullptr)
            delete m_bombExplodeSystem;
        if(m_bombPlaceSystem != nullptr)
            delete m_bombPlaceSystem;
        if(m_bombPlacePositionSystem != nullptr)
            delete m_bombPlacePositionSystem;
        if(m_playerInputSystem != nullptr)
            delete m_playerInputSystem;
        if(m_playerMovementSystem != nullptr)
            delete m_playerMovementSystem;
        if(m_healthSystem != nullptr)
            delete m_healthSystem;
        if(m_explosionSystem != nullptr)
            delete m_explosionSystem;
        if(m_collisionSystem != nullptr)
            delete m_collisionSystem;
        if(m_explosionManagementSystem != nullptr)
            delete m_explosionManagementSystem;
        if(m_damageSystem != nullptr)
            delete m_damageSystem;
        if(m_killEntityTypeSystem != nullptr)
            delete m_killEntityTypeSystem;
        if(m_timerSystem != nullptr)
            delete m_timerSystem;
        if(m_entityFactory != nullptr)
            delete m_entityFactory;
        if(m_winChecker != nullptr)
            delete m_winChecker;
        if(m_playerManager != nullptr)
            delete m_playerManager;
        if(m_map != nullptr)
            delete m_map;

        LOG(INFO) << "StateBomberman deleted.";
    }

    void StateBomberman::init()
    {
        LOG(INFO) << "Initializing StateBomberman.";
        m_map = new BombermanMap();
        m_world = new anax::World();
        m_playerManager = new PlayerManager();
        m_winChecker = new WinChecker(m_playerManager);

        m_spriteRenderingSystem = new SpriteRenderingSystem();
		m_world->addSystem(*m_spriteRenderingSystem);

        m_timerSystem = new TimerSystem();
        m_world->addSystem(*m_timerSystem);

        m_playerInputSystem = new PlayerInputSystem();
        m_playerInputSystem->setGameEventHandler(getGameEventHandler());
        m_world->addSystem(*m_playerInputSystem);

        m_playerMovementSystem = new PlayerMovementSystem(m_map);
        m_world->addSystem(*m_playerMovementSystem);

        m_animationSystem = new AnimationSystem();
        m_world->addSystem(*m_animationSystem);

        m_entityFactory = new EntityFactory(m_world, getTextureManager());
        m_map->setEntityFactory(m_entityFactory);

        m_bombPlaceSystem = new BombPlaceSystem(m_entityFactory);
        m_world->addSystem(*m_bombPlaceSystem);

        m_bombExplodeSystem = new BombExplodeSystem(m_entityFactory);
        m_world->addSystem(*m_bombExplodeSystem);

        m_collisionSystem = new CollisionSystem(m_map);
        m_world->addSystem(*m_collisionSystem);

        m_bombPlacePositionSystem = new BombPlacePositionSystem(m_map, m_collisionSystem);
        m_world->addSystem(*m_bombPlacePositionSystem);

        m_explosionSystem = new ExplosionSystem(m_map, m_entityFactory, m_collisionSystem);
        m_world->addSystem(*m_explosionSystem);

        m_explosionManagementSystem = new ExplosionManagementSystem(getTextureManager());
        m_world->addSystem(*m_explosionManagementSystem);

        m_damageSystem = new DamageSystem();
        m_world->addSystem(*m_damageSystem);

        m_killEntityTypeSystem = new KillEntityTypeSystem();
        m_world->addSystem(*m_killEntityTypeSystem);

        m_healthSystem = new HealthSystem();
        m_world->addSystem(*m_healthSystem);

        m_map->setTexture(getTextureManager()->get("tilemap_proto.png"));

        m_map->init(glm::ivec2(17, 15));

        glm::ivec2 playerPos(0, 0);

        getGameEventHandler()->getGameEventSignal().connect(sigc::mem_fun(this, &StateBomberman::onGameEvent));

        playerPos.x = 32; playerPos.y = 32;
        playerPos.x = 15 * 32; playerPos.y = 13 * 32;

        int n = 0;

        for(int i = 0; i < getInterface()->getPlayerManager()->size(); ++i)
        {
            piga::Player *pigaPlayer = getInterface()->getPlayerManager()->getPlayer(i);
            if(pigaPlayer->isActive())
            {
                addPlayer(getPlayerPos(n), pigaPlayer, n);
                ++n;
            }
        }

        m_world->refresh();

        startNewGame();

        LOG(INFO) << "StateBomberman initialized.";
    }

    void StateBomberman::update(float frameTime)
    {
        m_world->refresh();
        m_timerSystem->update(frameTime);
        m_explosionManagementSystem->update(frameTime);
        m_animationSystem->update(frameTime);
        m_explosionSystem->update(frameTime);

        m_playerInputSystem->update();
        m_playerMovementSystem->update(frameTime);
        m_bombExplodeSystem->update();

        m_bombPlacePositionSystem->update(frameTime);
        m_bombPlaceSystem->update();

        m_collisionSystem->update(frameTime);
        m_damageSystem->update(frameTime);
        m_healthSystem->update(frameTime);
        m_playerManager->update(frameTime);

        m_hudContainer->onUpdate(frameTime);

        //Check if anybody has won
        if(m_winChecker->winDetected())
        {
            if(m_hudContainer->getWidget("WinnerWidget") == nullptr)
            {
                std::shared_ptr<PiH::WeHaveAWinnerWidget> winnerWidget(new PiH::WeHaveAWinnerWidget(m_hudContainer));
                winnerWidget->setFont(getFontManager()->get("PressStart2P.ttf:28"));
                winnerWidget->setWinnerName(m_winChecker->getWinner()->getName());
                winnerWidget->setVictoryImageTexture(getTextureManager()->get("hud.png"), PiH::IntRect(224, 0, 500, 152));
                std::vector<PiH::IntRect> particles = {PiH::IntRect(0, 64, 96, 96)};
                winnerWidget->setParticleTexture(getTextureManager()->get("hud.png"), particles);
                winnerWidget->setBoundingBox(PiH::FloatRect(0, 0, getWindow()->getSize().x, getWindow()->getSize().y));
                m_hudContainer->addWidget(winnerWidget, "WinnerWidget");
            }
            else
            {
                std::shared_ptr<PiH::WeHaveAWinnerWidget> winnerWidget = std::static_pointer_cast<PiH::WeHaveAWinnerWidget>(m_hudContainer->getWidget("WinnerWidget"));
                if(winnerWidget->isDone())
                {
                    m_hudContainer->deleteWidget("WinnerWidget");
                    startNewGame();
                }
            }
        }
    }
    void StateBomberman::render(Window *window)
    {
		m_map->render(window, m_offset);
        m_spriteRenderingSystem->render(window, m_offset);
        m_hudContainer->onRender(window->getSDLRenderer(), PiH::FloatRect(0, 0, 0, 0));
    }
    void StateBomberman::onGameEvent(const piga::GameEvent &gameEvent, float frametime)
    {
        if(m_hudContainer->getWidget("WinnerWidget") != nullptr)
        {
            std::shared_ptr<PiH::WeHaveAWinnerWidget> winnerWidget = std::static_pointer_cast<PiH::WeHaveAWinnerWidget>(m_hudContainer->getWidget("WinnerWidget"));
            winnerWidget->setDone(true);
        }
    }
    void StateBomberman::startNewGame()
    {
        m_map->createInnerStamps();
        m_map->createFillerWalls();
        m_map->createOuterWall();
        m_playerManager->resetPlayers();
        m_world->refresh();
        m_map->createPlayerSpace(m_playerManager->getPlayerPositions(32));

        //Kill all explosions, bombs and powerups.
        m_killEntityTypeSystem->killType(Type::Explosion);
        m_killEntityTypeSystem->killType(Type::Bomb);
        m_killEntityTypeSystem->killType(Type::Powerup);

        m_world->refresh();
    }
    void StateBomberman::addPlayer(glm::ivec2 playerPos, piga::Player *pigaPlayer, int n)
    {
        std::shared_ptr<PiH::HealthAndNameDisplay> healthIndicator(new PiH::HealthAndNameDisplay(m_hudContainer));
        healthIndicator->getHealthIndicator()->setFullIcon(PiH::IntRect(0, 0, 32, 32));
        healthIndicator->getHealthIndicator()->setDepletedIcon(PiH::IntRect(64, 0, 32, 32));
        healthIndicator->getHealthIndicator()->setMaximumHealth(3);
        healthIndicator->getHealthIndicator()->setCurrentHealth(3);
        healthIndicator->setFont(getFontManager()->get("PressStart2P.ttf:18"));
        healthIndicator->setTexture(getTextureManager()->get("hud.png"));
        healthIndicator->setName(pigaPlayer->getName());
        healthIndicator->setPosition(playerPos.x, playerPos.y);

        m_hudContainer->addWidget(healthIndicator, std::string("HealthAndName_") + pigaPlayer->getName());

        std::shared_ptr<Player> player = std::make_shared<Player>(pigaPlayer->getName(), n);

		anax::Entity playerEntity = m_entityFactory->createPlayer(playerPos,
                                                                  m_playerMovementSystem,
                                                                  healthIndicator.get(),
                                                                  player,
                                                                  getConfig()->getFloatValue(Config::BOMB_PLACE_COOLDOWN));
        player->setEntity(playerEntity);

        std::shared_ptr<UI::PowerupQueue> powerupQueue(new UI::PowerupQueue(getTextureManager(), 3, m_hudContainer));
        player->setPowerupQueueUI(powerupQueue.get());
        m_hudContainer->addWidget(powerupQueue, std::string("PowerupQueue_") + pigaPlayer->getName());

        glm::ivec2 pos, powerupQueuePos;
        if(playerPos.x > (m_map->getMapSize().x * 32) / 2)
        {
            pos.x = getWindow()->getSize().x - healthIndicator->getBoundingBox().w;
            healthIndicator->setSideOfIcons(PiH::RIGHT);
            powerupQueuePos.x = getWindow()->getSize().x - powerupQueue->getMaxWidth(32);
        }
        else
        {
            pos.x = 0;
            powerupQueuePos.x = 0;
            healthIndicator->setSideOfIcons(PiH::LEFT);
        }
        if(playerPos.y > (m_map->getMapSize().y * 32) / 2)
        {
            pos.y = getWindow()->getSize().y - healthIndicator->getBoundingBox().h;
            powerupQueuePos.y = pos.y - 32;
        }
        else
        {
            pos.y = 0;
            powerupQueuePos.y = healthIndicator->getBoundingBox().h;
        }
        healthIndicator->setPosition(pos.x, pos.y);
        powerupQueue->setPosition(powerupQueuePos.x, powerupQueuePos.y);

        m_playerManager->set(player, pigaPlayer->getName());
    }
    glm::ivec2 StateBomberman::getPlayerPos(int playerID)
    {
        switch(playerID)
        {
            case 0:
                return glm::ivec2(32,
                                  32);
            case 1:
                return glm::ivec2((m_map->getMapSize().x - 2) * 32,
                                  (m_map->getMapSize().y - 2) * 32);
            case 2:
                return glm::ivec2((m_map->getMapSize().x - 2) * 32,
                                  32);
            case 3:
                return glm::ivec2(32,
                                  (m_map->getMapSize().y - 2) * 32);
            default:
                return glm::ivec2((m_map->getMapSize().x) * 16,
                                  (m_map->getMapSize().y) * 16);
        }
    }
}
