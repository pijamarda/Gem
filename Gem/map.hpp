/*
Este es el mapa, se construye como un VECTOR en 2D de punteros a objectos Celda
*/
#include "celda.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp> 

class Map
{
	private:		
		std::vector< std::vector<Celda*> > grid;
	public:
		//Map();		
		Map(int nivel);				
		std::string getCeldaStr(int posX, int posY);
		int getCeldaID(int posX, int posY);
		sf::Vector2i getCeldaTexturePos(int posX, int posY);
		bool celdaVisible(int x, int y);
		void setAire(int x, int y);
		bool celdaPermitida(int x,int y);
};


Map::Map(int level)
{
	srand(time(NULL));
	bool finalColocado = false;
	//Primero hacemos que el vector tenga un tamaño MAXWIDTH De ancho
	grid.resize(MAXWIDTH);
	for (int i=0; i< MAXWIDTH; i++)
		//por cada uno de los valores de X creamos un vector de tamaño MAXHEIGHT de alto
		grid[i].resize(MAXHEIGHT);

	//Decidimos aleatoriamente donde estara la salida
	//buscamos entre el 1-31
	int salidaX = rand() % (MAXWIDTH-3) + 1;
	//buscamos entre el 11-15
	int salidaY = rand() % (4) + MAXHEIGHT-5;
	std::cout << salidaX << " " << salidaY << std::endl;

	for (int j=0; j<MAXHEIGHT; j++)
	{
		for (int i=0; i<MAXWIDTH; i++)
		{
			//en x calculamos el porcentaje que queremos con materiales
			int x = (int)(MAXHEIGHT * PORHEIGHT);

			//esto marca el borde del mapa, a la izquierda, a la derecho y abajo hay rocas, para esto
			//utilizamos el constructor AD-HOC pasandole el material MURO, ID=0
			if (level==0)
			{
				if (i == 0 || i == MAXWIDTH-1 || j == MAXHEIGHT-1)
					grid[i][j] = new Celda(0);
				//Llenamos de aire (ID=1) un 20% de la parte superior del mapa
				else if (j < MAXHEIGHT - x)
					grid[i][j] = new Celda(1);
				else if (j == MAXHEIGHT - x)
					grid[i][j] = new Celda(2);
				else if (i==salidaX && j==salidaY && !finalColocado)
				{
					grid[i][j] = new Celda(15);
					finalColocado = true;
				}
				else
					grid[i][j] = new Celda();
			}
			else
			{
				//Si no estamos en el primer nivel la parte superior esta llena de rocas
				if (i == 0 || i == MAXWIDTH-1 || j == MAXHEIGHT-1 || j == 0)
					grid[i][j] = new Celda(0);
				else if (j == 1)
					grid[i][j] = new Celda(1);
				//forzamos que la siguiente linea al aire sea siempre arena
				else if (j == 2)
					grid[i][j] = new Celda(2);
				else if (i==salidaX && j==salidaY && !finalColocado)
				{
					grid[i][j] = new Celda(15);
					finalColocado = true;
				}
				else
					grid[i][j] = new Celda();
			}
			//vamos a intentar colocar la salida de nivel
			//OJO porque no nos aseguramos de que se ha colocado el final, pero bueno
			
			//el resto de celdas se compone de el resto de materiales, sin contar los especiales
		
		}
	}
}

/*Map::Map(int nivel)
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

			//esto marca el borde del mapa, a la izquierda, a la derecho arriba y abajo hay rocas, para esto
			//utilizamos el constructor AD-HOC pasandole el material MURO, ID=0
			if (i == 0 || i == MAXWIDTH-1 || j == 0 || j == MAXHEIGHT-1)
				grid[i][j] = new Celda(0);
			//Llenamos de aire (ID=1) un 20% de la parte superior del mapa
			else if (j < 2)
				grid[i][j] = new Celda(1);
			//forzamos que la siguiente linea al aire sea siempre arena
			else if (j == 2)
				grid[i][j] = new Celda(2);
			//el resto de celdas se compone de el resto de materiales, sin contar los especiales
			else
				grid[i][j] = new Celda();
		}
	}
}*/

//funcion que devuelve el tipo de celda por posicion, devuelve una cadena de texto simple
//se utiliza principalmente como DEBUG para la version de consola
std::string Map::getCeldaStr(int posX, int posY)
{	
	return grid[posX][posY]->getMaterial();	
}

int Map::getCeldaID(int posX, int posY)
{
	if (posY == 16)
		std::cout << std::endl;
	return grid[posX][posY]->getMaterialID();
}

sf::Vector2i Map::getCeldaTexturePos(int posX, int posY)
{
	sf::Vector2i temp;
	temp.x = grid[posX][posY]->getMaterialTPx();
	temp.y = grid[posX][posY]->getMaterialTPy();
	return temp;
}

bool Map::celdaVisible(int x, int y)
{
	bool esVisible = false;

	if (x==0 || x == MAXWIDTH-1)
		esVisible = true;
	else if (y==MAXHEIGHT -1 || y==0)
		esVisible = true;
	else
	{
		if ((y-1 > 0) )
			if (grid[x][y-1]->getMaterialID() == 1)
				esVisible = true;
		if (x+1 < MAXWIDTH-1)
			if (grid[x+1][y]->getMaterialID() == 1)
				esVisible = true;
		if (y+1 < MAXHEIGHT-1)
			if (grid[x][y+1]->getMaterialID() == 1)
				esVisible = true;
		if (x-1 > 0)
			if (grid[x-1][y]->getMaterialID() == 1)
				esVisible = true;
		if (x>18 && y>14)
			std::cout << std::endl;
	}
	return esVisible;
	
}

void Map::setAire(int x, int y)
{
	grid[x][y]->setAire();
}

bool Map::celdaPermitida(int x,int y)
{
	bool permitida = false;
	if (x>0 && x<MAXWIDTH-1 && y > 0 &&y<MAXHEIGHT-1)
	{
		permitida = true;
	}
	return permitida;
}

