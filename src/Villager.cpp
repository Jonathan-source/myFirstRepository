#include "Villager.h"
#include <iostream>

//********** CONSTRUCTORS **********
Villager::Villager(float _speed, int _health, int _attackDmg, sf::Texture &_texture)
	:Entity(_speed, _health, _attackDmg, _texture), selected(false), xDir(0.0f), yDir(0.0f), moving(false), lengthToMousePos(0.0f), hasDonefirstIteration(false)
{
	animation = Animation(64, 64); // <-- TextureSize 64x64
	sprite.setTextureRect(animation.uvRect);

	this->mouseTargetPos = sf::Vector2f(0.0f, 0.0f);
	sf::Color white2 = sf::Color(255, 255, 255, 45);
	font.loadFromFile("assets/atari.ttf");
	//generate the stats for villagers
	initStats();
	UIprofil.setSize(sf::Vector2f(600.0f, 100.0f));
	UIprofil.setFillColor(white2);
	text.setFont(font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Yellow);
	text.setString("Name\n" + skillString);

	generateName();
}

Villager::Villager(sf::Texture& _texture)
	:Entity(4,100,10, _texture), selected(false), xDir(0.0f), yDir(0.0f), moving(false), lengthToMousePos(0.0f), hasDonefirstIteration(false)
{
	animation = Animation(64, 64); // <-- TextureSize 64x64
	sprite.setTextureRect(animation.uvRect);

	this->mouseTargetPos = sf::Vector2f(0.0f, 0.0f);
	sf::Color white2 = sf::Color(255, 255, 255, 45);
	font.loadFromFile("assets/atari.ttf");
	//generate the stats for villagers
	initStats();
	UIprofil.setSize(sf::Vector2f(600.0f, 100.0f));
	UIprofil.setFillColor(white2);
	text.setFont(font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::White);
	text.setString("Name\n"+skillString);

	generateName();

}
void Villager::generateName()
{
	// Load from file
	std::ifstream myfile("assets/names.txt");

	if (myfile.fail())
	{
		std::cout << "Error opening file\n";
	}
	int ranName = rand() % 99;	//PICKS A NUMBER AND TAKE THAT NAME POS IN FILE
	std::string fileInput;
	if (myfile.is_open())
	{
		for (int i = 0; i < ranName; i++) {
			//myfile >> fileInput;
			std::getline(myfile, fileInput); //ONLY TO SKIP THE LINES IN THE FILE	
		}
		std::getline(myfile, fileInput);
		text.setString("\n " + fileInput + "\n " + skillString);
	}
	myfile.close();
}
void Villager::initStats()
{

	int val = rand() % 4 + 1;
	if (val == 1)
	{
		printf("This villager is superb at mining!\n");
		skillArr[MINER] = 2;
		skillString = "Miner trait: 100% more gain when mining!\n";
	}
	else if (val == 2)
	{
		printf("This villager is superb at Woodcutting!\n");
		skillArr[LUMBER] = 2;
		skillString = "Lumber trait: 100% more gain when \n woodcutting!\n";
	}
	else if (val == 3)
	{
		printf("This villager is superb at runing!\n");
		skillArr[RUNNER] = 2;
		this->setSpeed(this->getSpeed() * 1.5);
		skillString = "Runner trait: 50% faster when running!\n";
	}
	else if (val == 4)
	{
		printf("Alive trait: Double the health!\n");
		skillArr[ALIVE] = 2;
		this->setHealth(this->getHealth() * 2);
		skillString = "Alive trait: Double the health!\n";
	}
}
// ***********************************

//DECONSTRUCTOR
Villager::~Villager()
{
}
		
void Villager::move()
{
	if (this->moving == true)
	{
		this->sprite.move(xDir * this->getSpeed(), yDir * this->getSpeed());
		if (resourceEntity != nullptr)
		{
			this->deAssignResource();
		}
	}
}

bool Villager::collideWithVillagers(Villager& other)
{
	bool ifCollided = false;
	if (this->getGlobalBounds().intersects(other.getGlobalBounds())) {
		ifCollided = true;
		this->moving = false;
	}
	return ifCollided;
}

void Villager::toggleSelect()
{
	this->selected = !this->selected;
}

