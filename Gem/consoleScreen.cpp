#include "consoleScreen.hpp"

consoleScreen::consoleScreen(Map *mapa, Willy *willy)
{
	this->mapa = mapa;
	this->willy = willy;
}

void consoleScreen::print_map()
{

	std::string linea;

	for (int j = 0; j<MAXHEIGHT; j++)
	{
		for (int i = 0; i<MAXWIDTH; i++)
		{
			linea.append(mapa->getCeldaStr(i, j));
		}
		std::cout << linea << std::endl;
		linea.clear();
	}
	//DEBUG
	//willy->printInvConsola();
}

void consoleScreen::setMap(Map *mapa)
{
	this->mapa = mapa;
}