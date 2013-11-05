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
	durabilidad = elementos[n].dureza;
	coins = elementos[n].coins;
}

//Una primera aproximacion que se me ha ocurrido para la construccion de niveles con materiales segun
//vamos bajando seria que cuando pasamos al constructor 2 parametros, el segundo le indica en que nivel estamos
Celda::Celda(bool b,int nivel)
{	
	//Ahora deberemos generar un nivel, con elementos que nunca superen el nivel básico que marca el nivel
	//TODO: muy burdo puesto que en el nivel 0 solo habra arena, en el segundo arena y piedras etc.
	//pero es una primera aproximacion
	int num = 0;
	//TODO: No es muy elegante pero de esta manera no se general los materiales especiales, que en principio
	//estarian en las primeras posiciones del tileset y de la estructura elementos
	//se puede ver que no funciona bien ya que mas abajo tambien hay que descartar los elementos 6 y 15
	num = rand() % (MAXMATERIALES-ESPECIALESMAT) + ESPECIALESMAT;
	//Ademas descartamos la salida ey el caracter especial negro
	//el material 6 es el negro
	//el material 15 es la salida
	while (num == 6 || num == 15 || num > nivel + 2)
		num = rand() % (MAXMATERIALES-ESPECIALESMAT) + ESPECIALESMAT;
	material = num;
	durabilidad = elementos[num].dureza;
	coins = elementos[num].coins;
	visible = true;
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

int Celda::getDurabilidad()
{
	return this->durabilidad;
}

void Celda::celdaMinar(int x,int y)
{
	if (durabilidad > 0)
		durabilidad--;
}

int Celda::getCoins()
{
	return coins;
}