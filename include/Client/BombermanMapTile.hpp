#ifndef CLIENT_BOMBERMANMAPTILE_HPP_INCLUDED
#define CLIENT_BOMBERMANMAPTILE_HPP_INCLUDED

#include <Client/EntityDropGenerator.hpp>

namespace Client
{
    class BombermanMapTile
    {
        public:
			enum TilePhysics {
				SOLID,
				PASSABLE,

				_COUNT
			};

            BombermanMapTile()
            {
                id = 0;
                physics = TilePhysics::SOLID;
            }

			int id = 0;
            bool bombable = false;
			TilePhysics physics = PASSABLE;
            EntityDropGenerator *dropGenerator = nullptr;
    };
}

#endif
