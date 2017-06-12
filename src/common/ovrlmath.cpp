#include <math.h>
#include "common/math.h"

namespace openvrl {

/**
 *
 */
const vector3d_t                openvrl::VECZERO  = {0,0,0};
const vector3d_t                openvrl::VECUNITX = {1,0,0};
const vector3d_t                openvrl::VECUNITY = {0,1,0};
const vector3d_t                openvrl::VECUNITZ = {0,0,1};
const vector3d_t                openvrl::VECUNITXYZ = {1,1,1};
const vector3d_t                openvrl::VECNEGUNITX = {-1,0,0};
const vector3d_t                openvrl::VECNEGUNITY = {0,-1,0};
const vector3d_t                openvrl::VECNEGUNITZ = {0,0,-1};
const vector3d_t                openvrl::VECNEGUNIT = {-1,-1,-1};
const vector3d_t                openvrl::VECNEGUNITXYZ = {-1,-1,-1};
const vector2d_t                openvrl::VECZERO_2D  = {0,0};
const vector2d_t                openvrl::VECUNITX_2D = {1,0};
const vector2d_t                openvrl::VECUNITY_2D = {0,1};
const vector2d_t                openvrl::VECUNITXY_2D = {1,1};
const vector2d_t                openvrl::VECNEGUNITX_2D = {-1,0};
const vector2d_t                openvrl::VECNEGUNITY_2D = {0,-1};
const vector2d_t                openvrl::VECNEGUNITXY_2D = {-1,-1};

/*************************************************
 *  3D vector math
 */
vector3d_t OVRLIBAPI rotate_vector(const vector3d_t& v, const vector3d_t& a)
{
  vector3d_t tmp = v;
  real x,y,z, c,s, ax, ay, az;

  ax = a.x;
  ay = a.y;
  az = a.z;

  y = tmp.y;
  z = tmp.z;
  c = cos(ax);
  s = sin(ax);
  tmp.y = y*c - z*s;
  tmp.z = z*c + y*s;

  z = tmp.z;
  x = tmp.x;
  c = cos(ay);
  s = sin(ay);
  tmp.x = x*c + z*s;
  tmp.z = z*c - x*s;

  y = tmp.y;
  x = tmp.x;
  c = cos(az);
  s = sin(az);
  tmp.x = x*c + y*s;
  tmp.y = y*c - x*s;

  return tmp;
}

vector3d_t OVRLIBAPI
scale_vector(const vector3d_t& v, const vector3d_t& sv)
{
  vector3d_t tmp;

  tmp.x = v.x * sv.x;
  tmp.y = v.y * sv.y;
  tmp.z = v.z * sv.z;

  return tmp;
}

vector2d_t OVRLIBAPI
transform_vector(const vector3d_t& v, real persp)
{
  vector2d_t tmp;
  real grhz = persp/v.z; // let's speed up convertations...

  if ( v.z!=0.0 ) {
         tmp.x = v.x*grhz;
         tmp.y = v.y*grhz;
  } else {
                tmp.x = v.x*256;
                tmp.y = v.y*256;
  }

  return tmp;
}

//real OVRLIBAPI
//vector_length(const vector3d_t& v);
//{
//        return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
//}


vector3d_t OVRLIBAPI
cross_product(const vector3d_t& a, const vector3d_t& b)
{
  vector3d_t tmp;

  tmp.x = a.y*b.z - a.z*b.y;
  tmp.y = a.z*b.x - a.x*b.z;
  tmp.z = a.x*b.y - a.y*b.x;

  return tmp;
}

//real OVRLIBAPI dot_product(const vector3d_t& a, const vector3d_t& b);
//{
//  return a.x*b.x + a.y*b.y + a.z*b.z;
//}

//vector3d_t OVRLIBAPI normalize_vector(const vector3d_t& v)
//{
//  return div_vector(v, sqrt(v.x*v.x + v.y*v.y + v.z*v.z));
//}

vector3d_t OVRLIBAPI
mul_vector(const vector3d_t& v, real k)
{
  vector3d_t tmp;

  tmp.x = v.x*k;
  tmp.y = v.y*k;
  tmp.z = v.z*k;

  return tmp;
}

vector3d_t OVRLIBAPI
div_vector(const vector3d_t& v, real k)
{
  vector3d_t tmp;
  real K;

  if ( k<constants::EPSILON ) return v;
  K = 1.0/k;
  tmp.x = v.x * K;
  tmp.y = v.y * K;
  tmp.z = v.z * K;

  return tmp;
}

vector3d_t OVRLIBAPI
add_vectors(const vector3d_t& v1, const vector3d_t& v2)
{
  vector3d_t tmp;

  tmp.x = v1.x + v2.x;
  tmp.y = v1.y + v2.y;
  tmp.z = v1.z + v2.z;

  return tmp;
}

vector3d_t OVRLIBAPI
sub_vectors(const vector3d_t& v1, const vector3d_t& v2)
{
  vector3d_t tmp;

  tmp.x = v1.x - v2.x;
  tmp.y = v1.y - v2.y;
  tmp.z = v1.z - v2.z;

  return tmp;
}

vector3d_t OVRLIBAPI
neg_vector(const vector3d_t& v)
{
  vector3d_t tmp;

  tmp.x = -v.x;
  tmp.y = -v.y;
  tmp.z = -v.z;

  return tmp;
}


/******
 *  Reflection and refraction code is borrowed from:
 *      "Illumination and Color in Computer Generated Imagery"
 *      Source for code given in the Appendices
 *      (c)Roy Hall - 1988,1989
 *
 */

/* ****************************************************************
 *  DIR_VECT *geo_rfl (V, N)
 *   DIR_VECT   *V          (in)  incident vector
 *   DIR_VECT   *N          (in)  surface normal
 *
 *  Returns the reflected direction vector.  The reflected
 *   direction is computed using the method given by Whitted
 *   (1980), refer to Eq.(\*(rM).
 */
vector3d_t OVRLIBAPI vector_reflection(const vector3d_t& V, const vector3d_t& N)
{
    real   N_dot_V;
    vector3d_t rfl;

    N_dot_V = dot_product (N,V);
    rfl.x = (2.0 * N_dot_V * N.x) - V.x;
    rfl.y = (2.0 * N_dot_V * N.y) - V.y;
    rfl.z = (2.0 * N_dot_V * N.z) - V.z;

    return rfl;
}

/* ****************************************************************
 *  DIR_VECT *geo_rfr (V, N, ni, nt)
 *   DIR_VECT   *V          (in)  incident vector
 *   DIR_VECT   *N          (in)  surface normal
 *   real     ni          (in)  index of refraction for the
 *                              material on the front of the
 *                              interface (same side as N)
 *   real     nt          (in)  index of refraction for the
 *                              material on the back of the
 *                              interface (opposite size as N)
 *
 *  Returns the refracted vector, if there complete internal
 *   refracted (no refracted vector) then a NULL vector is
 *   NULL is returned.  The vector is computed using the
 *   method given by Hall (1983) with enhancements as
 *   described in Appendix III.
 */
vector3d_t OVRLIBAPI vector_refraction(const vector3d_t& V, const vector3d_t& N, real ni, real nt)
{
    vector3d_t T;      /* the refracted vector */
    vector3d_t sin_T;      /* sin vect of the refracted vect */
    vector3d_t cos_V;      /* cos vect of the incident vect */
    real len_sin_T;  /* length of sin T squared */
    real n_mult;     /* ni over nt */
    real N_dot_V;
    real N_dot_T;

    if ( (N_dot_V = dot_product(N,V)) > 0.0 )
       n_mult = ni / nt;
    else
       n_mult = nt / ni;
    cos_V.x = N_dot_V * N.x;
    cos_V.y = N_dot_V * N.y;
    cos_V.z = N_dot_V * N.z;
    sin_T.x = (n_mult) * (cos_V.x - V.x);
    sin_T.y = (n_mult) * (cos_V.y - V.y);
    sin_T.z = (n_mult) * (cos_V.z - V.z);
    if ( (len_sin_T = dot_product(sin_T, sin_T)) >= 1.0 )
        return VECZERO;    /* internal reflection */
    N_dot_T = sqrt(1.0 - len_sin_T);
    if ( N_dot_V < 0.0 ) N_dot_T = -N_dot_T;
    T.x = sin_T.x - (N.x * N_dot_T);
    T.y = sin_T.y - (N.y * N_dot_T);
    T.z = sin_T.z - (N.z * N_dot_T);
    return T;
}


/*************************************************
 *  2D Version of vector2d_t manipulation functions
 *
 *
 * the main 2D rotation formula:
 * x'=xcos(a)-ysin(a)
 * y'=ycos(a)+xsin(a)
 */
vector2d_t OVRLIBAPI rotate_vector_2d(const vector2d_t& v, real a)
{
  vector2d_t tmp = v;
  real c,s;

  c = cos(a);
  s = sin(a);
  tmp.x = v.x*c - v.y*s;
  tmp.y = v.y*c + v.x*s;

  return tmp;
}

vector2d_t OVRLIBAPI
scale_vector_2d(const vector2d_t& v, const vector2d_t& sv)
{
  vector2d_t tmp;

  tmp.x = v.x * sv.x;
  tmp.y = v.y * sv.y;

  return tmp;
}

real OVRLIBAPI
transform_vector_2d(const vector2d_t& v)
{
/*  _2dvector tmp;
  real grhz = 256.0/v.z; // let's speed up convertations...

  if ( v.z!=0.0 ) {
         tmp.x = v.x*grhz;
         tmp.y = v.y*grhz;
  } else {
                tmp.x = v.x*256;
                tmp.y = v.y*256;
  }
*/
  return v.x;   // project it to absciss ordinate
}

//real OVRLIBAPI
//vector_length_2d(const vector2d_t& v);
//{
//        return sqrt(v.x*v.x + v.y*v.y);
//}


//real OVRLIBAPI dot_product_2d(const vector2d_t& a, const vector2d_t& b);
//{
//        return a.x*b.x + a.y*b.y;
//}

//vector2d_t OVRLIBAPI normalize_vector_2d(const vector2d_t& v)
//{
//        return div_vector_2d(v, sqrt(v.x*v.x + v.y*v.y));
//}

vector2d_t OVRLIBAPI
mul_vector_2d(const vector2d_t& v, real k)
{
  vector2d_t tmp;

  tmp.x = v.x*k;
  tmp.y = v.y*k;

  return tmp;
}

vector2d_t OVRLIBAPI
div_vector_2d(const vector2d_t& v, real k)
{
  vector2d_t tmp;
  real K;

  if ( k<constants::EPSILON ) return v;
  K = 1.0 / k;
  tmp.x = v.x * K;
  tmp.y = v.y * K;

  return tmp;
}

vector2d_t OVRLIBAPI
add_vectors_2d(const vector2d_t& v1, const vector2d_t& v2)
{
  vector2d_t tmp;

  tmp.x = v1.x + v2.x;
  tmp.y = v1.y + v2.y;

  return tmp;
}

vector2d_t OVRLIBAPI
sub_vectors_2d(const vector2d_t& v1, const vector2d_t& v2)
{
  vector2d_t tmp;

  tmp.x = v1.x - v2.x;
  tmp.y = v1.y - v2.y;

  return tmp;
}

vector2d_t OVRLIBAPI
neg_vector_2d(const vector2d_t& v)
{
  vector2d_t tmp;

  tmp.x = -v.x;
  tmp.y = -v.y;

  return tmp;
}

/******
 *  Reflection and refraction code is borrowed from:
 *      "Illumination and Color in Computer Generated Imagery"
 *      Source for code given in the Appendices
 *      (c)Roy Hall - 1988,1989
 *
 */

/* ****************************************************************
 *  DIR_VECT *geo_rfl (V, N)
 *   DIR_VECT   *V          (in)  incident vector
 *   DIR_VECT   *N          (in)  surface normal
 *
 *  Returns the reflected direction vector.  The reflected
 *   direction is computed using the method given by Whitted
 *   (1980), refer to Eq.(\*(rM).
 */
vector2d_t OVRLIBAPI vector_reflection_3d(const vector2d_t& V, const vector2d_t& N)
{
    real   N_dot_V;
    vector2d_t rfl;

    N_dot_V = dot_product_2d (N,V);
    rfl.x = (2.0 * N_dot_V * N.x) - V.x;
    rfl.y = (2.0 * N_dot_V * N.y) - V.y;

    return rfl;
}

/* ****************************************************************
 *  DIR_VECT *geo_rfr (V, N, ni, nt)
 *   DIR_VECT   *V          (in)  incident vector
 *   DIR_VECT   *N          (in)  surface normal
 *   real     ni          (in)  index of refraction for the
 *                              material on the front of the
 *                              interface (same side as N)
 *   real     nt          (in)  index of refraction for the
 *                              material on the back of the
 *                              interface (opposite size as N)
 *
 *  Returns the refracted vector, if there complete internal
 *   refracted (no refracted vector) then a NULL vector is
 *   NULL is returned.  The vector is computed using the
 *   method given by Hall (1983) with enhancements as
 *   described in Appendix III.
 */
vector2d_t OVRLIBAPI vector_refraction(const vector2d_t& V, const vector2d_t& N, real ni, real nt)
{
    vector2d_t T;      /* the refracted vector */
    vector2d_t sin_T;      /* sin vect of the refracted vect */
    vector2d_t cos_V;      /* cos vect of the incident vect */
    real len_sin_T;  /* length of sin T squared */
    real n_mult;     /* ni over nt */
    real N_dot_V;
    real N_dot_T;

    if ( (N_dot_V = dot_product_2d(N,V)) > 0.0 )
       n_mult = ni / nt;
    else
       n_mult = nt / ni;
    cos_V.x = N_dot_V * N.x;
    cos_V.y = N_dot_V * N.y;
    sin_T.x = (n_mult) * (cos_V.x - V.x);
    sin_T.y = (n_mult) * (cos_V.y - V.y);
    if ( (len_sin_T = dot_product_2d(sin_T, sin_T)) >= 1.0 )
        return VECZERO_2D;    /* internal reflection */
    N_dot_T = sqrt(1.0 - len_sin_T);
    if ( N_dot_V < 0.0 ) N_dot_T = -N_dot_T;
    T.x = sin_T.x - (N.x * N_dot_T);
    T.y = sin_T.y - (N.y * N_dot_T);
    return T;
}

/*************************************************
 *  3D Intersection mathematics
 */

/*************************************************
 *  2D Intersection mathematics
 */
/**
 *  Finds out if a point lies on a segment defined by two points
 */
bool OVRLIBAPI point_in_segment_2d(const vector2d_t& P1, const vector2d_t& P2, const vector2d_t& P)
{
    if ( P1.x != P2.x ) {    // S is not vertical
        if ( P1.x <= P.x && P.x <= P2.x)
            return true;
        if ( P1.x >= P.x && P.x >= P2.x)
            return true;
    }
    else { // S is vertical, so test y coordinate
        if ( P1.y <= P.y && P.y <= P2.y)
            return true;
        if ( P1.y >= P.y && P.y >= P2.y)
            return true;
    }
    return false;
}

/**
 *  Finds out if a point lies on a ray defined by two points
 */
bool OVRLIBAPI point_in_ray_2d(const vector2d_t& P1, const vector2d_t& P2, const vector2d_t& P)
{
  return false;
}

/** 2d line segment to line segment
 *
 *  P1-P2  - first line segment  [in]
 *  Q1-Q2  - second line segment [in]
 *  I      - intersection point  [out]
 *  return:
 *   INTERSECTION_NONE
 *   INTERSECTION_YES
 *   INTERSECTION_OVERLAP
 */
// Copyright 2000, softSurfer (www.softsurfer.com)
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from it's use.
// Users of this code must verify correctness for their application.
//
// the intersection of 2 finite segments:
// intersect2D_SegSeg( Segment S1, Segment S2, Point* I0, Point* I1 )
//     returns: 0=disjoint (no intersect)
//              1=intersect in unique point I0
//              2=overlap in segment from I0 to I1
INTERSECTION_t OVRLIBAPI
intersection_line_to_line_2d(const vector2d_t& P1, const vector2d_t& P2,
        const vector2d_t& Q1, const vector2d_t& Q2,
        vector2d_t* I1, vector2d_t* I2)
{
    vector2d_t U = P2 - P1;
    vector2d_t V = Q2 - Q1;
    vector2d_t W = P1 - Q1;
    real   D = perp_dot_product_2d(U,V);

    // test if they are parallel (includes either being a point)
    if ( D==0 ) {        // S1 and S2 are parallel
        if ( perp_dot_product_2d(U,W)!=0 || perp_dot_product_2d(V,W)!=0 ) {
            return INTERSECTION_NONE; // they are NOT collinear
        }
        // they are collinear or degenerate
        // check if the segments are points
        real dU = dot_product_2d(U,U);
        real dV = dot_product_2d(V,V);
        if ( dU==0 && dV==0 ) {   // both segments are points
            if ( P1 != Q1 ) // they are distinct points
                return INTERSECTION_NONE;
            *I1 = P1;        // all the same point
            return INTERSECTION_YES;
        }
        if ( dU==0 ) {    // S1 a single point
            if ( point_in_segment_2d(Q1, Q2, P1)==0 )  // but not in S2
                return INTERSECTION_NONE;
            *I1 = P1;
            return INTERSECTION_YES;
        }
        if ( dV==0 ) {    // S2 a single point
            if ( point_in_segment_2d(P1, P2, Q1)==0 )  // but not in S1
                return INTERSECTION_NONE;
            *I1 = Q1;
            return INTERSECTION_YES;
        }
        // get overlap (or not) of collinear segments
        real   t0, t1, tmp;   // endpoints of S1 in eqn for S2
        vector2d_t W1 = P2 - Q1;
        if ( V.x!=0 ) {
                t0 = W.x / V.x;
                t1 = W1.x / V.x;
        } else {
                t0 = W.y / V.y;
                t1 = W1.y / V.y;
        }
        if ( t0>t1 )     // must have t0 smaller than t1
                OVRL_SWAP1(t0, t1, tmp)  // swap if not

        if (t0 > 1 || t1 < 0)
            return INTERSECTION_NONE;     // NO overlap

        t0 = t0<0 ? 0 : t0;    // clip to min 0
        t1 = t1>1 ? 1 : t1;    // clip to max 1
        if ( t0==t1 ) {   // intersect is a point
            *I1 = Q1 + V*t0;
            return INTERSECTION_YES;
        }

        // they overlap in a valid subsegment
        *I1 = Q1 + V*t0;
        *I2 = Q1 + V*t1;
        return INTERSECTION_OVERLAP;
    }

    // the segments are skew and may intersect in a point
    // get the intersect parameter for S1
    real     sI = perp_dot_product_2d(V,W) / D;
    if ( sI<0 || sI>1)            // no intersect with S1
        return INTERSECTION_NONE;

    // get the intersect parameter for S2
    real     tI = perp_dot_product_2d(U,W) / D;
    if ( tI<0 || tI>1 )            // no intersect with S2
        return INTERSECTION_NONE;

    *I1 = P1 + U*sI;        // compute S1 intersect point
    return INTERSECTION_YES;
}

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
        vector2d_t* I1, vector2d_t* I2)
{
  return INTERSECTION_NONE;
}

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
        vector2d_t* I1, vector2d_t* I2)
{
  return INTERSECTION_NONE;
}


}