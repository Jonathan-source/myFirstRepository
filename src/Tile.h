#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"

class Tile : public sf::Drawable
{
private:
	static const int size = 64; // 64x64 in pixels	
	sf::Sprite sprite;
	int type;
	bool isCollidable;
	bool isVisible;
 public:
    Tile(int id, float x, float y, sf::Texture& texture);
    virtual ~Tile();

    int getType() const;
    sf::Vector2f getPosition() const;
	bool getIsCollidable() const;
	bool getIsVisible() const;
	void setVisibility(bool option);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
