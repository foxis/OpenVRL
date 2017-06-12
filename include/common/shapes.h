/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/shapes.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/03 11:24:24 $
 * $Description:  $
 *
 * $Log: shapes.h,v $
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */


#if !defined(AFX_COMSHAPS_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_)
#define AFX_COMSHAPS_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_

#include <math.h>

#include "common/matrix.h"
#include "common/point.h"
#include "common/vector.h"
#include "common/constants.h"

namespace openvrl {

class OVRLIBAPI C2DLine;
class OVRLIBAPI C3DLine;
class OVRLIBAPI C4DLine;
class OVRLIBAPI C2DCircle;
class OVRLIBAPI C3DSphere;
class OVRLIBAPI C4DSphere;
class OVRLIBAPI C2DRect;
class OVRLIBAPI C3DBox;
class OVRLIBAPI C3DOrientedBox;
class OVRLIBAPI C2DPlane;
class OVRLIBAPI C3DPlane;
class OVRLIBAPI C4DPlane;

//
// 2DLine
//
class OVRLIBAPI C2DLine
{
	C2DPoint m_p1;
	C2DPoint m_p2;

public:
	C2DLine()
	{ }
	C2DLine(real x, real y, real x1, real y1)
		:m_p1(x,y), m_p2(x1,y1)
	{ }
	C2DLine(const C2DPoint& p1, const C2DPoint& p2)
		:m_p1(p1), m_p2(p2)
	{ }
	C2DLine(const C2DLine& l)
	{ 
		*this = l;
	}
	~C2DLine();

	C2DLine& operator=(const C2DLine& l)
	{
		m_p1 = l.m_p1;
		m_p2 = l.m_p2;
		return *this;
	}

	C2DPoint p1() const { return m_p1; }
	C2DPoint p2() const { return m_p2; }
	C2DPoint& p1() { return m_p1; }
	C2DPoint& p2() { return m_p2; }
	real x1() const { return m_p1.x(); }
	real y1() const { return m_p1.y(); }
	real x2() const { return m_p2.x(); }
	real y2() const { return m_p2.y(); }
	real& x1() { return m_p1.x(); }
	real& y1() { return m_p1.y(); }
	real& x2() { return m_p2.x(); }
	real& y2() { return m_p2.y(); }

	real length() const { return m_p1.distance(m_p2); }
	C2DPoint interpolate(real t) const { return m_p1 + (m_p2-m_p1)*t; }
	real distance(const C2DPoint& p) const 
	{
		const real Ax= x1()-p.x();
		const real Bx= x2()-x1();
		const real Ay= y1()-p.y();
		const real By= y2()-y1();
		const real u= (Ax*Bx-Ay*By)/(Bx*Bx+By*By);
		const real a= Ax+u*Bx;
		const real b= Ay+u*By;
		return sqrt(a*a + b*b);
	}
	bool intersection(const C2DLine& l, C2DPoint& p) const
	{
		const real a1= x1()-l.x1();
		const real a2= x2()-x1();
		const real a3= l.x2()-l.x1();
		const real b1= y1()-l.y1();
		const real b2= y2()-y1();
		const real b3= l.y2()-l.y1();
		const real uan= (a3*b1-b3*a1);
		const real uad= (b3*a2-a3*b2);
		const real ubn= (a2*b1-b2*a1);
		const real ubd= (b3*a2-a3*b2);
		real ua, ub;

		if ( uad==0 || ubd==0 || uan==0 || ubn==0 )  return false;
		ua = uan/uad;
		ub = ubn/ubd;
		if ( ua>0&&ua<=1 && ub>0&&ub<=1 ) 
			p = p1() + (p2()-p1())*ua;
		else
			return false;
		return true;
	}
};

//
// 3DLine
//
class OVRLIBAPI C3DLine
{
	C3DPoint m_p1;
	C3DPoint m_p2;

public:
	C3DLine()
	{ }
	C3DLine(real x, real y, real z, real x1, real y1, real z1)
		:m_p1(x,y,z), m_p2(x1,y1,z1)
	{ }
	C3DLine(const C3DPoint& p1, const C3DPoint& p2)
		:m_p1(p1), m_p2(p2)
	{ }
	C3DLine(const C3DLine& l)
	{ 
		*this = l;
	}
	~C3DLine();

	C3DLine& operator=(const C3DLine& l)
	{
		m_p1 = l.m_p1;
		m_p2 = l.m_p2;
		return *this;
	}

	C3DPoint p1() const { return m_p1; }
	C3DPoint p2() const { return m_p2; }
	C3DPoint& p1() { return m_p1; }
	C3DPoint& p2() { return m_p2; }
	real x1() const { return m_p1.x(); }
	real y1() const { return m_p1.y(); }
	real z1() const { return m_p1.z(); }
	real x2() const { return m_p2.x(); }
	real y2() const { return m_p2.y(); }
	real z2() const { return m_p2.z(); }
	real& x1() { return m_p1.x(); }
	real& y1() { return m_p1.y(); }
	real& z1() { return m_p1.z(); }
	real& x2() { return m_p2.x(); }
	real& y2() { return m_p2.y(); }
	real& z2() { return m_p2.z(); }

