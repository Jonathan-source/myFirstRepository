#ifndef BUILDINGENTITY_H
#define BUILDINGENTITY_H
#include <SFML/Graphics.hpp>
	
class BuildingEntity : public sf::Drawable  
{
private:
	int hitpoints;
	int level;
protected:
	sf::Sprite sprite;
public:
	BuildingEntity(int hp, int level);
	virtual ~BuildingEntity();

	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	int getHitpoints() const;
	int getLevel() const;
	
	void setPosition(sf::Vector2f pos);
	void setLevel(int level);
	void setHitpoints(int hp);
	void upgrade();	

	//DRAW
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
