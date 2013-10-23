#include "map.hpp"
#include <iostream>

void print_map()
{
	Map* mapa = new Map();
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