	real length() const { return p1().distance(p2()); }
	C3DPoint interpolate(real t) const { return p1() + (p2()-p1())*t; }
	real distance(const C3DPoint& p) const 
	{
		const real Ax= x1()-p.x();
		const real Bx= x2()-x1();
		const real Ay= y1()-p.y();
		const real By= y2()-y1();
		const real Az= z1()-p.z();
		const real Bz= z2()-z1();
		const real u= -(Ax*Bx+Ay*By+Az*Bz)/(Bx*Bx+By*By+Bz*Bz);
		const real a= Ax+u*Bx;
		const real b= Ay+u*By;
		const real c= Az+u*Bz;
		return sqrt(a*a + b*b + c*c);
	}

	bool intersection(const C3DLine& l, C3DPoint& pa, C3DPoint& pb) const
	{
/*
   Calculate the line segment PaPb that is the shortest route between
   two lines P1P2 and P3P4. Calculate also the values of mua and mub where
      Pa = P1 + mua (P2 - P1)
      Pb = P3 + mub (P4 - P3)
   Return FALSE if no solution exists.
*/
		C3DPoint p13,p43,p21;
		real d1343,d4321,d1321,d4343,d2121;
		real numer,denom;
		real mua, mub;

		p13.x() = x1() - l.x1();
		p13.y() = y1() - l.y1();
		p13.z() = z1() - l.z1();
		p43.x() = l.x2() - l.x1();
		p43.y() = l.y2() - l.y1();
		p43.z() = l.z2() - l.z1();
		if (fabs(p43.x())  < constants::EPSILON && 
			fabs(p43.y())  < constants::EPSILON && 
			fabs(p43.z())  < constants::EPSILON)
			return false;
		p21.x() = x2() - x1();
		p21.y() = y2() - y1();
		p21.z() = z2() - z1();
		if (fabs(p21.x())  < constants::EPSILON && 
			fabs(p21.y())  < constants::EPSILON && 
			fabs(p21.z())  < constants::EPSILON)
			return false;

		d1343 = p13.x() * p43.x() + p13.y() * p43.y() + p13.z() * p43.z();
		d4321 = p43.x() * p21.x() + p43.y() * p21.y() + p43.z() * p21.z();
		d1321 = p13.x() * p21.x() + p13.y() * p21.y() + p13.z() * p21.z();
		d4343 = p43.x() * p43.x() + p43.y() * p43.y() + p43.z() * p43.z();
		d2121 = p21.x() * p21.x() + p21.y() * p21.y() + p21.z() * p21.z();

		denom = d2121 * d4343 - d4321 * d4321;
		if ( fabs(denom) < constants::EPSILON )
			return false;
		numer = d1343 * d4321 - d1321 * d4343;

		mua = numer / denom;
		mub = (d1343 + d4321 * mua) / d4343;

		pa.x() = l.x1() + mua * p21.x();
		pa.y() = l.y1() + mua * p21.y();
		pa.z() = l.z1() + mua * p21.z();
		pb.x() = l.x1() + mub * p43.x();
		pb.y() = l.y1() + mub * p43.y();
		pb.z() = l.z1() + mub * p43.z();

		return true;
	}
};

//
// 4DLine
//
class OVRLIBAPI C4DLine
{
	C4DPoint m_p1;
	C4DPoint m_p2;

public:
	C4DLine()
	{ }
	C4DLine(real x, real y, real z, real w, real x1, real y1, real z1, real w1)
		:m_p1(x,y,z,w), m_p2(x1,y1,z1,w1)
	{ }
	C4DLine(const C4DPoint& p1, const C4DPoint& p2)
		:m_p1(p1), m_p2(p2)
	{ }
	C4DLine(const C4DLine& l)
	{ 
		*this = l;
	}
	~C4DLine();

	C4DLine& operator=(const C4DLine& l)
	{
		m_p1 = l.m_p1;
		m_p2 = l.m_p2;
		return *this;
	}

	C4DPoint p1() const { return m_p1; }
	C4DPoint p2() const { return m_p2; }
	C4DPoint& p1() { return m_p1; }
	C4DPoint& p2() { return m_p2; }
	real x1() const { return m_p1.x(); }
	real y1() const { return m_p1.y(); }
	real z1() const { return m_p1.z(); }
	real w1() const { return m_p1.w(); }
	real x2() const { return m_p2.x(); }
	real y2() const { return m_p2.y(); }
	real z2() const { return m_p2.z(); }
	real w2() const { return m_p2.w(); }
	real& x1() { return m_p1.x(); }
	real& y1() { return m_p1.y(); }
	real& z1() { return m_p1.z(); }
	real& w1() { return m_p1.w(); }
	real& x2() { return m_p2.x(); }
	real& y2() { return m_p2.y(); }
	real& z2() { return m_p2.z(); }
	real& w2() { return m_p2.w(); }

