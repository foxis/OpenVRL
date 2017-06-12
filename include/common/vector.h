/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/vector.h,v $
 * $Implementation: ~/src/ $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:56 $
 * $Description:  $
 *
 * $Log: vector.h,v $
 * Revision 1.3  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.2  2005/02/11 11:02:49  foxis
 * fixed many bugs
 * added joints
 *
 * Revision 1.1.1.1  2005/02/02 15:39:14  foxis
 * sources import
 *
 * Revision 0.3  20010411  :: FoxiE
 *
 */

#if !defined(AFX_COMVECTR_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_)
#define AFX_COMVECTR_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "common/matrix.h"
#include "common/point.h"
#include "common/constants.h"

namespace openvrl {

//////////////////// --------=[ Vectors
//
// 2DVector
//
class OVRLIBAPI C2DVector : public C2DPoint
{
public:
	C2DVector() : C2DPoint()
	{ }
	C2DVector(real x, real y) : C2DPoint(x,y)
	{ }
	C2DVector(const C2DVector& pt) : C2DPoint(pt)
	{ }
	C2DVector(const C2DPoint& pt) : C2DPoint(pt)
	{ }
	~C2DVector() 
	{ }

	real sq_length() const
	{
		return m_x*m_x + m_y*m_y;
	}
	real length() const
	{
		return sqrt(sq_length());
	}
	void normalize()
	{
		const real tmp = 1/length();
		x() *= tmp;
		y() *= tmp;
	}
	C2DVector normalize() const
	{
		C2DVector n(*this);
		n.normalize();
		return n;
	}
	void neg()
	{
		x() = -x();
		y() = -y();
	}
	C2DVector neg() const
	{
		C2DVector n(*this);
		n.neg();
		return n;
	}
	real dot(const C2DVector& pt) const
	{
		return pt.x()*x() + pt.y()*y();
	}
	C2DVector cross(const C2DVector& pt) const
	{
		return C2DVector(0,0);
	}
	C2DVector linear_interpolate(const C2DVector& v, real t) const
	{
		return C2DVector(
			x()+(v.x()-x())*t,
			y()+(v.y()-y())*t);
	}

// ******
// *  Reflection and refraction code is borrowed from:
// *      "Illumination and Color in Computer Generated Imagery"
// *      Source for code given in the Appendices
// *      (c)Roy Hall - 1988,1989
// *
// *

// *  Returns the reflected direction vector.  The reflected
// *   direction is computed using the method given by Whitted
// *   (1980), refer to Eq.(\*(rM).
// *
// reflects a vector <v> against this vector. *this is a normal vector
//
	C2DVector reflection(const C2DVector& v)
	{
	    real   N_dot_V;
	    C2DVector rfl;
	
	    N_dot_V = dot(v)*2;
	    rfl.x() = (N_dot_V * x()) - v.x();
	    rfl.y() = (N_dot_V * y()) - v.y();

	    return rfl;
	}


// *   OVRL_real     ni          (in)  index of refraction for the
// *                              material on the front of the
// *                              interface (same side as N)
// *   OVRL_real     nt          (in)  index of refraction for the
// *                              material on the back of the
// *                              interface (opposite size as N)
// *
// *  Returns the refracted vector, if there complete internal
// *   refracted (no refracted vector) then a NULL vector is
// *   NULL is returned.  The vector is computed using the
// *   method given by Hall (1983) with enhancements as
// *   described in Appendix III.
// *
	C2DVector refraction(const C2DVector& v, real ni, real nt)
	{
	    C2DVector T;      /* the refracted vector */
	    C2DVector sin_T;      /* sin vect of the refracted vect */
	    C2DVector cos_V;      /* cos vect of the incident vect */
	    real len_sin_T;  /* length of sin T squared */
	    real n_mult;     /* ni over nt */
	    real N_dot_V;
	    real N_dot_T;
	
	    if ( (N_dot_V = dot(v)) > 0.0 )
			n_mult = ni / nt;
		else
			n_mult = nt / ni;
		cos_V.x() = x() * N_dot_V;
		cos_V.y() = y() * N_dot_V;
		sin_T.x() = (cos_V.x() - v.x()) * (n_mult);
		sin_T.y() = (cos_V.y() - v.y()) * (n_mult);
		if ( (len_sin_T = sin_T.dot(sin_T)) >= 1.0 )
	        return T;    /* internal reflection */
	    N_dot_T = sqrt(1.0 - len_sin_T);
	    if ( N_dot_V < 0.0 ) 
			N_dot_T = -N_dot_T;
	    T.x() = sin_T.x() - x() * N_dot_T;
	    T.y() = sin_T.y() - y() * N_dot_T;
	    return T;
	}

