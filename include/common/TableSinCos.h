/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/TableSinCos.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/03 11:24:24 $
 * $Description:  $
 *
 * $Log: TableSinCos.h,v $
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(AFX_TABLESINCOS_H__48B351E4_A216_11D6_8083_D66192D7171A__INCLUDED_)
#define AFX_TABLESINCOS_H__48B351E4_A216_11D6_8083_D66192D7171A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "common/types.h"
#include "common/constants.h"

namespace openvrl {

class OVRLIBAPI CTableSinCos 
{
	static double m_scale;
	static unsigned long m_ref_count;
	static double*	m_table;
	static unsigned long	m_size;

public:
	CTableSinCos();
	CTableSinCos(unsigned long size);
	~CTableSinCos();

	double get_at(unsigned long n) const
	{
		return m_table[n];
	}


	double fsin(double rad) const;
	double fcos(double rad) const;

	double sin(double rad) const;
	double cos(double rad) const;
	double arcsin(double x) const;
	double arccos(double x) const;
	double tg(double rad) const;
	double ctg(double rad) const;

	double rad2deg(double rad) const
	{
		return (180*rad)/constants::m_pi;
	}
	double deg2rad(double deg) const 
	{
		return (deg*constants::m_pi)/180.0;
	}

protected:
	void InitTable(unsigned long n);
	void ReleaseTable();
};

};

#endif // !defined(AFX_TABLESINCOS_H__48B351E4_A216_11D6_8083_D66192D7171A__INCLUDED_)
