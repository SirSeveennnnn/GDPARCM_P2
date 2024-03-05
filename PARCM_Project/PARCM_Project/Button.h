#pragma once
#include "AGameObject.h"
#include "AudioLooper.h"

class Button : public AGameObject
{
public:
	Button(String name, AudioLooper* looper, string assignedAudio);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	bool isMouseOver(sf::Vector2f mousePosition);

private:
	string assignedAudio;
	AudioLooper* looper;

	bool enabled = false;
	sf::Color enabledColor;
	sf::Color disabledColor;
};

