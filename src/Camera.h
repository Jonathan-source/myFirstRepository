#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
class Camera
{
private:
    sf::View view;
    Map *tileMap;
    float cameraSensitivity;
    float aspectRatio; //16:9
    int windowHeight, windowWidth;
    int renderDistance;
public:
    //Constructor
    Camera();
    //INITIALIZE
    void initView(sf::RenderWindow &window);
    void initView(sf::RenderWindow &window, Map &map);
    //FUNCTIONS
    void move(sf::RenderWindow &window);
    void scroll(sf::RenderWindow &window,int _sum);
    void maintainAspectRatio(sf::RenderWindow &window);
    //GET
    sf::Vector2f getPosition();
    //DRAW
    void drawMap(sf::RenderWindow &window);
    
};
#endif