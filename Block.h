#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Block : public sf::Drawable
{
public:
	Block(float t_X, float t_Y, float t_Width, float t_Height, int color_R, int color_G, int color_B);
	Block() = delete;
	~Block() = default;

	void update();
	Vector2f getPosition();

	float left();
	float right();
	float top();
	float bottom();

	bool isDestroyed();
	void destroy();
	Vector2f getSize();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	RectangleShape shape;
	bool destroyed{ false };
};
