#pragma once
#include "AGameObject.h"
class LoadingBar : public AGameObject
{
public:
	LoadingBar(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void AddProgress();

private:

	float finished = 0;
	float maxFinished = 510;
	float maxWidth = 0;
	float percent = 0;

};

