#pragma once
#include"IETThread.h"
#include "IWorkerAction.h"
#include<string>

using namespace std;

class IExecutionEvent;

class StreamAssetLoader : public IWorkerAction
{
public:
	StreamAssetLoader(string path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	string path;
	IExecutionEvent* executionEvent;
};

