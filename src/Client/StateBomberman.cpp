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
#include <Client/CollisionSystem.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/VelocityComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/DamageSystem.hpp>
#include <Client/InvincibleSystem.hpp>

#include <pihud/FontManager.hpp>
#include <pihud/Label.hpp>

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
        if(m_spriteRenderingSystem != nullptr)
        	delete m_spriteRenderingSystem;
        if(m_animationSystem != nullptr)
            delete m_animationSystem;
        if(m_bombExplodeSystem != nullptr)
            delete m_bombExplodeSystem;
        if(m_bombPlaceSystem != nullptr)
            delete m_bombPlaceSystem;
        if(m_entityFactory != nullptr)
            delete m_entityFactory;
        if(m_winChecker != nullptr)
            delete m_winChecker;
        if(m_playerManager != nullptr)
            delete m_playerManager;
        if(m_map != nullptr)
            delete m_map;
        if(m_playerInputSystem != nullptr)
            delete m_playerInputSystem;
        if(m_playerMovementSystem != nullptr)
            delete m_playerMovementSystem;
        if(m_invincibleSystem != nullptr)
            delete m_invincibleSystem;
        if(m_explosionSystem != nullptr)
            delete m_explosionSystem;
        if(m_collisionSystem != nullptr)
            delete m_collisionSystem;
        if(m_explosionManagementSystem != nullptr)
            delete m_explosionManagementSystem;
        if(m_damageSystem != nullptr)
            delete m_damageSystem;
        if(m_timerSystem != nullptr)
            delete m_timerSystem;
        if(m_world != nullptr)
            delete m_world;

        delete m_hudContainer;
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
        m_playerInputSystem->setSDLEventHandler(getSDLEventHandler());
        m_world->addSystem(*m_playerInputSystem);

        m_playerMovementSystem = new PlayerMovementSystem(m_map);
        m_world->addSystem(*m_playerMovementSystem);

        m_animationSystem = new AnimationSystem();
        m_world->addSystem(*m_animationSystem);

        m_entityFactory = new EntityFactory(m_world, getTextureManager());

        m_bombPlaceSystem = new BombPlaceSystem(m_entityFactory);
        m_world->addSystem(*m_bombPlaceSystem);

        m_bombPlacePositionSystem = new BombPlacePositionSystem(m_map);
        m_world->addSystem(*m_bombPlacePositionSystem);

        m_bombExplodeSystem = new BombExplodeSystem(m_entityFactory);
        m_world->addSystem(*m_bombExplodeSystem);

        m_explosionSystem = new ExplosionSystem(m_map, m_entityFactory);
        m_world->addSystem(*m_explosionSystem);

        m_explosionManagementSystem = new ExplosionManagementSystem(getTextureManager());
        m_world->addSystem(*m_explosionManagementSystem);

        m_collisionSystem = new CollisionSystem(m_map);
        m_world->addSystem(*m_collisionSystem);

        m_damageSystem = new DamageSystem();
        m_world->addSystem(*m_damageSystem);

        m_invincibleSystem = new HealthSystem();
        m_world->addSystem(*m_invincibleSystem);

        m_map->setTexture(getTextureManager()->get("tilemap_proto.png"));

        m_map->init(glm::ivec2(17, 15));

        glm::ivec2 playerPos(0, 0);

       	InputMap inputMap;
        inputMap.set(SDL_SCANCODE_W, PlayerInputEnum::UP);
       	inputMap.set(SDL_SCANCODE_A, PlayerInputEnum::LEFT);
        inputMap.set(SDL_SCANCODE_S, PlayerInputEnum::DOWN);
        inputMap.set(SDL_SCANCODE_D, PlayerInputEnum::RIGHT);
        inputMap.set(SDL_SCANCODE_SPACE, PlayerInputEnum::ACTION);
        playerPos.x = 32; playerPos.y = 32;
        this->addPlayer(inputMap, playerPos, "Player 1");

        inputMap.clear();

        inputMap.set(SDL_SCANCODE_UP, PlayerInputEnum::UP);
       	inputMap.set(SDL_SCANCODE_LEFT, PlayerInputEnum::LEFT);
        inputMap.set(SDL_SCANCODE_DOWN, PlayerInputEnum::DOWN);
        inputMap.set(SDL_SCANCODE_RIGHT, PlayerInputEnum::RIGHT);
        inputMap.set(SDL_SCANCODE_L, PlayerInputEnum::ACTION);
        playerPos.x = 15 * 32; playerPos.y = 13 * 32;
        this->addPlayer(inputMap, playerPos, "Player 2");

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

        m_bombPlacePositionSystem->update();
        m_bombPlaceSystem->update();

        m_collisionSystem->update(frameTime);
        m_damageSystem->update(frameTime);
        m_invincibleSystem->update(frameTime);
        m_playerManager->update(frameTime);

        m_hudContainer->onUpdate(frameTime);

        //Check if anybody has won
        if(m_winChecker->winDetected())
        {
            LOG(INFO) << "We have a winner! " << m_winChecker->getWinner()->getName();
            startNewGame();
        }
    }

    void StateBomberman::render(Window *window)
    {
		m_map->render(window, m_offset);
        m_spriteRenderingSystem->render(window, m_offset);
        m_hudContainer->onRender(window->getSDLRenderer(), PiH::FloatRect(0, 0, 0, 0));
    }

    void StateBomberman::startNewGame()
    {
        m_map->createOuterWall(0);
        m_map->createOuterWall(1);
        m_map->createInnerStamps();
        m_map->createFillerWalls();
        m_playerManager->resetPlayers();
        m_world->refresh();
        m_map->createPlayerSpace(m_playerManager->getPlayerPositions(32));
    }
    void StateBomberman::addPlayer(InputMap inputs, glm::ivec2 playerPos, const std::string &name)
    {
        PiH::HealthAndNameDisplay *healthIndicator = new PiH::HealthAndNameDisplay(m_hudContainer);
        healthIndicator->getHealthIndicator()->setFullIcon(PiH::IntRect(0, 0, 32, 32));
        healthIndicator->getHealthIndicator()->setDepletedIcon(PiH::IntRect(64, 0, 32, 32));
        healthIndicator->getHealthIndicator()->setMaximumHealth(3);
        healthIndicator->getHealthIndicator()->setCurrentHealth(3);
        healthIndicator->setFont(getFontManager()->get("PressStart2P.ttf:18"));
        healthIndicator->setTexture(getTextureManager()->get("hud.png"));
        healthIndicator->setName(name);
        healthIndicator->setPosition(playerPos.x, playerPos.y);

        m_hudContainer->addWidget(healthIndicator, "HealthAndName_" + name);

        std::shared_ptr<Player> player = std::make_shared<Player>(name);

		anax::Entity playerEntity = m_entityFactory->createPlayer(playerPos,
                                                                  inputs,
                                                                  m_playerMovementSystem,
                                                                  healthIndicator,
                                                                  player);
        player->setEntity(playerEntity);

        glm::ivec2 pos;
        if(playerPos.x > (m_map->getMapSize().x * 32) / 2)
        {
            pos.x = getWindow()->getSize().x - healthIndicator->getBoundingBox().w;
            healthIndicator->setSideOfIcons(PiH::RIGHT);
        }
        else
        {
            pos.x = 0;
            healthIndicator->setSideOfIcons(PiH::LEFT);
        }
        if(playerPos.y > (m_map->getMapSize().y * 32) / 2)
        {
            pos.y = getWindow()->getSize().y - healthIndicator->getBoundingBox().h;
        }
        else
        {
            pos.y = 0;
        }
        healthIndicator->setPosition(pos.x, pos.y);

        m_playerManager->set(player, name);
    }
}
