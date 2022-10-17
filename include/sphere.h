#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <vec.h>

typedef struct sphere Sphere;

struct sphere {
   vec4f position;
   float radius;
} __attribute__((aligned(16)));

#include <ray_tracer.h>

pure static __always_inline bool sphere_get_collision(Sphere* const self, Ray ray, vec4f* const out) {
   vec4fc C = self->position;
   cfloat r = self->radius;
   vec4fc o = ray.start;
   vec4fc u = ray.direction;

   cfloat a = dot4f(u,u);
   vec4fc oc = sub4f(o,C);
   cfloat b = 2.0f * dot4f(u, oc);
   cfloat c = dot4f(oc,oc) - (r*r);

   cfloat discriminant = (b*b) - (4.0f*a*c);
   if(discriminant < 0.0f) {
      return false;
   }
   *out = cast_ray(ray, ((-b) - sqrtf(discriminant)) / (2.0f * a));
   return true;
}

pure static __always_inline vec4f sphere_get_normal(Sphere* const self, vec4fc point) {
   return normalize4f(sub4f(point, self->position));
}

pure static __always_inline vec4f sphere_get_reflection(Sphere* const self, vec4fc point) {
   NOT_UNUSED(self);
   NOT_UNUSED(point);
   return (vec4f){0.0f};
}

pure static __always_inline vec4f sphere_get_diffraction(Sphere* const self, vec4fc point) {
   NOT_UNUSED(self);
   NOT_UNUSED(point);
   return (vec4f){0.0f};
}

pure static __always_inline Sphere new_sphere(vec4fc position, float radius) {
   return (Sphere){.position = position, .radius = radius};
}

#endif