// Person_3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <string>

#include "Paint.h"
#include "Card.h"
#include "Deck.h"
#include "Fcard.h"
#include "Fdeck.h"


#include <Windows.h>
#include <iostream>


int main()
{
	Deck mydeck;
	Paint Mypaint;
	Fcard myfcard;
	Fdeck myfdeck;

	//Mypaint.fill_box("=", 3, 50, 15, 20, 30);
	// (Mypaint.isfunc("{/s}")) { std::cout << "\nTrue\n\n"; }
	//Mypaint.print_text("{s(5, 0)}Anyone who {/s}reads Old and Middle{s(1, 0)} English{s(2, 0)} literary texts will be familiar {/s}with the mid-brown volumes of the EETS, {s(3, 0)}with the symbol {/s}of Alfred's jewel embo{s(4, 0)}ssed on{/s} the{/s} front cover.{/s}", 15, 30, 20);
	//Mypaint.print_text("-----------------\n{s(5, 0)}|               |\n{s(1, 0)}|  hello\tWorld |{/s}\n|               |{/s} \n-----------------\n ", 30, 20);
	//Mypaint.print_text("{/s}myart{s(5, 0)}nnnn{/s}kkkk{s(4, 0)}qwert{s(6, 0)}asdf{/s}ssss{/s}myart{/s}", 40, 40);

	//Mypaint.setcur(50, 50);
	//system("pause");
	//std::cout << "\n" << Mypaint.Width_box("----------------------------\n|               |\n\n|{s(10, 0)} hello\tWorld {s(15, 0)}|\n|               |\n-----------------\n") << "\n";
	//Mypaint.print_Hline(5, 5, 15, 20);
	//Mypaint.print_Wline(5, 6, 15, 10);
	//Mypaint.print_box(10, 10, 30, 20, 12);
	//Mypaint.setcur(50, 50);
	//Mypaint.loading(10, 1000, 20, 20);

	//Card myCard(5);
	//std::cout << myCard.Card_to_filestring();
	//std::cout << "\n\n";
	//myCard.recard((std::string)"Maskit", 5, 5, 5555, 34, 12, 3, 3,(std::string)"deadas");
	//std::cout << "\n\n";
	//std::cout << myCard.Card_to_printstring();
	//std::cout << "\n\n";
	//myCard.character_up(*myCard.int_to_Character(4), 10);
	//myCard.character_up(*myCard.int_to_Character(3), -10);
	//Mypaint.print_text(myCard.Card_to_printstring(), 35, 0);


	//std::cout << myCard.Card_to_filestring();
	//std::cout << "\n\n";
	//std::cout << "1   | asd           | 0   | 5   | 1   | 5555| 34  | 12  | goblin  | water   | it`s better card!| ";
	//std::cout << "\n\n";

	//myCard.filestring_to_Card("1   | asd           | 0   | 5   | 1   | 5555| 34  | 12  | goblin  | water   | it`s better card!| ");
	//std::cout << "\n\n";	
	//std::cout << myCard.Card_to_filestring();
	//std::cout << "\n\n";


	//system("pause");

	//mydeck.new_card();
	mydeck.file_to_deck("Deck.txt");
	mydeck.new_card();
	
	//myfdeck;

	//for (int q = 0; q < mydeck.deck_size(); ++q) {
		//myfcard.setFcard(mydeck[mydeck.deck_size() - 1], 0, 0, false);
		//myfcard.fcard = mydeck[0];
		//mydeck[0].setCharacter(*mydeck[0].int_to_Character(4), 5);

		//Mypaint.print_card(mydeck[0], 15, 15);
		//Mypaint.print_card(myfcard.fcard, 35, 15);
		//myfcard.fcard.character_up(*myfcard.fcard.int_to_Character(4), 4);
		//Mypaint.print_fighting_card(myfcard);

	//}
	//Mypaint.print_text(myfcard.Fcard_to_printstring(), 10, 10);

	//Mypaint.print_fighting_deck(myfdeck);
	myfdeck.setFdeck(mydeck);
	
	Mypaint.fdeck_menu(myfdeck);
	std::cout << "\n";
	system("pause");

	//Mypaint.print_deck(mydeck, 5, 1, 15, 15);

	Mypaint.deck_menu(mydeck);

	return 0;
}

