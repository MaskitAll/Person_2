#pragma once
#include "stdafx.h"
#include "Paint.h"
#include <vector>

class Map
{
	struct Coord {
		int x;
		int y;

		Coord();
		Coord(int x1, int y1);
		Coord& operator=(Coord coord);

	};
	struct Pole {
		char name;
		int fone_color;
		std::string description;

	};
	Coord coord;
	Pole pole;


public:
	Map();
	~Map();

	void create_world();


};

