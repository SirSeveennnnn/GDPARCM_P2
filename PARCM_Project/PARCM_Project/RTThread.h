#pragma once
#include "IETThread.h"


class camera;
class RTSemaphore;

class RTThread : public IETThread
{
public:
	RTThread(int id, camera* camera, RTSemaphore* semaphore);
	~RTThread();
	bool isRunning = false;
	int id;

private:
	void run();

	RTSemaphore* semaphore;
	camera* cam = nullptr;
	 
};

