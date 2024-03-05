#include "Button.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

Button::Button(String name, AudioLooper* looper, string assignedAudio) : AGameObject(name)
{
	this->looper = looper;
	this->assignedAudio = assignedAudio;
}

void Button::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Button", 0);
	this->sprite->setTexture(*texture);

	//sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	//this->sprite->setTextureRect(sf::IntRect(0, 0, BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT));

	sf::Vector2u textureSize = texture->getSize();

	// Set the origin to the center of the texture
	this->sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);

}

void Button::processInput(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
		if (isMouseOver(mousePosition))
		{
			std::cout << this->name + " is Pressed!" << std::endl;

			if (enabled)
			{
				cout << "Button is Enabled" << endl;
				this->sprite->setColor(sf::Color::White);
				enabled = false;
			}
			else if (!enabled)
			{
				cout << "Button is Disabled" << endl;
				this->sprite->setColor(sf::Color::Green);
				enabled = true;
			}

			looper->ToggleMusic(assignedAudio);
		}
	}
}

bool Button::isMouseOver(sf::Vector2f mousePosition)
{
	// Check if the mouse position is within the button's bounds
	sf::FloatRect buttonBounds = sprite->getGlobalBounds();
	return buttonBounds.contains(mousePosition);
}

void Button::update(sf::Time deltaTime)
{
}
