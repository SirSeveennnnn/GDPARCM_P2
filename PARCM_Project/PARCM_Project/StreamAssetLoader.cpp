#include "StreamAssetLoader.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"
#include "TextureManager.h"
#include <random>

StreamAssetLoader::StreamAssetLoader(string path, int index, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->executionEvent = executionEvent;
	this->index = index;
}

StreamAssetLoader::~StreamAssetLoader()
{
	//cout << "Stream Asset Loader Destroyed" << endl;
}

void StreamAssetLoader::onStartTask()
{
	IETThread::sleep(200);
	TextureManager::getInstance()->addToSequence(path, index);
	this->executionEvent->onFinishedExecution();

}


