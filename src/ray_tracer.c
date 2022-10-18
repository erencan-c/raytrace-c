#include <collision_object.h>
#include <ray_tracer.h>

pixel_position_function pixel_positon = plane_pixel_position;

constfn vec4f plane_pixel_position(const ScreenPlane self, const size_t x, const size_t y) {
   cfloat x_ratio = (float)x / (float)self.resolution.width;
   cfloat y_ratio = (float)y / (float)self.resolution.height;
   return add4f(self.top_left_corner, add4f(mul4fs(self.right, x_ratio), mul4fs(self.down, y_ratio)));
}

vec4fc vec127 = {127.0f, 127.0f, 127.0f, 127.0f};
vec4fc vec128 = {128.0f, 128.0f, 128.0f, 128.0f};

pure Color trace_ray(
   const Ray self,
   size_t objects_len,
   CollisionObject* const objects,
   const size_t depth
) {
   vec4f collision_point = {0.0f};
   vec4f normal;
   vec4f reflection_ray, diffraction_ray;
   NOT_UNUSED(depth);
   NOT_UNUSED(reflection_ray);
   NOT_UNUSED(diffraction_ray);
   CollisionObject object = {0};
   for(size_t i = 0; i < objects_len; i++) {
      object = objects[i];
      if(get_collision(object, self, &collision_point)) {
         normal = get_normal(object, collision_point);
         // return (Color){.r = 0xFF, .g = 0xFF, .b = 0xFF};
         array4fc arr_normal = vec4f_to_array4f(add4f(mul4f(normal, vec127), vec128));
         // return (Color){.as_integer = 0xFF000000};
         return (Color){
            .r = arr_normal.data[0],
            .g = arr_normal.data[1],
            .b = arr_normal.data[2],
            .a = 0xFF
         };
         // reflection_ray = get_reflection(object, normal);
         // diffraction_ray = get_diffraction(object, normal);
      } else {
         // return (Color){.as_integer = 0xFF000000};
      }
   }
   // if(depth == 0) {
      return (Color){.as_integer = 0xFFFF00FF};
   // }
}
