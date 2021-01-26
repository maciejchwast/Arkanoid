#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball : public sf::Drawable
{
public:
	Ball(float, float, Color);
	Ball() = delete;
	~Ball() = default;

	void update();  //opisuje ruch pileczki
	void actual_velocity(float); //zmiana predkosci w poziomach

	void setPosition(int x, int y);

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	Vector2f getPosition();

	float left();
	float right();
	float top();
	float bottom();

	Color kolorek = Color::Yellow;


private:
	CircleShape shape;
	const float ballRadius_{ 10.0f };
	float ballVelocity_{ 3.0f };
	Vector2f velocity{ ballVelocity_, ballVelocity_ };
	void  draw(RenderTarget& target, RenderStates state) const override;
};

