#pragma once
#include "Card.h"


class Fcard
{


public:

	int fx;
	int fy;
	Card fcard;
	bool fcurrent;


	Fcard();
	Fcard(Card card, int x, int y, bool current);
	~Fcard();

	bool isCard();

	void setFcard(Card card, int x, int y, bool current);

	std::string Fcard_to_printstring();

	void ch_current();

};

