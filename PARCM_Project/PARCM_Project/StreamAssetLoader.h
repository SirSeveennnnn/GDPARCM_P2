#pragma once
#include"IETThread.h"
#include "IWorkerAction.h"
#include<string>

using namespace std;

class IExecutionEvent;

class StreamAssetLoader : public IWorkerAction
{
public:
	StreamAssetLoader(string path, int index, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	int index;
	string path;
	IExecutionEvent* executionEvent;
};

