#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>

class SHDrawable
{
private:
	sf::Texture texture;

	void loadSpriteFromFile(std::string textureName)
	{
		if(!texture.loadFromFile("../../Assets/" + textureName + ".png"))
		{
			texture.loadFromFile("../../Assets/placeholder.png");
		}
		sprite.setTexture(texture);
	}
protected:
	float xPos, yPos;
	sf::Sprite sprite;

public:
	SHDrawable()
	{
		loadSpriteFromFile("placeholder");
		xPos = 0;
		yPos = 0;
	}

	SHDrawable(std::string textureName, float x, float y)
	{
		loadSpriteFromFile(textureName);
		xPos = x;
		yPos = y;
	}

	void setPosition(float x, float y)
	{
		xPos = x;
		yPos = y;
	}

	void draw(sf::RenderWindow& rw)
	{
		sprite.setPosition(xPos,yPos);
		rw.draw(sprite);
	}
};