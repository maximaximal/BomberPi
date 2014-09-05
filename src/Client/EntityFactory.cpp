#include <Client/EntityFactory.hpp>

#include <Client/PositionComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/TimerComponent.hpp>
#include <Client/BombLayerComponent.hpp>

namespace Client
{

    EntityFactory::EntityFactory(std::shared_ptr<anax::World> world,
                                 std::shared_ptr<TextureManager> textureManager)
    {
        m_world = world;
        m_textureManager = textureManager;
    }
    EntityFactory::~EntityFactory()
    {

    }

    anax::Entity EntityFactory::createPlayer(const glm::ivec2 &pos, const InputMap &inputMap)
    {
        auto entity = m_world->createEntity();
        entity.addComponent(new PositionComponent(pos.x, pos.y));
        SpriteComponent *spriteComponent = new SpriteComponent();
        spriteComponent->texture = m_textureManager->get("player_proto.png");
		spriteComponent->srcRect.w = 32;
		spriteComponent->srcRect.h = 32;
        entity.addComponent(spriteComponent);
        PlayerInputComponent *inputComponent = new PlayerInputComponent();
        inputComponent->inputMap = inputMap;
        entity.addComponent(inputComponent);
        entity.addComponent(new BombLayerComponent());
        entity.addComponent(new BodyComponent(10, 10, 10, 10));
        entity.addComponent(new PlayerComponent());
        entity.activate();

        return entity;
    }

    anax::Entity EntityFactory::createBomb(const glm::ivec2 &pos, anax::Entity &thrower)
    {
        auto entity = m_world->createEntity();
        entity.addComponent(new PositionComponent(pos.x, pos.y));
        SpriteComponent *spriteComponent = new SpriteComponent();
        spriteComponent->texture = m_textureManager->get("bomb_proto.png");
		spriteComponent->srcRect.w = 32;
		spriteComponent->srcRect.h = 32;
        entity.addComponent(spriteComponent);
        entity.addComponent(new BodyComponent(0, 0, 32, 32));
        TimerComponent *timer = new TimerComponent();
        timer->timeToPass = 1.3;
        entity.activate();

        return entity;
    }
}