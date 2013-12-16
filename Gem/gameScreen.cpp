#include "gameScreen.hpp"

//funcion principal, es llamada desde el proceso main, en un futuro sera llamada desde un menu
gameScreen::gameScreen(Map *mapa, Willy *willy)
{
	//creamos el primer nivel y lo asignamos directamente al gestor de mapas	
	this->mapaActual = mapa;
	hayConsola = false;
	level = 0;
	init();
}

//funcion para debug, asi podremos actualizar la salida por consola
gameScreen::gameScreen(Map *mapa, consoleScreen *consola, Willy *willy)
{
	//creamos el primer nivel y lo asignamos directamente al gestor de mapas	
	this->mapaActual = mapa;
	this->consola = consola;
	this->willy = willy;
	hayConsola = true;
	level = 0;
	init();
}

//Tenemos el bucle aqui fuera de manera que podamos controlar la velocidad del minado
//TODO: Comprobar en un futuro lejano si es el sitio correcto
int gameScreen::minarLoop()
{
	for (int i = 0; i<MAXWIDTH; i++)
	for (int j = 0; j<MAXHEIGHT; j++)
	if (gridSeleccion[i][j] == 1)
	if (mapaActual->minar(i, j, willy))
	{
		gridSeleccion[i][j] = 0;
		return 0;
	}
	return 0;
}

//Ponemos todas las variables "globales" a un estado inicial de manera que no se tranfieran entre el cambio de mapas
//e inicializamos lo que haga falta.
//Se queda aqui ya que no resetea nada del mapa especificamente
int gameScreen::resetMap()
{
	for (int i = 0; i<MAXWIDTH; i++)
	for (int j = 0; j<MAXHEIGHT; j++)
		gridSeleccion[i][j] = 0;
	aMinar = false;
	pulsado = false;
	return 0;
}


//Esta funcion es la controladora de pantalla global, la tenemos separa para poder utilizar distintos 
//constructores a discreccion
void gameScreen::init()
{
	pulsado = false;
	aMinar = false;

	ultX = 0;
	ultY = 0;

	bool semaforoStop = false;
	bool seleccionCursor = true;

	frameCounter = 0;
	switchFrame = 100;
	frameSpeed = 500;

	//funcion de creacion de la pantalla principal, las variables globales vienen siempre de constantes.hpp
	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Tilemap");

	//limpiamos el mapa e inicializamos las variables que hagan falta
	resetMap();



	sf::Texture texture;
	sf::Sprite tiles;

	if (!texture.loadFromFile("items.png"))
		std::cout << "No se encuentra el fichero de texturas" << std::endl;
	else
		tiles.setTexture(texture);

	//definicion del cursor de seleccion
	sf::RectangleShape cursor(sf::Vector2f(26, 26));
	cursor.setOutlineColor(sf::Color::Red);
	cursor.setOutlineThickness(3.0f);
	cursor.setPosition(3, 3);
	cursor.setFillColor(sf::Color::Transparent);

	//bucle principal, que se mantiene mientras tengamos la ventana abierta
	while (window.isOpen())
	{
		// Gestionamos los eventos tipo input de usuario
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					pulsado = true;
				}
				//Ahora mismo el boton derecho funciona como Toggle, es decir que se pulsa una vez para minar
				//y se pulsa otra vez para dejar de minar
				//TODO: Revisar el comportamiento para ver como realizar la accion de minar, si debe ser dependiente
				// de la pulsacion del boton derecho o no
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					if (aMinar)
						aMinar = false;
					else
						aMinar = true;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					pulsado = false;
					semaforoStop = false;
				}
			}

			if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed)
			{
				int coordX;
				int coordY;
				if (event.type == sf::Event::MouseMoved)
				{
					coordX = event.mouseMove.x;
					coordY = event.mouseMove.y;
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					coordX = event.mouseButton.x;
					coordY = event.mouseButton.y;
				}
				//std::cout << coordX << " " << coordY << std::endl;

				for (int j = 0; j<MAXHEIGHT; j++)
				{
					for (int i = 0; i<MAXWIDTH; i++)
					{

						if (coordX > i * 32 && coordX < (i + 1) * 32 && coordY > j * 32 && coordY < (j + 1) * 32)
						{
							//std::cout << "hay colision en " << "x: " << i <<" y: " << j << std::endl;
							//std::cout<< "i "<<i << " j " <<j << " ultX " << ultX << " ultY " << ultY<< std::endl;
							cursor.setPosition(i * 32 + 3, j * 32 + 3);
							if (pulsado)
							{

								if (mapaActual->celdaPermitida(i, j) && mapaActual->getCeldaID(i, j) != 1)
								{

									if (ultX != i || ultY != j)
									{
										ultX = i;
										ultY = j;
										if (!semaforoStop)
										{
											semaforoStop = true;
											if (gridSeleccion[i][j] == 1)
												seleccionCursor = false;
											else seleccionCursor = true;
										}
										if (gridSeleccion[i][j] == 0 && seleccionCursor)
										{

											gridSeleccion[i][j] = 1;
										}
										else if (gridSeleccion[i][j] == 1 && !seleccionCursor)
										{
											gridSeleccion[i][j] = 0;
										}
									}
									else
									{
										ultX = i;
										ultY = j;
										//gridSeleccion[i][j] = 0;
									}

								}

								//std::cout << "hay colision en " << "x: " << i <<" y: " << j << std::endl;
								if (mapaActual->celdaVisible(i, j) && mapaActual->celdaPermitida(i, j) && mapaActual->getCeldaID(i, j) == 15)
								{
									//mapaActual->setAire(i,j);
									resetMap();
									mapaActual = new Map(++level);
									consola->setMap(mapaActual);
								}
							}
						}
					}
				}
			}
		}

		//Voy a intentar crear mi propio renderer
		//recorro todo el mapa1
		//renderizador principal

		frameCounter += frameSpeed * reloj.restart().asSeconds();
		//std::cout <<  frameCounter << std::endl;
		if (aMinar && (frameCounter >= switchFrame))
		{
			//std::cout << gridSeleccion[i][j] << std::endl;
			minarLoop();
			frameCounter = 0;
			//si tenemos activada la consola para el modo debug, actualizamos por pantalla
			//la ponemos aqui para que no refresque todo el rato
			//TODO: Revisar y buscar otro sitio para poner la consola por pantalla
			//DEBUG
			//if (hayConsola) consola->print_map();
		}

		if (frameCounter >32000) { frameCounter = 0; }

		window.clear(sf::Color::White);
		for (int j = 0; j<MAXHEIGHT; j++)
		{
			for (int i = 0; i<MAXWIDTH; i++)
			{
				tiles.setPosition(i * 32, j * 32);
				tiles.setTextureRect(sf::IntRect(32 * (mapaActual->getCeldaTexturePos(i, j)).x, 32 * (mapaActual->getCeldaTexturePos(i, j)).y, 32, 32));
				if (mapaActual->celdaVisible(i, j))
					window.draw(tiles);
			}
		}
		window.draw(cursor);

		for (int j = 0; j<MAXHEIGHT; j++)
		{
			for (int i = 0; i<MAXWIDTH; i++)
			{
				if (gridSeleccion[i][j] == 1)
				{
					sf::RectangleShape seleccion(sf::Vector2f(26, 26));
					seleccion.setOutlineColor(sf::Color::Blue);
					seleccion.setOutlineThickness(3.0f);
					seleccion.setPosition(i * 32 + 3, j * 32 + 3);
					seleccion.setFillColor(sf::Color::Transparent);
					window.draw(seleccion);
				}
			}
		}

		window.display();
	}
}