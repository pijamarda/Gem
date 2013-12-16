//La clase Willy tiene 2 funciones especificas, la primera es servir como la clase con la que se dibujara el
//muñequito tipo lemmings que va minando por el mapa segun toca
//La segunda es servir para guardar los items que va ganando el propio jugador
#include <SFML/Graphics.hpp>
#include <iostream>

class Willy
{
private:
	//---VARIABLES----//
	enum State
	{
		IDLE, WALKING, MINING
	};
	float SPEED;
	float SIZE;
	sf::Vector2i position;
	sf::Vector2i aceleracion;
	State estado;
	int coins;
	int copper;
	int silver;
	int gold;

public:
	//---CONSTRUCT----//
	Willy();
	Willy(sf::Vector2i);

	//---METODOS----//
	sf::Vector2i getPosition();
	void setPosition(sf::Vector2i);
	void addCoins(int);
	void printInvConsola();
	void updateCoins();
};

