#include "VillagerHandler.h"

VillagerHandler::VillagerHandler(sf::Texture &_texture)
	:capacity(10), nrOfActive(0), hasDonefirstIteration(false), isVillagerSelected(false)
{
	srand(time(NULL));
	farmerTexture = &_texture;
	sf::Color white2 = sf::Color(255, 255, 255, 15);

	for (int i = 0; i < 4; i++)
	{
		quad[i] = sf::Vertex(sf::Vector2f(0, 0));
		quad[i].color = white2;
	}

	spawnPos = (sf::Vector2i(256, 0));
	villagers = new Villager * [capacity] {nullptr};

	for (int i = 0; i < 3; i++)
	{
		villagers[i] = new Villager(4,100,10, _texture);
		nrOfActive++;
		villagers[i]->setPosition(spawnPos.x+=64, spawnPos.y+=10);	//TODO Change this <-
	}
}

VillagerHandler::~VillagerHandler()
{
	int num = 0;
	for (int i = 0; i < capacity; i++)
	{
		if(villagers[i] != nullptr)
		{
			delete villagers[i];
			num++;
		}
	}
	std::cout << "[VillageHandler]: " << num << " villagers were de-allocated.\n";
	delete[] villagers;
}


void VillagerHandler::spawnAVillager()
{
	if (nrOfActive <= capacity)
	{
		villagers[nrOfActive] = new Villager(*farmerTexture);
		villagers[nrOfActive++]->setPosition(spawnPos.x, spawnPos.y);
		std::cout << "[VillageHandler]: A villager were allocated.\n";
	}
}

void VillagerHandler::expand()
{
	
}

void VillagerHandler::freeMemory()
{

}

void VillagerHandler::resourceTick(GUI* _gui)
{
	for (int i = 0; i < nrOfActive; i++)
	{
		villagers[i]->callResourceTick(_gui);
	}
}

int VillagerHandler::getNrOfActive()
{
	return nrOfActive;
}

int VillagerHandler::getCapacity()
{
	return capacity;
}

Villager** VillagerHandler::getVillagerList() const
{
	return villagers;
}

void VillagerHandler::moveAllVillagers()
{
	for (int i = 0; i < nrOfActive; i++) {
		villagers[i]->move();
		villagers[i]->updateImage(); //SHOW CORRECT IMAGE SO VILLAGER FACE CORRECT DIRECTION
	}
}

void VillagerHandler::drawAllVillagers(sf::RenderWindow& window)
{
	for (int i = 0; i < nrOfActive; i++) {
		window.draw(*villagers[i]);
	}
	window.draw(this->quad, 4, sf::Quads);
}

void VillagerHandler::selectVillager(sf::RenderWindow& window, sf::Event &event, float yPos)
{
	firstMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	bool foundOne = false;

	for (int i = 0; i < this->nrOfActive && !foundOne; i++)
	{
		// Check if any button contain the mouse-pointer.
		if (villagers[i]->getBoundingBox().contains(firstMousePosition.x, firstMousePosition.y))
		{
			for (int y = 0; y < nrOfActive; y++)
			{
				villagers[y]->setIfSelected(false);
			}
			// Then check if left button is pressed.
			if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
			{
				villagers[i]->toggleSelect();
				foundOne = true;
				//Button is being pressed, check and perform button action.
			}
		}
		else if (firstMousePosition.y < yPos)
		{
			villagers[i]->setIfSelected(false);
		}
		
	}
}

void VillagerHandler::setVillagerMoveToTarget(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		for (int i = 0; i < nrOfActive; i++)
		{	
			if (villagers[i]->getIfSelected()) {
			
				//creating a normalized vector to move villager on X & Y
				villagers[i]->setMouseTargetPos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				//std::cout << std::to_string(mouseTargetPos.x) << " . " << std::to_string(mouseTargetPos.x) << std::endl;
				sf::Vector2f villagerCenter = villagers[i]->getEntityCenter();

				sf::Vector2f towardsDirection = villagers[i]->getMouseTargetPos() - villagerCenter;
				sf::Vector2f towDirNorm;
				normalized(towDirNorm, towardsDirection);
				villagers[i]->setXDir(towDirNorm.x);
				villagers[i]->setYDir(towDirNorm.y);

				villagers[i]->setMoving(true);
			}
		}

	}
	for (int i = 0; i < nrOfActive; i++) {
			distanceToMousePosition = villagers[i]->getMouseTargetPos() - villagers[i]->getEntityCenter();

			lengthToMousePos = sqrt(pow(distanceToMousePosition.x, 2) + pow(distanceToMousePosition.y, 2));

			if (lengthToMousePos < 20.0f)
			{
				villagers[i]->setMoving(false);
				villagers[i]->setXDir(0.0f);
				villagers[i]->setYDir(0.0f);
			}
	}
}

void VillagerHandler::setVillagerToGather(int _position)
{
	villagers[_position]->setIsGathering(true);
}

void VillagerHandler::collideWithVillagers()
{
	for (int y = 0; y < nrOfActive; y++)
	{
		for (int i = 0; i < nrOfActive; i++)
		{
			if (i != y)
			{
				while(villagers[y]->collideWithVillagers(*villagers[i]))
				{
					villagers[y]->setMoving(false);
					villagers[y]->setPosition(villagers[y]->getPosition().x + 1, villagers[y]->getPosition().y);
				}
			}
		}
	}
}

bool VillagerHandler::checkIfSelected()
{
	this->isVillagerSelected = false;
	for (int i = 0; i < nrOfActive; i++) 
	{
		if (villagers[i]->getIfSelected()) 
		{
			this->isVillagerSelected = true;
		}		
	}
	return this->isVillagerSelected;
}

void VillagerHandler::showVillagersProfil(Camera& _camera)
{
	for (int i = 0; i < nrOfActive; i++) 
	{
		if (villagers[i]->getIfSelected()) 
		{
			villagers[i]->showProfil(_camera);
		}		
	}
}

sf::Vector2f VillagerHandler::getPositionOfSelectedVillager() const
{
	for (int i = 0; i < nrOfActive; i++) 
	{
		if (villagers[i]->getIfSelected()) 
		{
			return villagers[i]->getPosition();
		}		
	}
}

inline void VillagerHandler::normalized (sf::Vector2f& res, const sf::Vector2f& v)
{
    float len = sqrt(v.x*v.x + v.y*v.y);
    if (len != 0) {
        res.x = v.x / len;
        res.y = v.y / len;
    }
}
