#include<SFML/Graphics.hpp> 

//Al lanzar la aplicacion es el primer nivel que vamos a crear
//inmediatamente lo asignamos a mapaActual
Map* mapa0;
//Del segundo nivel en adelante el mapa se guarda directamente en mapaActual, de manera que no mantenemos los anteriores
//aunque en un futuro podriamos mantenerlos
Map* mapaActual;
int gridSeleccion[MAXWIDTH][MAXHEIGHT];
bool pulsado=false;
bool aMinar = false;

int ultX=0;
int ultY=0;

//Esta variable controla que cuando se pulsa una vez, la variable seleccionCursor solo cambia una vez
//y mientras mantenga pulsado el raton este cambio es mantenido. 
//una vez que se suelta, cuando se vuelva a pinchar seleccionCursor tomara el 
//nuevo valor que se mantendra mientras se mantenga la pulsacion
bool semaforoStop = false;
//Controla que cuando se esta haciendo una "seleccion" de elementos a minar si se pasa por encima de elementos
//ya seleccionados no los deseleccione mientras se mantenga la pulsacion
bool seleccionCursor = true;

//Controla la velocidad con la que se actualizan los distintos elementos
float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
sf::Clock reloj;

//realiza la accion de minar, es un bucle que pasa por todas las celdas del juego, e intenta minarlas todas,
//la manera principal con la que se controla es con "gridSeleccion" que mantiene cuales son las celdas seleccionadas
//para ser minadas
int minar()
{
	for (int i=0; i < MAXWIDTH; i++)
		for (int j=0; j < MAXHEIGHT; j++)
			//si la celda esta pegada a una celda aire, y es una celda que puede ser minada (ahora mismo solo comprueba
			//que no es uno de los bordos, como vemos dentro de la funcion se hace el check de tipo de celda MAL)
			if (mapaActual->celdaVisible(i,j) && mapaActual->celdaPermitida(i,j) && gridSeleccion[i][j] == 1)
			{	
				//TODO: Hay que cambiar la comprobacion del tipo de celda y sacarla de aqui. Aunque la ventaja de tenerlo
				//aqui es que permitimos quitar la seleccion automaticamente de las celdas en las que no permitimos minar
				//TODO: sacar la comprobacion de celdaPermitida del IF exterior y crear un nuevo IF interior, para que
				//si no dejamos minar quitemos la seleccion
				//No dejamos minar la celda 15 que es la de salida

				if (mapaActual->getCeldaID(i,j)!=15)
					mapaActual->setAire(i,j);
				//una vez que hemos minado quitamos la seleccion 
				gridSeleccion[i][j]=0;				
				return 0;
			}
	return 0;
}

//Ponemos todas las variables "globales" a un estado inicial de manera que no se tranfieran entre el cambio de mapas
//e inicializamos lo que haga falta
int resetMap()
{
	for (int i=0; i<MAXWIDTH; i++)
		for (int j=0; j<MAXHEIGHT; j++)
			gridSeleccion[i][j] = 0;
	aMinar = false;
	pulsado=false;
	return 0;
}

//funcion principal, es llamada desde el proceso main, en un futuro sera llamada desde un menu
int gameWindow()
{
    //funcion de creacion de la pantalla principal, las variables globales vienen siempre de constantes.hpp
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Tilemap");

	//limpiamos el mapa e inicializamos las variables que hagan falta
	resetMap();

	//creamos el primer nivel y lo asignamos directamente al gestor de mapas
	mapa0 = new Map(0);
	mapaActual=mapa0;

	sf::Texture texture; 
    sf::Sprite tiles; 

	if(!texture.loadFromFile("items.png"))
        std::cout << "No se encuentra el fichero de texturas" << std::endl; 
	else
        tiles.setTexture(texture);
 
	//definicion del cursor de seleccion
	sf::RectangleShape cursor(sf::Vector2f(26, 26));
	cursor.setOutlineColor(sf::Color::Red);
	cursor.setOutlineThickness(3.0f);
	cursor.setPosition(3,3);	
	cursor.setFillColor(sf::Color::Transparent);

    //bucle principal, que se mantiene mientras tengamos la ventana abierta
    while (window.isOpen())
    {
        // Gestionamos los eventos tipo input de usuario
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();	
			
			if(event.type == sf::Event::MouseButtonPressed)
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
			if(event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					pulsado = false;
					semaforoStop = false;
				}				
			}

			if(event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed)
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
				
				for (int j=0; j<MAXHEIGHT; j++)
				{
					for (int i=0; i<MAXWIDTH; i++)
					{	
						
						if ( coordX > i*32 && coordX < (i+1)*32 && coordY > j*32 && coordY < (j+1)*32 )
						{
							//std::cout << "hay colision en " << "x: " << i <<" y: " << j << std::endl;
							std::cout<< "i "<<i << " j " <<j << " ultX " << ultX << " ultY " << ultY<< std::endl;
							cursor.setPosition(i*32+3,j*32+3);
							if (pulsado)
							{	
								
								if (mapaActual->celdaPermitida(i,j) && mapaActual->getCeldaID(i,j) != 1 )
								{	
									
									if (ultX != i || ultY !=j)
									{
										ultX=i;
										ultY=j;
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
										ultX=i;
										ultY=j;
										//gridSeleccion[i][j] = 0;
									}
									
								}
								
								//std::cout << "hay colision en " << "x: " << i <<" y: " << j << std::endl;
								if (mapaActual->celdaVisible(i,j) && mapaActual->celdaPermitida(i,j) && mapaActual->getCeldaID(i,j) == 15)
								{
									//mapaActual->setAire(i,j);
									resetMap();	
									mapaActual = new Map(1);																										
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
			minar();	
			frameCounter = 0;
		}

		if (frameCounter >32000) {frameCounter = 0;}

		window.clear(sf::Color::White);
		for (int j=0; j<MAXHEIGHT; j++)
		{
			for (int i=0; i<MAXWIDTH; i++)
			{				
				tiles.setPosition(i*32,j*32);
				tiles.setTextureRect(sf::IntRect(32*(mapaActual->getCeldaTexturePos(i,j)).x,32*(mapaActual->getCeldaTexturePos(i,j)).y, 32, 32));
				if (mapaActual->celdaVisible(i,j))
					window.draw(tiles);
			}			
		}
		window.draw(cursor);
		
		for (int j=0; j<MAXHEIGHT; j++)
		{
			for (int i=0; i<MAXWIDTH; i++)
			{		
				if (gridSeleccion[i][j] == 1)
				{
					sf::RectangleShape seleccion(sf::Vector2f(26, 26));
					seleccion.setOutlineColor(sf::Color::Blue);
					seleccion.setOutlineThickness(3.0f);
					seleccion.setPosition(i*32+3,j*32+3);	
					seleccion.setFillColor(sf::Color::Transparent);
					window.draw(seleccion);					
				}
			}			
		}
		
        window.display();
    }
    return 0;

	
}