	static C2DVector ZERO() { return C2DVector(0,0); }
	static C2DVector UNITX() { return C2DVector(1,0); }
	static C2DVector UNITY() { return C2DVector(0,1); }
	static C2DVector UNITXY() { return C2DVector(1,1); }
	static C2DVector NEGUNITX() { return C2DVector(-1,0); }
	static C2DVector NEGUNITY() { return C2DVector(0,-1); }
	static C2DVector NEGUNITXY() { return C2DVector(-1,-1); }
};

//
// 3DVector
//
class OVRLIBAPI C3DVector : public C3DPoint
{
public:
	C3DVector() : C3DPoint()
	{ }
	C3DVector(real x, real y, real z) : C3DPoint(x,y,z)
	{ }
	C3DVector(const C3DVector& pt) : C3DPoint(pt)
	{ }
	C3DVector(const C3DPoint& pt) : C3DPoint(pt)
	{ }
	~C3DVector() 
	{ }

	real sq_length() const
	{
		return m_x*m_x + m_y*m_y + m_z*m_z;
	}
	real length() const
	{
		return sqrt(sq_length());
	}
	void normalize()
	{
		const real tmp = 1/length();
		x() *= tmp;
		y() *= tmp;
		z() *= tmp;
	}
	C3DVector normalize() const
	{
		C3DVector n(*this);
		n.normalize();
		return n;
	}
	void neg()
	{
		x() = -x();
		y() = -y();
		z() = -z();
	}
	C3DVector neg() const
	{
		C3DVector n(*this);
		n.neg();
		return n;
	}
	real dot(const C3DVector& pt) const
	{
		return pt.x()*x() + pt.y()*y() + pt.z()*z();
	}
	C3DVector cross(const C3DVector& b) const
	{
 		return C3DVector(y()*b.z() - z()*b.y(), 
			z()*b.x() - x()*b.z(), 
			x()*b.y() - y()*b.x());
	}
	C3DVector linear_interpolate(const C3DVector& v, real t) const
	{
		return C3DVector(
			x()+(v.x()-x())*t,
			y()+(v.y()-y())*t,
			z()+(v.z()-z())*t);
	}

