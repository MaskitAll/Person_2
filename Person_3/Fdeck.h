#pragma once
#include "Fcard.h"
#include "Deck.h"

class Fdeck
{
	Deck fdeck;
	Fcard pole_fcard[6][6];

public:
	int cur_x;
	int cur_y;


	Fdeck();
	Fdeck(Deck deck);
	~Fdeck();

	Deck getFdeck();
	void setFdeck(Deck deck);
	Fcard getfcard();
	Fcard getfcard(int x, int y);

	void setCard();
	void setCard(int currentCard);

	/*Толкьо для игры*/
	void step_up();
	void step_left();
	void step_right();
	void step_down();
};

