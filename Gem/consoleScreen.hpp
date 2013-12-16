#include "map.hpp"


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