#include "Animation.h"

void Animation::Update(int row, int imageCount, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount)
		{
			currentImage.x = 0;
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

void Animation::imageSwitch(int row, int imageChoiceX, int imageChoiceY)
{
	currentImage.y = row;
	uvRect.left = imageChoiceX * uvRect.width;
	uvRect.top = imageChoiceY * uvRect.height;
}

Animation::Animation(int imageSizeX, int imageSizeY, float switchTime)
{
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = imageSizeX;
	uvRect.height = imageSizeY;

}
Animation::Animation(int imageSizeX, int imageSizeY)
	:totalTime(0), switchTime(30)
{
	currentImage.x = 0;
	uvRect.width = imageSizeX;
	uvRect.height = imageSizeY;
}
Animation::Animation()
	:totalTime(0), switchTime(30)
{
	this->uvRect.width = 0;
	this->uvRect.height = 0;

}

Animation::~Animation()
{
}
