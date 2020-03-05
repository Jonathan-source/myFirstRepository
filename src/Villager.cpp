#include "Villager.h"
#include <iostream>

//********** CONSTRUCTORS **********
Villager::Villager(float _speed, int _health, int _attackDmg)
	:Entity(_speed, _health, _attackDmg), selected(false), xDir(0.0f), yDir(0.0f), moving(false), lengthToMousePos(0.0f), hasDonefirstIteration(false)
{
	this->setNormalTexture();

}

Villager::Villager()
	:Entity(4.0f, 100, 10), selected(false), xDir(0.0f), yDir(0.0f), moving(false), lengthToMousePos(0.0f), hasDonefirstIteration(false)
{
	this->mouseTargetPos = sf::Vector2f(0.0f, 0.0f);
	sf::Color white2 = sf::Color(255, 255, 255, 45);
	font.loadFromFile("assets/atari.ttf");
	this->setNormalTexture();
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

bool Villager::getIfSelected()
{
	return selected;
}

bool Villager::getIfMoving()
{
	return moving;
}

void Villager::showProfil(Camera& _camera)
{
	this->UIprofil.setPosition(_camera.getPosition().x - 930, _camera.getPosition().y - 500);
	text.setPosition(this->UIprofil.getPosition());

}

void Villager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	if (this->selected) {
		target.draw(this->UIprofil);
		target.draw(this->text);
	}
}
