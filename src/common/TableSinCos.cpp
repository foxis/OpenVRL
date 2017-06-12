#include "stdafx.h"

#include <math.h>
#include "common/TableSinCos.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

double* CTableSinCos::m_table = 0;
unsigned long CTableSinCos::m_size = 0;
unsigned long CTableSinCos::m_ref_count = 0;
double CTableSinCos::m_scale = 0;


CTableSinCos::CTableSinCos()
{
	if ( m_ref_count++==0 ) 
	{
		InitTable(1024);
	}
}

CTableSinCos::CTableSinCos(unsigned long size)
{
	if ( m_ref_count++==0 ) 
	{
		InitTable(size);
	}
}

CTableSinCos::~CTableSinCos()
{
	if ( --m_ref_count==0 )
	{
		ReleaseTable();
	}
}

double CTableSinCos::fsin(double rad) const
{
	double sin1, sin2;
	double index, tmp;

	index = rad * m_scale;
	tmp = floor(index);
	sin1 = get_at((unsigned long)tmp);
	sin2 = get_at((unsigned long)ceil(index));
	return sin1+ (sin2-sin1)*(index-tmp);
}

double CTableSinCos::fcos(double rad) const
{
	double cos1, cos2;
	double index, tmp;

	index = (constants::m_pi2-rad) * m_scale;
	tmp = floor(index);
	cos1 = get_at((unsigned long)tmp);
	cos2 = get_at((unsigned long)ceil(index));
	return cos1+ (cos2-cos1)*(index-tmp);
}

double CTableSinCos::sin(double rad) const
{
	double sin1, sin2;
	double index, tmp;
	if ( rad>constants::m_2pi || rad<-constants::m_2pi )
		rad = rad - constants::m_2pi*floor(rad*constants::m_12pi);
	if ( rad<0 )
		rad = _2pi()+rad;

	index = (rad - constants::m_pi2*floor(rad*constants::m_1pi2)) * m_scale;
	if ( rad>=pi2()&&rad<pi() || rad>=_3pi2()&&rad<_2pi() ) index = m_size-1-index;
	tmp = floor(index);
	sin1 = get_at((unsigned long)tmp);
	sin2 = get_at((unsigned long)ceil(index));
	tmp = sin1+ (sin2-sin1)*(index-tmp);
	if ( rad<=pi() )
		return tmp;
	else 
		return -tmp;
}

double CTableSinCos::cos(double rad) const
{
	double cos1, cos2;
	double index, tmp;
	if ( rad>=_2pi() || rad<=-_2pi() )
		rad = rad - _2pi()*floor(rad*_12pi());
	if ( rad<0 )
		rad = _2pi()+rad;

	index = m_size-1-(rad - pi2()*floor(rad*_1pi2())) * m_scale;
	if ( rad>=pi2()&&rad<pi() || rad>=_3pi2()&&rad<_2pi() ) index = m_size-1-index;
	tmp = floor(index);
	cos1 = get_at((unsigned long)tmp);
	cos2 = get_at((unsigned long)ceil(index));
	tmp = cos1 + (cos2-cos1)*(index-tmp);
	if ( rad>=pi2()&&rad<=_3pi2() )
		return -tmp;
	else
		return tmp;
}

double CTableSinCos::arcsin(double x) const
{
	return 0;
}

double CTableSinCos::arccos(double x) const
{
	return 0;
}

double CTableSinCos::tg(double rad) const
{
	return sin(rad)/cos(rad);
}

double CTableSinCos::ctg(double rad) const
{
	return cos(rad)/sin(rad);
}

void CTableSinCos::InitTable(unsigned long n)
{
	unsigned long i;
	double delta, a;
	double* ptr;

	m_table = new double[n];
	m_size = n;

	ptr = m_table;
	delta = pi2()/(double)(n-1);
	for ( a=0,i=0;i<n;i++,ptr++ )
	{
		*ptr = ::sin(a);
		a += delta;
	}

	m_scale = (n-1)*_1pi2();
}

void CTableSinCos::ReleaseTable()
{
	delete[] m_table;
	m_table = 0;
	m_size = 0;
}

}