	real length() const { return p1().distance(p2()); }
	C4DPoint interpolate(real t) const { return p1() + (p2()-p1())*t; }
	real distance(const C4DPoint& p) const 
	{
		const real Ax= x1()-p.x();
		const real Bx= x2()-x1();
		const real Ay= y1()-p.y();
		const real By= y2()-y1();
		const real Az= z1()-p.z();
		const real Bz= z2()-z1();
		const real Aw= w1()-p.w();
		const real Bw= w2()-w1();
		const real u= -(Ax*Bx+Ay*By+Az*Bz+Aw*Bw)/(Bx*Bx+By*By+Bz*Bz+Bw*Bw);
		const real a= Ax+u*Bx;
		const real b= Ay+u*By;
		const real c= Az+u*Bz;
		const real d= Aw+u*Bw;
		return sqrt(a*a + b*b + c*c + d*d);
	}
};

//
// 2D Rect
//
class OVRLIBAPI C2DRect
{
	C2DPoint	m_topleft;
	C2DPoint	m_bottomright;

public:
	C2DRect()
	{ }
	C2DRect(real x, real y, real x1, real y1)
		:m_topleft(x,y), m_bottomright(x1,y1)
	{ }
	C2DRect(const C2DPoint& top, const C2DPoint& bottom)
		:m_topleft(top), m_bottomright(bottom)
	{ }
	C2DRect(const C2DRect& rc)
	{ 
		*this = rc;
	}
	~C2DRect()
	{ }

	C2DRect& operator=(const C2DRect& rc)
	{
		m_topleft = rc.m_topleft;
		m_bottomright = rc.m_bottomright;
		return *this;
	}

	C2DPoint lefttop() const { return C2DPoint(left(), top()); }
	C2DPoint leftbottom() const { return C2DPoint(left(), bottom()); }
	C2DPoint righttop() const { return C2DPoint(right(), top()); }
	C2DPoint rightbottom() const { return C2DPoint(right(), bottom()); }

	real left() const { return m_topleft.x(); }
	real top() const { return m_topleft.y(); }
	real right() const { return m_bottomright.x(); }
	real bottom() const { return m_bottomright.y(); }
	real width() const { return right()-left(); }
	real height() const { return top()-bottom(); }

	real& left() { return m_topleft.x(); }
	real& top() { return m_topleft.y(); }
	real& right() { return m_bottomright.x(); }
	real& bottom() { return m_bottomright.y(); }
	
	void width(real w) { right() = left() +w; }
	void height(real h) { top() = bottom()+h; }
};

//
// 3D box
//
class OVRLIBAPI C3DBox
{
	C3DPoint	m_topleft;
	C3DPoint	m_bottomright;

public:
	C3DBox()
	{ }
	C3DBox(real x, real y, real z, real x1, real y1, real z1)
		:m_topleft(x,y,z), m_bottomright(x1,y1,z1)
	{ }
	C3DBox(const C3DPoint& top, const C3DPoint& bottom)
		:m_topleft(top), m_bottomright(bottom)
	{ }
	C3DBox(const C3DBox& rc)
	{ 
		*this = rc;
	}
	~C3DBox()
	{ }

	C3DBox& operator=(const C3DBox& rc)
	{
		m_topleft = rc.m_topleft;
		m_bottomright = rc.m_bottomright;
		return *this;
	}

	C3DPoint frontlefttop() const { return C3DPoint(left(), top(), front()); }
	C3DPoint frontleftbottom() const { return C3DPoint(left(), bottom(), front()); }
	C3DPoint frontrighttop() const { return C3DPoint(right(), top(), front()); }
	C3DPoint frontrightbottom() const { return C3DPoint(right(), bottom(), front()); }
	C3DPoint backlefttop() const { return C3DPoint(left(), top(), back()); }
	C3DPoint backleftbottom() const { return C3DPoint(left(), bottom(), back()); }
	C3DPoint backrighttop() const { return C3DPoint(right(), top(), back()); }
	C3DPoint backrightbottom() const { return C3DPoint(right(), bottom(), back()); }

	real left() const { return m_topleft.x(); }
	real top() const { return m_topleft.y(); }
	real right() const { return m_bottomright.x(); }
	real bottom() const { return m_bottomright.y(); }
	real front() const { return m_bottomright.z(); }
	real back() const { return m_topleft.z(); }
	real width() const { return right()-left(); }
	real height() const { return top()-bottom(); }
	real depth() const { return back()-front(); }

	real& left() { return m_topleft.x(); }
	real& top() { return m_topleft.y(); }
	real& right() { return m_bottomright.x(); }
	real& bottom() { return m_bottomright.y(); }
	real& front() { return m_bottomright.z(); }
	real& back() { return m_topleft.z(); }
	
	void width(real w) { right() = left() +w; }
	void height(real h) { top() = bottom()+h; }
	void depth(real d) { back() = front() +d; }
};

//
// 3D oriented box
//
class OVRLIBAPI C3DOrientedBox
{
	C3DPoint	m_topleft;
	C3DPoint	m_bottomright;
	CQuaternion m_orientation;

public:
	C3DOrientedBox()
	{ }
	C3DOrientedBox(real x, real y, real z, real x1, real y1, real z1,
		real ax, real ay, real az)
		:m_topleft(x,y,z), m_bottomright(x1,y1,z1), m_orientation(ax,ay,az)
	{ }
	C3DOrientedBox(const C3DPoint& top, const C3DPoint& bottom, const CQuaternion& orientation)
		:m_topleft(top), m_bottomright(bottom), m_orientation(orientation)
	{ }
	C3DOrientedBox(const C3DOrientedBox& rc)
	{ 
		*this = rc;
	}
	~C3DOrientedBox()
	{ }

