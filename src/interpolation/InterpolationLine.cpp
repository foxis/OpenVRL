#include <math.h>
#include "interp/InterpolationLine.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInterpolationLine::CInterpolationLine()
	:m_delta(1)
{ }

CInterpolationLine::CInterpolationLine(real x1, real y1, real x2, real y2, real delta)
	:m_p1(x1,y1), m_p2(x2,y2), m_delta(delta), m_p(x1,y1)
{ }

CInterpolationLine::CInterpolationLine(const C2DPoint& p1, const C2DPoint& p2, real delta)
	:m_p1(p1), m_p2(p2), m_delta(delta), m_p(p1)
{ }

CInterpolationLine::~CInterpolationLine()
{ }

int CInterpolationLine::Run() 
{
	return CInterpolationEngine::Run();
}


void CInterpolationLine::onStart() 
{
	real tmp;
	m_iterations = 0;
	m_p = m_p1;
	m_pd = m_p2-m_p1;
	tmp = m_p1.distance(m_p1);
	m_length = (unsigned long)floor(tmp/m_delta);
	m_pd *= m_delta/tmp;
}

void CInterpolationLine::onStop() 
{
}

void CInterpolationLine::Interpolate() 
{
	m_p += m_pd;
	m_pt[0] = m_p.x();
	m_pt[1] = m_p.y();
	onNewPoint(m_pt, 2);
	m_iterations++;
}

void CInterpolationLine::onNewPoint(const real *p, num_t n)
{
	char c=15;
//	c = (m_x-floor(m_x))*255*(m_y-floor(m_y));
//	SetPixel(m_hdc, (int)floor(p[0]), (int)floor(p[1]), RGB(c,c,c));
}

}