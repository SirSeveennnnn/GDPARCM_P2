#include "RTThread.h"
#include "camera.h"
#include "RTSemaphore.h"
#include <iostream>

using namespace std;

RTThread::RTThread(int id, camera* camera, RTSemaphore* semaphore)
{
    this->id = id;
	this->cam = camera;
    this->semaphore = semaphore;

}

RTThread::~RTThread()
{
}

void RTThread::run()
{
    cout << "Thread " << this->id << " has started" << endl;
    isRunning = true;

    std::vector<cv::Vec3b> rowPixels;
    for (int i = 0; i < cam->image_width; ++i) {
         color pixel_color(0, 0, 0);
         for (int sample = 0; sample < cam->samples_per_pixel; ++sample) {
              ray r = cam->get_ray(i, id);
              pixel_color += cam->ray_color(r, cam->max_depth, *cam->world);
          }

            // Scale and store the pixel color
      
          rowPixels.push_back(cv::Vec3b(pixel_color.z(), pixel_color.y(), pixel_color.x()));
    }
       
    semaphore->acquire();
    std::cout << "Thread " << id << " has acquired a permit!" << std::endl;

    cam->image->setRow(id, rowPixels, cam->samples_per_pixel);
    semaphore->release();

    isRunning = false;
  
}
