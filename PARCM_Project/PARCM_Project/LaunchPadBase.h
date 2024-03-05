#pragma once
#include "AGameObject.h"
class LaunchPadBase : public AGameObject
{
public:
	LaunchPadBase(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
private:
};

