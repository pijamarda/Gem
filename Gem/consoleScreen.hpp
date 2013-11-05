#include "map.hpp"
#include <iostream>

class consoleScreen
{
public:
	//--VARIABLES--//
	Map *mapa;
	Willy *willy;

	//--METODOS---//
	void consoleScreen::print_map();
	void setMap(Map*);

	//--CONSTRUCT--//
	consoleScreen(Map*, Willy*);
};

consoleScreen::consoleScreen(Map *mapa, Willy *willy)
{
	this->mapa = mapa;
	this->willy = willy;
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
	//DEBUG
	//willy->printInvConsola();
}

void consoleScreen::setMap(Map *mapa)
{
	this->mapa=mapa;
}