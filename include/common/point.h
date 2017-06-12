/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/point.h,v $
 * $Implementation: ~/src/ $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:12 $
 * $Description:  $
 *
 * $Log: point.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:12  foxis
 * sources import
 *
 * Revision 0.3  20010411  :: FoxiE
 *
 */

#if !defined(AFX_COMPOINT_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_)
#define AFX_COMCPOINT_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

#include "common/types.h"

namespace openvrl {

//
// 2D Point class OVRLIBAPI
//
class OVRLIBAPI C2DPoint
{
protected:
	real m_x;
	real m_y;

public:
	C2DPoint()
	{ }
	C2DPoint(real _x, real _y)
	{
		x() = _x;
		y() = _y;
	}
	C2DPoint(const C2DPoint& pt)
	{
		*this = pt;
	}
	~C2DPoint()
	{ }

	C2DPoint& operator=(const C2DPoint& pt)
	{
		x() = pt.x();
		y() = pt.y();
		return *this;
	}

	C2DPoint& operator+=(const C2DPoint& pt)
	{
		x() += pt.x();
		y() += pt.y();
		return *this;
	}
	C2DPoint& operator-=(const C2DPoint& pt)
	{
		x() -= pt.x();
		y() -= pt.y();
		return *this;
	}
	C2DPoint& operator*=(real k)
	{
		x() *= k;
		y() *= k;
		return *this;
	}
	C2DPoint& operator/=(real k) 
	{
		const real _1k = 1/k;
		x() *= _1k;
		y() *= _1k;
		return *this;
	}
	C2DPoint operator+(const C2DPoint& pt) const
	{
		return C2DPoint(x()+pt.x(), y()+pt.y());
	}
	C2DPoint operator-(const C2DPoint& pt) const
	{
		return C2DPoint(x()-pt.x(), y()-pt.y());
	}
	C2DPoint operator*(real k) const
	{
		return C2DPoint(x()*k, y()*k);
	}
	C2DPoint operator/(real k) const
	{
		const real _1k = 1/k;
		return C2DPoint(x()*_1k, y()*_1k);
	}
	real sq_distance(const C2DPoint& pt) const
	{
		return (pt.x()-x())*(pt.x()-x()) + (pt.y()-y())*(pt.y()-y());
	}
	real distance(const C2DPoint& pt) const
	{
		return sqrt(sq_distance(pt));
	}

	real x() const { return m_x; }
	real y() const { return m_y; }
	real& x() { return m_x; }
	real& y() { return m_y; }
	real x(real x) { return m_x = x; }
	real y(real y) { return m_y = y; }
};


//
// 3D Point class OVRLIBAPI
//
class OVRLIBAPI C3DPoint
{
protected:
	real m_x;
	real m_y;
	real m_z;

public:
	C3DPoint()
	{ }
	C3DPoint(real _x, real _y, real _z)
	{
		x() = _x;
		y() = _y;
		z() = _z;
	}
	C3DPoint(const C3DPoint& pt)
	{
		*this = pt;
	}
	~C3DPoint()
	{ }

	C3DPoint& operator=(const C3DPoint& pt)
	{
		x() = pt.x();
		y() = pt.y();
		z() = pt.z();
		return *this;
	}

	C3DPoint& operator+=(const C3DPoint& pt)
	{
		x() += pt.x();
		y() += pt.y();
		z() += pt.z();
		return *this;
	}
	C3DPoint& operator-=(const C3DPoint& pt)
	{
		x() -= pt.x();
		y() -= pt.y();
		z() -= pt.z();
		return *this;
	}
	C3DPoint& operator*=(real k)
	{
		x() *= k;
		y() *= k;
		z() *= k;
		return *this;
	}
	C3DPoint& operator/=(real k) 
	{
		const real _1k = 1/k;
		x() *= _1k;
		y() *= _1k;
		z() *= _1k;
		return *this;
	}
	C3DPoint operator+(const C3DPoint& pt) const
	{
		return C3DPoint(x()+pt.x(), y()+pt.y(), z()+pt.z());
	}
	C3DPoint operator-(const C3DPoint& pt) const
	{
		return C3DPoint(x()-pt.x(), y()-pt.y(), z()-pt.z());
	}
	C3DPoint operator*(real k) const
	{
		return C3DPoint(x()*k, y()*k, z()*k);
	}
	C3DPoint operator/(real k) const
	{
		const real _1k = 1/k;
		return C3DPoint(x()*_1k, y()*_1k, z()*_1k);
	}
	real sq_distance(const C3DPoint& pt) const
	{
		return (pt.x()-x())*(pt.x()-x()) + (pt.y()-y())*(pt.y()-y()) + (pt.z()-z())*(pt.z()-z());
	}
	real distance(const C3DPoint& pt) const
	{
		return sqrt(sq_distance(pt));
	}

