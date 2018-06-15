#include "stdafx.h"
#include "Fcard.h"


Fcard::Fcard() : fx(-1), fy(-1), fcard(), fcurrent(false)
{
}


Fcard::Fcard(Card card, int x, int y, bool current) : fcard(card), fx(x), fy(y),  fcurrent(false)
{
}

Fcard::~Fcard()
{
}

bool Fcard::isCard() {
	return (fcard.isEmptyCard());
}

void Fcard::setFcard(Card card, int x, int y, bool current) {
	fcard = card;
	fx = x;
	fy = y;
	fcurrent = current;
}

void Fcard::ch_current() {
	if (fcurrent) fcurrent = false;
	fcurrent = true;
}

std::string Fcard::Fcard_to_printstring() {
	std::string end_str = "";
	/*1*/
	for (int i = 0; i < 12; ++i) { end_str += "-"; }
	end_str += "\n";
	/*2*/
	end_str += "|";
	for (int i = 0; i < fcard.h_to_12(fcard.getName(), 1); ++i) { end_str += " "; }
	std::cout << fcard.getName();
	for (int i = 0; i < fcard.h_to_12(fcard.getName(), 0); ++i) { end_str += " "; }
	end_str += "|\n";
	/*3*/
	end_str += "|";
	fcard.getCharacter(*fcard.int_to_Character(4));
	end_str += "|\n";
	/*4*/
	end_str += "|";

	end_str += "|\n";
	/*5*/
	for (int i = 0; i < 12; ++i) {
		end_str += "-";
	}
	return end_str;
}