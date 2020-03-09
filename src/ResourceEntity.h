#pragma once
#include <SFML/Graphics.hpp>
enum resourceType {
	WOOD,
	GOLD,
	IRON,
	FOOD,
};
class ResourceEntity : public sf::Drawable
{
private:

protected:
	sf::Sprite sprite;
	sf::Texture* resourceTexture;
	sf::Texture* resourceTextureEmpty;
	int resourceAmount; //HOW MUCH RESOURCE CAN BE GATHERED FROM THIS OBJECT.
	int type;	//0 = WOOD,   1 = GOLD   2 = IRON   3 = FOOD
	sf::FloatRect hitBox;

public:
	ResourceEntity();
	ResourceEntity(sf::Texture& _texture, int _resourceType, int _resourceAmount, sf::Vector2f _position, sf::Texture& _textureResEmpty);
	~ResourceEntity();
	
	//TICK
	int removeFromResource(int _sum);
	//GET
	int getResourceType() const;
	int getResourceAmount() const;
	sf::Vector2f getPosition() const;
	//Area which is used to se if Villager are inside range to gather
	sf::FloatRect getHitBox() const;
	//SET
	void setPosition(sf::Vector2f _pos);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

