#include "consoleScreen.hpp"
#include "gameScreen.hpp"

int main()
{
	//Al lanzar la aplicacion es el primer nivel que vamos a crear
	//inmediatamente lo asignamos al puntero mapaini y lo pasamos a las 2 pantallas
	Map *mapaini = new Map(0);
	load();
	consoleScreen *consola = new consoleScreen(mapaini);
	gameScreen *pantalla = new gameScreen(mapaini,consola);
	int x;
	//std::cin >> x;
	
}