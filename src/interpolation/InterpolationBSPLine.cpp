#include "interp/InterpolationBSPline.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInterpolationBSPLine::CInterpolationBSPLine()
	:m_points(0), m_point(0), m_delta(1), m_u(0), m_t(4)
{
	m_point = 0;
}

CInterpolationBSPLine::CInterpolationBSPLine(const real* p, num_t n, real delta, uint t)
	:m_points(0), m_point(0), m_delta(delta), m_u(0), m_t(t)
{
	set_points(p, n);
}

CInterpolationBSPLine::CInterpolationBSPLine(const C2DPoint* p, num_t n, real delta, uint t)
	:m_points(0), m_point(0), m_delta(delta), m_u(0), m_t(t)
{
	set_points(p,n);
}

CInterpolationBSPLine::~CInterpolationBSPLine()
{  
	OVRL_DELETE(m_point);
}

void CInterpolationBSPLine::set_points(const real* p, num_t n)
{
	OVRL_DELETE(m_point);
	m_points = n;
	OVRL_NEW_EX(m_point,C2DPoint,n);
	for ( index_t i=0;i<n;i++ )
	{
		m_point[i].x() = p[i<<1];
		m_point[i].y() = p[(i<<1)+1];
	}
}
void CInterpolationBSPLine::set_points(const C2DPoint* p, num_t n)
{
	OVRL_DELETE(m_point);
	m_points = n;
	OVRL_NEW_EX(m_point,C2DPoint,n);
	for ( index_t i=0;i<n;i++ )
		m_point[i] = p[i];
}

int CInterpolationBSPLine::Run()
{
	return CInterpolationEngine::Run();
}

void CInterpolationBSPLine::onStart()
{
	m_p = m_point[0];
	m_length = (int)floor((size()-m_t+1)/m_delta);
	m_interval = 0;
	m_iterations = 0;
	OVRL_NEW_EX(m_u,int,size()+m_t);

	for ( index_t i=0; i<=size()-1+m_t; i++ )
	{
		if ( i<m_t )
			m_u[i]=0;
		else if ( (m_t<=i) && (i<=size()-1) )
			m_u[i]=i-m_t+1;
		else if (i>size()-1)
			m_u[i]=size()-m_t+1;  // if n-t=-2 then we're screwed, everything goes to 0
	}
}

void CInterpolationBSPLine::onStop()
{
	OVRL_DELETE(m_u);
}

void CInterpolationBSPLine::Interpolate()
{
	real temp;

	m_p.x() = 0;
	m_p.y() = 0;
	for ( index_t i=0; i<size(); i++ )
	{
		temp = blend(i,m_t);  // same blend is used for each dimension coordinate
		m_p.x() = m_p.x() + m_point[i].x() * temp;
		m_p.y() = m_p.y() + m_point[i].y() * temp;
	}

	m_pt[0] = m_p.x();
	m_pt[1] = m_p.y();
	onNewPoint(m_pt, 2);
	m_iterations++;
	m_interval += m_delta;
}

bool CInterpolationBSPLine::isFinished() const
{
	return CInterpolationEngine::isFinished();
}

void CInterpolationBSPLine::onNewPoint(const real* p, num_t n)
{
	char c=100;
//	c = (m_x-floor(m_x))*255*(m_y-floor(m_y));
//	SetPixel(m_hdc, (int)floor(p[0]), (int)floor(p[1]), RGB(c,c,c));
}


real CInterpolationBSPLine::blend(ulong k, uint t)  // calculate the blending value
{
	if (t==1)                     // base case for the recursion
	{
		if ((m_u[k]<=m_interval) && (m_interval<m_u[k+1]))
			return 1;
		else
			return 0;
	}
	else
	{
	    if ((m_u[k+t-1]==m_u[k]) && (m_u[k+t]==m_u[k+1]))  // check for divide by zero
			return 0;
		else if (m_u[k+t-1]==m_u[k]) // if a term's denominator is zero,use just the other
			return (m_u[k+t] - m_interval) / (m_u[k+t] - m_u[k+1]) * blend(k+1, t-1);
		else if (m_u[k+t]==m_u[k+1])
			return (m_interval - m_u[k]) / (m_u[k+t-1] - m_u[k]) * blend(k, t-1);
		else
			return (m_interval - m_u[k]) / (m_u[k+t-1] - m_u[k]) * blend(k, t-1) +
				(m_u[k+t] - m_interval) / (m_u[k+t] - m_u[k+1]) * blend(k+1, t-1);
	}
}

}