	C3DOrientedBox& operator=(const C3DOrientedBox& rc)
	{
		m_topleft = rc.m_topleft;
		m_bottomright = rc.m_bottomright;
		m_orientation = rc.m_orientation;
		return *this;
	}

	C3DPoint frontlefttop() const { return C3DPoint(left(), top(), front()); }
	C3DPoint frontleftbottom() const { return C3DPoint(left(), bottom(), front()); }
	C3DPoint frontrighttop() const { return C3DPoint(right(), top(), front()); }
	C3DPoint frontrightbottom() const { return C3DPoint(right(), bottom(), front()); }
	C3DPoint backlefttop() const { return C3DPoint(left(), top(), back()); }
	C3DPoint backleftbottom() const { return C3DPoint(left(), bottom(), back()); }
	C3DPoint backrighttop() const { return C3DPoint(right(), top(), back()); }
	C3DPoint backrightbottom() const { return C3DPoint(right(), bottom(), back()); }

	CQuaternion orientation() const { return m_orientation; }
	real left() const { return m_topleft.x(); }
	real top() const { return m_topleft.y(); }
	real right() const { return m_bottomright.x(); }
	real bottom() const { return m_bottomright.y(); }
	real front() const { return m_bottomright.z(); }
	real back() const { return m_topleft.z(); }
	real width() const { return right()-left(); }
	real height() const { return top()-bottom(); }
	real depth() const { return back()-front(); }

	CQuaternion& orientation() { return m_orientation; }
	real& left() { return m_topleft.x(); }
	real& top() { return m_topleft.y(); }
	real& right() { return m_bottomright.x(); }
	real& bottom() { return m_bottomright.y(); }
	real& front() { return m_bottomright.z(); }
	real& back() { return m_topleft.z(); }
	
	void width(real w) { right() = left() +w; }
	void height(real h) { top() = bottom()+h; }
	void depth(real d) { back() = front() +d; }
};

//
// 2D Circle
//
class OVRLIBAPI C2DCircle
{
	C2DPoint m_centre;
	real	m_radius;

public:
	C2DCircle() 
	{ }
	C2DCircle(real radius)
		:m_centre(0,0), m_radius(radius)
	{ }
	C2DCircle(real x, real y, real r)
		:m_centre(x,y), m_radius(r)
	{ }
	C2DCircle(const C2DPoint& c, real r)
		:m_centre(c), m_radius(r)
	{ }
	C2DCircle(const C2DCircle& c)
	{
		*this = c;
	}
	~C2DCircle()
	{ }

	C2DCircle& operator=(const C2DCircle& c)
	{
		m_centre = c.m_centre;
		m_radius = c.m_radius;
		return *this;
	}

	C2DPoint centre() const { return m_centre; }
	real x() const { return m_centre.x(); }
	real y() const { return m_centre.y(); }
	real r() const { return m_radius; }
	C2DPoint& centre() { return m_centre; }
	real& x() { return m_centre.x(); }
	real& y() { return m_centre.y(); }
	real& r() { return m_radius; }

	bool is_inside(const C2DPoint& p) const
	{
		const real Ax = x()-p.x();
		const real Ay = y()-p.y();
		return r()*r() >= Ax*Ax+Ay*Ay;
	}
	bool intersect_line(const C2DLine& l, C2DPoint& pa, C2DPoint& pb) const
	{
		const real Ax= l.x2()-l.x1();
		const real Ay= l.y2()-l.y1();
		const real a= Ax*Ax+Ay*Ay;
		const real cy= y()-l.y1();
		const real b= 2*(Ax*l.x1() + Ay*cy);
		const real c= (cy-r())*(cy+r())+l.x1()*l.x1();
		const real D= b*b -4*a*c; 
		real ua, ub;
		if ( D<0 ) return false;
		const real sD= sqrt(D);
		const real _2a= 2*a;
		ua = (sD-b)/_2a;
		ub = (-sD-b)/_2a;
		if ( ua>=0&&ua<=1 )
		{
			pa.x() = l.x1() + ua*Ax;
			pa.y() = l.y1() + ua*Ay;
			if ( ub<0&&ub>1 ) pb = pa;
		} else
			if ( ub<0&&ub>1 )
				return false;
		if ( ua>=0&&ua<=1 )
		{
			pb.x() = l.x1() + ub*Ax;
			pb.y() = l.y1() + ub*Ay;
			if ( ua<0&&ua>1 ) pa = pb;
		}
		else
			if ( ua<0&&ua>1 )
				return false;
		return true;
	}
	bool intersect_circle(const C2DCircle &c, real& u) const
	{
		const real dist=c.centre().distance(centre());
		const real R = c.r()+r()+constants::EPSILON;
		u = dist/R;
		return dist<=R;
	}
	bool intersect_sweep_circle(const C2DVector& v,	const C2DVector& a, 
		const C2DCircle &c1, const C2DVector& v1,	const C2DVector& a1,
		real& u1, real& u2) const
	{
		const C2DVector A = centre()-c1.centre();
		const C2DVector B = v-v1;
		const C2DVector C = (a-a1)*0.5;
		const real R= r()+c1.r();
		return false;
	}
	bool intersect_sweep_point(const C2DPoint &c, const C2DVector& v,
		const C2DVector& a, real& u1, real& u2) const
	{
		return false;
	}
};

//
// 3D Sphere
//
class OVRLIBAPI C3DSphere
{
	C3DPoint m_centre;
	real	m_radius;

public:
	C3DSphere() 
	{ }
	C3DSphere(real radius)
		:m_centre(0,0,0), m_radius(radius)
	{ }
	C3DSphere(real x, real y, real z, real r)
		:m_centre(x,y,z), m_radius(r)
	{ }
	C3DSphere(const C3DPoint& c, real r)
		:m_centre(c), m_radius(r)
	{ }
	C3DSphere(const C3DSphere& c)
	{
		*this = c;
	}
	~C3DSphere()
	{ }

