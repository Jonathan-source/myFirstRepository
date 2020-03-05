#include "VillagerHandler.h"

VillagerHandler::VillagerHandler()
	:capacity(10), nrOfActive(0), hasDonefirstIteration(false)
{

	sf::Color white2 = sf::Color(255, 255, 255, 15);

	for (int i = 0; i < 4; i++)
	{
		quad[i] = sf::Vertex(sf::Vector2f(0, 0));
		quad[i].color = white2;
	}
	spawnPos = (sf::Vector2i(0, 0));
	villagers = new Villager * [capacity] {nullptr};
	for (int i = 0; i < 3; i++)
	{
		villagers[i] = new Villager();
		nrOfActive++;
		villagers[i]->setPosition(spawnPos.x+=64, spawnPos.y+=10);	//TODO Change this <-
	}
}

void VillagerHandler::spawnAVillager()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && nrOfActive <= capacity)
	{
		villagers[nrOfActive] = new Villager();
		villagers[nrOfActive++]->setPosition(spawnPos.x, spawnPos.y);
		printf("Spawned a villager\n");
	}
}

void VillagerHandler::expand()
{
	
}

void VillagerHandler::freeMemory()
{

}

int VillagerHandler::getNrOfActive()
{
	return nrOfActive;
}

int VillagerHandler::getCapacity()
{
	return capacity;
}

void VillagerHandler::moveAllVillagers()
{
	for (int i = 0; i < nrOfActive; i++) {
		villagers[i]->move();
	}
}

void VillagerHandler::drawAllVillagers(sf::RenderWindow& window)
{
	for (int i = 0; i < nrOfActive; i++) {
		window.draw(*villagers[i]);
	}
	window.draw(this->quad, 4, sf::Quads);
}

//selectionBoxUpdate only used inside the class!
void VillagerHandler::selectionBoxUpdate(sf::RenderWindow& window, sf::Vector2f &mousePos)
{
	if (!hasDonefirstIteration)
	{
		hasDonefirstIteration = true;
		firstMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		quad[0].position = sf::Vector2f(firstMousePosition);

	}

	quad[1].position = sf::Vector2f((float)firstMousePosition.x, (float)mousePos.y);
	quad[2].position = (sf::Vector2f((float)mousePos.x, (float)mousePos.y));
	quad[3].position = (sf::Vector2f((float)mousePos.x, (float)firstMousePosition.y));
}

void VillagerHandler::selectVillager(sf::RenderWindow& window)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		hasDonefirstIteration = false; //resets when button released;;
		for (int i = 0; i < 4; i++)
		{
			quad[i].position = sf::Vector2f(0, 0);
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));;

		selectionBoxUpdate(window, mousePos);

		float sizeX = (float)mousePos.x - (float)firstMousePosition.x;
		float sizeY = (float)mousePos.y - (float)firstMousePosition.y;
		bool foundOne = false;
		for (int i = 0; i < nrOfActive; i++)
		{
			if (mousePos.x >= villagers[i]->getPosition().x && mousePos.x <= (villagers[i]->getPosition().x + villagers[i]->getGlobalBounds().width)
				&& mousePos.y <= villagers[i]->getPosition().y + villagers[i]->getGlobalBounds().height && mousePos.y >= villagers[i]->getPosition().y
				|| villagers[i]->getGlobalBounds().intersects(sf::FloatRect((sf::Vector2f)firstMousePosition, sf::Vector2f(sizeX, sizeY))))
			{
				if (!foundOne) 
				{
					villagers[i]->setIfSelected(true);
					villagers[i]->setSelectTexture();
					foundOne = true;
				}
			}
			else
			{
				villagers[i]->setIfSelected(false);
				villagers[i]->setNormalTexture();
			}
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

void VillagerHandler::showVillagersProfil(Camera& _camera)
{
	for (int i = 0; i < nrOfActive; i++) {
		if (villagers[i]->getIfSelected()) {
			villagers[i]->showProfil(_camera);
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
