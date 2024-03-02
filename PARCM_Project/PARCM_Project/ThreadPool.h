#pragma once
#include <queue>
#include <unordered_map>
#include "IETThread.h"

using namespace std;

class PoolWorkerThread;
class IWorkerAction;

class IFinishedTask {
public:
	virtual void onFinished(int threadID) = 0;
};

class ThreadPool : public IETThread, public IFinishedTask
{
private:
	
public:
	ThreadPool(string name, int numWorkers);
	~ThreadPool();

	void StartScheduler();
	void StopScheduler();
	void ScheduleTask(IWorkerAction* action);

private:
	void run() override;
	void onFinished(int threadID) override;

	string name;
	bool running = false;
	int numWorkers = 0;
	unordered_map<int, PoolWorkerThread*> activeThreads;
	queue<PoolWorkerThread*> inactiveThreads;
	queue<IWorkerAction*> pendingActions;
};