	//
	void mul(const C4x4Matrix& m)
	{
		C3DVector tmp;
#define M__4x4MMUL__M(m,i) m[0+i]*x()+m[4+i]*y()+m[8+i]*z()+m[12+i]
		tmp.x() = M__4x4MMUL__M(m.data(),0);
		tmp.y() = M__4x4MMUL__M(m.data(),1);
		tmp.z() = M__4x4MMUL__M(m.data(),2);
#undef M__4x4MMUL__M
		*this=tmp;
	}
	C3DVector mul(const C4x4Matrix& m) const
	{
		C3DVector tmp;
#define M__4x4MMUL__M(m,i) m[0+i]*x()+m[4+i]*y()+m[8+i]*z()+m[12+i]
		tmp.x() = M__4x4MMUL__M(m.data(),0);
		tmp.y() = M__4x4MMUL__M(m.data(),1);
		tmp.z() = M__4x4MMUL__M(m.data(),2);
#undef M__4x4MMUL__M
		return tmp;
	}

// ******
// *  Reflection and refraction code is borrowed from:
// *      "Illumination and Color in Computer Generated Imagery"
// *      Source for code given in the Appendices
// *      (c)Roy Hall - 1988,1989
// *
// *

// *  Returns the reflected direction vector.  The reflected
// *   direction is computed using the method given by Whitted
// *   (1980), refer to Eq.(\*(rM).
// *
// reflects a vector <v> against this vector. *this is a normal vector
//
	C3DVector reflection(const C3DVector& v)
	{
	    real   N_dot_V;
	    C3DVector rfl;
	
	    N_dot_V = dot(v)*2;
	    rfl.x() = (N_dot_V * x()) - v.x();
	    rfl.y() = (N_dot_V * y()) - v.y();
	    rfl.z() = (N_dot_V * z()) - v.z();

	    return rfl;
	}


// *   OVRL_real     ni          (in)  index of refraction for the
// *                              material on the front of the
// *                              interface (same side as N)
// *   OVRL_real     nt          (in)  index of refraction for the
// *                              material on the back of the
// *                              interface (opposite size as N)
// *
// *  Returns the refracted vector, if there complete internal
// *   refracted (no refracted vector) then a NULL vector is
// *   NULL is returned.  The vector is computed using the
// *   method given by Hall (1983) with enhancements as
// *   described in Appendix III.
// *
	C3DVector refraction(const C3DVector& v, real ni, real nt)
	{
	    C3DVector T;      /* the refracted vector */
	    C3DVector sin_T;      /* sin vect of the refracted vect */
	    C3DVector cos_V;      /* cos vect of the incident vect */
	    real len_sin_T;  /* length of sin T squared */
	    real n_mult;     /* ni over nt */
	    real N_dot_V;
	    real N_dot_T;
	
	    if ( (N_dot_V = dot(v)) > 0.0 )
			n_mult = ni / nt;
		else
			n_mult = nt / ni;
		cos_V.x() = x() * N_dot_V;
		cos_V.y() = y() * N_dot_V;
		cos_V.z() = z() * N_dot_V;
		sin_T.x() = (cos_V.x() - v.x()) * (n_mult);
		sin_T.y() = (cos_V.y() - v.y()) * (n_mult);
		sin_T.z() = (cos_V.z() - v.z()) * (n_mult);
		if ( (len_sin_T = sin_T.dot(sin_T)) >= 1.0 )
	        return T;    /* internal reflection */
	    N_dot_T = sqrt(1.0 - len_sin_T);
	    if ( N_dot_V < 0.0 ) 
			N_dot_T = -N_dot_T;
	    T.x() = sin_T.x() - x() * N_dot_T;
	    T.y() = sin_T.y() - y() * N_dot_T;
	    T.z() = sin_T.z() - z() * N_dot_T;
	    return T;
	}

	static C3DVector ZERO() { return C3DVector(0,0,0); }
	static C3DVector UNITX() { return C3DVector(1,0,0); }
	static C3DVector UNITY() { return C3DVector(0,1,0); }
	static C3DVector UNITZ() { return C3DVector(0,0,1); }
	static C3DVector UNITXYZ() { return C3DVector(1,1,1); }
	static C3DVector NEGUNITX() { return C3DVector(-1,0,0); }
	static C3DVector NEGUNITY() { return C3DVector(0,-1,0); }
	static C3DVector NEGUNITZ() { return C3DVector(0,0,-1); }
	static C3DVector NEGUNITXYZ() { return C3DVector(-1,-1,-1); }
};

//
// 4DVector
//
class OVRLIBAPI C4DVector : public C4DPoint
{
public:
	C4DVector() : C4DPoint()
	{ }
	C4DVector(real x, real y, real z, real w) : C4DPoint(x,y,z,w)
	{ }
	C4DVector(const C4DVector& pt) : C4DPoint(pt)
	{ }
	C4DVector(const C4DPoint& pt) : C4DPoint(pt)
	{ }
	~C4DVector() 
	{ }

	real sq_length() const
	{
		return m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w;
	}
	real length() const
	{
		return sqrt(sq_length());
	}
	void normalize()
	{
		const real tmp = 1/length();
		x() *= tmp;
		y() *= tmp;
		z() *= tmp;
		w() *= tmp;
	}
	C4DVector normalize() const
	{
		C4DVector n(*this);
		n.normalize();
		return n;
	}
	void neg()
	{
		const real d = 1.0/length();
		x() *= -d;
		y() *= -d;
		z() *= -d;
		w() *= d;
	}	
	C4DVector neg() const
	{
		C4DVector n(*this);
		n.neg();
		return n;
	}
	void inverse()
	{
		neg();
	}
	C4DVector inverse() const 
	{
		C4DVector tmp(*this);
		tmp.inverse();
		return tmp;
	}
	real dot(const C4DVector& pt) const
	{
		return (pt.x()*x() + pt.y()*y() + pt.z()*z() + pt.w()*w())/(length()*pt.length());
	}
	real dotunit(const C4DVector& pt) const
	{
		return pt.x()*x() + pt.y()*y() + pt.z()*z() + pt.w()*w();
	}
	C4DVector linear_interpolate(const C4DVector& v, real t) const
	{
		return C4DVector(
			x()+(v.x()-x())*t,
			y()+(v.y()-y())*t,
			z()+(v.z()-z())*t,
			w()+(v.w()-w())*t);
	}


