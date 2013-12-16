#include "map.hpp"

Map::Map(int level)
{
	srand(time(NULL));
	bool finalColocado = false;
	//Primero hacemos que el vector tenga un tamaño MAXWIDTH De ancho
	grid.resize(MAXWIDTH);
	for (int i = 0; i< MAXWIDTH; i++)
		//por cada uno de los valores de X creamos un vector de tamaño MAXHEIGHT de alto
		grid[i].resize(MAXHEIGHT);

	//Decidimos aleatoriamente donde estara la salida
	//buscamos entre el 1-31
	int salidaX = rand() % (MAXWIDTH - 3) + 1;
	//buscamos entre el 11-15
	int salidaY = rand() % (4) + MAXHEIGHT - 5;
	std::cout << salidaX << " " << salidaY << std::endl;

	for (int j = 0; j<MAXHEIGHT; j++)
	{
		for (int i = 0; i<MAXWIDTH; i++)
		{
			//en x calculamos el porcentaje que queremos con materiales
			int x = (int)(MAXHEIGHT * PORHEIGHT);

			if (level == 0)
			{
				//esto marca el borde del mapa, a la izquierda, a la derecho y abajo hay rocas, para esto
				//utilizamos el constructor AD-HOC pasandole el material MURO, ID=0
				if (i == 0 || i == MAXWIDTH - 1 || j == MAXHEIGHT - 1)
					grid[i][j] = new Celda(0);
				//Llenamos de aire (ID=1) un 20% de la parte superior del mapa
				else if (j < MAXHEIGHT - x)
					grid[i][j] = new Celda(1);
				//hacemos que justamente la siguiente capa al aire sea arena
				else if (j == MAXHEIGHT - x)
					grid[i][j] = new Celda(2);
				//Ahora colocamos la salida, la colocacion la hemos decidido mas arriba
				else if (i == salidaX && j == salidaY && !finalColocado)
				{
					grid[i][j] = new Celda(15);
					finalColocado = true;
				}
				//por último rellenamos el resto de celdas
				//TODO: Aqui deberiamos indicar de alguna forma que casi todos los elementos que colocamos
				//deben ser arena
				else
					grid[i][j] = new Celda(true, level);
			}
			else
			{
				//Si no estamos en el primer nivel la parte superior esta llena de rocas
				if (i == 0 || i == MAXWIDTH - 1 || j == MAXHEIGHT - 1 || j == 0)
					grid[i][j] = new Celda(0);
				else if (j == 1)
					grid[i][j] = new Celda(1);
				//forzamos que la siguiente linea al aire sea siempre arena
				else if (j == 2)
					grid[i][j] = new Celda(2);
				else if (i == salidaX && j == salidaY && !finalColocado)
				{
					grid[i][j] = new Celda(15);
					finalColocado = true;
				}
				else
					grid[i][j] = new Celda(true, level);
			}
		}
	}
}

//funcion que devuelve el tipo de celda por posicion, devuelve una cadena de texto simple
//se utiliza principalmente como DEBUG para la version de consola
std::string Map::getCeldaStr(int posX, int posY)
{
	return grid[posX][posY]->getMaterial();
}

//Devuelve el identificador de celda
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

	if (x == 0 || x == MAXWIDTH - 1)
		esVisible = true;
	else if (y == MAXHEIGHT - 1 || y == 0)
		esVisible = true;
	else
	{
		if ((y - 1 > 0))
		if (grid[x][y - 1]->getMaterialID() == 1)
			esVisible = true;
		if (x + 1 < MAXWIDTH - 1)
		if (grid[x + 1][y]->getMaterialID() == 1)
			esVisible = true;
		if (y + 1 < MAXHEIGHT - 1)
		if (grid[x][y + 1]->getMaterialID() == 1)
			esVisible = true;
		if (x - 1 > 0)
		if (grid[x - 1][y]->getMaterialID() == 1)
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

//por ahora solo comprobamos los bordes del mapa a nivel posicion y no a nivel material
//TODO: añadir en este metodo cuales son los materiales que no son permitidos
bool Map::celdaPermitida(int x, int y)
{
	bool permitida = false;
	if (x>0 && x<MAXWIDTH - 1 && y > 0 && y<MAXHEIGHT - 1)
	{
		permitida = true;
	}
	return permitida;
}

//realiza la accion de minar, es un bucle que pasa por todas las celdas del juego, e intenta minarlas todas,
//la manera principal con la que se controla es con "gridSeleccion" que mantiene cuales son las celdas seleccionadas
//para ser minadas
bool Map::minar(int x, int y, Willy *willy)
{

	//si la celda esta pegada a una celda aire, y es una celda que puede ser minada (ahora mismo solo comprueba
	//que no es uno de los bordos, como vemos dentro de la funcion se hace el check de tipo de celda MAL)
	if (this->celdaVisible(x, y) && this->celdaPermitida(x, y))
	{
		//TODO: Hay que cambiar la comprobacion del tipo de celda y sacarla de aqui. Aunque la ventaja de tenerlo
		//aqui es que permitimos quitar la seleccion automaticamente de las celdas en las que no permitimos minar
		//TODO: sacar la comprobacion de celdaPermitida del IF exterior y crear un nuevo IF interior, para que
		//si no dejamos minar quitemos la seleccion
		//No dejamos minar la celda 15 que es la de salida

		if (this->getCeldaID(x, y) != 15)
		{
			if (grid[x][y]->getDurabilidad() > 0)
				grid[x][y]->celdaMinar(x, y);
			if (grid[x][y]->getDurabilidad() == 0)
			{
				int monedas = grid[x][y]->getCoins();
				//DEBUG
				std::cout << "Willy gana: " << monedas << std::endl;
				willy->addCoins(monedas);
				//DEBUG
				willy->printInvConsola();
				this->setAire(x, y);
				return true;
			}
			//una vez que hemos minado quitamos la seleccion 
			//gridSeleccion[i][j]=0;
		}
	}
	return false;
}