	C3DSphere& operator=(const C3DSphere& c)
	{
		m_centre = c.m_centre;
		m_radius = c.m_radius;
		return *this;
	}

	C3DPoint centre() const { return m_centre; }
	real x() const { return m_centre.x(); }
	real y() const { return m_centre.y(); }
	real z() const { return m_centre.z(); }
	real r() const { return m_radius; }
	C3DPoint& centre() { return m_centre; }
	real& x() { return m_centre.x(); }
	real& y() { return m_centre.y(); }
	real& z() { return m_centre.z(); }
	real& r() { return m_radius; }


	bool is_inside(const C3DPoint& p)
	{
		const real Ax = x()-p.x();
		const real Ay = y()-p.y();
		const real Az = z()-p.z();
		return r()*r() >= Ax*Ax+Ay*Ay+Az*Az;
	}
	//
	//
	//
	bool intersect_line(const C3DLine& l, C3DPoint& pa, C3DPoint& pb)
	{
		const real Ax= l.x2()-l.x1();
		const real Ay= l.y2()-l.y1();
		const real Az= l.z2()-l.z1();
		const real a= Ax*Ax+Ay*Ay+Az*Az;
		const real cy= y()-l.y1();
		const real cz= z()-l.z1();
		const real b= 2*(Ax*l.x1() + Ay*cy + Az*cz);
		const real c= (cy-r())*(cy+r())+l.x1()*l.x1() + cz*cz;
		const real D= b*b -4*a*c; 
		real ua, ub;
		if ( D<0 ) return false;
		const real sD= sqrt(D);
		const real _2a= 2*a;
		ua = (sD-b)/_2a;
		ub = (-sD-b)/_2a;
		if ( ua>=0&&ua<=1 )
		{
			pa.x() = l.x1() + ua*Ax;
			pa.y() = l.y1() + ua*Ay;
			pa.z() = l.z1() + ua*Az;
			if ( ub<0&&ub>1 ) pb = pa;
		} else
			if ( ub<0&&ub>1 )
				return false;
		if ( ua>=0&&ua<=1 )
		{
			pb.x() = l.x1() + ub*Ax;
			pb.y() = l.y1() + ub*Ay;
			pb.z() = l.z1() + ub*Az;
			if ( ua<0&&ua>1 ) pa = pb;
		}
		else
			if ( ua<0&&ua>1 )
				return false;
		return true;
	}
	bool intersect_sphere(const C3DSphere &c, real& u) const
	{
		const real dist=c.centre().distance(centre());
		const real R = c.r()+r()+constants::EPSILON;
		u = dist/R;
		return dist<=R;
	}
	//
	// this one doesn't include acceleration in intersection time computation
	// thus in some cases it cat to produce wrong results...
	// nevertheless it is acceptable in many cases
	// 
	// including acceleration results in 4th degree equation, wich i cannot solve
	// yet...
	//
	bool intersect_sweep_sphere(const C3DVector& v,	const C3DVector& va, 
		const C3DSphere &c1, const C3DVector& v1,	const C3DVector& va1,
		real& u1, real& u2) const
	{
		const real R = r()+c1.r();
		const C3DVector A = v-v1;
		const C3DVector C = centre()-c1.centre();
		const real a = A.sq_length()*2;
		const real c = C.sq_length()-R*R;
		const real b = C.dot(A)*2;

		if ( c<constants::EPSILON ) {
			u1 = u2 = R / C.length();
			return true;
		}
		if ( a>=0&&a<=constants::EPSILON )
		{
			u1 = u2 = -c / b;
			return true;
		}
		const real D= b*b - 2*a*c;
		if ( D<constants::EPSILON )
		{
			u1 = u2 = 0;
			return false;
		}
		const real sD = sqrt(D);
		u1 = -(b-sD)/a;
		u2 = -(b+sD)/a;
		return u1<=1&&u1>=0 || u2<=1&&u2>=0;
	}
	bool intersect_sweep_point(const C3DVector& v,	const C3DVector& va, 
		const C3DPoint &c1, const C3DVector& v1,	const C3DVector& va1, 
		real& u1, real& u2) const
	{
		const C3DVector A = v-v1;
		const C3DVector B = centre()-c1;
		const real a = 2*A.sq_length();
		const real c = B.sq_length();
		const real b = 2*A.dot(B);

		if ( a==0 )
		{
			u1 = u2 = -c / b;
			return true;
		}
		const real D= b*b - 2*a*c;
		if ( D<constants::EPSILON )
		{
			u1 = u2 = 0;
			return false;
		}
		const real sD = sqrt(D);
		u1 = -(b-sD)/a;
		u2 = (b-sD)/a;
		return true;
	}
};

//
// 4DSphere
//
class OVRLIBAPI C4DSphere
{
	C4DPoint m_centre;
	real	m_radius;

public:
	C4DSphere() 
	{ }
	C4DSphere(real radius)
		:m_centre(0,0,0,0), m_radius(radius)
	{ }
	C4DSphere(real x, real y, real z, real w, real r)
		:m_centre(x,y,z,w), m_radius(r)
	{ }
	C4DSphere(const C4DPoint& c, real r)
		:m_centre(c), m_radius(r)
	{ }
	C4DSphere(const C4DSphere& c)
	{
		*this = c;
	}
	~C4DSphere()
	{ }

