#include "LaunchPadBase.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

LaunchPadBase::LaunchPadBase(String name) : AGameObject(name)
{

}

void LaunchPadBase::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("LaunchPadBase", 0);
	this->sprite->setTexture(*texture);

	//sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	//this->sprite->setTextureRect(sf::IntRect(0, 0, BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT));

	sf::Vector2u textureSize = texture->getSize();
	// Set the origin to the center of the texture
	this->sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);


	this->setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);
}

void LaunchPadBase::processInput(sf::Event event)
{
	
}

void LaunchPadBase::update(sf::Time deltaTime)
{
}
