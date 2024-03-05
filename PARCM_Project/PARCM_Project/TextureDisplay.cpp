#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include "FadeEffect.h"
#include "LoadingBar.h"

TextureDisplay::TextureDisplay(): AGameObject("TextureDisplay")
{
	
}

void TextureDisplay::initialize()
{
	
}

void TextureDisplay::processInput(sf::Event event)
{
	
}

/*
	if (this->streamingType == StreamingType::BATCH_LOAD && !this->startedStreaming && this->ticks > this->STREAMING_LOAD_DELAY)
	{
		this->startedStreaming = true;
		this->ticks = 0.0f;
		//TextureManager::getInstance()->loadStreamingAssets();
	}
	else if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY)
	{
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed, this);
		this->numDisplayed++;

	}
*/


void TextureDisplay::update(sf::Time deltaTime)
{
	
	//<code here for spawning icon object periodically>
	this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();


	if (this->ticks > this->STREAMING_LOAD_DELAY && index < maxIndex)
	{
		//Trigger Instance Manager
		TextureManager::getInstance()->loadSequence(index, this);
		index++;
		this->ticks = 0.0f;
	}

}

void TextureDisplay::spawnObject()
{
	String objectName = "Icon_" + to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);

	//std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if(this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}
	GameObjectManager::getInstance()->addObject(iconObj);
}

void TextureDisplay::onFinishedExecution()
{
	//this->spawnObject();
	std::cout << "IExecution Event Fired" << std::endl;

	AGameObject* gameObject = GameObjectManager::getInstance()->findObjectByName("LoadingBar");
	LoadingBar* loadingBar = dynamic_cast<LoadingBar*>(gameObject);
	loadingBar->AddProgress();

	finishedLoading++;
	if (finishedLoading == maxIndex)
	{
		//Start fade
		AGameObject* gameObject = GameObjectManager::getInstance()->findObjectByName("FadeEffect");
		FadeEffect* fade = dynamic_cast<FadeEffect*>(gameObject);
		fade->StartFade();
	}
}
