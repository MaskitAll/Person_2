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

bool Fcard::isCurrent() {
	return fcurrent;
}

void Fcard::setFcard(Card card, int x, int y, bool current) {
	fcard = card;
	fx = x;
	fy = y;
	fcurrent = current;
}

void Fcard::set_emptyFcard() {
	fcard.set_emptyCard();
	fx = -1;
	fy = -1;
	fcurrent = false;
}

void Fcard::set_emptyFcard(int x, int y) {
	fcard.set_emptyCard();
	fx = x;
	fy = y;
	fcurrent = false;
}

Card Fcard::getCard() {
	return fcard;
}

void Fcard::ch_current() {
	if (fcurrent) {
		fcurrent = false;
	}
	else {
		fcurrent = true;
	}
}

std::string Fcard::Fcard_to_printstring() {
	std::string end_str = "";
	/*1*/
	for (int i = 0; i <= 13; ++i) { end_str += "-"; }
	end_str += "\n";
	/*2*/
	end_str += "|";
	for (int i = 0; i < h_to_12(fcard.getName(), 1); ++i) { end_str += " "; }
	end_str += fcard.getName();
	for (int i = 0; i < h_to_12(fcard.getName(), 0); ++i) { end_str += " "; }
	end_str += "|\n";
	/*3*/
	end_str += "|";
	for (int i = 0; i < h_to_12(std::to_string(fcard.getCharacter(*fcard.int_to_Character(4)).local), 1); ++i) { end_str += " "; }
	end_str += fcard.character_to_printstring(*fcard.int_to_Character(4));
	for (int i = 0; i < h_to_12(std::to_string(fcard.getCharacter(*fcard.int_to_Character(4)).local), 0); ++i) { end_str += " "; }
	end_str += "|\n";
	/*4*/
	end_str += "|";
	for (int i = 0; i < h_to_12(std::to_string(fcard.getCharacter(*fcard.int_to_Character(2)).local) + "\\ / " + std::to_string(fcard.getCharacter(*fcard.int_to_Character(3)).local), 1) + 1; ++i) { end_str += " "; }
	end_str += fcard.character_to_printstring(*fcard.int_to_Character(2));
	end_str += "\\/";
	end_str += fcard.character_to_printstring(*fcard.int_to_Character(3));
	for (int i = 0; i < h_to_12(std::to_string(fcard.getCharacter(*fcard.int_to_Character(2)).local) + "\\ / " + std::to_string(fcard.getCharacter(*fcard.int_to_Character(3)).local), 0) + 1; ++i) { end_str += " "; }
	end_str += "|\n";
	/*5*/
	for (int i = 0; i <= 13; ++i) {
		end_str += "-";
	}
	return end_str;
}

std::string Fcard::emptyFcard_to_printstring() {
	std::string end_str = "";
	/*1*/
	for (int i = 0; i <= 13; ++i) { end_str += "-"; }
	end_str += "\n";
	/*2*/
	end_str += "|";
	for (int i = 0; i <= 11; ++i) { end_str += " "; }
	end_str += "|\n";
	/*3*/
	end_str += "|";
	for (int i = 0; i <= 11; ++i) { end_str += " "; }
	end_str += "|\n";
	/*4*/
	end_str += "|";
	for (int i = 0; i <= 11; ++i) { end_str += " "; }
	end_str += "|\n";
	/*5*/
	for (int i = 0; i <= 13; ++i) {	end_str += "-"; }
	return end_str;

}