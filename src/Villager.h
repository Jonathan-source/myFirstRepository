#ifndef VILLAGER_H
#define VILLAGER_H
#include "Entity.h"
#include "Camera.h"
#include "Animation.h"
#include "ResourceEntity.h"
#include "GUI.h"
enum skills {
	LUMBER,
	MINER,
	RUNNER,
	ALIVE,
};

class Villager : public Entity
{
private:
	//Existenz.se
	
	bool selected;
	bool moving;
	bool hasDonefirstIteration;	 //Used for box selection.
	bool isGathering; //USED TO CHECK IF VILLAGER IS GATHERING
	ResourceEntity* resourceEntity = nullptr; //if villager is gathering, take from this <-
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
	//ANIMATION
	Animation animation;
	void generateName();
	void initStats();
public:
    Villager(sf::Texture& _texture);
	Villager(float _speed, int _health, int _attackDmg, sf::Texture& _texture);
	~Villager();
	//Functions
	void move();
	bool collideWithVillagers(Villager &other);
	void toggleSelect();
	//GAIN RESOURCES FROM VILLAGER WHO IS GATHERING
	void callResourceTick(GUI* _gui);
	//SET
	void setPosition(int x, int y);
	void setIfSelected(bool _cond);
	void setXDir(float _val);
	void setYDir(float _val);
	void setMoving(bool _cond);
	void setMouseTargetPos(sf::Vector2f _mouseTargetPos);
	void setIsGathering(bool _cond);
	void assignResource(ResourceEntity* _resourceEntity);
	void deAssignResource();
	//GET
	bool getIfGathering() const;
	sf::Vector2f getMouseTargetPos();
	sf::Vector2f getEntityCenter();
	sf::FloatRect getBoundingBox() const;
	bool getIfSelected();
	bool getIfMoving();
	sf::Vector2f getPosition() const;
	//ANIMATION FUNCTION
	void updateImage();


	void showProfil(Camera &_camera);
	//Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};

#endif
