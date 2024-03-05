#include "LoadingBar.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

LoadingBar::LoadingBar(String name) : AGameObject(name)
{

}

void LoadingBar::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	maxWidth = BaseRunner::WINDOW_WIDTH;

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("White", 0);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	this->sprite->setTextureRect(sf::IntRect(0, 0, 0, 20));


}

void LoadingBar::processInput(sf::Event event)
{
	
}

void LoadingBar::update(sf::Time deltaTime)
{
	
}

void LoadingBar::AddProgress()
{
	finished++;
	float progress = finished / maxFinished;
	percent = 0.0f + progress * (maxWidth - 0.0f);

	this->sprite->setTextureRect(sf::IntRect(0, 0, percent, 20));
}
