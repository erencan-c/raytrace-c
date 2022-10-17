#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ppm.h>
#include <vec.h>
#include <ray_tracer.h>
#include <collision_object.h>
#include <sphere.h>
#include <sys/time.h>

#ifndef NOT_UNUSED
   #define NOT_UNUSED(x) ((void)(x))
#endif

#define WIDTH 800
#define HEIGHT 800

int main() {
   struct timeval start, stop;
   gettimeofday(&start, NULL);

   ScreenPlane scr = {
      .resolution = (Point2){.width = WIDTH, .height = HEIGHT},
      .top_left_corner = {-0.5f, 0.5f, 0.0f, 0.0f},
      .down = {0.0f, -1.0f, 0.0f, 0.0f},
      .right = {1.0f, 0.0f, 0.0f, 0.0f},
   };
   Camera cam = {
      .focal_position = {0.0f, 0.0f, -1.0f, 0.0f},
   };
   PPM* ppm = PPM_new(WIDTH, HEIGHT);

   CollisionObject* objects = calloc(1, sizeof(*objects));
   Sphere my_sphere = new_sphere((vec4fc){1.0f, 1.0f, 3.0f, 0.0f}, 1.0f);
   objects[0] = (CollisionObject){.type = COLLISION_OBJECT_SPHERE, .data.sphere = &my_sphere};
   
   for(size_t i = 0; i < ppm->row; i++) {
      for(size_t j = 0; j < ppm->col; j++) {
         vec4fc pixel_pos = pixel_positon(scr, i, j);
         Ray traced = {
            .start = cam.focal_position,
            .direction = sub4f(pixel_pos, cam.focal_position),
         };
         // print4f(traced.start);
         Color color = trace_ray(traced, 1, objects, 6);
         PIXEL(ppm, i, j) = (PPM_Color){.r = color.r, .g = color.g, .b = color.b};
      }
   }

   gettimeofday(&stop, NULL);
   printf("%lu\n", (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec));

   // PPM_write(ppm, "deneme.ppm");
   return 0;
}
