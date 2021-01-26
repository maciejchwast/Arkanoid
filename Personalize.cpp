#include "Personalize.h"
#include <iostream>

Personalize::Personalize(float width, float height) {
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Blad wczytwywania fontu!" << std::endl;

	}

	//ustawianie napisow w menu

	opcje[0].setFont(font);
	opcje[0].setFillColor(sf::Color::Red);
	opcje[0].setString("Motyw 1");
	opcje[0].setStyle(sf::Text::Underlined | sf::Text::Bold);
	opcje[0].setPosition(sf::Vector2f(350, 300));

	opcje[1].setFont(font);
	opcje[1].setFillColor(sf::Color::White);
	opcje[1].setString("Motyw 2");
	opcje[1].setPosition(sf::Vector2f(350, 370));

	opcje[2].setFont(font);
	opcje[2].setFillColor(sf::Color::White);
	opcje[2].setString("Motyw 3");
	opcje[2].setPosition(sf::Vector2f(350, 440));

	opcje[3].setFont(font);
	opcje[3].setFillColor(sf::Color::White);
	opcje[3].setString("Wyjdz do menu");
	opcje[3].setPosition(sf::Vector2f(300, 510));

	selectedItemIndex = 0;

}

void Personalize::draw(sf::RenderWindow &window) {
	sf::Texture motywy;

	if (!motywy.loadFromFile("motywy.png"))
	{
		std::cout << "Nie mozna zaladowac tla menu!" << std::endl;
	}
	sf::Sprite m(motywy);
	window.clear();
	window.draw(m);

	//wypisywanie na ekranie menu
	for (int i = 0; i < MAX_NUMBER_OF_MENU_ITEMS; i++) {

		window.draw(opcje[i]);

	}
}

//przesuniecie wyboru w gore
void Personalize::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		opcje[selectedItemIndex].setFillColor(sf::Color::White);
		opcje[selectedItemIndex].setStyle(sf::Text::Regular);
		selectedItemIndex--;
		opcje[selectedItemIndex].setFillColor(sf::Color::Red);
		opcje[selectedItemIndex].setStyle(sf::Text::Underlined | sf::Text::Bold);
	}
}

//przesuniecie wyboru w dol
void Personalize::MoveDown() {
	if ((selectedItemIndex - 2 <= 0)) {
		opcje[selectedItemIndex].setFillColor(sf::Color::White);
		opcje[selectedItemIndex].setStyle(sf::Text::Regular);
		selectedItemIndex++;
		opcje[selectedItemIndex].setFillColor(sf::Color::Red);
		opcje[selectedItemIndex].setStyle(sf::Text::Underlined | sf::Text::Bold);
	}
}