	C4DSphere& operator=(const C4DSphere& c)
	{
		m_centre = c.m_centre;
		m_radius = c.m_radius;
		return *this;
	}

	C4DPoint centre() const { return m_centre; }
	real x() const { return m_centre.x(); }
	real y() const { return m_centre.y(); }
	real z() const { return m_centre.z(); }
	real w() const { return m_centre.w(); }
	real r() const { return m_radius; }
	C4DPoint& centre() { return m_centre; }
	real& x() { return m_centre.x(); }
	real& y() { return m_centre.y(); }
	real& z() { return m_centre.z(); }
	real& w() { return m_centre.w(); }
	real& r() { return m_radius; }

	bool is_inside(const C4DPoint& p)
	{
		const real Ax = x()-p.x();
		const real Ay = y()-p.y();
		const real Az = z()-p.z();
		const real Aw = w()-p.w();
		return r()*r() >= Ax*Ax+Ay*Ay+Az*Az+Aw*Aw;
	}
};

//
// 2DPlane
//
class OVRLIBAPI C2DPlane
{
	C2DPoint m_origin;
	C2DVector m_normal;

public:
	C2DPlane()
	{ }
	C2DPlane(real x, real y, real nx, real ny)
		:m_origin(x,y), m_normal(nx,ny)
	{ }
	C2DPlane(const C2DPoint& o, const C2DVector& n)
		:m_origin(o), m_normal(n)
	{ }
	C2DPlane(const C2DLine& l)
	{
		C2DVector tmp(l.p2()-l.p1());
		origin() = l.p1();
		normal().x() = -tmp.y();
		normal().y() = tmp.x();
		normal().normalize();
	}
	C2DPlane(const C2DPlane& p)
	{
		*this = p;
	}
	~C2DPlane()
	{ }

	C2DPlane& operator=(const C2DPlane& p)
	{
		origin() = p.origin();
		normal() = p.normal();
		return *this;
	}

	C2DPoint origin() const { return m_origin; }
	C2DVector normal() const { return m_normal; }
	C2DPoint& origin() { return m_origin; }
	C2DVector& normal() { return m_normal; }

	real dot(const C2DPoint& p) const
	{
		C2DVector tmp(p);
		tmp -= origin();
		return normal().dot(tmp);
	}
	real distance(const C2DPoint& p) const
	{
		C2DVector tmp(normal());
		tmp.normalize();
		return tmp.dot(p);
	}
	real distance_unit(const C2DPoint& p) const
	{
		return normal().dot(p);
	}

	//
	// intersection routines. 
	// all routines return boolean representing whether
	// there was a collision
	// and also returns a local time constant for interpolating into
	// an intersection
	//
	bool intersect_line(const C2DLine& l, real & mu) const
	{
		const real Ax = l.x2() - l.x1();
		const real Ay = l.y2() - l.y1();
		const real D = - normal().x() * origin().x() - normal().y() * origin().y();
		const real denom = normal().x() * Ax + normal().y() * Ay;
		if ( fabs(D)<constants::EPSILON )
			return false;
		mu = -(D + normal().x() * l.x1() + normal().y() * l.y1()) / denom;
		if ( mu < 0 || mu > 1 )   /* Intersection not along line segment */
			return false;
		return true;
	}
	bool intersect_circle(const C2DCircle& c, real& u) const
	{
		const real d = distance_unit(c.centre());
		const real R = c.r();
		if ( d<=R && d>=-R )
		{
			u = (d==0)?0:R/d;
			return true;
		}
		else
			return false;
	}
	//
	// NOTE: no checkings for if velocity is zero
	//
	bool intersect_sweep_circle(const C2DCircle& c, const C2DVector& v, 
		const C2DVector& a, real& u1, real& u2) const
	{
		const real da = normal().dot(v)*0.5;
		const real db = normal().dot(v);
		const real D = -normal().dot(origin());
		const real dc = normal().dot(c.centre()) + D - c.r();
		if ( dc<=constants::EPSILON )
		{
			u1 = u2 = (dc==0)?0:(dc/c.r()-1);
			return true;
		}
		if ( da==0 )
		{
			u1 = u2 = -(D+dc)/db;
			return u1>0;
		}
		else
		{
			const real sDet = db*db - 4*da*dc;
			if ( sDet<constants::EPSILON ) return false;
			const real Det = sqrt(sDet);
			const real _12da = 1/(2*da); 
			u1 = -(db-Det)*_12da; //
			u2 = -(db+Det)*_12da; //
			return u1>=0 && u1<=1 && u2>=0&&u2<=1;
		}

		return false;
	}
	//
	// the very same function, just without the radius
	//
	bool intersect_sweep_point(const C2DPoint& c, const C2DVector& v, 
		const C2DVector& a, real& u1, real& u2) const
	{
		const real da = normal().dot(v)*0.5;
		const real db = normal().dot(v);
		const real D = -normal().dot(origin());
		const real dc = normal().dot(c) + D;
		if ( dc<=constants::EPSILON )
		{
			u1 = u2 = dc;
			return true;
		}
		if ( da==0 )
		{
			u1 = u2 = -(D+dc)/db;
			return u1>0;
		}
		else
		{
			const real sDet = db*db - 4*da*dc;
			if ( sDet<=constants::EPSILON ) return false;
			const real Det = sqrt(sDet);
			const real _12da = 1/(2*da); 
			u1 = -(db-Det)*_12da; //
			u2 = -(db+Det)*_12da; //
			return u1>=0 && u1<=1 && u2>=0&&u2<=1;
		}

		return false;
	}
};

//
// 3DPlane
//
class OVRLIBAPI C3DPlane
{
	C3DPoint m_origin;
	C3DVector m_normal;

public:
	C3DPlane()
	{ }
	C3DPlane(real x, real y, real z, real nx, real ny, real nz)
		:m_origin(x,y,z), m_normal(nx,ny,nz)
	{ }
	C3DPlane(const C3DPoint& o, const C3DVector& n)
		:m_origin(o), m_normal(n)
	{ }
	C3DPlane(const C3DPlane& p)
	{
		*this = p;
	}
	~C3DPlane()
	{ }

