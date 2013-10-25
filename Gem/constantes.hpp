/*
CONSTANTES: Este fichero es donde guardaremos las constantes globales del proyecto de manera que no tengamos
			que ir iendo de un lado a otro para buscarlas.
DATA:	Tambien trataremos de tener aqui los datos a leer, como por ejemplo todos los elementos de los que se compone el juego
		y sus datos.
*/

static const int MAXGLOBAL = 32;
static const int TAMPIXEL = 32;
static const int MAXMATERIALES = 16; //Se utiliza para la creacion del array con todos los elementos
static const int MAXHEIGHT = MAXGLOBAL;
static const int MAXWIDTH = MAXGLOBAL;
static const int WINDOWWIDTH = MAXHEIGHT * TAMPIXEL;
static const int WINDOWHEIGHT = MAXWIDTH * TAMPIXEL;

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
	elementos[1].largo = "Air";
	elementos[2].id=2;
	elementos[2].corto = "S";
	elementos[2].largo = "Sand";
	elementos[3].id=3;
	elementos[3].corto = "M";
	elementos[3].largo = "Mud";
	//---------------------------//
	elementos[4].id=4;
	elementos[4].corto = "I";
	elementos[4].largo = "Iron";
	elementos[5].id=5;
	elementos[5].corto = "G";
	elementos[5].largo = "Gold";
	elementos[6].id=6;
	elementos[6].corto = "I";
	elementos[6].largo = "Iron";
	elementos[7].id=7;
	elementos[7].corto = "G";
	elementos[7].largo = "Gold";
	//---------------------------//
	elementos[8].id=8;
	elementos[8].corto = "R";
	elementos[8].largo = "Ruby";
	elementos[9].id=9;
	elementos[9].corto = "M";
	elementos[9].largo = "Amethist";
	elementos[10].id=10;
	elementos[10].corto = "G";
	elementos[10].largo = "Gold";
	elementos[11].id=11;
	elementos[11].corto = "E";
	elementos[11].largo = "Emerald";
	//---------------------------//
	elementos[12].id=12;
	elementos[12].corto = "S";
	elementos[12].largo = "Sand";
	elementos[13].id=13;
	elementos[13].corto = "M";
	elementos[13].largo = "Mud";
	elementos[14].id=14;
	elementos[14].corto = "P";
	elementos[14].largo = "Potion";
	elementos[15].id=15;
	elementos[15].corto = "E";
	elementos[15].largo = "Exit";
}

//Devuelve la cadena de texto de un solo caracter en string, en principio esto lo utilizaremos como DEBUG en la consola
std::string getShort(int n)
{
	return elementos[n].corto;
}