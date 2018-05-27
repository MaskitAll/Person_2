#pragma once
#include <vector>
#include "Card.h"
#include "Paint.h"
#include "Deck.h"

class Fighting_pole
{
	struct posicion {
		int x;
		int y;
		bool my_or_other;
	};
	bool current;
	Card fighting_card;

public:
	Fighting_pole();
	~Fighting_pole();


};