	C3DPlane& operator=(const C3DPlane& p)
	{
		origin() = p.origin();
		normal() = p.normal();
		return *this;
	}

	C3DPoint origin() const { return m_origin; }
	C3DVector normal() const { return m_normal; }
	C3DPoint& origin() { return m_origin; }
	C3DVector& normal() { return m_normal; }

	real dot(const C3DPoint& p) const
	{
		C3DPoint tmp(p);
		tmp -= origin();
		return normal().dot(tmp);
	}
	real distance(const C3DPoint& p) const
	{
		C3DVector tmp(normal());
		tmp.normalize();
		return tmp.dot(p);
	}
	real distance_unit(const C3DPoint& p) const
	{
		return normal().dot(p);
	}

	//
	// intersection routines. 
	// all routines return boolean representing whether
	// there was a collision
	// and also returns a local time constant for interpolating into
	// an intersection
	//
	bool intersect_line(const C3DLine& l, real& mu) const
	{
		const real Ax = l.x2() - l.x1();
		const real Ay = l.y2() - l.y1();
		const real Az = l.z2() - l.z1();
		const real D = - normal().x() * origin().x() - normal().y() * origin().y() - normal().z() * origin().z();
		const real denom = normal().x() * Ax + normal().y() * Ay + normal().z()*Az;
		if ( fabs(D)<constants::EPSILON )
			return false;
		mu = -(D + normal().x() * l.x1() + normal().y() * l.y1() + normal().z() * l.z1()) / denom;
		if ( mu < 0 || mu > 1 )   /* Intersection not along line segment */
			return false;
		return true;
	}
	bool intersect_sphere(const C3DSphere& c, real& u) const
	{
		const real d = distance_unit(c.centre());
		const real R = c.r();
		if ( d<=R && d>=-R )
		{
			u = (d==0)?0:R/d;
			return true;
		}
		else
			return false;
	}
	//
	// NOTE: no checkings for if velocity is zero
	//
	bool intersect_sweep_sphere(const C3DSphere& c, const C3DVector& v, 
		const C3DVector& a, real& u1, real& u2) const
	{
		const real da = normal().dot(v)*0.5;
		const real db = normal().dot(v);
		const real D = -normal().dot(origin());
		const real dc = normal().dot(c.centre()) + D - c.r();
		if ( dc<=constants::EPSILON )
		{
			u1 = u2 = (dc==0)?0:(dc/c.r()-1);
			return true;
		}
		if ( da==0 )
		{
			u1 = u2 = -(D+dc)/db;
			return u1>0;
		}
		else
		{
			const real sDet = db*db - 4*da*dc;
			if ( sDet<=constants::EPSILON ) return false;
			const real Det = sqrt(sDet);
			const real _12da = 1/(2*da); 
			u1 = -(db-Det)*_12da; //
			u2 = -(db+Det)*_12da; //
			return u1>=0 && u1<=1 && u2>=0&&u2<=1;
		}

		return false;
	}
	//
	// the very same function, just without the radius
	//
	bool intersect_sweep_point(const C3DPoint& c, const C3DVector& v, 
		const C3DVector& a, real& u1, real& u2) const
	{
		const real da = normal().dot(v)*0.5;
		const real db = normal().dot(v);
		const real D = -normal().dot(origin());
		const real dc = normal().dot(c) + D;
		if ( dc<=constants::EPSILON )
		{
			u1 = u2 = dc;
			return true;
		}
		if ( da==0 )
		{
			u1 = u2 = -(D+dc)/db;
			return u1>0;
		}
		else
		{
			const real sDet = db*db - 4*da*dc;
			if ( sDet<=constants::EPSILON ) return false;
			const real Det = sqrt(sDet);
			const real _12da = 1/(2*da); 
			u1 = -(db-Det)*_12da; //
			u2 = -(db+Det)*_12da; //
			return u1>=0 && u1<=1 && u2>=0&&u2<=1;
		}

		return false;
	}
};

//
// 4DPlane
//
class OVRLIBAPI C4DPlane
{
	C4DPoint m_origin;
	C4DVector m_normal;

public:
	C4DPlane()
	{ }
	C4DPlane(real x, real y, real z, real w, real nx, real ny, real nz, real nw)
		:m_origin(x,y,z,w), m_normal(nx,ny,nz,nw)
	{ }
	C4DPlane(const C4DPoint& o, const C4DVector& n)
		:m_origin(o), m_normal(n)
	{ }
	C4DPlane(const C4DPlane& p)
	{
		*this = p;
	}
	~C4DPlane()
	{ }

