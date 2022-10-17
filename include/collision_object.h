#ifndef __COLLISION_OBJECT_H__
#define __COLLISION_OBJECT_H__

#include <stdbool.h>
#include <ray_tracer.h>
#include <vec.h>
#include <sphere.h>

typedef struct collision_object {
   enum collision_object_type {
      COLLISION_OBJECT_SPHERE,
   } type;
   union collision_object_data {
      Sphere* sphere;
   } data;
} CollisionObject;

pure static __always_inline bool get_collision(const CollisionObject self, const Ray ray, vec4f* out) {
   switch(self.type) {
      case COLLISION_OBJECT_SPHERE:
         return sphere_get_collision(self.data.sphere, ray, out);
      break;
   }
   return false;
}

pure static __always_inline vec4f get_normal(const CollisionObject self, vec4fc point) {
   switch(self.type) {
      case COLLISION_OBJECT_SPHERE:
         return sphere_get_normal(self.data.sphere, point);
      break;
   }
   return (vec4fc){0.0f,0.0f,0.0f,0.0f};
}

pure static __always_inline vec4f get_reflection(const CollisionObject self, vec4fc normal) {
   switch(self.type) {
      case COLLISION_OBJECT_SPHERE:
         return sphere_get_reflection(self.data.sphere, normal);
      break;
   }
   return (vec4fc){0.0f,0.0f,0.0f,0.0f};
}

pure static __always_inline vec4f get_diffraction(const CollisionObject self, vec4fc normal) {
   switch(self.type) {
      case COLLISION_OBJECT_SPHERE:
         return sphere_get_diffraction(self.data.sphere, normal);
      break;
   }
   return (vec4fc){0.0f,0.0f,0.0f,0.0f};
}

#endif
