#ifndef CLIENT_BOMBERMANMAPTILE_HPP_INCLUDED
#define CLIENT_BOMBERMANMAPTILE_HPP_INCLUDED

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

			int id;
			TilePhysics physics;
    };
}

#endif
