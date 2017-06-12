/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/math.h,v $
 * $Implementation: ~/src/math/math.cc $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/07/28 16:00:18 $
 * $Description: Vectors math, intersection math $
 *
 * $Log: math.h,v $
 * Revision 1.3  2005/07/28 16:00:18  foxis
 * fixed SQR conflict
 *
 * Revision 1.2  2005/07/14 12:59:56  foxis
 * demo bugfix
 * sln bugfix
 *
 * Revision 1.1.1.1  2005/02/02 15:39:11  foxis
 * sources import
 *
 * Revision 0.4  20050126  13:23:18 FoxiE
 * pertvarkiau tipus, viedoj define dabar inline
 *
 * Revision 0.3  20010823  15:02:08 FoxiE
 * Idejau kelias 2D intersection fun-jas
 *
 * Revision 0.2  20010822  ??:??:?? FoxiE
 * Idejau vector reflection ir refraction fun-jas
 *
 * Revision 0.1  20010814  09:09:04 FoxiE
 * Pradejau rasyti logus :)
 *
 */



#if !defined(__ovrl_OVRLMATH_HPP)
#define __ovrl_OVRLMATH_HPP

#include <math.h>
#include "common/types.h"
#include "common/constants.h"
#include "common/exception.h"

namespace openvrl {

#if defined(__cplusplus)
#if !defined(SQR)
inline 
real SQR(real a) 
{
	return a*a;
}
#endif

inline 
real PROXIMITY(real a, real b)	// was i insane writing this???
{
	return sqrt(SQR(a) - SQR(b));
}
#else
#error @todo: no support for C stype inlines...
#endif /* ifdef __cplusplus */

/**
 *
 */
extern OVRLIBAPI const vector3d_t                VECZERO;
extern OVRLIBAPI const vector3d_t                VECUNITX;
extern OVRLIBAPI const vector3d_t                VECUNITY;
extern OVRLIBAPI const vector3d_t                VECUNITZ;
extern OVRLIBAPI const vector3d_t                VECUNITXYZ;
extern OVRLIBAPI const vector3d_t                VECNEGUNITX;
extern OVRLIBAPI const vector3d_t                VECNEGUNITY;
extern OVRLIBAPI const vector3d_t                VECNEGUNITZ;
extern OVRLIBAPI const vector3d_t                VECNEGUNIT;
extern OVRLIBAPI const vector3d_t                VECNEGUNITXYZ;
extern OVRLIBAPI const vector2d_t                VECZERO_2D;
extern OVRLIBAPI const vector2d_t                VECUNITX_2D;
extern OVRLIBAPI const vector2d_t                VECUNITY_2D;
extern OVRLIBAPI const vector2d_t                VECUNITXY_2D;
extern OVRLIBAPI const vector2d_t                VECNEGUNITX_2D;
extern OVRLIBAPI const vector2d_t                VECNEGUNITY_2D;
extern OVRLIBAPI const vector2d_t                VECNEGUNITXY_2D;

/*************************************************
 *  3d vector math api
 **/

#if defined(__cplusplus)
extern "C" {
#endif

vector3d_t OVRLIBAPI rotate_vector(const vector3d_t&, const vector3d_t&);
vector3d_t OVRLIBAPI scale_vector(const vector3d_t&, const vector3d_t&);
vector2d_t OVRLIBAPI transform_vector(const vector3d_t&);
vector3d_t OVRLIBAPI cross_product(const vector3d_t&, const vector3d_t&);
vector3d_t OVRLIBAPI mul_vector(const vector3d_t&, real);
vector3d_t OVRLIBAPI div_vector(const vector3d_t&, real);
vector3d_t OVRLIBAPI add_vectors(const vector3d_t&, const vector3d_t&);
vector3d_t OVRLIBAPI sub_vectors(const vector3d_t&, const vector3d_t&);
vector3d_t OVRLIBAPI neg_vector(const vector3d_t&);
vector3d_t OVRLIBAPI vector_reflection(const vector3d_t& V, const vector3d_t& N);
vector3d_t OVRLIBAPI vector_refraction(const vector3d_t& V, const vector3d_t& N, real ni, real nt);

#if defined(__cplusplus)
inline real vector_length(const vector3d_t& v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
inline vector3d_t normalize_vector(const vector3d_t& v) {
	return div_vector(v, vector_length(v));
}
inline real dot_product(const vector3d_t& a, const vector3d_t& b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
#else
#error @todo: no support for C stype inlines...
#endif

/*************************************************
 *  2d vector math
 **/
vector2d_t OVRLIBAPI rotate_vector_2d(const vector2d_t&, real);
vector2d_t OVRLIBAPI scale_vector_2d(const vector2d_t&, const vector2d_t&);
vector2d_t OVRLIBAPI mul_vector_2d(const vector2d_t&, real);
vector2d_t OVRLIBAPI div_vector_2d(const vector2d_t&, real);
vector2d_t OVRLIBAPI add_vectors_2d(const vector2d_t&, const vector2d_t&);
vector2d_t OVRLIBAPI sub_vectors_2d(const vector2d_t&, const vector2d_t&);
vector2d_t OVRLIBAPI neg_vector_2d(const vector2d_t&);
vector3d_t OVRLIBAPI vector_reflection_2d(const vector2d_t& V, const vector2d_t& N);
vector3d_t OVRLIBAPI vector_refraction_2d(const vector2d_t& V, const vector2d_t& N, real ni, real nt);

#if defined(__cplusplus)
inline real vector_length_2d(const vector2d_t& v) {
	return sqrt(v.x*v.x + v.y*v.y);
}
inline vector2d_t normalize_vector_2d(const vector2d_t& v) {
	return div_vector_2d(v, vector_length_2d(v));
}
inline real dot_product_2d(const vector2d_t& a, const vector2d_t& b) {
	return a.x*b.x + a.y*b.y;
}
inline real perp_dot_product_2d(const vector2d_t& a, const vector2d_t& b) {
	return a.x*b.y - a.y*b.x;
}
#endif


/*************************************************
 *  3D Intersection mathematics
 */

/*************************************************
 *  2D Intersection mathematics
 */

/**
 *  Finds out if a point lies on a segment defined by two points
 */
bool OVRLIBAPI point_in_segment_2d(const vector2d_t& P1, const vector2d_t& P2, const vector2d_t& P);

/**
 *  Finds out if a point lies on a ray defined by two points
 */
bool OVRLIBAPI point_in_ray_2d(const vector2d_t& P1, const vector2d_t& P2, const vector2d_t& P);

/**
 *  intersection result flags
 */
enum INTERSECTION_enum {
     INTERSECTION_NONE,         /* no intersection */
     INTERSECTION_YES,          /* intersection */
     INTERSECTION_OVERLAP       /* overlapping */
};
typedef INTERSECTION_enum INTERSECTION_t;

/** 2d line segment to line segment
 *
 *  P1-P2  - first line segment  [in]
 *  Q1-Q2  - second line segment [in]
 *  I1      - intersection point  [out]
 *  I1-I2   - the resulting segment of two overlaping segments
 *  return:
 *   INTERSECTION_NONE
 *   INTERSECTION_YES
 *   INTERSECTION_OVERLAP
 */
INTERSECTION_t OVRLIBAPI
intersection_line_to_line_2d(const vector2d_t& P1, const vector2d_t& P2,
        const vector2d_t& Q1, const vector2d_t& Q2,
        vector2d_t* I1, vector2d_t* I2);

/** 2d ray to line segment
 *
 *  P1, P2  - two points which lie on the ray  [in]
 *  Q1-Q2  - line segment [in]
 *  I      - intersection point  [out]
 *  return:
 *   INTERSECTION_NONE
 *   INTERSECTION_YES
 *   INTERSECTION_OVERLAP
 */
INTERSECTION_t OVRLIBAPI
intersection_ray_to_line_2d(const vector2d_t& P1, const vector2d_t& P2,
        const vector2d_t& Q1, const vector2d_t& Q2,
        vector2d_t* I1, vector2d_t* I2);

/** 2d ray to ray
 *
 *  P1, P2  - two points which lie on the first ray  [in]
 *  Q1, Q2  - two points which lie on the second ray  [in]
 *  I      - intersection point  [out]
 *  return:
 *   INTERSECTION_NONE
 *   INTERSECTION_YES
 *   INTERSECTION_OVERLAP
 */
INTERSECTION_t OVRLIBAPI
intersection_ray_to_ray_2d(const vector2d_t& P1, const vector2d_t& P2,
        const vector2d_t& Q1, const vector2d_t& Q2,
        vector2d_t* I1, vector2d_t* I2);

#if defined(__cplusplus)
};
#endif /* ifdef __cplusplus */



/*************************************************
 *  Overloaded operators
 */
#if defined(__cplusplus)

// ]--=[ DRGB_t operators
inline DRGB_t operator+(const DRGB_t& a, const DRGB_t& b)
{
   DRGB_t tmp;
   tmp.r = a.r + b.r;
   tmp.g = a.g + b.g;
   tmp.b = a.b + b.b;
   tmp.a = a.a + b.a;
   return tmp;
}

inline DRGB_t operator-(const DRGB_t& a, const DRGB_t& b)
{
   DRGB_t tmp;
   tmp.r = a.r - b.r;
   tmp.g = a.g - b.g;
   tmp.b = a.b - b.b;
   tmp.a = a.a - b.a;
   return tmp;
}

inline DRGB_t operator*(const DRGB_t& a, const DRGB_t& b)
{
   DRGB_t tmp;
   tmp.r = a.r * b.r;
   tmp.g = a.g * b.g;
   tmp.b = a.b * b.b;
   tmp.a = a.a * b.a;
   return tmp;
}

inline DRGB_t operator/(const DRGB_t& a, const DRGB_t& b)
{
   DRGB_t tmp;
   tmp.r = a.r / b.r;
   tmp.g = a.g / b.g;
   tmp.b = a.b / b.b;
   tmp.a = a.a / b.a;
   return tmp;
}

inline DRGB_t operator*(const DRGB_t& a, const real b)
{
   DRGB_t tmp;
   tmp.r = (short_real)(a.r * b);
   tmp.g = (short_real)(a.g * b);
   tmp.b = (short_real)(a.b * b);
   tmp.a = (short_real)(a.a * b);
   return tmp;
}

inline DRGB_t operator/(const DRGB_t& a, const real b)
{
   DRGB_t tmp;
   tmp.r = (short_real)(a.r / b);
   tmp.g = (short_real)(a.g / b);
   tmp.b = (short_real)(a.b / b);
   tmp.a = (short_real)(a.a / b);
   return tmp;
}

inline DRGB_t& operator+=(DRGB_t& a, const DRGB_t& b)
{
   a.r = a.r + b.r;
   a.g = a.g + b.g;
   a.b = a.b + b.b;
   a.a = a.a + b.a;
   return a;
}

inline DRGB_t& operator-=(DRGB_t& a, const DRGB_t& b)
{
   a.r = a.r - b.r;
   a.g = a.g - b.g;
   a.b = a.b - b.b;
   a.a = a.a - b.a;
   return a;
}

inline DRGB_t& operator*=(DRGB_t& a, const DRGB_t& b)
{
   a.r = a.r * b.r;
   a.g = a.g * b.g;
   a.b = a.b * b.b;
   a.a = a.a * b.a;
   return a;
}

inline DRGB_t& operator/=(DRGB_t& a, const DRGB_t& b)
{
   a.r = a.r / b.r;
   a.g = a.g / b.g;
   a.b = a.b / b.b;
   a.a = a.a / b.a;
   return a;
}

inline DRGB_t& operator*=(DRGB_t& a, const real b)
{
   a.r = (short_real)(a.r * b);
   a.g = (short_real)(a.g * b);
   a.b = (short_real)(a.b * b);
   a.a = (short_real)(a.a * b);
   return a;
}

inline DRGB_t& operator/=(DRGB_t& a, const real b)
{
   a.r = (short_real)(a.r / b);
   a.g = (short_real)(a.g / b);
   a.b = (short_real)(a.b / b);
   a.a = (short_real)(a.a / b);
   return a;
}

inline bool operator==(const DRGB_t& a, const DRGB_t& b)
{
  return ( a.r==b.r && a.g==b.g && a.b==b.b && a.a==b.a ) ? true : false;
}

inline bool operator!=(const DRGB_t& a, const DRGB_t& b)
{
  return ( a==b )?false:true;
}

// ]--=[ vector3d_t operators
inline vector3d_t operator+(const vector3d_t& a, const vector3d_t& b)
{
   vector3d_t tmp;
   tmp.x = a.x + b.x;
   tmp.y = a.y + b.y;
   tmp.z = a.z + b.z;
   return tmp;
}

inline vector3d_t operator-(const vector3d_t& a, const vector3d_t& b)
{
   vector3d_t tmp;
   tmp.x = a.x - b.x;
   tmp.y = a.y - b.y;
   tmp.z = a.z - b.z;
   return tmp;
}

inline vector3d_t operator*(const vector3d_t& a, const vector3d_t& b)
{
   vector3d_t tmp;
   tmp.x = a.x * b.x;
   tmp.y = a.y * b.y;
   tmp.z = a.z * b.z;
   return tmp;
}

inline vector3d_t operator/(const vector3d_t& a, const vector3d_t& b)
{
   vector3d_t tmp;
   tmp.x = a.x / b.x;
   tmp.y = a.y / b.y;
   tmp.z = a.z / b.z;
   return tmp;
}

inline vector3d_t operator*(const vector3d_t& a, const real b)
{
   vector3d_t tmp;
   tmp.x = a.x * b;
   tmp.y = a.y * b;
   tmp.z = a.z * b;
   return tmp;
}

inline vector3d_t operator/(const vector3d_t& a, const real b)
{
   vector3d_t tmp;
   tmp.x = a.x / b;
   tmp.y = a.y / b;
   tmp.z = a.z / b;
   return tmp;
}

inline vector3d_t& operator+=(vector3d_t& a, const vector3d_t& b)
{
   a.x = a.x + b.x;
   a.y = a.y + b.y;
   a.z = a.z + b.z;
   return a;
}

inline vector3d_t& operator-=(vector3d_t& a, const vector3d_t& b)
{
   a.x = a.x - b.x;
   a.y = a.y - b.y;
   a.z = a.z - b.z;
   return a;
}

inline vector3d_t& operator*=(vector3d_t& a, const vector3d_t& b)
{
   a.x = a.x * b.x;
   a.y = a.y * b.y;
   a.z = a.z * b.z;
   return a;
}

inline vector3d_t& operator/=(vector3d_t& a, const vector3d_t& b)
{
   a.x = a.x / b.x;
   a.y = a.y / b.y;
   a.z = a.z / b.z;
   return a;
}

inline vector3d_t& operator*=(vector3d_t& a, const real b)
{
   a.x = a.x * b;
   a.y = a.y * b;
   a.z = a.z * b;
   return a;
}

inline vector3d_t& operator/=(vector3d_t& a, const real b)
{
   a.x = a.x / b;
   a.y = a.y / b;
   a.z = a.z / b;
   return a;
}

inline bool operator==(const vector3d_t& a, const vector3d_t& b)
{
  return ( a.x==b.x && a.y==b.y && a.z==b.z ) ? true : false;
}

inline bool operator!=(const vector3d_t& a, const vector3d_t& b)
{
  return ( a==b )?false:true;
}

// ]--=[ vector2d_t operators
inline vector2d_t operator+(const vector2d_t& a, const vector2d_t& b)
{
   vector2d_t tmp;
   tmp.x = a.x + b.x;
   tmp.y = a.y + b.y;
   return tmp;
}

inline vector2d_t operator-(const vector2d_t& a, const vector2d_t& b)
{
   vector2d_t tmp;
   tmp.x = a.x - b.x;
   tmp.y = a.y - b.y;
   return tmp;
}

inline vector2d_t operator*(const vector2d_t& a, const vector2d_t& b)
{
   vector2d_t tmp;
   tmp.x = a.x * b.x;
   tmp.y = a.y * b.y;
   return tmp;
}

inline vector2d_t operator/(const vector2d_t& a, const vector2d_t& b)
{
   vector2d_t tmp;
   tmp.x = a.x / b.x;
   tmp.y = a.y / b.y;
   return tmp;
}

inline vector2d_t operator*(const vector2d_t& a, const real b)
{
   vector2d_t tmp;
   tmp.x = a.x * b;
   tmp.y = a.y * b;
   return tmp;
}

inline vector2d_t operator/(const vector2d_t& a, const real b)
{
   vector2d_t tmp;
   tmp.x = a.x / b;
   tmp.y = a.y / b;
   return tmp;
}

inline vector2d_t& operator+=(vector2d_t& a, const vector2d_t& b)
{
   a.x = a.x + b.x;
   a.y = a.y + b.y;
   return a;
}

inline vector2d_t& operator-=(vector2d_t& a, const vector2d_t& b)
{
   a.x = a.x - b.x;
   a.y = a.y - b.y;
   return a;
}

inline vector2d_t& operator*=(vector2d_t& a, const vector2d_t& b)
{
   a.x = a.x * b.x;
   a.y = a.y * b.y;
   return a;
}

inline vector2d_t& operator/=(vector2d_t& a, const vector2d_t& b)
{
   a.x = a.x / b.x;
   a.y = a.y / b.y;
   return a;
}

inline vector2d_t& operator*=(vector2d_t& a, const real b)
{
   a.x = a.x * b;
   a.y = a.y * b;
   return a;
}

inline vector2d_t& operator/=(vector2d_t& a, const real b)
{
   a.x = a.x / b;
   a.y = a.y / b;
   return a;
}

inline bool operator==(const vector2d_t& a, const vector2d_t& b)
{
  return ( a.x==b.x && a.y==b.y ) ? true : false;
}

inline bool operator!=(const vector2d_t& a, const vector2d_t& b)
{
  return ( a==b )?false:true;
}

#else
#error @todo: no support for C stype inlines...
#endif

};

#endif /* ifndef __ovrl_OVRLMATH_HPP */
