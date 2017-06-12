/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/interp/InterpolationLine.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/03 11:24:24 $
 * $Description:  $
 *
 * $Log: InterpolationLine.h,v $
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(AFX_INTERPOLATIONLINE_H__86ED88ED_A1A8_11D6_8083_A5BA507CC382__INCLUDED_)
#define AFX_INTERPOLATIONLINE_H__86ED88ED_A1A8_11D6_8083_A5BA507CC382__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common/all.h"
#include "interp/InterpolationEngine.h"

namespace openvrl {

class OVRLIBAPI CInterpolationLine : public CInterpolationEngine  
{
	C2DPoint	m_p1, m_p2;
	C2DPoint	m_p, m_pd;
	real m_pt[2];
	real m_delta;

	CInterpolationLine();
public:
	CInterpolationLine(real x1, real y1, real x2, real y2, real delta);
	CInterpolationLine(const C2DPoint& p1, const C2DPoint& p2, real delta);
	virtual ~CInterpolationLine();

	virtual int Run();
	virtual void onStart();
	virtual void onStop();
	virtual void onNewPoint(const real* p, num_t n);
	virtual void Interpolate();

	C2DPoint get_p1() const { return m_p1; }
	C2DPoint get_p2() const { return m_p2; }
	C2DPoint get_p() const { return m_p; }
	C2DPoint get_pd() const { return m_pd; }

	real get_x1() const { return m_p1.x(); }
	real get_y1() const { return m_p1.y(); }
	real get_x2() const { return m_p2.x(); }
	real get_y2() const { return m_p2.y(); }
	real get_x() const { return m_p.x(); }
	real get_y() const { return m_p.y(); }
	real get_dx() const { return m_pd.x(); }
	real get_dy() const { return m_pd.y(); }
	real get_delta() const { return m_delta; }

	C2DPoint& get_p1() { return m_p1; }
	C2DPoint& get_p2() { return m_p2; }
	C2DPoint& get_p() { return m_p; }
	C2DPoint& get_pd() { return m_pd; }

	real& get_x1() { return m_p1.x(); }
	real& get_y1() { return m_p1.y(); }
	real& get_x2() { return m_p2.x(); }
	real& get_y2() { return m_p2.y(); }
	real& get_x() { return m_p.x(); }
	real& get_y() { return m_p.y(); }
	real& get_dx() { return m_pd.x(); }
	real& get_dy() { return m_pd.y(); }
	real& get_delta() { return m_delta; }

	void get_p1(const C2DPoint& p) { m_p1=p; }
	void get_p2(const C2DPoint& p) { m_p2=p; }
	void get_p(const C2DPoint& p) { m_p=p; }
	void get_pd(const C2DPoint& p) { m_pd=p; }

	void set_x1(real x1) { m_p1.x()=x1; }
	void set_y1(real y1) { m_p1.y()=y1; }
	void set_x2(real x2) { m_p2.x()=x2; }
	void set_y2(real y2) { m_p2.y()=y2; }
	void set_x(real x) { m_p.x()=x; }
	void set_y(real y) { m_p.y()=y; }
	void set_dx(real dx) { m_pd.x()=dx; }
	void set_dy(real dy) { m_pd.y()=dy; }
	void set_delta(real delta) { m_delta=delta; }
};

};

#endif // !defined(AFX_INTERPOLATIONLINE_H__86ED88ED_A1A8_11D6_8083_A5BA507CC382__INCLUDED_)