void Villager::callResourceTick(GUI *_gui)
{
	if (this->isGathering && this->resourceEntity != nullptr)
	{
		if (resourceEntity->getResourceType() == WOOD)	//WOOD
		{
			int sum = resourceEntity->removeFromResource(100 * this->skillArr[LUMBER]);

			
			if (sum == -1)
			{
				this->isGathering = false;
			}
			else
			{
				_gui->addToWood(sum);
			}
		}
		else if(resourceEntity->getResourceType() == GOLD || resourceEntity->getResourceType() == IRON)	//ORES
		{
			int sum = resourceEntity->removeFromResource(5 * this->skillArr[MINER]);
			if (sum == -1)
			{
				this->isGathering = false;
			}
			else
			{

			}
		}
		else if (resourceEntity->getResourceType() == FOOD)
		{
			//TO DO
		}
	}
}

void Villager::setPosition(int x, int y)
{
	this->sprite.setPosition((float)x, (float)y);
}

void Villager::setIfSelected(bool _cond)
{
	selected = _cond;
}

void Villager::setXDir(float _val)
{
	xDir = _val;
}

void Villager::setYDir(float _val)
{
	yDir = _val;
}

void Villager::setMoving(bool _cond)
{
	moving = _cond;
}

void Villager::setMouseTargetPos(sf::Vector2f _mouseTargetPos)
{
	mouseTargetPos = _mouseTargetPos;
}

void Villager::setIsGathering(bool _cond)
{
	isGathering = _cond;
}

void Villager::assignResource(ResourceEntity* _resourceEntity)
{
	resourceEntity = _resourceEntity;
}

void Villager::deAssignResource()
{
	resourceEntity = nullptr;
	isGathering = false;
}

bool Villager::getIfGathering() const
{
	return isGathering;
}

sf::Vector2f Villager::getMouseTargetPos()
{
	return mouseTargetPos;
}

sf::Vector2f Villager::getEntityCenter()
{
	sf::Vector2f entityCenter = sf::Vector2f(this->sprite.getPosition().x + (this->sprite.getGlobalBounds().width / 2),
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2);
	return entityCenter;
}

sf::FloatRect Villager::getBoundingBox() const
{
	return this->sprite.getGlobalBounds();
}

bool Villager::getIfSelected()
{
	return selected;
}

bool Villager::getIfMoving()
{
	return moving;
}

void Villager::updateImage()
{
	int row = 0;

	if (this->selected)
	{
		row = 1;
		animation.imageSwitch(0, 0, row);
		sprite.setTextureRect(animation.uvRect);
	}
	else {
		row = 0;
		animation.imageSwitch(0, 0, row);
		sprite.setTextureRect(animation.uvRect);
	}

	//GOING CLOSE TO STRAIGHT DOWN
	if (xDir < 0.30 && xDir > -0.2f && yDir > 0.8) 
	{	
		animation.imageSwitch(0, 0, row);
		sprite.setTextureRect(animation.uvRect);
	}
	//GOING CLOSE TO RIGHT
	else if (xDir > 0.4 && yDir < 0.8 && yDir > -0.8)
	{
		animation.imageSwitch(0, 3, row);
		sprite.setTextureRect(animation.uvRect);
	}
	//GOING CLOSE TO LEFT
	else if (xDir < -0.4 && yDir < 0.8 && yDir > -0.8)
	{
		animation.imageSwitch(0, 2, row);
		sprite.setTextureRect(animation.uvRect);
	}
	//GOING CLOSE TO STRAGIHT UP
	else if (xDir < 0.30 && xDir > -0.20f && yDir < -0.8)
	{
		animation.imageSwitch(0, 1, row);
		sprite.setTextureRect(animation.uvRect);
	}

	if (this->isGathering) //Play animation while gathering
	{
		animation.Update(2,4,3.0f);
		sprite.setTextureRect(animation.uvRect);
	}
}

void Villager::showProfil(Camera& _camera)
{
	this->UIprofil.setPosition(_camera.getPosition().x - 930, _camera.getPosition().y - 500);
	text.setPosition(this->UIprofil.getPosition());

}

sf::Vector2f Villager::getPosition() const
{
	return this->sprite.getPosition();
}


void Villager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	if (this->selected) {
		target.draw(this->UIprofil);
		target.draw(this->text);
	}
}
