#include<SFML/Graphics.hpp> 

Map* mapa0;
Map* mapaActual;
int gridSeleccion[MAXWIDTH][MAXHEIGHT];
bool pulsado=false;
bool aMinar = false;

int ruloX=0;
int ruloY=0;

float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
sf::Clock reloj;

int minar()
{
	for (int ruloX=0; ruloX < MAXWIDTH; ruloX++)
		for (int ruloY=0; ruloY < MAXHEIGHT; ruloY++)
			if (mapaActual->celdaVisible(ruloX,ruloY) && mapaActual->celdaPermitida(ruloX,ruloY) && gridSeleccion[ruloX][ruloY] == 1)
			{
				//sf::sleep(sf::milliseconds(1));
				if (mapaActual->getCeldaID(ruloX,ruloY)!=15)
					mapaActual->setAire(ruloX,ruloY);
				gridSeleccion[ruloX][ruloY]=0;				
				return 0;
			}
	return 0;
}

int resetMap()
{
	for (int i=0; i<MAXWIDTH; i++)
		for (int j=0; j<MAXHEIGHT; j++)
			gridSeleccion[i][j] = 0;
	aMinar = false;
	pulsado=false;
	return 0;
}

int gameWindow()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Tilemap");

	
	for (int i=0; i<MAXWIDTH; i++)
		for (int j=0; j<MAXHEIGHT; j++)
			gridSeleccion[i][j] = 0;

	mapa0 = new Map(0);
	mapaActual=mapa0;

	int level1[MAXWIDTH][MAXHEIGHT];

	int contador = 0;
	for (int j=0; j<MAXHEIGHT; j++)
	{
		for (int i=0; i<MAXWIDTH; i++)
		{			
			level1[i][j] = mapaActual->getCeldaID(i,j);
		}
	}
	sf::Texture texture; 
    sf::Sprite tiles; 

	if(!texture.loadFromFile("items.png"))
        std::cout << "could not locate the specified file" << std::endl; 
	else
        tiles.setTexture(texture);
 
	sf::RectangleShape cursor(sf::Vector2f(26, 26));
	cursor.setOutlineColor(sf::Color::Red);
	cursor.setOutlineThickness(3.0f);
	cursor.setPosition(3,3);	
	cursor.setFillColor(sf::Color::Transparent);

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();	

			if(event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					pulsado = true;
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
					pulsado = false;
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//aMinar = false;
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
							cursor.setPosition(i*32+3,j*32+3);
							if (pulsado)
							{	
								
								if (mapaActual->celdaPermitida(i,j) && mapaActual->getCeldaID(i,j) != 1 )
								{
									gridSeleccion[i][j] = 1;
								}
								else gridSeleccion[i][j] = 0;
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
			//std::cout << gridSeleccion[ruloX][ruloY] << std::endl;
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

