#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "ThreadPool.h"
#include "IExecutionEvent.h"

class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;
	typedef std::unordered_map<int, sf::Texture*> SequenceMap;
	
public:
	static TextureManager* getInstance();
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory
	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	int getNumFrames(const String assetName);

	sf::Texture* getStreamTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;
	void instantiateAsTexture(String path, String assetName, bool isStreaming);


	void loadSequence(int index, IExecutionEvent* executionEvent);
	void addToSequence(String path, int index);
	sf::Texture* getSequenceTexture(int index);

	int streamingAssetCount = 0;
private:
	void countStreamingAssets();

	const std::string STREAMING_PATH = "Media/Streaming/";
	const std::string SEQUENCE_PATH = "Media/Sequence/";

	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	SequenceMap sequenceMap;
	HashTable textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;
	ThreadPool* textureThreadPool;

};