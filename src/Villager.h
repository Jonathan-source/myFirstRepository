#ifndef VILLAGER_H
#define VILLAGER_H
#include "Entity.h"
#include "Camera.h"
enum skills {
	MINER,
	LUMBER,
	RUNNER,
	ALIVE,
};
const int AMOUNTOFNAMES = 100;
class Villager : public Entity
{
private:

	bool selected;
	bool moving;
	bool hasDonefirstIteration;	 //Used for box selection.
	float xDir;
	float yDir;
	float lengthToMousePos;
	sf::Vector2f mouseTargetPos;
	//STATS
	int skillArr[4] = { 1 }; // value 1 is default skills, value 2 means extra benefits in that skill
	//PROFILE
	sf::RectangleShape UIprofil;
	sf::Font font;
	sf::Text text;
	std::string skillString; //Explains the extra good skill the villager has
	std::string namesContainer[100]; // Contains 100 names for villagers

	void generateName();
	void initStats();
public:
    Villager();
	Villager(float _speed, int _health, int _attackDmg);
	~Villager();
	//Functions
	void move();
	bool collideWithVillagers(Villager &other);
	//SET
	void setPosition(int x, int y);
	void setIfSelected(bool _cond);
	void setXDir(float _val);
	void setYDir(float _val);
	void setMoving(bool _cond);
	void setMouseTargetPos(sf::Vector2f _mouseTargetPos);
	//GET
	sf::Vector2f getMouseTargetPos();
	sf::Vector2f getEntityCenter();
	bool getIfSelected();
	bool getIfMoving();
	
	void showProfil(Camera &_camera);
	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif