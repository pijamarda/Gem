#include "SFML/Graphics.hpp"

class Willy
{
	enum State
	{
		IDLE, WALKING, MINING
	};
	float SPEED;
	float SIZE;
	sf::Vector2i posicion;
	sf::Vector2i aceleracion;
	State estado;
	Willy(sf::Vector2i);
	sf::Vector2i getPosition();
};

Willy::Willy(sf::Vector2i pos)
{
	this->posicion = pos;
	estado = State::IDLE;
}

sf::Vector2i Willy::getPosition()
{
	return posicion;
}