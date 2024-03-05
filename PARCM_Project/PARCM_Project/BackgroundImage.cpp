#include "BackgroundImage.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

BackgroundImage::BackgroundImage(String name) : AGameObject(name)
{
}

void BackgroundImage::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("BlackLeather", 0);
	texture->setRepeated(true);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	this->sprite->setTextureRect(sf::IntRect(0, 0, BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT));
	this->setPosition(0,0);
}

void BackgroundImage::processInput(sf::Event event)
{
	
}

void BackgroundImage::update(sf::Time deltaTime)
{
}
