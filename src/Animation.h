#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
private:
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
public:
	void Update(int row, int imageCount, float deltaTime);
	void imageSwitch(int row, int imageChoice, int imageChoiceY);

	sf::IntRect uvRect;

	Animation(int imageSizeX, int imageSizeY, float switchTime);
	Animation(int imageSizeX, int imageSizeY);
	Animation();
	~Animation();
};

