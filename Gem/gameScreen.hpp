
int gameWindow()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Tilemap");

	Map* mapa1 = new Map();
	Map* mapaActual=mapa1;

	int level1[MAXWIDTH][MAXHEIGHT];

	int contador = 0;
	for (int j=0; j<MAXHEIGHT; j++)
	{
		for (int i=0; i<MAXWIDTH; i++)
		{
			
			level1[i][j] = mapaActual->getCeldaID(i,j);
			if (j > 14)
				std::cout<<std::endl;
		}
	}
	sf::Texture texture; 
    sf::Sprite tiles; 

	if(!texture.loadFromFile("items.png"))
        std::cout << "could not locate the specified file" << std::endl; 
	else
        tiles.setTexture(texture);
 
    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();	
        }
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
            int coordX = event.mouseButton.x;
			int coordY = event.mouseButton.y;
			//std::cout << coordX << std::endl;
			for (int j=0; j<MAXHEIGHT; j++)
			{
				for (int i=0; i<MAXWIDTH; i++)
				{	
					if ( coordX > i*32 && coordX < (i+1)*32 && coordY > j*32 && coordY < (j+1)*32 )
					{
						//std::cout << "hay colision en " << "x: " << i <<" y: " << j << std::endl;
						if (mapaActual->celdaVisible(i,j) && mapaActual->celdaPermitida(i,j))
							mapaActual->setAire(i,j);
						if (coordX > WINDOWWIDTH - 20)
							mapaActual = new Map(0);
					}
				}			
			}
		}
        // draw the map
        window.clear(sf::Color::White);
		//Voy a intentar crear mi propio renderer

		//recorro todo el mapa1
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

        window.display();
    }

    return 0;
}