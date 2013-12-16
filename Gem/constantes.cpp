#include "constantes.hpp"

tMat elementos[MAXMATERIALES];

void load()
{
	//generamos la dureza automaticamente
	//TODO: Revisar
	for (int i = 0; i<MAXMATERIALES; i++)
	{
		elementos[i].dureza = (i - 1) * 2;
		elementos[i].coins = 9778 * i;
	}
	elementos[0].id = 0;
	elementos[0].corto = "#";
	elementos[0].largo = "Muro";
	elementos[0].posT[0] = 0;
	elementos[0].posT[1] = 0;
	elementos[1].id = 1;
	elementos[1].corto = "A";
	elementos[1].largo = "Air";
	elementos[1].posT[0] = 1;
	elementos[1].posT[1] = 0;
	elementos[2].id = 2;
	elementos[2].corto = "S";
	elementos[2].largo = "Sand";
	elementos[2].posT[0] = 2;
	elementos[2].posT[1] = 0;

	elementos[3].id = 3;
	elementos[3].corto = "M";
	elementos[3].largo = "Mud";
	elementos[3].posT[0] = 3;
	elementos[3].posT[1] = 0;

	//---------------------------//
	elementos[4].id = 4;
	elementos[4].corto = "C";
	elementos[4].largo = "Copper";
	elementos[4].posT[0] = 0;
	elementos[4].posT[1] = 1;
	elementos[5].id = 5;
	elementos[5].corto = "P";
	elementos[5].largo = "Plata";
	elementos[5].posT[0] = 1;
	elementos[5].posT[1] = 1;
	elementos[6].id = 6;
	elementos[6].corto = "G";
	elementos[6].largo = "Gold";
	elementos[6].posT[0] = 2;
	elementos[6].posT[1] = 1;
	elementos[7].id = 7;
	elementos[7].corto = "I";
	elementos[7].largo = "Iron";
	elementos[7].posT[0] = 3;
	elementos[7].posT[1] = 1;
	//---------------------------//
	elementos[8].id = 8;
	elementos[8].corto = "R";
	elementos[8].largo = "Ruby";
	elementos[8].posT[0] = 0;
	elementos[8].posT[1] = 2;
	elementos[9].id = 9;
	elementos[9].corto = "Z";
	elementos[9].largo = "Zaphire";
	elementos[9].posT[0] = 1;
	elementos[9].posT[1] = 2;
	elementos[10].id = 10;
	elementos[10].corto = "E";
	elementos[10].posT[0] = 2;
	elementos[10].posT[1] = 2;
	elementos[10].largo = "Emerald";
	elementos[11].id = 11;
	elementos[11].corto = "D";
	elementos[11].largo = "Diamond";
	elementos[11].posT[0] = 3;
	elementos[11].posT[1] = 2;
	//---------------------------//
	elementos[12].id = 12;
	elementos[12].corto = "X";
	elementos[12].largo = "Especial1";
	elementos[12].posT[0] = 0;
	elementos[12].posT[1] = 3;
	elementos[13].id = 13;
	elementos[13].corto = "Y";
	elementos[13].largo = "Especial2";
	elementos[13].posT[0] = 1;
	elementos[13].posT[1] = 3;
	elementos[14].id = 14;
	elementos[14].corto = "P";
	elementos[14].largo = "Potion";
	elementos[14].posT[0] = 2;
	elementos[14].posT[1] = 3;
	elementos[15].id = 15;
	elementos[15].corto = "E";
	elementos[15].largo = "Exit";
	elementos[15].posT[0] = 3;
	elementos[15].posT[1] = 3;
}

//Devuelve la cadena de texto de un solo caracter en string, en principio esto lo utilizaremos como DEBUG en la consola
std::string getShort(int n)
{
	return elementos[n].corto;
}

//Devuelve la posicion x dentro del fichero de texturas
int postx(int n)
{
	int temp = elementos[n].posT[0];
	return temp;
}

//Devuelve la posicion y dentro del fichero de texturas
int posty(int n)
{
	return elementos[n].posT[1];
}