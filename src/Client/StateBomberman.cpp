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
#include <Client/PlayerComponent.hpp>
#include <Client/VelocityComponent.hpp>
#include <Client/BodyComponent.hpp>

namespace Client
{

    StateBomberman::StateBomberman()
    {

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
        if(m_map != nullptr)
            delete m_map;
        if(m_playerInputSystem != nullptr)
            delete m_playerInputSystem;
        if(m_playerMovementSystem != nullptr)
            delete m_playerMovementSystem;
        if(m_explosionSystem != nullptr)
        	delete m_explosionSystem;
        if(m_timerSystem != nullptr)
            delete m_timerSystem;
        if(m_world != nullptr)
            delete m_world;

		LOG(INFO) << "StateBomberman deleted.";
    }

    void StateBomberman::init()
    {
        LOG(INFO) << "Initializing StateBomberman.";
        m_map = new BombermanMap();
        m_world = new anax::World();

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

        m_map->setTexture(getTextureManager()->get("tilemap_proto.png"));

        m_map->init(glm::ivec2(17, 15));

        m_map->createOuterWall(0);
        m_map->createOuterWall(1);
        m_map->createInnerStamps();
        m_map->createFillerWalls();

        std::vector<glm::ivec2> playerPositions;
        glm::ivec2 playerPos(0, 0);

       	InputMap inputMap;
        inputMap.set(SDL_SCANCODE_W, PlayerInputEnum::UP);
       	inputMap.set(SDL_SCANCODE_A, PlayerInputEnum::LEFT);
        inputMap.set(SDL_SCANCODE_S, PlayerInputEnum::DOWN);
        inputMap.set(SDL_SCANCODE_D, PlayerInputEnum::RIGHT);
        inputMap.set(SDL_SCANCODE_SPACE, PlayerInputEnum::ACTION);
        playerPos.x = 32; playerPos.y = 32;
		m_entityFactory->createPlayer(playerPos, inputMap);
        playerPositions.push_back(playerPos / 32);

        inputMap.clear();

        inputMap.set(SDL_SCANCODE_UP, PlayerInputEnum::UP);
       	inputMap.set(SDL_SCANCODE_LEFT, PlayerInputEnum::LEFT);
        inputMap.set(SDL_SCANCODE_DOWN, PlayerInputEnum::DOWN);
        inputMap.set(SDL_SCANCODE_RIGHT, PlayerInputEnum::RIGHT);
        inputMap.set(SDL_SCANCODE_L, PlayerInputEnum::ACTION);
        playerPos.x = 15 * 32; playerPos.y = 13 * 32;
		m_entityFactory->createPlayer(playerPos, inputMap);
        playerPositions.push_back(playerPos / 32);

        m_map->createPlayerSpace(playerPositions);

        m_world->refresh();
        LOG(INFO) << "StateBomberman initialized.";
    }

    void StateBomberman::update(float frameTime)
    {
        m_world->refresh();
        m_timerSystem->update(frameTime);
        m_animationSystem->update(frameTime);
		m_explosionSystem->update(frameTime);

        m_playerInputSystem->update();
        m_playerMovementSystem->update(frameTime);
        m_bombExplodeSystem->update();

        m_bombPlacePositionSystem->update();
        m_bombPlaceSystem->update();
    }

    void StateBomberman::render(Window *window)
    {
		m_map->render(window);
        m_spriteRenderingSystem->render(window);
    }
}
