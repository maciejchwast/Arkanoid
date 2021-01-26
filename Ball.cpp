#include "Ball.h"



Ball::Ball(float t_X, float t_Y, Color)  //definicja konstruktora
{
	shape.setPosition(t_X, t_Y);  //przypisanie pozycji początkowej
	shape.setRadius(this->ballRadius_);  //ustawienie promienia
	shape.setFillColor(kolorek);  //ustawienie koloru
	shape.setOrigin(this->ballRadius_, this->ballRadius_);  //ustawienie kursora na srodek kuli
}

void Ball::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Ball::actual_velocity(float new_velocity)
{
	ballVelocity_ = { new_velocity };
}

void Ball::setPosition(int x, int y) {
	shape.setPosition(x, y);
}

void Ball::update()
{
	this->shape.setFillColor(kolorek);
	shape.move(this->velocity);

	if (this->left() < 0) //tutaj jest uwzglednienie tego, zeby pilecza odbijala się od scianek
	{
		velocity.x = ballVelocity_;
	}
	else if (this->right() > 800)
	{
		velocity.x = -ballVelocity_;
	}

	if (this->top() < 0)
	{
		velocity.y = ballVelocity_;
	}
	else if (this->bottom() > 600)
	{
		velocity.y = ballVelocity_; //TUTAJ!
	}
}

float Ball::left()
{
	return this->shape.getPosition().x - shape.getRadius();
}

float Ball::right()
{
	return this->shape.getPosition().x + shape.getRadius();
}

float Ball::top()
{
	return this->shape.getPosition().y - shape.getRadius();
}

float Ball::bottom()
{
	return this->shape.getPosition().y + shape.getRadius();
}

void Ball::moveDown()
{
	this->velocity.y = ballVelocity_;
}

void Ball::moveUp()
{
	this->velocity.y = -ballVelocity_;
}

void Ball::moveRight()
{
	this->velocity.x = ballVelocity_;
}

void Ball::moveLeft()
{
	this->velocity.x = -ballVelocity_;
}

Vector2f Ball::getPosition()
{
	return shape.getPosition();
}
