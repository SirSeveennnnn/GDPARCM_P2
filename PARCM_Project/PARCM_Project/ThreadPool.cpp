#include "ThreadPool.h"
#include "PoolWorkerThread.h"
#include "IWorkerAction.h"

ThreadPool::ThreadPool(string name, int numWorkers)
{
	this->name = name;
	this->numWorkers = numWorkers;
	for (int i = 0; i < this->numWorkers; i++)
	{
		this->inactiveThreads.push(new PoolWorkerThread(i, this));
	}

	std::cout << "Number of Threads Created: " << this->numWorkers << std::endl;
}

ThreadPool::~ThreadPool()
{
	this->StopScheduler();
	this->activeThreads.clear();
	while (this->inactiveThreads.empty() == false)
	{
		this->inactiveThreads.pop();
	}
}

void ThreadPool::StartScheduler()
{
	this->running = true;
	this->start();
}

void ThreadPool::StopScheduler()
{
	this->running = false;
}

void ThreadPool::ScheduleTask(IWorkerAction* action)
{
	this->pendingActions.push(action);
	
}

void ThreadPool::run()
{

	while (this->running)
	{

		if (this->pendingActions.empty() == false)
		{

			if (this->inactiveThreads.empty() == false)
			{
				PoolWorkerThread* workerThread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[workerThread->getThreadID()] = workerThread;

				workerThread->assignTask(this->pendingActions.front());
				workerThread->start();
				this->pendingActions.pop();

			}
			else
			{
				//std::cout << "ThreadPool: " << this->name << " No more available threads. Threads: " << this->inactiveThreads.size() << std::endl;
			}
		}
		else
		{
			//std::cout << "ThreadPool: " << this->name << " No jobs scheduled." << std::endl;
		}
	}

}

void ThreadPool::onFinished(int threadID)
{

	if (this->activeThreads[threadID] != nullptr)
	{
		
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));
	}
}
