#include <limits>
#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

int main(int argc, void** argv)
{
	// open a window with the title SFML WORKS!
	sf::RenderWindow window( sf::VideoMode ( 600, 600 ), "SFML WORKS!  FPS: ----" );
	int count = 0;

	time_t start = time(0);
	time_t current;

	while ( window.isOpen())
	{
		current = time(0);
		if (current - start >= 1)
		{
			start = current;
			std::string str("SFML WORKS!  FPS: " + std::to_string(count));
			window.setTitle(str);
			count = 0;
		}
		else
		{
			count++;
		}
		window.clear(sf::Color::Black);

		// Make and create a chircle
		sf::CircleShape shape(50);
		shape.setFillColor(sf::Color(100, 250, 50));

		// Draw the circle onto the window
		window.draw(shape);

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