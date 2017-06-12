/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/interp/InterpolationBSPLine.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/03 11:24:24 $
 * $Description:  $
 *
 * $Log: InterpolationBSPLine.h,v $
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(AFX_INTERPOLATIONCInterpolationBSPLine_H__48B351E1_A216_11D6_8083_D66192D7171A__INCLUDED_)
#define AFX_INTERPOLATIONCInterpolationBSPLine_H__48B351E1_A216_11D6_8083_D66192D7171A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common/all.h"
#include "interp/InterpolationEngine.h"

namespace openvrl {

//
// CInterpolationBSPLine smth
//
class OVRLIBAPI CInterpolationBSPLine : public CInterpolationEngine  
{
	num_t m_points;
	C2DPoint*	m_point;
	C2DPoint	m_p;
	real		m_pt[2];
	real		m_delta;
	uint m_t;
	int			*m_u;
	real		m_increment, m_interval;

	CInterpolationBSPLine();
public:
	CInterpolationBSPLine(const real* p, num_t n, real delta, uint t=4);
	CInterpolationBSPLine(const C2DPoint* p, num_t n, real delta, uint t=4);
	virtual ~CInterpolationBSPLine();

	void set_points(const real* p, num_t n);
	void set_points(const C2DPoint* p, num_t n);

	virtual int Run();
	virtual void onStart();
	virtual void onStop();
	virtual void onNewPoint(const real* p, num_t n);
	virtual void Interpolate();

	virtual bool isFinished() const;

	C2DPoint get_at(index_t i) const { return m_point[i]; }
	real get_x_at(index_t i) const { return m_point[i].x(); }
	real get_y_at(index_t i) const { return m_point[i].y(); }
	real get_x() const { return m_p.x(); }
	real get_y() const { return m_p.y(); }
	real get_delta() const { return m_delta; }
	uint get_t() const { return m_t; }

	C2DPoint& get_at(index_t i) { return m_point[i]; }
	real& get_x_at(index_t i) { return m_point[i].x(); }
	real& get_y_at(index_t i) { return m_point[i].y(); }
	real& get_x() { return m_p.x(); }
	real& get_y() { return m_p.y(); }
	real& get_delta() { return m_delta; }
	uint& get_t() { return m_t; }

	void set_at(index_t i, const C2DPoint& p) { m_point[i]=p; }
	void set_x_at(index_t i, real x) { m_point[i].x()=x; }
	void set_y_at(index_t i, real y) { m_point[i].y()=y; }
	void set_x(real x) { m_p.x()=x; }
	void set_y(real y) { m_p.y()=y; }
	void set_delta(real delta) { m_delta=delta; }
	void set_t(uint t) { m_t=t; }

	size_t size() const { return m_points; }

protected:
	real blend(ulong k, uint t);
};

};

#endif // !defined(AFX_INTERPOLATIONCInterpolationBSPLine_H__48B351E1_A216_11D6_8083_D66192D7171A__INCLUDED_)