	real x() const { return m_x; }
	real y() const { return m_y; }
	real z() const { return m_z; }
	real& x() { return m_x; }
	real& y() { return m_y; }
	real& z() { return m_z; }
	real x(real x) { return m_x = x; }
	real y(real y) { return m_y = y; }
	real z(real z) { return m_z = z; }
};

//
// 4DPoint class OVRLIBAPI
//
class OVRLIBAPI C4DPoint
{
protected:
	real m_x;
	real m_y;
	real m_z;
	real m_w;

public:
	C4DPoint()
	{ }
	C4DPoint(real _x, real _y, real _z, real _w)
	{
		x() = _x;
		y() = _y;
		z() = _z;
		w() = _w;
	}
	C4DPoint(const C4DPoint& pt)
	{
		*this = pt;
	}
	~C4DPoint()
	{ }

	C4DPoint& operator=(const C4DPoint& pt)
	{
		x() = pt.x();
		y() = pt.y();
		z() = pt.z();
		w() = pt.w();
		return *this;
	}

	C4DPoint& operator+=(const C4DPoint& pt)
	{
		x() += pt.x();
		y() += pt.y();
		z() += pt.z();
		w() += pt.w();
		return *this;
	}
	C4DPoint& operator-=(const C4DPoint& pt)
	{
		x() -= pt.x();
		y() -= pt.y();
		z() -= pt.z();
		w() -= pt.w();
		return *this;
	}
	C4DPoint& operator*=(real k)
	{
		x() *= k;
		y() *= k;
		z() *= k;
		w() *= k;
		return *this;
	}
	C4DPoint& operator/=(real k) 
	{
		const real _1k = 1/k;
		x() *= _1k;
		y() *= _1k;
		z() *= _1k;
		w() *= _1k;
		return *this;
	}
	C4DPoint operator+(const C4DPoint& pt) const
	{
		return C4DPoint(x()+pt.x(), y()+pt.y(), z()+pt.z(), w()+pt.w());
	}
	C4DPoint operator-(const C4DPoint& pt) const
	{
		return C4DPoint(x()-pt.x(), y()-pt.y(), z()-pt.z(), w()-pt.w());
	}
	C4DPoint operator*(real k) const
	{
		return C4DPoint(x()*k, y()*k, z()*k, w()*k);
	}
	C4DPoint operator/(real k) const
	{
		const real _1k = 1/k;
		return C4DPoint(x()*_1k, y()*_1k, z()*_1k, w()*_1k);
	}
	real sq_distance(const C4DPoint& pt) const
	{
		return (pt.x()-x())*(pt.x()-x()) + (pt.y()-y())*(pt.y()-y()) + (pt.z()-z())*(pt.z()-z());
	}
	real distance(const C4DPoint& pt) const
	{
		return sqrt(sq_distance(pt));
	}

	real x() const { return m_x; }
	real y() const { return m_y; }
	real z() const { return m_z; }
	real w() const { return m_w; }
	real& x() { return m_x; }
	real& y() { return m_y; }
	real& z() { return m_z; }
	real& w() { return m_w; }
	real x(real x) { return m_x = x; }
	real y(real y) { return m_y = y; }
	real z(real z) { return m_z = z; }
	real w(real w) { return m_w = w; }
};

};

#endif // !defined(AFX_COMPOINT_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_)
