#include <Client/CollisionSystem.hpp>
#include <easylogging++.h>

namespace Client
{
    CollisionSystem::CollisionSystem(BombermanMap *bombermanMap)
    {
        m_map = bombermanMap;
    }
    CollisionSystem::~CollisionSystem()
    {

    }
    void CollisionSystem::update(float frametime)
    {
        //The 2 rectangles have their positions assigned to the
        //coordinate root to simplify collision detection.

        SDL_Rect rectA;
        SDL_Rect rectB;
        glm::ivec2 point;
		std::shared_ptr<Collision> collision;
        for(auto &entityAConst : getEntities())
        {
            anax::Entity entityA = const_cast<anax::Entity&>(entityAConst);
            auto &posA = entityA.getComponent<PositionComponent>();
            auto &bodyA = entityA.getComponent<BodyComponent>();

            rectA.x = posA.pos.x + bodyA.x; //LEFT
            rectA.y = posA.pos.y + bodyA.y; //TOP
            rectA.w = bodyA.w + rectA.x;    //RIGHT
            rectA.h = bodyA.h + rectA.y;    //BOTTOM


            //Check the map for collisions
            //TOP-LEFT
            point.x = (int) rectA.x / 32; point.y = (int) rectA.y / 32;
            collideWithMapTile(m_map->getCollisionOf(point), point, entityA);

            //TOP-RIGHT
            point.x = (int) rectA.w / 32; point.y = (int) rectA.y / 32;
            collideWithMapTile(m_map->getCollisionOf(point), point, entityA);

            //BOTTOM-RIGHT
            point.x = (int) rectA.w / 32; point.y = (int) rectA.h / 32;
            collideWithMapTile(m_map->getCollisionOf(point), point, entityA);

            //BOTTOM-LEFT
            point.x = (int) rectA.x / 32; point.y = (int) rectA.h / 32;
            collideWithMapTile(m_map->getCollisionOf(point), point, entityA);

            for(auto &entityBConst : getEntities())
            {
                anax::Entity entityB = const_cast<anax::Entity&>(entityBConst);
                if(entityA.getId() != entityB.getId())
                {
                    //Only check for collision if the IDs are not equal.
                    auto &posB = entityB.getComponent<PositionComponent>();
                    auto &bodyB = entityB.getComponent<BodyComponent>();

                    rectB.x = posB.pos.x + bodyB.x;
                    rectB.y = posB.pos.y + bodyB.y;
                    rectB.w = bodyB.w + rectB.x;
                    rectB.h = bodyB.h + rectB.y;

                    //Check for collisions.
                    if(rectA.x < rectB.w
                            && rectA.w > rectB.x
                            && rectA.y < rectB.h
                            && rectA.h > rectB.y)
                    {
                        //Collision detected!
                        collision = std::make_shared<Collision>(entityA, entityB);
                        bodyA.collisionSignal(collision);
                    }
                }
            }
        }
    }
    void CollisionSystem::collideWithMapTile(uint8_t collision, const glm::ivec2 &tile, anax::Entity &e)
    {
        if(collision == EmbeddedTilemap::CollideFully)
		{
			std::shared_ptr<Collision> collision;
			SDL_Rect rect;
            rect.x = tile.x * 32;
            rect.y = tile.y * 32;
			rect.w = 32;
			rect.h = 32;
			collision = std::make_shared<Collision>(e, rect);
			if(e.hasComponent<BodyComponent>())
			{
				auto &body = e.getComponent<BodyComponent>();
                body.collisionSignal(collision);
			}
        }
    }
    anax::Entity CollisionSystem::getEntityAt(const glm::ivec2 &pos, bool &entityFound)
    {
        SDL_Rect rect;
        entityFound = false;
        for(auto &entity : getEntities())
        {
            auto &posComp = entity.getComponent<PositionComponent>();
            auto &body = entity.getComponent<BodyComponent>();

            rect.x = posComp.pos.x;
            rect.y = posComp.pos.y;
            rect.w = body.w;
            rect.h = body.h;

            if(pos.x < rect.x + rect.w
                    && pos.x >= rect.x
                    && pos.y >= rect.y
                    && pos.y < rect.y + rect.h)
            {
                entityFound = true;
                return entity;
            }
        }
    }
}
