#include <Client/StateBomberman.hpp>
#include <easylogging++.h>
#include <Client/TextureManager.hpp>
#include <easylogging++.h>

#include <Client/SpriteRenderingSystem.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/PlayerInputSystem.hpp>
#include <Client/PlayerMovementSystem.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/VelocityComponent.hpp>

namespace Client
{

    StateBomberman::StateBomberman()
    {

    }
    StateBomberman::~StateBomberman()
    {
		LOG(INFO) << "StateBomberman deleted.";
    }

    void StateBomberman::init()
    {
        LOG(INFO) << "Initializing StateBomberman.";
        m_map = std::make_shared<BombermanMap>();
        m_world = std::make_shared<anax::World>();

        m_spriteRenderingSystem = std::make_shared<SpriteRenderingSystem>();
		m_world->addSystem(*m_spriteRenderingSystem.get());

        m_playerInputSystem = std::make_shared<PlayerInputSystem>();
        m_playerInputSystem->setSDLEventHandler(getSDLEventHandler());
        m_world->addSystem(*m_playerInputSystem);

        m_playerMovementSystem = std::make_shared<PlayerMovementSystem>();
        m_world->addSystem(*m_playerMovementSystem);

        m_map->setTexture(getTextureManager()->get("tilemap_proto.png"));

        m_map->init(glm::ivec2(17, 15));

        m_map->createOuterWall();
        m_map->createInnerStamps();

        auto entity = m_world->createEntity();
        entity.addComponent(new PositionComponent(20, 10));
        SpriteComponent *spriteComponent = new SpriteComponent();
        spriteComponent->texture = getTextureManager()->get("player_proto.png");
		spriteComponent->srcRect.w = 32;
		spriteComponent->srcRect.h = 32;
        entity.addComponent(spriteComponent);
        PlayerInputComponent *inputComponent = new PlayerInputComponent();
        inputComponent->inputMap.set(SDL_SCANCODE_W, PlayerInputEnum::UP);
        inputComponent->inputMap.set(SDL_SCANCODE_A, PlayerInputEnum::LEFT);
        inputComponent->inputMap.set(SDL_SCANCODE_S, PlayerInputEnum::DOWN);
        inputComponent->inputMap.set(SDL_SCANCODE_D, PlayerInputEnum::RIGHT);
        inputComponent->inputMap.set(SDL_SCANCODE_SPACE, PlayerInputEnum::ACTION);
        entity.addComponent(inputComponent);
        entity.addComponent(new PlayerComponent());
        entity.activate();

        m_world->refresh();
        LOG(INFO) << "StateBomberman initialized.";
    }

    void StateBomberman::update(float frameTime)
    {
        m_world->refresh();
        m_playerMovementSystem->update(frameTime);
    }

    void StateBomberman::render(std::shared_ptr<Window> window)
    {
		m_map->render(window);
        m_spriteRenderingSystem->render(window);
    }
}