	//
	void mul(const C4x4Matrix& m)
	{
		C4DVector tmp;
#define M__4x4MMUL__M(m,i) m[0+i]*x()+m[4+i]*y()+m[8+i]*z()+m[12+i]*w()
		tmp.x() = M__4x4MMUL__M(m.data(),0);
		tmp.y() = M__4x4MMUL__M(m.data(),1);
		tmp.z() = M__4x4MMUL__M(m.data(),2);
		tmp.w() = M__4x4MMUL__M(m.data(),3);
#undef M__4x4MMUL__M
		*this=tmp;
	}
	C4DVector mul(const C4x4Matrix& m) const
	{
		C4DVector tmp;
#define M__4x4MMUL__M(m,i) m[0+i]*x()+m[4+i]*y()+m[8+i]*z()+m[12+i]*w()
		tmp.x() = M__4x4MMUL__M(m.data(),0);
		tmp.y() = M__4x4MMUL__M(m.data(),1);
		tmp.z() = M__4x4MMUL__M(m.data(),2);
		tmp.w() = M__4x4MMUL__M(m.data(),3);
#undef M__4x4MMUL__M
		return tmp;
	}

	static C4DVector ZERO() { return C4DVector(0,0,0,0); }
	static C4DVector UNITX() { return C4DVector(1,0,0,0); }
	static C4DVector UNITY() { return C4DVector(0,1,0,0); }
	static C4DVector UNITZ() { return C4DVector(0,0,1,0); }
	static C4DVector UNITW() { return C4DVector(0,0,0,1); }
	static C4DVector UNITXW() { return C4DVector(1,0,0,1); }
	static C4DVector UNITYW() { return C4DVector(0,1,0,1); }
	static C4DVector UNITZW() { return C4DVector(0,0,1,1); }
	static C4DVector UNITXYZW() { return C4DVector(1,1,1,1); }
	static C4DVector NEGUNITX() { return C4DVector(-1,0,0,0); }
	static C4DVector NEGUNITY() { return C4DVector(0,-1,0,0); }
	static C4DVector NEGUNITZ() { return C4DVector(0,0,-1,0); }
	static C4DVector NEGUNITW() { return C4DVector(0,0,0,-1); }
	static C4DVector NEGUNITXW() { return C4DVector(-1,0,0,-1); }
	static C4DVector NEGUNITYW() { return C4DVector(0,-1,0,-1); }
	static C4DVector NEGUNITZW() { return C4DVector(0,0,-1,-1); }
	static C4DVector NEGUNITXYZW() { return C4DVector(-1,-1,-1,-1); }
};

//
// Quaternion
//
class OVRLIBAPI CQuaternion : public C4DVector
{
public:
	CQuaternion() : C4DVector()
	{ }
	CQuaternion(real x, real y, real z, real w)
	{ 
		set(x,y,z,w);
	}
	CQuaternion(real ax, real ay, real az)
	{ 
		set(cos(az),cos(ay),cos(ax),1); // @todo dunno for real
	}
	CQuaternion(const C3DVector& v, real w)
	{ 
		set(v.x(),v.y(),v.z(),w);
	}
	CQuaternion(const CQuaternion& pt) : C4DVector(pt)
	{ }
	CQuaternion(const C4DVector& pt) : C4DVector(pt)
	{ }
	~CQuaternion() 
	{ }

