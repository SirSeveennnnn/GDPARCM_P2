#pragma once
#include "AGameObject.h"
class FadeEffect : public AGameObject
{
public:

	FadeEffect(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void StartFade();

private:
	bool startFade = false;
	float ticks = 0;
	float duration = 5000;

	float lerp(float t);
};

