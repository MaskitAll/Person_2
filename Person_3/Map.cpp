#include "stdafx.h"
#include "Map.h"


Map::Coord::Coord() {
	x = 0;
	y = 0;
}

Map::Coord::Coord(int x1, int y1) {
	if (x1 < 0) x1 = 0;
	if (y1 < 0) y1 = 0;
	x = x1;
	y = y1;
}

Map::Coord& Map::Coord::operator=(Coord coord) {
	x = coord.x;
	y = coord.y;
	return *this;
}

Map::Map()
{

}


Map::~Map()
{
}

void Map::create_world() {

	
}
