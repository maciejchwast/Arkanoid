#pragma once
#include <SFML/Graphics.hpp>



class EndGame
{
public:
	EndGame(float width, float height);


	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }	//zwrocenie aktualnie podswietlonego wybou z menu
private:
	int selectedItemIndex = 0;
	sf::Font font;
	sf::Text menu[2];
};

