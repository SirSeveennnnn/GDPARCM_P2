
#include <iostream>
#include "BaseRunner.h"
int main() {
	BaseRunner runner;
	runner.run();
    
    
}

/*
#include "opencv2/core.hpp"
#include <iostream>
#include <opencv2/imgcodecs.hpp>

#include "RTImage.h"


#include "rtweekend.h"
#include "camera.h"
#include "color.h"
#include "hittablelist.h"
#include "material.h"
#include "sphere.h"


int main() {
    
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  
    for (int a = -6; a < 6; a++) {
        for (int b = -6; b < 6; b++) {

            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    } 
    

    auto material1 = make_shared<dielectric>(1.5);
    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    auto material4 = make_shared<metal>(color(0.9, 0.9, 0.9), 0.0);

    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material2));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material3));
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material4));
    world.add(make_shared<sphere>(point3(-8, 1, 0), 1.0, material1));

    camera* cam = new camera();

    cam->aspect_ratio = 1.0 / 1.0;
    cam->image_width = 1080;
    cam->samples_per_pixel = 100;
    cam->max_depth = 10;

    cam->vfov = 30;
    cam->lookfrom = point3(10, 1, 3);
    cam->lookat = point3(0, 1, 0);
    cam->vup = vec3(0, 1, 0);

    cam->defocus_angle = 6.0f;
    cam->focus_dist = 6.5f;

    cam->render(world);
}
*/
