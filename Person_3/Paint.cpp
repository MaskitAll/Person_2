#include "stdafx.h"
#include "Paint.h"

Paint::Paint()
{
}

Paint::~Paint()
{
}

/*utility*/

void Paint::setcur(int x, int y)	//��������� ������� �� �������  x y, �����: setcur(0, 0);
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void Paint::SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

bool Paint::isNumber(std::string str) {
	if (str == "") { return false; }
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] != ' ') {
			if (!isdigit(str[i])) {
				return false;
			}
		}
	}
	return true;
}

int Paint::Width_box(std::string str) {
	int max_widght = 0;
	for (size_t i = 0; i < str.size(); ++i) {
		if (max_widght < str.find("\n", i)) {
			max_widght = str.find("\n", i) - i;
			i = str.find("\n", i);
		}
	};
	return max_widght;
}

std::string Paint::text_without_funcs(std::string str) {
	std::string end_str = "";
	size_t size = 0;
	int i = 0;
	while (size < str.size()) {
		i = str.find("{", i);
		if (i != -1) {
			end_str += str.substr(size, i - size - 1);
			size = str.find("}", i);
			++i;
		}
		else {
			end_str += str.substr(size + 1, str.size() - size);
			break;
		}
	}
	return end_str;
}

std::string Paint::text_without_funcs_and_break(std::string str) {
	std::string end_str = "";
	str = text_without_funcs(str);
	for(int i = 0; i < str.size(); ++i){
		if (str[i] != '\r' && str[i] != '\n'&& str[i] != '\t'&& str[i] != '\v'&& str[i] != '\a') {
			end_str += str[i];
		}
	}
	return end_str;
}

/*{s(n, k)} {/s}*/
/*{u}{/u}*/

bool Paint::isfunc(std::string substr) {
	//std::cout << "\nsub = " << substr << "\n"; 
	int i = 0;
	if (substr[i] == '{') {
		if (substr[i + 1] && substr[i + 1] == 's') {
			int pos = 0;
			int pos1 = 0;
			int pos2 = 0;
			pos = substr.find("(", i) + 1;
			pos1 = substr.find(",", pos);
			if (!isNumber(substr.substr(pos, pos1 - pos))) return false;
			pos1++;
			pos2 = substr.find(")", pos1);
			if (!isNumber(substr.substr(pos1, pos2 - pos1))) return false;
			return true;
		}
	}
	if (substr == "{/s}") {
		return true;
	}
	return false;
}

void Paint::print_text(std::string str) {
	int y1 = 0;
	int apostr = 0;
	
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != '{') {
			std::cout << str[i];
		}
		else {
			if (str[i] == '{' && isfunc(str.substr(i, str.find("}", i) - i + 1))) {
				++i;
				if (str[i] == 's') {
					int textground = std::stoi(str.substr(str.find("(", i) + 1, str.find(",", i) - 1));
					int background = std::stoi(str.substr(str.find(",", i) + 1, str.find(")", i) - 1));
					i = str.find("}", i);
					++apostr;
					SetColor(textground, background);
				}
				else if (str[i] == '/') {
					++i;
					if (str[i] == 's') {
						if (apostr <= 1) { i = str.find("}", i); SetColor(15, 0); }
						else {
							int textground = 0;
							int background = 0;
							int pos = i - 3;
							for (int q = apostr; q > 0; --q) {
								while (str[pos] != '{' && pos > 0) { --pos; }
								if (str[pos + 1] == 's' && isfunc(str.substr(pos, str.find("}", pos) - pos + 1))) {
									--pos;
									textground = std::stoi(str.substr(str.find("(", pos) + 1, str.find(",", pos) - 1));
									background = std::stoi(str.substr(str.find(",", pos) + 1, str.find(")", pos) - 1));
								}
								else if (str.substr(pos, str.find("}", pos) - pos + 1) == "{/s}" && q == 0) {
									textground = 15;
									background = 0;
									break;
								}
								else if (str.substr(pos, str.find("}", pos) - pos + 1) == "{/s}") {
									++q;
									--pos;
									continue;
								}
							}
							i = str.find("}", i);
							SetColor(textground, background);
						}
					}
					if (apostr > 0) { --apostr; }
				}
			}
			else {
			}
		}
	}
}

