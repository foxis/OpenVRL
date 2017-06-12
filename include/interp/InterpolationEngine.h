/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/interp/InterpolationEngine.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/03 11:24:24 $
 * $Description:  $
 *
 * $Log: InterpolationEngine.h,v $
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */


#if !defined(AFX_INTERPOLATIONENGINE_H__86ED88EC_A1A8_11D6_8083_A5BA507CC382__INCLUDED_)
#define AFX_INTERPOLATIONENGINE_H__86ED88EC_A1A8_11D6_8083_A5BA507CC382__INCLUDED_

#include "common/all.h"

namespace openvrl {

class OVRLIBAPI CInterpolationEngine  
{
protected:
	num_t m_length;
	num_t m_iterations;

public:
	CInterpolationEngine();
	virtual ~CInterpolationEngine();

	virtual int Run();
	virtual bool isFinished() const 
	{
		return m_iterations>=m_length;
	}
	virtual void onStart() = 0;
	virtual void onStop() = 0;
	virtual void Interpolate() = 0;
	virtual void onNewPoint(const real* p, num_t n) = 0;
	num_t get_length() const { return m_length; }
	num_t get_iterations() const { return m_iterations; }
};

};

#endif // !defined(AFX_INTERPOLATIONENGINE_H__86ED88EC_A1A8_11D6_8083_A5BA507CC382__INCLUDED_)
