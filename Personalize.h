#pragma once
#include <SFML/Graphics.hpp>

#define	MAX_NUMBER_OF_MENU_ITEMS 4

class Personalize
{
public:
	Personalize(float width, float height);


	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }	//zwrocenie aktualnie podswietlonego wybou z menu
private:
	int selectedItemIndex = 0;
	sf::Font font;
	sf::Text opcje[MAX_NUMBER_OF_MENU_ITEMS];
};

