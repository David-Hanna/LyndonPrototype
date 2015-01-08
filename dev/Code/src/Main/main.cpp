#include <limits>
#include <iostream>
#include "SFML/Graphics.hpp"

int main(int argc, void** argv)
{

	sf::RenderWindow window( sf::VideoMode ( 600, 600 ), "SFML WORKS!" );

	while ( window.isOpen())
	{
		window.clear();

		window.display();
	}

	//std::cout << "Hello, World!" << std::endl;
	//system("pause");
	return 0;
}