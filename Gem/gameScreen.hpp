#include "consoleScreen.hpp"

class gameScreen
{
public:

	//-----VARIABLES-----

	//Del segundo nivel en adelante el mapa se guarda directamente en mapaActual, 
	//de manera que no mantenemos los anteriores aunque en un futuro podriamos mantenerlos
	Map* mapaActual;

	int level;

	//jugador
	Willy *willy;

	int gridSeleccion[MAXWIDTH][MAXHEIGHT];
	bool pulsado;
	bool aMinar;

	int ultX;
	int ultY;

	consoleScreen *consola;
	bool hayConsola;

	//Esta variable controla que cuando se pulsa una vez, la variable seleccionCursor solo cambia una vez
	//y mientras mantenga pulsado el raton este cambio es mantenido. 
	//una vez que se suelta, cuando se vuelva a pinchar seleccionCursor tomara el 
	//nuevo valor que se mantendra mientras se mantenga la pulsacion
	bool semaforoStop;
	//Controla que cuando se esta haciendo una "seleccion" de elementos a minar si se pasa por encima de elementos
	//ya seleccionados no los deseleccione mientras se mantenga la pulsacion
	bool seleccionCursor;

	//Controla la velocidad con la que se actualizan los distintos elementos
	float frameCounter, switchFrame, frameSpeed;
	sf::Clock reloj;

	//------METODOS------------

	int gameScreen::minarLoop();
	int gameScreen::resetMap();
	void gameScreen::init();

	//------CONSTRUCT----------

	gameScreen(Map*, Willy*);
	gameScreen(Map*,consoleScreen*, Willy*);
};





