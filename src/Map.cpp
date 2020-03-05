#include "Map.h"

Map::Map()
{
	for (int row = 0; row < this->mapHeight; row++)
		for (int column = 0; column < this->mapWidth; column++)
			this->mapArray[column][row] = nullptr;
	

	std::cout << "[Map]: Object successfully created.\n";
}

void Map::loadMap(std::string fileName, ResourceManager<sf::Texture, TextureID>* t)
{
		std::cout << "[Map]: Loading map...";

		// Load from file
		std::ifstream myfile(fileName);
		
		if (myfile.fail()) 
		{
       		std::cout << "Error opening file\n";
		} 

		// Create a container for input, and a counter for tiles.
		char fileInput;
		int tileCounter = 0;

		if(myfile.is_open())
		{	
			// Loop through the rows
				for (int row = 0; row < this->mapHeight; row++)
				{
					// Loop through the columns
					for (int column = 0; column < this->mapWidth; column++)
					{
						// Read from file
						myfile >> fileInput;

						// Turn char into int, identify & create tile
						switch((int)fileInput- 48)
						{
							case 0:
								this->mapArray[column][row] = new Tile(0, column * 64.f, row * 64.f, t->getResource(TextureID::Water));
								tileCounter++;
								break;
							case 1:
								this->mapArray[column][row] = new Tile(1, column * 64.f, row * 64.f, t->getResource(TextureID::Grass));	
								tileCounter++;
								break;			
							case 2:				
								break;
							case 3:
								break;
							case 4:
								break;
							case 5:
								break;
							case 6: 
								break;
							case 7:
								break;
							case 8:
								break;
							case 9:
								break;
							default:
									std::cout << "[Map]: This should never happen.\n";
									myfile.close();
								break;
						}
					}
				}
		myfile.close();	 
  		}
	std::cout << "\n[Map]: Map has been loaded. " << tileCounter << " tiles were successfully created.\n";
}

Map::~Map()
{
	int num = 0;
	for (int row = 0; row < this->mapHeight; row++){
		for (int column = 0; column < this->mapWidth; column++){
			if(this->mapArray[column][row] != nullptr){
				delete this->mapArray[column][row];	
				num++;
			}
		}
	}
	std::cout << "[Map]: " << num << " tiles were sucessfully deleted.\n";		
}

Tile* Map::getTileAt(int x, int y)
{
	return mapArray[x][y];
}

sf::Vector2i Map::getMapSize() const
{
	return sf::Vector2i(mapWidth, mapHeight);
}