#include "map.hpp"
#include <iostream>

class consoleScreen
{
public:
	//--VARIABLES--
	Map *mapa;

	//--METODOS--
	void consoleScreen::print_map();

	//--CONSTRUCT--
	consoleScreen(Map*);
};

consoleScreen::consoleScreen(Map *mapa)
{
	this->mapa = mapa;
	this->print_map();
}

void consoleScreen::print_map()
{
	
	std::string linea;	
	
	for (int j=0; j<MAXHEIGHT; j++)
	{
		for (int i=0; i<MAXWIDTH; i++)
		{			
			linea.append(mapa->getCeldaStr(i,j));
		}
		std::cout << linea << std::endl;
		linea.clear();
	}
	int i;
	//std::cin >> i;
}