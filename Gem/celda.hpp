/*
Esta clase representa cada una de las celdas de las que se compone el mapa
*/
#include <random>
#include "constantes.hpp"

class Celda
{
	public:		
		//----VARIABLES----//
		int material;
		bool visible;
		int posTx;
		int posTy;
		int durabilidad;
		int coins;

		//----CONSTRUCT----//
		Celda();
		Celda(int n);
		Celda(bool b,int nivel);

		//---METODOS-----/
		std::string getMaterial();
		int getMaterialID();
		int getMaterialTPx();
		int getMaterialTPy();
		void setAire();
		int getDurabilidad();
		void celdaMinar(int,int);
		int getCoins();
		
};