	C4DPlane& operator=(const C4DPlane& p)
	{
		origin() = p.origin();
		normal() = p.normal();
		return *this;
	}

	C4DPoint origin() const { return m_origin; }
	C4DVector normal() const { return m_normal; }
	C4DPoint& origin() { return m_origin; }
	C4DVector& normal() { return m_normal; }

	real dot(const C4DPoint& p) const
	{
		C4DPoint tmp(p);
		tmp -= origin();
		return normal().dot(tmp);
	}
	real distance(const C4DPoint& p) const
	{
		C4DVector tmp(normal());
		tmp.normalize();
		return tmp.dot(p);
	}
	real distance_unit(const C4DPoint& p) const
	{
		return normal().dot(p);
	}

	//
	// intersection routines. 
	// all routines return boolean representing whether
	// there was a collision
	// and also returns a local time constant for interpolating into
	// an intersection
	//
	bool intersect_line(const C4DLine& l, C4DPoint& p) const
	{
		const real Ax = l.x2() - l.x1();
		const real Ay = l.y2() - l.y1();
		const real Az = l.z2() - l.z1();
		const real Aw = l.w2() - l.w1();
		const real D = - normal().x() * origin().x() - normal().y() * origin().y() - 
			normal().z() * origin().z() - normal().w() * origin().w();
		const real denom = normal().x() * Ax + normal().y() * Ay + normal().z()*Az + normal().w()*Aw;
		if ( fabs(D)<constants::EPSILON )
			return false;
		const real mu = -(D + normal().x() * l.x1() + normal().y() * l.y1() + 
			normal().z() * l.z1() + normal().w() * l.w1()) / denom;
		if ( mu < 0 || mu > 1 )   /* Intersection not along line segment */
			return false;
		p.x() = l.x1() + mu * Ax;
		p.y() = l.y1() + mu * Ay;
		p.z() = l.z1() + mu * Az;
		p.w() = l.w1() + mu * Aw;
		return true;
	}
	bool intersect_sphere(const C4DSphere& c, real& u) const
	{
		const real d = distance_unit(c.centre());
		const real R = c.r();
		if ( d<=R && d>=-R )
		{
			u = (d==0)?0:R/d;
			return true;
		}
		else
			return false;
	}
	//
	// NOTE: no checkings for if velocity is zero
	//
	bool intersect_sweep_sphere(const C4DSphere& c, const C4DVector& v, 
		const C4DVector& a, real& u1, real& u2) const
	{
		const real da = normal().dot(v)*0.5;
		const real db = normal().dot(v);
		const real D = -normal().dot(origin());
		const real dc = normal().dot(c.centre()) + D - c.r();
		if ( dc<=constants::EPSILON )
		{
			u1 = u2 = (dc==0)?0:dc/c.r()-1;
			return true;
		}
		if ( da==0 )
		{
			u1 = u2 = -(D+dc)/db;
			return u1>0;
		}
		else
		{
			const real sDet = db*db - 4*da*dc;
			if ( sDet<=constants::EPSILON ) return false;
			const real Det = sqrt(sDet);
			const real _12da = 1/(2*da); 
			u1 = -(db-Det)*_12da; //
			u2 = -(db+Det)*_12da; //
			return u1>=0 && u1<=1 && u2>=0&&u2<=1;
		}

		return false;
	}
	//
	// the very same function, just without the radius
	//
	bool intersect_sweep_point(const C4DPoint& c, const C4DVector& v, 
		const C4DVector& a, real& u1, real& u2) const
	{
		const real da = normal().dot(v)*0.5;
		const real db = normal().dot(v);
		const real D = -normal().dot(origin());
		const real dc = normal().dot(c) + D;
		if ( dc<=constants::EPSILON )
		{
			u1 = u2 = dc;
			return true;
		}
		if ( da==0 )
		{
			u1 = u2 = -(D+dc)/db;
			return u1>0;
		}
		else
		{
			const real sDet = db*db - 4*da*dc;
			if ( sDet<=constants::EPSILON ) return false;
			const real Det = sqrt(sDet);
			const real _12da = 1/(2*da); 
			u1 = -(db-Det)*_12da; //
			u2 = -(db+Det)*_12da; //
			return u1>=0 && u1<=1 && u2>=0&&u2<=1;
		}

		return false;
	}
};

};

#endif // define AFX_COMSHAPS_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_
