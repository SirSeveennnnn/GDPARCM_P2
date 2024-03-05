#pragma once
#include "AGameObject.h"
class VideoObject : public AGameObject
{
public:

	VideoObject(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

private:
	int currentFrame = 0;
	int maxFrame = 511;
	float ticks = 0;
	float ticksPerFrame = 166.66f;
};

