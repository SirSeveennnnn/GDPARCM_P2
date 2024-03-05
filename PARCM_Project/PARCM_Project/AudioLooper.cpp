#include "AudioLooper.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "TextureManager.h"
#include "StringUtils.h"
#include "BaseRunner.h"

AudioLooper::AudioLooper(String name) : AGameObject(name)
{
	
}

AudioLooper::~AudioLooper()
{
	
}

void AudioLooper::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/audio.txt");
	String path;

	while (std::getline(stream, path))
	{
		//Get From File
		std::vector<String> tokens = StringUtils::split(path, '/');
		String audioName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		
		//Create Music
		sf::Music* music = new sf::Music();
		music->openFromFile(path);

		musicLoops.insert({audioName, music});
		musicStatus.insert({audioName, false});

		//Debug
		std::cout << "[AudioLooper] Loaded Audio: " << audioName << std::endl;
	}

}

void AudioLooper::processInput(sf::Event event)
{

}

void AudioLooper::update(sf::Time deltaTime)
{
	ticks += deltaTime.asMilliseconds();

	if (ticks >= musicDuration)
	{
		for (const auto& pair : activeLoops)
		{
			pair.second->play();
		}

		ticks = 0;
	}

}

void AudioLooper::ToggleMusic(string audioName)
{

	if (musicStatus[audioName])
	{
		cout << "Removing: " << audioName << endl;
		RemoveMusicFromLoop(audioName);
	}
	else if (!musicStatus[audioName])
	{
		cout << "Adding: " << audioName << endl;
		AddMusicToLoop(audioName);
	}

	musicStatus[audioName] = !musicStatus[audioName];
	
}

void AudioLooper::StopAllMusic()
{
	for (const auto& pair : activeLoops)
	{
		pair.second->stop();
	}
}

void AudioLooper::AddMusicToLoop(string audioName)
{
	activeLoops.insert({ audioName, musicLoops[audioName]});
}

void AudioLooper::RemoveMusicFromLoop(string audioName)
{
	// Find the element in activeLoops corresponding to the given audioName
	auto it = activeLoops.find(audioName);

	// If the element is found, erase it from activeLoops
	if (it != activeLoops.end())
	{
		activeLoops.erase(it);
	}
}