void Paint::print_text(std::string str, int lenght) {
	int current_len = 0;
	for (size_t i = 0; i < str.size(); ++i) {
		if (current_len % lenght == 0) {
			int k = i;
			int sublenght = lenght;
			while (k > 0 && (i - k) < sublenght && str[k] != ' ' && str[k] != '\n') { 
				if (str[k] == '}') {
					int tsize = 0;
					while(str[k] != '{') {--k; ++tsize; }
					if (isfunc(str.substr(k, tsize))) {sublenght += tsize;}
				}
				--k;
			}
			if (str[k] == ' ') { str[k] = '\n'; i = k; }
			else { str = str.substr(0, i) + "\n" + str.substr(i, str.size()); }
			current_len = 0;
		}
		if (str[i] == '{' && isfunc(str.substr(i, str.find("}", i) - i + 1))) {
			i += str.find("}", i) - i + 1;
		}
			++current_len;
	}
	print_text(str);
}

void Paint::print_text(std::string str, int x, int y) {
	if (x < 0 || y < 0) { return; }
	int y1 = 0;
	int apostr = 0;
	setcur(x, y + y1);
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != '\n' && str[i] != '{') {
			std::cout << str[i];
		}
		else {
			if (str[i] == '\n') {
				y1++;
				setcur(x, y + y1);
				continue;
			}
			if (str[i] == '{' && isfunc(str.substr(i, str.find("}", i) - i + 1))) {
				++i;
				if (str[i] == 's') {
					int textground = std::stoi(str.substr(str.find("(", i) + 1, str.find(",", i) - 1));
					int background = std::stoi(str.substr(str.find(",", i) + 1, str.find(")", i) - 1));
					i = str.find("}", i);
					++apostr;
					SetColor(textground, background);
				}
				else if (str[i] == '/') {
					++i;
					if (str[i] == 's') {
						if (apostr <= 1) { i = str.find("}", i); SetColor(15, 0); }
						else {
							int textground = 0;
							int background = 0;
							int pos = i - 3;
							for (int q = apostr; q > 0; --q) {
								while (str[pos] != '{' && pos > 0) { --pos; }
								if (str[pos + 1] == 's' && isfunc(str.substr(pos, str.find("}", pos) - pos + 1))) {
									--pos;
									textground = std::stoi(str.substr(str.find("(", pos) + 1, str.find(",", pos) - 1));
									background = std::stoi(str.substr(str.find(",", pos) + 1, str.find(")", pos) - 1));
								}
								else if (str.substr(pos, str.find("}", pos) - pos + 1) == "{/s}" && q == 0) {
									textground = 15; 
									background = 0;
									break;
								}
								else if(str.substr(pos, str.find("}", pos) - pos + 1) == "{/s}"){
									++q;
									--pos;
									continue;
								}
							}
							i = str.find("}", i);
							SetColor(textground, background);
						}
					}
					if (apostr > 0) { --apostr; }
				}
			}
			else {
			}
		}
	}
}
	
void Paint::print_text(std::string str, int x, int y, int lenght) {
	int current_len = 0;
	for (size_t i = 0; i < str.size(); ++i) {
		if (current_len % lenght == 0) {
			int k = i;
			int sublenght = lenght;
			while (k > 0 && (i - k) < sublenght && str[k] != ' ' && str[k] != '\n') {
				if (str[k] == '}') {
					int tsize = 0;
					while (str[k] != '{') { --k; ++tsize; }
					if (isfunc(str.substr(k, tsize))) { sublenght += tsize; }
				}
				--k;
			}
			if (str[k] == ' ') { str[k] = '\n'; i = k; }
			else { str = str.substr(0, i) + "\n" + str.substr(i, str.size()); }
			current_len = 0;
		}
		if (str[i] == '{' && isfunc(str.substr(i, str.find("}", i) - i + 1))) {
			i += str.find("}", i) - i + 1;
		}
		++current_len;
	}
	print_text(str, x, y);
}

