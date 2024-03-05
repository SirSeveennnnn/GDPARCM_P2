#include "VideoObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

VideoObject::VideoObject(String name) : AGameObject(name)
{
}

void VideoObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getSequenceTexture(currentFrame);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	this->sprite->setTextureRect(sf::IntRect(0, 0, BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT));
	this->setPosition(0, 0);
	this->setScale(1.5f, 1.5f);

}

void VideoObject::processInput(sf::Event event)
{
	
}

void VideoObject::update(sf::Time deltaTime)
{
	this->ticks += deltaTime.asMilliseconds();
	if (this->ticks > ticksPerFrame && currentFrame < maxFrame)
	{
		currentFrame++;
		sf::Texture* texture = TextureManager::getInstance()->getSequenceTexture(currentFrame);
		this->sprite->setTexture(*texture);
		this->ticks = 0;
	}
	
}