#include "stdafx.h"
#include "Fdeck.h"


Fdeck::Fdeck()
{
	Card card;
	for (int y = 0; y < 6; ++y) {
		for (int x = 0; x < 6; ++x) {
			fdeck[x][y].setFcard(card, x, y, false);
		}
	}
	fdeck[0][0].ch_current();
}


Fdeck::~Fdeck()
{
}
