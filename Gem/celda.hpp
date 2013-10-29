/*
Esta clase representa cada una de las celdas de las que se compone el mapa
*/
#include <random>
#include "constantes.hpp"

class Celda
{
	public:		
		int material;
		bool visible;
		int posTx;
		int posTy;
		Celda();
		Celda(int n);
		std::string getMaterial();
		int getMaterialID();
		int getMaterialTPx();
		int getMaterialTPy();
		void setAire();
		
};

//Este es el constructor estandar, que construye cualquier tipo de material salvo los ESPECIALES
//en este caso en particular consideramos especiales los 2 primeros
Celda::Celda()
{
	int num = 0;
	//while ((num = rand() % (MAXMATERIALES-ESPECIALESMAT) + ESPECIALESMAT) == 6)
	num = rand() % (MAXMATERIALES-ESPECIALESMAT) + ESPECIALESMAT;
	//Ademas descartamos la salida ey el caracter especial negro
	//el material 6 es el negro
	//el material 15 es la salida
	while (num == 6 || num == 15)
		num = rand() % (MAXMATERIALES-ESPECIALESMAT) + ESPECIALESMAT;
	material = num;
	visible = true;
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

int Celda::getMaterialID()
{
	return material;
}

int Celda::getMaterialTPx()
{
	return postx(material);
}

int Celda::getMaterialTPy()
{
	return posty(material);
}

void Celda::setAire()
{
	this->material = 1;
}