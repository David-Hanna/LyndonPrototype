#include <limits>
#include <iostream>

int main(int argc, void** argv)
{
	std::cout << "Hello, World!" << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return 0;
}