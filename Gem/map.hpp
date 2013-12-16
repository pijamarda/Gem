/*
Este es el mapa, se construye como un VECTOR en 2D de punteros a objectos Celda
*/

#include "celda.hpp"
#include "willy.hpp"

#include <vector>


class Map
{
	private:
		//---VARIABLES---
		std::vector< std::vector<Celda*> > grid;

	public:
		//---VARIABLES---//
		
		
		//--CONSTRUCT--
		Map(int);

		//---METODOS----
		std::string getCeldaStr(int, int);
		int getCeldaID(int, int);
		sf::Vector2i getCeldaTexturePos(int, int);
		bool celdaVisible(int, int);
		void setAire(int, int);
		bool celdaPermitida(int,int);
		bool minar(int,int, Willy*);
};




