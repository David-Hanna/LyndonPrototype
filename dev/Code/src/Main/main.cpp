#include <limits>
#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

#include <HEMath.h>
#include "../Utilities/SHDrawable.h"



void fps(sf::RenderWindow& rw)
{
	static time_t start = time(0);
	static time_t current;
	static int fpsCount = 0;

	current = time(0);
		if (current - start >= 1)
		{
			start = current;
			std::string str("SFML WORKS!  FPS: " + std::to_string(fpsCount));
			rw.setTitle(str);
			fpsCount = 0;
		}
		else
		{
			fpsCount++;
		}
};

int main(int argc, void** argv)
{
	// open a window with the title SFML WORKS!
	sf::RenderWindow window( sf::VideoMode ( 600, 600 ), "SFML WORKS!  FPS: ----" );
	
	SHDrawable fpo, ally1("AllyShip",200,200), enemy1("EnemyShip",200,450), player("PlayerShip",25,25);
	fpo.setPosition(150,150);


	while ( window.isOpen())
	{
		
		fps(window);
		window.clear(sf::Color::Black);

		fpo.draw(window);
		ally1.draw(window);
		enemy1.draw(window);
		player.draw(window);

		window.display();

		// add actionListeners to the window
		sf::Event event;
		while (window.pollEvent(event))
		{
			//close the window when the X is clicked
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}

	//std::cout << "Hello Again, World!" << std::endl;
	//system("pause");
	return 0;
}