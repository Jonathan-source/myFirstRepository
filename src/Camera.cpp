#include "Camera.h"
//CONSTRUCTOR

Camera::Camera()
:  cameraSensitivity(20.0f), aspectRatio(1.78), windowHeight(1080), windowWidth(1920), renderDistance(20)
{
    tileMap = nullptr;
    //--- SETTINGS ---
	std::ifstream myFile ("settings.txt");
	if(myFile.is_open()){
        myFile >> cameraSensitivity;
		/*while(myFile >> a)
		{
			cameraSensitivity = a;
		}*/
	}
    myFile.close();
}
//INITIALIZE
void Camera::initView(sf::RenderWindow &window)
{

    view = sf::View((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

    window.setView(view);
}

void Camera::initView(sf::RenderWindow &window, Map &map)
{
    this->tileMap = &map;
    view = sf::View((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

    window.setView(view);
}
//MOVE-FUNCTIONS
void Camera::move(sf::RenderWindow &window)
{
    sf::Vector2i mousepos = sf::Mouse::getPosition(window);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || mousepos.x < 25)
    {
        view.move(-cameraSensitivity,0);
        window.setView(view);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || mousepos.x > (windowWidth - 25))
    {
        view.move(cameraSensitivity,0);
        window.setView(view);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || mousepos.y < 25)
    {
        view.move(0,-cameraSensitivity);
        window.setView(view);
    }       
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || mousepos.y > (windowHeight - 25))
    {
        view.move(0,cameraSensitivity);
        window.setView(view);
    }   
}

void Camera::scroll(sf::RenderWindow &window,int _sum)   //Camera zooms in or out;
{
    if(_sum == -1 && view.getSize().x >= 500.f) //ZOOM IN
    {
        view.zoom(0.9);
    }
    else if(_sum == 1 && view.getSize().x <= 3000.f) //ZOOM OUT
    {
        view.zoom(1.1);
    }
    window.setView(view);
}

void Camera::maintainAspectRatio(sf::RenderWindow &window)
{
    if(window.getSize().x != windowWidth)
    {
        windowWidth = window.getSize().x;
        windowHeight = (windowWidth / aspectRatio);
        window.setSize(sf::Vector2u(windowWidth, windowHeight));
    }
    else if(window.getSize().y != windowHeight)
    {
        windowHeight = window.getSize().y;
        windowWidth = (windowHeight * aspectRatio);
        window.setSize(sf::Vector2u(windowWidth, windowHeight));

    }
}

sf::Vector2f Camera::getPosition()
{
    return this->view.getCenter();
}
    //DRAW
void Camera::drawMap(sf::RenderWindow &window)
    {
        int viewCenX = (int)(view.getCenter().x / 64);   //Center x position for camera
        int viewCenY = (int)(view.getCenter().y / 64);   // Center y position for camera
        int mapSizeX = (int)tileMap->getMapSize().x;
        int mapSizey = (int)tileMap->getMapSize().y;
        int tempX = 0;
        int tempY = 0;

        for (int y = (viewCenY - (renderDistance)); y <= ((viewCenY + (renderDistance))); y++)
            {
                tempY = y;

                if(y < 0)
                    tempY = 0;

                if(y >= mapSizey)
                    tempY = mapSizey-1; 
                

                for (int x = (viewCenX - (renderDistance)); x <= ((viewCenX + (renderDistance))); x++)
                    {
                        tempX = x;
                        
                        if(x < 0)
                            tempX = 0;

                        if(x >= mapSizeX)
                            tempX = mapSizeX-1;
                        

                      window.draw(*tileMap->getTileAt(tempX,tempY));

                    }
	        }
    }