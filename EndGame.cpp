#include "EndGame.h"
#include <iostream>
#include <fstream>

EndGame::EndGame(float width, float height) {
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Blad wczytwywania fontu!" << std::endl;

	}

	//ustawianie napisow w menu

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Green);
	menu[0].setString("WROC DO MENU");
	menu[0].setStyle(sf::Text::Underlined | sf::Text::Bold);
	menu[0].setPosition(sf::Vector2f(260, 400));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("WYJDZ Z GRY");
	menu[1].setPosition(sf::Vector2f(290, 500));


	selectedItemIndex = 0;

}

void EndGame::draw(sf::RenderWindow &window) {
	sf::Texture background;
	if (!background.loadFromFile("game_over_screen.png"))
	{
		std::cout << "Nie mozna zaladowac tla koncowego!" << std::endl;
	}
	sf::Sprite s(background);
	window.draw(s);

	//wypisywanie na ekranie ekranu koncowego
	for (int i = 0; i < 2; i++) {

		window.draw(menu[i]);

	}
}

//przesuniecie wyboru w gore
void EndGame::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		menu[selectedItemIndex].setStyle(sf::Text::Regular);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Green);
		menu[selectedItemIndex].setStyle(sf::Text::Underlined | sf::Text::Bold);
	}
}

//przesuniecie wyboru w dol
void EndGame::MoveDown() {
	if ((selectedItemIndex - 1 < 0)) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		menu[selectedItemIndex].setStyle(sf::Text::Regular);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Green);
		menu[selectedItemIndex].setStyle(sf::Text::Underlined | sf::Text::Bold);
	}
}