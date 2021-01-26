#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Blad wczytwywania fontu!" << std::endl;

	}

	//ustawianie napisow w menu

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("START");
	menu[0].setStyle(sf::Text::Underlined | sf::Text::Bold);
	menu[0].setPosition(sf::Vector2f(350, 300));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("OPCJE");
	menu[1].setPosition(sf::Vector2f(350, 400));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("WYJDZ");
	menu[2].setPosition(sf::Vector2f(350, 500));

	selectedItemIndex = 0;

}

void Menu::draw(sf::RenderWindow &window) {
	sf::Texture background;
	if (!background.loadFromFile("menu_background.png"))
	{
		std::cout << "Nie mozna zaladowac tla menu!" << std::endl;
	}
	sf::Sprite s(background);
	window.draw(s);

	//wypisywanie na ekranie menu
	for (int i = 0; i < MAX_NUMBER_OF_MENU_ITEMS; i++) {

		window.draw(menu[i]);

	}
}

//przesuniecie wyboru w gore
void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		menu[selectedItemIndex].setStyle(sf::Text::Regular);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menu[selectedItemIndex].setStyle(sf::Text::Underlined | sf::Text::Bold);
	}
}

//przesuniecie wyboru w dol
void Menu::MoveDown() {
	if ((selectedItemIndex - 1 <= 0)) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		menu[selectedItemIndex].setStyle(sf::Text::Regular);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menu[selectedItemIndex].setStyle(sf::Text::Underlined | sf::Text::Bold);
	}
}