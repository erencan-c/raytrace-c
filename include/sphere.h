#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <vec.h>

typedef struct sphere Sphere;

#ifdef __GNUC__
   struct sphere {
      vec4f position;
      float radius;
   } __attribute__((aligned(16)));
#elif _MSC_VER
   #pragma pack(push,16)
   struct sphere {
      vec4f position;
      float radius;
   };
#endif

#include <ray_tracer.h>
pure bool sphere_get_collision(const Sphere* const self, Ray ray, vec4f* const out);
pure vec4f sphere_get_normal(const Sphere* const self, vec4fc point);
pure vec4f sphere_get_reflection(const Sphere* const self, vec4fc point);
pure vec4f sphere_get_diffraction(const Sphere* const self, vec4fc point);
pure Sphere new_sphere(vec4fc position, cfloat radius);

#endif