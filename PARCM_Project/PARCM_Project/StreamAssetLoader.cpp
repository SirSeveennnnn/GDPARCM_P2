#include "StreamAssetLoader.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"
#include "TextureManager.h"
#include <random>

StreamAssetLoader::StreamAssetLoader(string path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->executionEvent = executionEvent;
}

StreamAssetLoader::~StreamAssetLoader()
{
	//cout << "Stream Asset Loader Destroyed" << endl;
}

void StreamAssetLoader::onStartTask()
{

	

	std::vector<string> tokens = StringUtils::split(path, '/');
	string assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	this->executionEvent->onFinishedExecution();

}
