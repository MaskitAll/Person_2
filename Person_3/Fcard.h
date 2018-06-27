#pragma once
#include "Card.h"


class Fcard:Card
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
	bool isCurrent();

	void setFcard(Card card, int x, int y, bool current);
	void set_emptyFcard();
	void set_emptyFcard(int x, int y);

	Card getCard();

	std::string Fcard_to_printstring();
	std::string Fcard::emptyFcard_to_printstring();

	void ch_current();

};

