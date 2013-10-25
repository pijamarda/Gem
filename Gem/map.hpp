/*
Este es el mapa, se construye como un VECTOR en 2D de punteros a objectos Celda
*/
#include "celda.hpp"
#include <string>
#include <vector>

class Map
{
	private:		
		std::vector< std::vector<Celda*> > grid;
	public:
		Map();				
		std::string getCeldaStr(int posX, int posY);
		int getCeldaID(int posX, int posY);
};


Map::Map()
{
	//Primero hacemos que el vector tenga un tamaño MAXWIDTH De ancho
	grid.resize(MAXWIDTH);
	for (int i=0; i< MAXWIDTH; i++)
		//por cada uno de los valores de X creamos un vector de tamaño MAXHEIGHT de alto
		grid[i].resize(MAXHEIGHT);

	for (int j=0; j<MAXHEIGHT; j++)
	{
		for (int i=0; i<MAXWIDTH; i++)
		{
			//en x calculamos el porcentaje que queremos con materiales
			int x = (int)(MAXHEIGHT * PORHEIGHT);

			//esto marca el borde del mapa, a la izquierda, a la derecho y abajo hay rocas, para esto
			//utilizamos el constructor AD-HOC pasandole el material MURO, ID=0
			if (i == 0 || i == MAXWIDTH-1 || j == MAXHEIGHT-1)
				grid[i][j] = new Celda(0);
			//Llenamos de aire (ID=1) un 20% de la parte superior del mapa
			else if (j < MAXHEIGHT - x)
				grid[i][j] = new Celda(1);
			//el resto de celdas se compone de el resto de materiales, sin contar los especiales
			else
				grid[i][j] = new Celda();
		}
	}	
}

//funcion que devuelve el tipo de celda por posicion, devuelve una cadena de texto simple
//se utiliza principalmente como DEBUG para la version de consola
std::string Map::getCeldaStr(int posX, int posY)
{	
	return grid[posX][posY]->getMaterial();	
}

int Map::getCeldaID(int posX, int posY)
{
	return grid[posX][posY]->getMaterialID();
}