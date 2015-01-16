#include "InputHandler.h"

void InputHandler::OnUpdate()
{
	std::string charsPressed("");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		charsPressed += "left,";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		charsPressed += "right,";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		charsPressed += "up,";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		charsPressed += "down,";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //shoot
	{
		charsPressed += "s,";
	}

	HE::EventData eventData(0, HE::eEventType_ButtonPressed, charsPressed);
	HE::EventManager::instance().FireEvent(eventData);
}