void Paint::loading(int n, int delay, int x, int y) {
	for (int j = 0; j < n; ++j) {
		Sleep(delay);
		system("cls");
		setcur(x, y);
		std::cout << "_...\\" << std::endl;
		Sleep(delay);
		system("cls");
		setcur(x, y);
		std::cout << "_../" << std::endl;
		Sleep(delay);
		system("cls");
		setcur(x, y);
		std::cout << "_..\\" << std::endl;
		Sleep(delay);
		system("cls");
		setcur(x, y);
		std::cout << "_./" << std::endl;
		Sleep(delay);
		system("cls");
		setcur(x, y);
		std::cout << "_.\\" << std::endl;
		Sleep(delay);
		system("cls");
		setcur(x, y);
		std::cout << "_/" << std::endl;
	}
}

/*graphic*/

void Paint::fill_box(int x1, int y1, int x2, int y2) {
	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) { return; }
	if (x1 > x2) { std::swap(x1, x2); }
	if (y1 > y2) { std::swap(y1, y2); }
	for (int y = y1; y <= y2; ++y) {
		setcur(x1, y);
		for (int x = x1; x <= x2; ++x) {
			std::cout << " ";
		}
	}
}

void Paint::fill_box(std::string str, int x1, int y1, int x2, int y2) {
	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) { return; }
	if (x1 > x2) { std::swap(x1, x2); }
	if (y1 > y2) { std::swap(y1, y2); }
	for (int y = y1; y < y2; ++y) {
		setcur(x1, y);
		for (int x = x1; x < x2; ++x) {
			std::cout << str;
		}
	}
}

void Paint::fill_box(std::string str, int width, int x1, int y1, int x2, int y2) {
	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || width < 0) { return; }
	if (x1 > x2) { std::swap(x1, x2); }
	if (y1 > y2) { std::swap(y1, y2); }
	for (int y = y1; y < y2; ++y) {
		setcur(x1, y);
		for (int x = x1; x < x2; ++x) {
			if (x - x1 < width || y - y1 < width || x2 - x <= width || y2 - y <= width) {
				std::cout << str;
			}
			else {
				std::cout << " ";
			}
		}
	}
}

void Paint::print_Hline(int x, int y, int lenght) {
	setcur(x, y);
	for (int i = 0; i < lenght; ++i) { std::cout << "-"; }
}

void Paint::print_Hline(int x, int y, int background, int lenght) {
	SetColor(background, background);
	setcur(x, y);
	for (int i = 0; i < lenght; ++i) { std::cout << " "; }
	SetColor(15, 0);
}

void Paint::print_Wline(int x, int y, int lenght) {
	for (int i = 0; i < lenght; ++i) { setcur(x, y); std::cout << "|"; ++y; }
}

void Paint::print_Wline(int x, int y, int background, int lenght) {
	SetColor(background, background);
	for (int i = 0; i < lenght; ++i) { setcur(x, y); std::cout << " "; ++y; }
	SetColor(15, 0);
}

void Paint::print_box(int x1, int y1, int x2, int y2, int background) {
	print_Wline(x1, y1, background, (y2 - y1) + 1);
	print_Wline(x2, y1, background, (y2 - y1) + 1);
	print_Hline(x1, y1, background, (x2 - x1) + 1);
	print_Hline(x1, y2, background, (x2 - x1) + 1);
}

/*menu. Only for game*/

void Paint::screen_info(int &width, int &height) {
	HANDLE hWndConsole;
	if (hWndConsole = GetStdHandle(-12))
	{
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
		{
			width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
			height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
		}
		else
			printf("Error: %d\n", GetLastError());
	}
	else
		printf("Error: %d\n", GetLastError());
}

