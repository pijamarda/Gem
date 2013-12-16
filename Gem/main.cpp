#include "gameScreen.hpp"

int main()
{
	load();
	//Al lanzar la aplicacion es el primer nivel que vamos a crear
	//inmediatamente lo asignamos al puntero mapaini y lo pasamos a las 2 pantallas
	Map *mapaini = new Map(0);
	//vamos a probar a generar aqui la clase jugador en este caso Willy
	Willy *willy = new Willy();
	
	consoleScreen *consola = new consoleScreen(mapaini,willy);
	consola->print_map();
	gameScreen *pantalla = new gameScreen(mapaini,consola,willy);
	int x = 1212;	
	std::cout << x << std::endl;
	int salida = std::scanf("%d", &x);
	
	
}