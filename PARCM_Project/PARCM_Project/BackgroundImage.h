#pragma once
#include "AGameObject.h"
class BackgroundImage : public AGameObject
{
public:
	BackgroundImage(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
private:
	
};

