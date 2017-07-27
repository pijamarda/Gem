/*
CONSTANTES: Este fichero es donde guardaremos las constantes globales del proyecto de manera que no tengamos
			que ir iendo de un lado a otro para buscarlas.
DATA:	Tambien trataremos de tener aqui los datos a leer, como por ejemplo todos los elementos de los que se compone el juego
		y sus datos.
*/
#include <string>

//Esta es la estructura de todos los elementos del juego, cuyo identificador principal es el ID
struct tMat
{
	int id;
	std::string corto;
	std::string largo;
	int posT[2];
	int dureza;
	int coins;
};

static const int MAXGLOBAL = 16;
static const int TAMPIXEL = 32;
static const int MAXMATERIALES = 16; //Se utiliza para la creacion del array con todos los elementos
static const int MAXHEIGHT = 16;
static const int MAXWIDTH = 32;
static const int WINDOWWIDTH = MAXWIDTH * TAMPIXEL;
static const int WINDOWHEIGHT = MAXHEIGHT * TAMPIXEL;

//Este porcentaje indica la cantidad de "cielo" inicial que habria por cada mapa
static const float PORHEIGHT = 0.8f;

//Aqui indicamos el numero de bloques especiales, es util para cuando generemos aleatoriamiente los bloques en el mapa
//en principio estos bloques no se generaran
static const int ESPECIALESMAT = 2;

void load();
//Devuelve la cadena de texto de un solo caracter en string, en principio esto lo utilizaremos como DEBUG en la consola
std::string getShort(int n);

//Devuelve la posicion x dentro del fichero de texturas
int postx(int n);

//Devuelve la posicion y dentro del fichero de texturas
int posty(int n);

tMat elementos[MAXMATERIALES];
