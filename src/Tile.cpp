#include "Tile.h"

Tile::Tile(int id, float x, float y, sf::Texture &texture)
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(sf::Vector2f(x, y));		
	this->type = id;
	this->isOccupied = false;
	this->isVisible = true;
}

Tile::~Tile()
{

}

int Tile::getType() const
{
	return this->type;
}



sf::Vector2f Tile::getPosition() const
{
	return this->sprite.getPosition();
}

bool Tile::getIsOccupied() const
{
	return this->isOccupied;
}

void Tile::setIsOccupied(bool status)
{
	this->isOccupied = status;
}

bool Tile::getIsVisible() const
{
	return this->isVisible;
}

void Tile::setVisibility(bool option)
{
	this->isVisible = option;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(this->isVisible)
	{
		target.draw(this->sprite);
	}
}