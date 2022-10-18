#ifndef __VEC_H__
#define __VEC_H__

#include <stdio.h>
#include <xmmintrin.h>
#include <math.h>

#ifndef pure
   #ifdef __GNUC__
      #define pure __attribute__((pure))
   #else
      #define pure
   #endif
#endif

#ifndef constfn
   #ifdef __GNUC__
      #define constfn __attribute__((const))
   #else
      #define constfn
   #endif
#endif

#ifdef __GNUC__
   // #define __always_inline __attribute__((always_inline))
#else
   #define __always_inline inline
#endif

typedef __m128 vec4f;
typedef const __m128 vec4fc;

typedef const float cfloat;

typedef struct array4f {
   float data[4];
} array4f;

typedef const array4f array4fc;

constfn static inline vec4f add4f(vec4fc lhs, vec4fc rhs) {
   return _mm_add_ps(lhs, rhs);
}

constfn static inline vec4f sub4f(vec4fc lhs, vec4fc rhs) {
   return _mm_sub_ps(lhs, rhs);
}

constfn static inline vec4f mul4f(vec4fc lhs, vec4fc rhs) {
   return _mm_mul_ps(lhs, rhs);
}

constfn static inline vec4f div4f(vec4fc lhs, vec4fc rhs) {
   return _mm_div_ps(lhs, rhs);
}

/**
 * Multiplies each element of a 4xfloat vector with a scalar number.
 * \param vec The vector to be multiplied.
 * \param num The number to be multipled.
 * \returns The `vec` with each element multiplied by `num`
*/
constfn static inline vec4f mul4fs(vec4fc vec, cfloat num) {
   return mul4f(vec, (vec4fc){num, num, num, num});
}

/**
 * Divides each element of a 4xfloat vector by a scalar number.
 * \param vec The dividend vector.
 * \param num The divider scalar.
 * \returns The `vec` with each element divided by `num`
*/
constfn static inline vec4f div4fs(vec4fc vec, cfloat num) {
   return div4f(vec, (vec4fc){num, num, num, num});
}

/**
 * Multiplies each element of a 4xfloat vector with a scalar number.
 * \param num The number to be multipled.
 * \param vec The vector to be multiplied.
 * \returns The `vec` with each element multiplied by `num`
*/
constfn static inline vec4f mul4sf(cfloat num, vec4fc vec) {
   return mul4fs(vec,num);
}

/**
 * Divides a vector of a scalar number by a 4xfloat vector.
 * \param num The dividend scalar.
 * \param vec The divider vector.
 * \returns <num,num,num,num> with each element divided by the corresponding element of `vec`.
*/
constfn static inline vec4f div4sf(cfloat num, vec4fc vec) {
   return div4fs(vec,num);
}

constfn static inline float dot4f(vec4fc lhs, vec4fc rhs) {
   vec4fc multiplied = mul4f(lhs, rhs);
   vec4fc lo_dual = multiplied;
   vec4fc hi_dual = _mm_movehl_ps(multiplied, multiplied);
   vec4fc sum_dual = add4f(lo_dual, hi_dual);
   vec4fc lo = sum_dual;
   vec4fc hi = _mm_shuffle_ps(sum_dual, sum_dual, 0x1);
   vec4fc sum = add4f(lo,hi);
   return _mm_cvtss_f32(sum);
}

constfn static inline vec4f cross4f(vec4fc lhs, vec4fc rhs) {
   vec4fc tmp0 = _mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(3,0,2,1));
   vec4fc tmp2 = _mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(3,1,0,2));
   vec4fc tmp1 = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3,1,0,2));
   vec4fc tmp3 = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3,0,2,1));
   return sub4f(mul4f(tmp0,tmp1), mul4f(tmp2,tmp3));
}

constfn static inline float len4f(vec4fc self) {
   return sqrtf(dot4f(self,self));
}

constfn static inline vec4f normalize4f(vec4fc self) {
   return div4fs(self,len4f(self));
}

constfn static inline array4f vec4f_to_array4f(vec4fc self) {
   array4f arr;
   _mm_store_ps(&arr.data[0], self);
   return arr;
}

void print4f(vec4fc self);

#endif
