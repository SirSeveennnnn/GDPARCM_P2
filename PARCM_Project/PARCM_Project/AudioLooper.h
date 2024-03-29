#pragma once
#include "AGameObject.h"
#include <SFML/Audio.hpp>

#include <vector>
#include <unordered_map>

using namespace std;

class AudioLooper : public AGameObject
{
public:
	AudioLooper(String name);
	~AudioLooper();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void ToggleMusic(string audioName);

	void StopAllMusic();

private:
	unordered_map<string, sf::Music*> activeLoops;
	unordered_map<string, sf::Music*> musicLoops;
	unordered_map<string, bool> musicStatus;

	void AddMusicToLoop(string audioName);
	void RemoveMusicFromLoop(string audioName);

	float musicDuration = 5500.0f;
	float ticks = 0;
};

