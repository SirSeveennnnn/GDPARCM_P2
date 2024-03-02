#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "RTImage.h"
#include "RTThread.h"
#include <iostream>
#include <vector>
#include "RTSemaphore.h"

class camera {
public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    image_width = 100;  // Rendered image width in pixel count
    int    samples_per_pixel = 10;   // Count of random samples for each pixel
    int    max_depth = 10;   // Maximum number of ray bounces into scene

    double vfov = 90;  // Vertical view angle (field of view)

    point3 lookfrom = point3(0, 0, -1);  // Point camera is looking from
    point3 lookat = point3(0, 0, 0);   // Point camera is looking at
    vec3   vup = vec3(0, 1, 0);     // Camera-relative "up" direction

    double defocus_angle = 0;  // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus

    RTImage* image;
    hittable* world;
    std::vector<RTThread*> threadList;
    RTSemaphore* image_semaphore;
    

    void render(hittable& world) {
        initialize();
        this->world = &world;
        image_semaphore = new RTSemaphore();
        //std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
          
            RTThread* thread = new RTThread(j, this, image_semaphore);
            thread->start();

            threadList.push_back(thread);
            /*
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }

                image->setPixel(i, j, pixel_color.x(), pixel_color.y(), pixel_color.z(), samples_per_pixel);
            }
              */
        }
        
        while (true) // Infinite loop, will break when no thread is running
        {
            bool anyThreadRunning = false; // Flag to track if any thread is running

            
            for (int i = 0; i < threadList.size(); i++)
            {
                if (threadList[i]->isRunning)
                {
                    std::cout << "Thread " << threadList[i]->id << " is still running" << std::endl;
                }
                else
                {
                    std::cout << "Thread " << threadList[i]->id << " is done" << std::endl;
                }
            }
             

            for (int i = 0; i < threadList.size(); i++)
            {
                if (threadList[i]->isRunning)
                {
                    anyThreadRunning = true; // Set the flag to true if any thread is running
                    break; // Exit the for loop early
                }
            }

            if (!anyThreadRunning)
            {
                cv::String fileName = "E:/.School/GDPARCM/GDPARCM_Macuha/PARCM_Project/ImageRender.png";
                image->saveImage(fileName);
                std::cout << "ALL THREAD COMPLETED" << std::endl;
               
                break;
            }
        }
         
        //Delete threads
        for (int i = 0; i < threadList.size(); i++)
        {
            delete threadList[i];
        }


    }

    ray get_ray(int i, int j) const {
        // Get a randomly-sampled camera ray for the pixel at location i,j, originating from
        // the camera defocus disk.

        // Get a randomly sampled camera ray for the pixel at location i,j.
        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto pixel_sample = pixel_center + pixel_sample_square();

        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        hit_record rec;

        if (depth <= 0)
            return color(0, 0, 0);

        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth - 1, world);
            return color(0, 0, 0);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }

private:
    cv::String fileName = "E:/.School/GDPARCM/GDPARCM/PARCM_Project/ImageRender.png";

    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    vec3   u, v, w;        // Camera frame basis vectors

    vec3   defocus_disk_u;  // Defocus disk horizontal radius
    vec3   defocus_disk_v;  // Defocus disk vertical radius

    

    void initialize() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = lookfrom;

        // Determine viewport dimensions.
       
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
        vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;

        image = new RTImage(image_width, image_height);
    }

    

    point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    vec3 pixel_sample_square() const {
        // Returns a random point in the square surrounding a pixel at the origin.
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

   


};

#endif