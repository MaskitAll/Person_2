#pragma once

#include <vector>
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <algorithm>
#include "Deck.h"
#include "Card.h"

class Deck
{
private:
	std::vector <Card> deck;
public:


	Card& operator[](int pos);
	Deck& operator=(Deck deck1);


	Deck();
	Deck(std::string filename);
	~Deck();

	void new_card();						//добавить новую карту
	void delete_card(int current);			//удалить карту
	int deck_size();						//возвращает количество карт
	void shuffle();							//перемешать карты
	void restore_order();					//восстановить порядок

	std::string deck_to_filestring();
	void filestring_to_deck(std::string filestring);

	void deck_to_file(std::string filename);
	void file_to_deck(std::string filename);

};