void Paint::deck_menu(Deck &deck) {							// ����� ��������� � ����������
	system("cls");
	int current_card = 0;
	int current_list_card = 0;
	int flag = 0;
	int widht = 0;											// x
	int height = 0;											// y
	screen_info(widht, height);	
	int r1x = 0;
	int r1y = 0;
	int r2x = 0;
	int r2y = 6;
	int r3x = (widht * 2 / 3);
	int r3y = 6;
	Deck fighting_deck;
																// ������ ������
	print_box(r1x, r1y, widht, height - 1, 15);					// ����� ����
	print_Hline(r2x, r2y, 15, widht);							// ��������� ��������
	print_Wline(r3x, r3y, 15, height - 6);						// ��������� ���� �� ����

/*1*/	print_text("{s(3,0)}MY GAME{/s}", (widht / 2) - 4, r1y + 3);

/*2*/	_print_deck(deck, current_card, r2x + 5, r2y + 5);
		print_text(deck[current_card].getDescription(), r2x + 5, r2y + 20);

/*3*/	print_text("{s(4,0)}Hello everyone!{/s}\n\nThis is my game\nLet`s play!\n\n1 - to add new card\n2 - to shuffle deck\n3 - to restore order deck\n4 - to save deck in file\n5 - to take deck in file\n6 - to change characteristic\n7 - to add card in fighting deck\n8 - to delete card\n\nA - to left card\nD - to right card", r3x + 2, r3y + 5);

	char vvod;
	do {
		setcur(0, 0);
		SetColor(15, 15);
		vvod = _getche();
		SetColor(15, 0);
		if (vvod == '1') { 
			fill_box(r2x + 1, r2y + 1, r3x - 1, height - 2); 
			deck.new_card(); 
			current_card = deck.deck_size() - 1;
			reCard(deck[current_card], r2x + 2, r2y + 2); 
			flag = 1;
		}
		if (vvod == '2' && deck.deck_size() != 0) { deck.shuffle(); flag = 1; }
		if (vvod == '3' && deck.deck_size() != 0) { deck.restore_order(); flag = 1; }
		if (vvod == '4') { deck.deck_to_file("Deck.txt"); }
		if (vvod == '5') { deck.file_to_deck("Deck.txt"); flag = 1; }
		if (vvod == '6' && deck.deck_size() != 0) {
			int n;
			fill_box(r3x + 1, r3y + 1, widht - 1, height - 2);
			print_text(" 1 - lvl,\n 2 - Rhand,\n 3 - Lhand,\n 4-  HP,\n 5 - Armor,\n 6 - Speed\n", r3x + 5, r3y + 5);
			fill_box(r2x + 1, r2y + 1, r3x - 1, height - 2);
			print_text("Enter char(1 - 6): ", r2x + 5, r2y + 5);
			std::cin >> n;
			while (n > 6 || n < 1) {
				fill_box(r2x + 5, r2y + 6, r2x + 20, r2y + 6);
				std::cin >> n;
			}
			int up;
			print_text("Enter up: ", r2x + 5, r2y + 7);
			std::cin >> up;
			deck[current_card].character_up(*deck[current_card].int_to_Character(n), up);
			flag = 4;
		}
		if (vvod == '7') { fighting_deck.new_card(); fighting_deck[fighting_deck.deck_size() - 1] = deck[current_card]; current_list_card = fighting_deck.deck_size() - 1; flag = 6; }
		if (vvod == '8' && deck.deck_size() != 0) { 
			deck.delete_card(current_card);
			if (deck.deck_size() != 0) {
				current_card = deck.deck_size() - 1;
				flag = 1;
			}
			else {
				current_card = 0;
				flag = 5;
			}

		}



		if (vvod == 'w' || vvod == 'W') { if (current_list_card > 0) { current_list_card--; flag = 6; } }
		if (vvod == 's' || vvod == 'S') { if (current_list_card < fighting_deck.deck_size() - 1) { current_list_card++; flag = 6; } }

		if (vvod == 'a' || vvod == 'A') { if (current_card > 0) { current_card--; flag = 1; } }
		if (vvod == 'd' || vvod == 'D') { if (current_card < deck.deck_size() - 1) { current_card++; flag = 1;} }
		if (vvod == 'q' || vvod == 'Q') { break; }


		/*������������ � ���������� ���� 2*/
		if (flag == 1) {
			fill_box(r2x + 1, r2y + 1, r3x - 1, height - 2);
			_print_deck(deck, current_card, r2x + 5, r2y + 5);
			print_text(deck[current_card].getDescription(), r2x + 5, r2y + 20);
			flag = 0;
		}
		/*������������ � ���������� ���� 1*/
		if (flag == 2) {
			fill_box(r1x + 1, r1y + 1, widht - 1, r2y - 1);
			print_text("{s(4,0)}MY GAME{/s}", (widht / 2) - 4, r1y + 3);
			flag = 0;
		}
		/*������������ � ���������� ���� 3*/
		if (flag == 3) {
			fill_box(r3x + 1, r3y + 1, widht - 1, height - 2);
			print_text("{s(4,0)}Hello everyone!{/s}\n\nThis is my game\nLet`s play!\n\n1 - to add new card\n2 - to shuffle deck\n3 - to restore order deck\n4 - to save deck in file\n5 - to take deck in file\n6 - to change characteristic\n7 - to delete card\n\nA - to left card\nD - to right card", r3x + 2, r3y + 5);
			flag = 0;
		}
		/*������������ � ���������� ���� 2 � 3*/
		if (flag == 4) {
			fill_box(r2x + 1, r2y + 1, r3x - 1, height - 2);
			_print_deck(deck, current_card, r2x + 5, r2y + 5);
			print_text(deck[current_card].getDescription(), r2x + 5, r2y + 20);
			fill_box(r3x + 1, r3y + 1, widht - 1, height - 2);
			print_text("{s(4,0)}Hello everyone!{/s}\n\nThis is my game\nLet`s play!\n\n1 - to add new card\n2 - to shuffle deck\n3 - to restore order deck\n4 - to save deck in file\n5 - to take deck in file\n6 - to change characteristic\n7 - to delete card\n\nA - to left card\nD - to right card", r3x + 2, r3y + 5);
			flag = 0;
		}
		/*������������ ���� 2*/
		if (flag == 5) {
			fill_box(r2x + 1, r2y + 1, r3x - 1, height - 2);
			flag = 0;
		}
		/*������������ � ���������� ���� 3 ������� fight_deck*/
		if (flag == 6) {
			fill_box(r3x + 1, r3y + 1, widht - 1, height - 2);
			print_list_deck(fighting_deck,current_list_card, r3x + 5, r3y + 5);
			flag = 0;
		}

	} while (vvod != 'q' && vvod != 'Q');
}


