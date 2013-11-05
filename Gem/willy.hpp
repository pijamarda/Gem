//La clase Willy tiene 2 funciones especificas, la primera es servir como la clase con la que se dibujara el
//muñequito tipo lemmings que va minando por el mapa segun toca
//La segunda es servir para guardar los items que va ganando el propio jugador

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

Willy::Willy(sf::Vector2i pos)
{
	this->position = pos;
	estado = State::IDLE;
}

Willy::Willy()
{
	this->coins=0, copper=0, silver=0, gold=0;
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
	std::string monedas = std::to_string(coins);	
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
}

//Muestra el inventario por consola, segun vayamos añadiendo items apareceran mas cosas
void Willy::printInvConsola()
{
	std::cout<< "Total: " << coins << std::endl;
	std::cout << "G " << gold << " S "<< silver  << " C " << copper << std::endl;	
}