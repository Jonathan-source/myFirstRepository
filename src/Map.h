#ifndef MAP_H
#define MAP_H

#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <string>
#include "enumTextures.h"

class Map
{
private:
        // The width and height of a tile in pixels
        static const int tileWidth 	= 64;
        static const int tileHeight 	= 64;
        // Map size in number of tiles
       	static const int mapWidth 	= 99;
	    static const int mapHeight 	= 99;

        //Containers
        Tile* mapArray[mapWidth][mapHeight];
 public:
        Map();
        virtual ~Map();

        //void drawMap(sf::RenderWindow &window);
        void loadMap(std::string fileName, ResourceManager<sf::Texture, TextureID>* t);
        Tile* getTileAt(int x, int y);
        void setTileToUsed(int x, int y);
        int getTileTypeAt(int x, int y) const;
        sf::Vector2i getMapSize() const;
};

#endif
