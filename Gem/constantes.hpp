/*
CONSTANTES: Este fichero es donde guardaremos las constantes globales del proyecto de manera que no tengamos
			que ir iendo de un lado a otro para buscarlas.
DATA:	Tambien trataremos de tener aqui los datos a leer, como por ejemplo todos los elementos de los que se compone el juego
		y sus datos.
*/

static const int MAXGLOBAL = 8;
static const int MAXMATERIALES = 6; //Se utiliza para la creacion del array con todos los elementos
static const int MAXHEIGHT = MAXGLOBAL;
static const int MAXWIDTH = MAXGLOBAL;

//Este porcentaje indica la cantidad de "cielo" inicial que habria por cada mapa
static const float PORHEIGHT = 0.8f; 

//Aqui indicamos el numero de bloques especiales, es util para cuando generemos aleatoriamiente los bloques en el mapa
//en principio estos bloques no se generaran
static const int ESPECIALESMAT = 2;
//Esta es la estructura de todos los elementos del juego, cuyo identificador principal es el ID
struct tMat
{
	int id;
	std::string corto;
	std::string largo;
};

tMat elementos[MAXMATERIALES];

void load()
{
	elementos[0].id=0;
	elementos[0].corto = "#";
	elementos[0].largo = "Muro";
	elementos[1].id=1;
	elementos[1].corto = "A";
	elementos[1].largo = "Aire";
	elementos[2].id=2;
	elementos[2].corto = "S";
	elementos[2].largo = "Sand";
	elementos[3].id=3;
	elementos[3].corto = "M";
	elementos[3].largo = "Mud";
	elementos[4].id=4;
	elementos[4].corto = "I";
	elementos[4].largo = "Iron";
	elementos[5].id=5;
	elementos[5].corto = "G";
	elementos[5].largo = "Gold";
}

//Devuelve la cadena de texto de un solo caracter en string, en principio esto lo utilizaremos como DEBUG en la consola
std::string getShort(int n)
{
	return elementos[n].corto;
}