	void set(real _x, real _y, real _z, real _w)
	{
//        real s;
        w() = _w;//cos(w*.5);
//        s = sin(w*.5) / sqrt(_x*_x+_y*_y+_z*_z);
        x() = _x;// * s;
        y() = _y;// * s;
        z() = _z;// * s;
        return ;
	}
	void set1(real _x, real _y, real _z, real _w)
	{
        real s;
        w() = (real)cos(w*1.0); // *.5
        s = sin(w*1.0) / sqrt(_x*_x+_y*_y+_z*_z);
        x() = _x * s;
        y() = _y * s;
        z() = _z * s;
        return ;
	}
	void mul(const CQuaternion& b)
	{
		CQuaternion q;
        q.x() = w()*b.x() + x()*b.w() + y()*b.z() - z()*b.y();
        q.y() = w()*b.y() - x()*b.z() + y()*b.w() + z()*b.x();
        q.z() = w()*b.z() + x()*b.y() - y()*b.x() + z()*b.w();
        q.w() = w()*b.w() - x()*b.x() - y()*b.y() - z()*b.z();
		*this = q;
	}
	CQuaternion mul(const CQuaternion& b) const
	{
		CQuaternion tmp(*this);
		tmp.mul(b);
		return tmp;
	}
	CQuaternion operator*(const CQuaternion& b) const
	{
		CQuaternion tmp(*this);
		tmp.mul(b);
		return tmp;
	}
	CQuaternion& operator*=(const CQuaternion& b)
	{
		mul(b);
		return *this;
	}
	

	C4x4Matrix get_matrix() const
	{
		return C4x4Matrix(
			1-2*(y()*y() + z()*z()),
			2*(x()*y() + w()*z()),
			2*(x()*z() - w()*y()),
			0,
			2*(x()*y() - w()*z()),
			1-2*(x()*x() + z()*z()),
			2*(y()*z() + w()*x()),
			0,
			2*(x()*z() + w()*y()),
			2*(y()*z() - w()*x()),
			1-2*(x()*x() + y()*y()),
			0,0,0,0,1
		);
	}

	//
	//
	//
#define	SLERP_EPSILON 1.0E-10
	CQuaternion slerp( const CQuaternion& b, real time, real spin )
	{
		CQuaternion tmp;
		real k1,k2;					// interpolation coefficions.
		real angle;					// angle between A and B
		real angleSpin;			// angle between A and B plus spin.
		real sin_a, cos_a;	// sine, cosine of angle
		int flipk2;						// use negation of k2.
	
		cos_a = dotunit( b );
		if (cos_a < 0.0) 
		{ 
			cos_a = -cos_a; 
			flipk2 = -1; 
		} 
		else 
			flipk2 = 1;
	
		if ( (1.0 - cos_a) < SLERP_EPSILON ) 
		{
			k1 = 1.0 - time;
			k2 = time;
		} 
		else 
		{				/* normal case */
			angle = acos(cos_a);
			sin_a = sin(angle);
			angleSpin = angle + spin*constants::m_pi;
			k1 = sin( angle - time*angleSpin ) / sin_a;
			k2 = sin( time*angleSpin ) / sin_a;
		}
		k2 *= flipk2;
	
		tmp.x() = k1*x() + k2*b.x();
		tmp.y() = k1*y() + k2*b.y();
		tmp.z() = k1*z() + k2*b.z();
		tmp.w() = k1*w() + k2*b.w();
		return tmp;
	}
	
	CQuaternion slerplong( const CQuaternion& b, real time, real spin )	
	{
		CQuaternion tmp;
		real k1,k2;					// interpolation coefficions.
		real angle;					// angle between A and B
		real angleSpin;			// angle between A and B plus spin.
		real sin_a, cos_a;	// sine, cosine of angle
	
		cos_a = dotunit( b );
	
		if (1.0 - fabs(cos_a) < SLERP_EPSILON) {
			k1 = 1.0 - time;
			k2 = time;
		} else {				/* normal case */
			angle = acos(cos_a);
			sin_a = sin(angle);
			angleSpin = angle + spin*constants::m_pi;
			k1 = sin( angle - time*angleSpin ) / sin_a;
			k2 = sin( time*angleSpin ) / sin_a;
		}
	
		tmp.x() = k1*x() + k2*b.x();
		tmp.y() = k1*y() + k2*b.y();
		tmp.z() = k1*z() + k2*b.z();
		tmp.w() = k1*w() + k2*b.w();
		return tmp;
	}
#undef SLERP_EPSILON
};

};	

#endif // define AFX_COMVECTR_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_
