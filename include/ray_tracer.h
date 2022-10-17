#ifndef __RAY_TRACER_H__
#define __RAY_TRACER_H__

#include <vec.h>
#include <stdint.h>
#include <stddef.h>

#ifndef NOT_UNUSED
   #define NOT_UNUSED(x) ((void)(x))
#endif

#ifndef constfn
   #ifdef __GNUC__
      #define constfn __attribute__((const))
   #else
      #define constfn
   #endif
#endif

typedef union point2 {
   struct {
      size_t x,y;
   };
   struct {
      size_t width,height;
   };
} Point2;

typedef union color {
   struct {
      uint8_t r,g,b,a;
   };
   uint8_t as_array[4];
   uint32_t as_integer;
} Color;

typedef struct screen_plane {
   vec4f top_left_corner;
   vec4f right;
   vec4f down;
   Point2 resolution;
} ScreenPlane;

typedef struct camera {
   vec4f focal_position;
   vec4f up;
   vec4f back_vision;
   vec4f side;
} Camera;

typedef struct ray {
   vec4f start;
   vec4f direction;
} Ray;

typedef vec4f (*pixel_position_function)(const ScreenPlane self, const size_t x, const size_t y);

extern pixel_position_function pixel_positon;

constfn static __always_inline vec4f cast_ray(const Ray self, cfloat t) {
   return add4f(self.start, mul4sf(t, self.direction));
}

constfn vec4f plane_pixel_position(const ScreenPlane self, const size_t x, const size_t y);

typedef struct collision_object CollisionObject;
// #include <collision_object.h>

pure Color trace_ray(const Ray self, size_t objects_len, CollisionObject* const objects, const size_t depth);

#endif
