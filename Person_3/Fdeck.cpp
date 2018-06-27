#include "stdafx.h"
#include "Fdeck.h"


Fdeck::Fdeck()
{
	cur_x = cur_y = 0;
	fdeck = {};
	Card card;
	for (int y = 0; y < 6; ++y) {
		for (int x = 0; x < 6; ++x) {
			pole_fcard[x][y].setFcard(card, x, y, false);
		}
	}
	pole_fcard[cur_x][cur_y].ch_current();
}

Fdeck::Fdeck(Deck deck)
{
	cur_x = cur_y = 0;
	fdeck = deck;
	Card card;
	for (int y = 0; y < 6; ++y) {
		for (int x = 0; x < 6; ++x) {
			pole_fcard[x][y].setFcard(card, x, y, false);
		}
	}
	pole_fcard[cur_x][cur_y].ch_current();
}

Fdeck::~Fdeck()
{
}


Deck Fdeck::getFdeck() {
	return fdeck;
}

void Fdeck::setFdeck(Deck deck) {
	fdeck = deck;
}

Fcard Fdeck::getfcard() {
	return pole_fcard[cur_x][cur_y];
}

Fcard Fdeck::getfcard(int x, int y) {
	return pole_fcard[x][y];
}

void Fdeck::setCard() {
	if (fdeck[0].isEmptyCard()){ // если перва€ карта в списке карт не пуста€
		if (pole_fcard[cur_x][cur_y].fcard.isEmptyCard()) {	// если €чейка пол€ пуста
			pole_fcard[cur_x][cur_y].fcard = fdeck[0];
			fdeck.delete_card(0);
		}
		else {
			pole_fcard[cur_x][cur_y].fcard.swapCard(fdeck[0]);
		}
	}
	return;
}

void Fdeck::setCard(int currentCard) {
	if (!fdeck[currentCard].isEmptyCard()) {
		if (pole_fcard[cur_x][cur_y].fcard.isEmptyCard()) {
			pole_fcard[cur_x][cur_y].fcard = fdeck[currentCard];
			fdeck.delete_card(currentCard);
		}
		else {
			pole_fcard[cur_x][cur_y].fcard.swapCard(fdeck[currentCard]);
		}
	}
	return;
}

void Fdeck::step_up(){
	if (cur_y > 0) {
		pole_fcard[cur_x][cur_y].ch_current();
		--cur_y; 
		pole_fcard[cur_x][cur_y].ch_current();
	}
}

void Fdeck::step_left() {
	if (cur_x > 0) {
		pole_fcard[cur_x][cur_y].ch_current();
		--cur_x;
		pole_fcard[cur_x][cur_y].ch_current();
	}
}

void Fdeck::step_right() {
	if (cur_x < 5) {
		pole_fcard[cur_x][cur_y].ch_current();
		++cur_x;
		pole_fcard[cur_x][cur_y].ch_current();
	}
}

void Fdeck::step_down() {
	if (cur_y < 5) {
		pole_fcard[cur_x][cur_y].ch_current();
		++cur_y;
		pole_fcard[cur_x][cur_y].ch_current();
	}
}
