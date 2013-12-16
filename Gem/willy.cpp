#include "willy.hpp"

Willy::Willy(sf::Vector2i pos)
{
	this->position = pos;
	estado = State::IDLE;
}

Willy::Willy()
{
	this->coins = 0, copper = 0, silver = 0, gold = 0;
	updateCoins();
}

sf::Vector2i Willy::getPosition()
{
	return position;
}

//Actualiza la posicion de Willy
void Willy::setPosition(sf::Vector2i pos)
{
	this->position = pos;
}

void Willy::addCoins(int n)
{
	this->coins += n;
	updateCoins();
}

//Aunque el total de dinero se guarda en una variable unica "coins", utilizamos este metodo para
//dividir el dinero en oro plata y cobre
void Willy::updateCoins()
{
	/*std::string monedas = std::to_string(coins);
	if (coins >=10000 )
	{
	gold=std::stoi(monedas.substr(0,monedas.length()-4));
	silver=std::stoi(monedas.substr(monedas.length()-4,2));
	copper=std::stoi(monedas.substr(monedas.length()-2,2));
	}
	else if (coins >= 100)
	{
	silver=std::stoi(monedas.substr(monedas.length()-4,2));
	copper=std::stoi(monedas.substr(monedas.length()-2,2));
	}
	else
	copper=std::stoi(monedas);
	*/
	copper = coins % 100;
	double silverTemp;
	double parteDecimal = modf((coins % 10000) / 100.0, &silverTemp);
	silver = silverTemp;
	double goldTemp;
	modf(coins / 10000.0, &goldTemp);
	gold = goldTemp;

}

//Muestra el inventario por consola, segun vayamos añadiendo items apareceran mas cosas
void Willy::printInvConsola()
{
	std::cout << "Total: " << coins << std::endl;
	std::cout << "G " << gold << " S " << silver << " C " << copper << std::endl;
}