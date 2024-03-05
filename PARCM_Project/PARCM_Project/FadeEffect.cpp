#include "FadeEffect.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

#include "AudioLooper.h"
#include "GameObjectManager.h"

FadeEffect::FadeEffect(String name) : AGameObject(name)
{
}

void FadeEffect::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Black", 0);
	texture->setRepeated(true);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	this->sprite->setTextureRect(sf::IntRect(0, 0, BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT));
	this->setPosition(0, 0);
	this->sprite->setColor(sf::Color(0, 0, 0, 0));
}

void FadeEffect::processInput(sf::Event event)
{

}

void FadeEffect::update(sf::Time deltaTime)
{
	if (startFade)
	{
		this->ticks += deltaTime.asMilliseconds();
		float t = ticks / duration;
		this->sprite->setColor(sf::Color(0, 0, 0, lerp(t)));

		if (this->ticks > this->duration)
		{
			//Stuff
			AGameObject* gameObject = GameObjectManager::getInstance()->findObjectByName("AudioLooper");
			AudioLooper* audioLooper = dynamic_cast<AudioLooper*>(gameObject);
			audioLooper->StopAllMusic();

			GameObjectManager::getInstance()->deleteAllGameObjects();
			GameObjectManager::getInstance()->InitializeMainMenu();
		}
	}
}

void FadeEffect::StartFade()
{
	startFade = true;
}

float FadeEffect::lerp(float t)
{
	return 0.0f + t * (255.0f - 0.0f);
}