void Paint::reCard(Card &card){
	std::string Name = "";
	std::cout << "\nEnter new cardName(1-12 symbols): ";
	getline(std::cin, Name);
	//std::cin >> Name;
	while (Name.size() > 12) {
		std::cout << "\nEnter new cardName(1-12 symbols): ";
		getline(std::cin, Name);
	}
	
	int Rhand = 0;
	std::cout << "\nEnter new Rhand damage: ";
	std::cin >> Rhand;
	while (Rhand < 0) {
		std::cout << "\nEnter new Rhand damage: ";
		std::cin >> Rhand;
	}

	int Lhand = 0;
	std::cout << "\nEnter new Lhand damage: ";
	std::cin >> Lhand;
	while (Lhand < 0) {
		std::cout << "\nEnter new Lhand damage: ";
		std::cin >> Lhand;
	}

	int race = 0;
	std::cout << "\nEnter new race(0 - 7): ";
	std::cin >> race;
	while (race < 0 || race > 7)
	{
		std::cout << "\nEnter new race(0 - 7): ";
		std::cin >> race;
	}

	int HP = 0;
	std::cout << "\nEnter new maxHP: ";
	std::cin >> HP;
	while (HP < 0) {
		std::cout << "\nEnter new maxHP: ";
		std::cin >> HP;
	}

	int Armor = 0;
	std::cout << "\nEnter new armor: ";
	std::cin >> Armor;
	while (Armor < 0) {
		std::cout << "\nEnter new armor: ";
		std::cin >> Armor;
	}

	int speed = 0;
	std::cout << "\nEnter new speed: ";
	std::cin >> speed;
	while (speed < 0) {
		std::cout << "\nEnter new speed: ";
		std::cin >> speed;
	}

	int elements = 0;
	std::cout << "\nEnter new card's elements(0 - 5): ";
	std::cin >> elements;
	while (elements < 0 || elements > 5)
	{
		std::cout << "\nEnter new card's elements(0 - 5): ";
		std::cin >> elements;
	}
	
	std::string description = "";
	std::cout << "\nEnter smth about card: ";
	getline(std::cin, description);
	
	card.recard(Name, Rhand, Lhand, HP, Armor, speed, race, elements, description );
}

