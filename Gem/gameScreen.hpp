#include "tilemap.hpp"

int gameWindow()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Tilemap");

	Map* mapa = new Map();

    // define the level with an array of tile indices
    int level[MAXHEIGHT*MAXWIDTH];
	int contador = 0;
	for (int j=0; j<MAXWIDTH; j++)
	{
		for (int i=0; i<MAXHEIGHT; i++)
		{
			level[contador]=mapa->getCeldaID(i,j);
			contador++;
			if (j > 5)
				std::cout<<std::endl;
		}
	}
	/*=
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 4, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 6, 3, 0, 2, 2, 0, 0, 1, 1, 1, 12, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 3, 0, 1, 1, 3, 3, 13, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 6, 0, 0, 1, 8, 11, 15,
    };*/

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("items.png", sf::Vector2u(32, 32), level, MAXHEIGHT, MAXWIDTH))
        return -1;

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

        // draw the map
        window.clear(sf::Color::White);
        window.draw(map);
        window.display();
    }

    return 0;
}