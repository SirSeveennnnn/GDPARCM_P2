#include <stddef.h>
#include "GameObjectManager.h"
#include <iostream>
#include "VideoObject.h"
#include "FPSCounter.h"

#include <SFML/Audio.hpp>

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new GameObjectManager();
	}

	return sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(AGameObject::String name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

List GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->gameObjectList.size();
}

void GameObjectManager::processInput(sf::Event event) {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		this->gameObjectList[i]->processInput(event);
	}
}

void GameObjectManager::update(sf::Time deltaTime)
{
	//std::cout << "Delta time: " << deltaTime.asSeconds() << "\n";
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		this->gameObjectList[i]->update(deltaTime);
	}
}

//draws the object if it contains a sprite
void GameObjectManager::draw(sf::RenderWindow* window) {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		this->gameObjectList[i]->draw(window);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	//also initialize the oject
	this->gameObjectMap[gameObject->getName()] = gameObject;
	this->gameObjectList.push_back(gameObject);
	this->gameObjectMap[gameObject->getName()]->initialize();
}

//also frees up allocation of the object.
void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}
	
	delete gameObject;
}

void GameObjectManager::deleteObjectByName(AGameObject::String name) {
	AGameObject* object = this->findObjectByName(name);
	
	if (object != NULL) {
		this->deleteObject(object);
	}
}

void GameObjectManager::deleteAllGameObjects()
{
	this->gameObjectMap.clear();

	// Delete each object in the list
	for (AGameObject* gameObject : this->gameObjectList) {
		delete gameObject;
	}

	// Clear the list
	this->gameObjectList.clear();
}

void GameObjectManager::InitializeMainMenu()
{
	VideoObject* videoObject = new VideoObject("VideoObject");
	videoObject->setPosition(0, 0);
	sharedInstance->addObject(videoObject);

	FPSCounter* fpsCounter = new FPSCounter();
	sharedInstance->addObject(fpsCounter);

	sf::Music* soundTrack = new sf::Music();
	soundTrack->openFromFile("Media/Audio/soundtrack.mp3");
	soundTrack->play();

}