void Paint::reCard(Card &card, int x, int y) {
	setcur(x, y);
	std::string Name = "";
	std::cout << "Enter new cardName(1-12 symbols): ";
	setcur(x, y + 1);
	getline(std::cin, Name);
	//std::cin >> Name;
	while (Name.size() > 12) {
		fill_box(x, y + 1, x + 25, y + 1);
		setcur(x, y + 1);
		getline(std::cin, Name);
	}
	setcur(x, y + 2);
	int Rhand = 0;
	std::cout << "Enter new Rhand damage: ";
	setcur(x, y + 3);
	std::cin >> Rhand;
	while (Rhand < 0) {
		fill_box(x, y + 3, x + 25, y + 3);
		setcur(x, y + 3);
		std::cin >> Rhand;
	}

	setcur(x, y + 4);
	int Lhand = 0;
	std::cout << "Enter new Lhand damage: ";
	setcur(x, y + 5);
	std::cin >> Lhand;
	while (Lhand < 0) {
		fill_box(x, y + 5, x + 25, y + 5);
		setcur(x, y + 5);
		std::cin >> Lhand;
	}

	setcur(x, y + 6);
	int race = 0;
	std::cout << "Enter new race(0 - 8): ";
	setcur(x, y + 7);
	std::cin >> race;
	while (race < 0 || race > 8)
	{
		fill_box(x, y + 7, x + 25, y + 7);
		setcur(x, y + 7);
		std::cin >> race;
	}

	setcur(x, y + 8);
	int HP = 0;
	std::cout << "Enter new maxHP: ";
	setcur(x, y + 9);
	std::cin >> HP;
	while (HP < 0) {
		fill_box(x, y + 9, x + 25, y + 9);
		setcur(x, y + 9);
		std::cin >> HP;
	}

	setcur(x, y + 10);
	int Armor = 0;
	std::cout << "Enter new armor: ";
	setcur(x, y + 11);
	std::cin >> Armor;
	while (Armor < 0) {
		fill_box(x, y + 11, x + 25, y + 11);
		setcur(x, y + 11);
		std::cin >> Armor;
	}

	setcur(x, y + 12);
	int speed = 0;
	std::cout << "Enter new speed: ";
	setcur(x, y + 13);
	std::cin >> speed;
	while (speed < 0) {
		fill_box(x, y + 13, x + 25, y + 13);
		setcur(x, y + 13);
		std::cin >> speed;
	}

	setcur(x, y + 14);
	int elements = 0;
	std::cout << "Enter new card's elements(0 - 6): ";
	setcur(x, y + 15);
	std::cin >> elements;
	while (elements < 0 || elements > 6)
	{
		fill_box(x, y + 15, x + 25, y + 15);
		setcur(x, y + 15);
		std::cin >> elements;
	}

	setcur(x, y + 16);
	std::string description = "";
	std::cout << "Enter smth about card(< 30 sym): ";
	setcur(x, y + 17);
	//std::cin >> description;
	getline(std::cin, description);
	while (description == "")
	{
		fill_box(x, y + 17, x + 25, y + 17);
		setcur(x, y + 17);
		getline(std::cin, description);
	}
	card.recard(Name, Rhand, Lhand, HP, Armor, speed, race, elements, description);
}

void Paint::print_card(Card card, int x, int y) {
	print_text(card.Card_to_printstring(),  x, y);
}

void Paint::print_deck(Deck deck) {
	int x = 0, y = 0;
	for (int i = 0; i < deck.deck_size(); ++i) {
		x = (i % 4) * 15;
		y = ((i / 4) + 1) * 13;
		print_card(deck[i], x, y);
	}
}

void Paint::print_deck(Deck deck, int x_indent, int y_indent, int x_field, int y_field) {
	int x = 0, y = 0;
	for (int i = 0; i < deck.deck_size(); ++i) {
		x = ((i % 4)  * x_field) + x_indent;
		y = ((i / 4)  * y_field) + y_indent;
		print_card(deck[i], x, y);
	}
}

