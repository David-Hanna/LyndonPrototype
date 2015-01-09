#include <limits>
#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

#include <HEMath.h>

int main(int argc, void** argv)
{
	// testing that engine has been hooked up properly
	HE::BitVector16 bitVector;
	bitVector.SetBit(3);
	bitVector.SetBit(8);
	bitVector.SetBit(15);

	for (unsigned int i = 0; i < 16; i++)
	{
		if (bitVector.GetBit(i))
			std::cout << "1" << std::endl;
		else
			std::cout << "0" << std::endl;
	}

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