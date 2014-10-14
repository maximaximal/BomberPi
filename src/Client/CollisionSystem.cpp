#include <Client/CollisionSystem.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <easylogging++.h>

namespace Client
{
    CollisionSystem::CollisionSystem(BombermanMap *bombermanMap)
    	: Base(anax::ComponentFilter().requires<PositionComponent,
               BodyComponent>())
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
        glm::ivec3 point;
		std::shared_ptr<Collision> collision;
        for(auto &entityA : getEntities())
        {
            auto &posA = entityA.getComponent<PositionComponent>();
            auto &bodyA = entityA.getComponent<BodyComponent>();

            rectA.x = posA.pos.x + bodyA.x; //LEFT
            rectA.y = posA.pos.y + bodyA.y; //TOP
            rectA.w = bodyA.w + rectA.x;    //RIGHT
            rectA.h = bodyA.h + rectA.y;    //BOTTOM


            point.z = 1;

            //Check the map for collisions
			bool collided = false;

				//TOP-LEFT
				point.x = rectA.x; point.y = rectA.y;
                try {
                    const BombermanMapTile &tile1 = m_map->getTileAtPixel(point);
					collideWithMapTile(tile1, point, entityA, collided);
                }
                catch(std::out_of_range &e) {}

				//TOP-RIGHT
				point.x = rectA.w; point.y = rectA.y;
                try {
					const BombermanMapTile &tile2 = m_map->getTileAtPixel(point);
					collideWithMapTile(tile2, point, entityA, collided);
                }
                catch(std::out_of_range &e) {}

				//BOTTOM-RIGHT
				point.x = rectA.w; point.y = rectA.h;
                try {
                    const BombermanMapTile &tile3 = m_map->getTileAtPixel(point);
					collideWithMapTile(tile3, point, entityA, collided);
                }
                catch(std::out_of_range &e) {}

				//BOTTOM-RIGHT
				point.x = rectA.x; point.y = rectA.h;
                try {
					const BombermanMapTile &tile4 = m_map->getTileAtPixel(point);
					collideWithMapTile(tile4, point, entityA, collided);
                }
				catch(std::out_of_range &e) {}

            for(auto &entityB : getEntities())
            {
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

    void CollisionSystem::collideWithMapTile(const BombermanMapTile &tile, const glm::ivec3 &pos, anax::Entity &e, bool &alreadyCollided)
    {
        if(!alreadyCollided)
        {
			if(tile.physics != BombermanMapTile::PASSABLE)
			{
				std::shared_ptr<Collision> collision;
				SDL_Rect rect;
				rect.x = ((int) pos.x / 32) * 32;
				rect.y = ((int) pos.y / 32) * 32;
				rect.w = 32;
				rect.h = 32;
				collision = std::make_shared<Collision>(e, rect);
				if(e.hasComponent<BodyComponent>())
				{
					auto &body = e.getComponent<BodyComponent>();
					body.collisionSignal(collision);
				}
				alreadyCollided = true;
			}
        }
	}
}