void Paint::_print_deck(Deck deck, int current, int x, int y) {
	if (current < 0 || x < 0 || y < 0) return;

	if (current - 2 >= 0) {
		print_card(deck[current], x + 1, y);
	}
	if (current - 1 >= 0) {
		print_card(deck[current], x + 2, y);
	}
	if (current + 2 <= deck.deck_size() - 1) {
		print_card(deck[current], x + 5, y);
	}
	if (current + 1 <= deck.deck_size() - 1) {
		print_card(deck[current], x + 4, y);
	}
	print_card(deck[current], x + 3, y);
}

void Paint::print_list_deck(Deck deck, int x, int y) {
	std::string str = "";
	for (int i = 0; i < deck.deck_size(); ++i) {
		str += deck[i].getName();
		str += ";\n";
	}
	print_text(str, x, y);
}

void Paint::print_list_deck(Deck deck, int current, int x, int y) {
	std::string str = "";
	for (int i = 0; i < deck.deck_size(); ++i) {
		if (i == current) { str += "{s(1, 0)}"; }
		str += deck[i].getName();
		str += ";";
		if (i == current) { str += "{/s}"; }
		str += "\n";
	}
	print_text(str, x, y);
}

void Paint::print_fighting_card(Fcard fightcard) {
	if (fightcard.fcurrent) {
		if (fightcard.fcard.isEmptyCard()) { print_text("{s(2,0)}" + fightcard.emptyFcard_to_printstring() + "{/s}", fightcard.fx * 14, fightcard.fy * 5); }
		else {
			print_text("{s(2,0)}" + fightcard.Fcard_to_printstring() + "{/s}", fightcard.fx * 14, fightcard.fy * 5);
		}
	}
	else {
		if (fightcard.fcard.isEmptyCard()) { print_text(fightcard.emptyFcard_to_printstring(), fightcard.fx * 14, fightcard.fy * 5); }
		else {
			print_text(fightcard.Fcard_to_printstring(), fightcard.fx * 14, fightcard.fy * 5);
		}
	}
}	

void Paint::print_fighting_card(Fcard fcard, int x_indent, int y_indent) {
	if (fcard.fcurrent == true) {
		if (fcard.fcard.isEmptyCard()) { print_text("{s(2,0)}" + fcard.emptyFcard_to_printstring() + "{/s}", fcard.fx * 14 + x_indent, fcard.fy * 5 + y_indent); }
		else {
			print_text("{s(2,0)}" + fcard.Fcard_to_printstring() + "{/s}", fcard.fx * 14 + x_indent, fcard.fy * 5 + y_indent);
		}
	}
	else {
		if (fcard.fcard.isEmptyCard()) { print_text(fcard.emptyFcard_to_printstring(), fcard.fx * 14 + x_indent, fcard.fy * 5 + y_indent); }
		else {
			print_text(fcard.Fcard_to_printstring(), fcard.fx * 14 + x_indent, fcard.fy * 5 + y_indent);
		}
	}
}

void Paint::print_fighting_deck(Fdeck fdeck){
	for (int y = 0; y < 6; ++y) {
		for (int x = 0; x < 6; ++x) {
			print_fighting_card(fdeck.getfcard(x, y));
		}
	}
}

void Paint::print_fighting_deck(Fdeck fdeck, int x_indent, int y_indent) {
	for (int y = 0; y < 6; ++y) {
		for (int x = 0; x < 6; ++x) {
			print_fighting_card(fdeck.getfcard(x, y), x_indent, y_indent);
		}
	}
}

void Paint::fdeck_menu(Fdeck &fightdeck){
	print_fighting_deck(fightdeck);
	print_list_deck(fightdeck.getFdeck(), 87, 2);
	 
	char vvod;
	do {
		setcur(0, 0);
		SetColor(0, 0);
		vvod = _getche();
		SetColor(15, 0);
		if (vvod == 'w' || vvod == 'W') { fightdeck.step_up(); }
		if (vvod == 's' || vvod == 'S') { fightdeck.step_down(); }
		if (vvod == 'a' || vvod == 'A') { fightdeck.step_left(); }
		if (vvod == 'd' || vvod == 'D') { fightdeck.step_right(); }

		if (vvod == '1') { fightdeck.setCard(); }
		


		print_fighting_deck(fightdeck);
		fill_box(87, 2, 100, 20);
		print_list_deck(fightdeck.getFdeck(), 87, 2);
	} while (vvod != 'q' && vvod != 'Q');
}