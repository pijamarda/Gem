/*
Esta clase representa cada una de las celdas de las que se compone el mapa
*/
#include <random>
#include "constantes.hpp"

class Celda
{
	public:		
		int material;
		Celda();
		Celda(int n);
		std::string getMaterial();		
};

//Este es el constructor estandar, que construye cualquier tipo de material salvo los ESPECIALES
Celda::Celda()
{
	int num = rand() % (MAXMATERIALES-ESPECIALESMAT) + ESPECIALESMAT;
	material = num;
}

//Sirve para construir un material AD-HOC
Celda::Celda(int n)
{
	//n=1 querra decir aire y n=0 muro	
	material = n;
}

std::string Celda::getMaterial()
{
	return getShort(material);
}