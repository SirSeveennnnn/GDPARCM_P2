#include <fstream>
#include <iostream>
#include <filesystem>
#include "TextureManager.h"
#include "StringUtils.h"
#include "StreamAssetLoader.h"


//a singleton class
TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

TextureManager::TextureManager()
{
	this->countStreamingAssets();
	this->textureThreadPool = new ThreadPool("Texture Thread Pool", 10);
	this->textureThreadPool->StartScheduler();
}

void TextureManager::loadFromAssetList()
{
	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String path;

	while(std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, false);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}

void TextureManager::loadSingleStreamAsset(int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;
	
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if(index == fileNum)
		{
			//StreamAssetLoader* assetLoader = new StreamAssetLoader(entry.path().string(), executionEvent);
			//this->textureThreadPool->ScheduleTask(assetLoader);

			break;
		}

		fileNum++;
	}
}

sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName][frameIndex];
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return NULL;
	}
}

int TextureManager::getNumFrames(const String assetName)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName].size();
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::getStreamTextureFromList(const int index)
{
	return this->streamTextureList[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return this->streamTextureList.size();
}

void TextureManager::countStreamingAssets()
{
	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->streamingAssetCount++;
	}
	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
}

void TextureManager::instantiateAsTexture(String path, String assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	this->textureMap[assetName].push_back(texture);

	if(isStreaming)
	{
		this->streamTextureList.push_back(texture);
	}
	else
	{
		this->baseTextureList.push_back(texture);
	}
	
}

void TextureManager::loadSequence(int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(SEQUENCE_PATH)) {
		
		if (index == fileNum)
		{
			std::cout << "Found Index: " << index << " and FileNum: " << fileNum << std::endl << " Path is: " << entry.path().string() << std::endl;
			StreamAssetLoader* assetLoader = new StreamAssetLoader(entry.path().string(), index, executionEvent);
			this->textureThreadPool->ScheduleTask(assetLoader);
			break;
		}

		fileNum++;
	
	}

}

void TextureManager::addToSequence(String path, int index)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);

	sequenceMap.insert({index, texture });
}

sf::Texture* TextureManager::getSequenceTexture(int index)
{
	return sequenceMap[index];
}
