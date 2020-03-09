#include "ResourceHandler.h"

ResourceHandler::ResourceHandler()
	:woodStored(0), ironStored(0), goldStored(0),foodStored(0),nrOfActive(0), capacity(1000)
{

	resourceObjects = new ResourceEntity * [capacity] {nullptr};

}

ResourceHandler::~ResourceHandler()
{
	int num = 0;
	for (int i = 0; i < capacity; i++)
	{
		if (resourceObjects[i] != nullptr)
		{
			delete resourceObjects[i];
			num++;
		}
	}
	std::cout << "[resourceObjects]: " << num << " resourceObjects were de-allocated.\n";
	delete[] resourceObjects;
}

void ResourceHandler::initResources(Map& _map, sf::Texture& _texture, sf::Texture& _texturesResourceEmpty)
{
	for (int i = 0; i < _map.getMapSize().x; i++)
	{
		for (int y = 0; y < _map.getMapSize().y; y++)
		{
			if (_map.getTileTypeAt(i,y) == 1)
			{
				int val = rand() % 100;

				if (val == 1)
				{
					printf("tree spawned:%d\n", nrOfActive);
					spawnResource(_texture, WOOD, 800, sf::Vector2f(i, y), _texturesResourceEmpty);
					_map.setTileToUsed(i, y);
				}
			}
		}
	}
}

void ResourceHandler::spawnResource(sf::Texture &_textures,int _type, int _resourceAmount, sf::Vector2f _pos, sf::Texture& _texturesResourceEmpty)
{
	if (nrOfActive <= capacity)
	{
		resourceObjects[nrOfActive] = new ResourceEntity(_textures, _type,  _resourceAmount, _pos, _texturesResourceEmpty);
		nrOfActive++;
	}
}

int ResourceHandler::gatherFromResource(Villager** villagerList, int _nrOfActive)
{
	int num = -1;
	for (int i = 0; i < this->nrOfActive && num == -1; i++)
	{
		for (int y = 0; y < _nrOfActive && num == -1; y++)
		{
			if (resourceObjects[i]->getHitBox().intersects(villagerList[y]->getGlobalBounds()) && villagerList[y]->getIfSelected()) 
			{
				num = y;
				villagerList[y]->assignResource(resourceObjects[i]);
				printf("VillagerList[%d] INSIDE TREES AREA CAN GATHER!!\n", num);
			}
		}
	}
	return num;
}

void ResourceHandler::drawAll(sf::RenderWindow& window)
{
	for (int i = 0; i < nrOfActive; i++)
	{
		window.draw(*this->resourceObjects[i]);
	}
}
