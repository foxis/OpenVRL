/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/system/ovrllog.h,v $
 * $Implementation: ~/src/ $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:21 $
 * $Description:  $
 *
 * $Log: ovrllog.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:21  foxis
 * sources import
 *
 * Revision 0.3  20010411  :: FoxiE
 *
 */

#if !defined(AFX_OVRLLOG_H__92FDEC01_AEB0_11D6_8083_D516DD2EE818__INCLUDED_)
#define AFX_OVRLLOG_H__92FDEC01_AEB0_11D6_8083_D516DD2EE818__INCLUDED_

#include "common/all.h"
#include "common/string.h"

namespace openvrl {

class OVRLIBAPI CLog  
{
	CString m_path;

public:
	CLog(const CString& path="log.txt");
	CLog(const CString& str, const CString& path="log.txt");
	virtual ~CLog();

	void write(const CString& str)
	{
		ovrl_dump_str_to_file(m_path.c_str(), str.c_str());
	}
	void write(int i)
	{
		char str[64];
		sprintf(str, "%i", i);
		write(str);
	}
	void write(ulong ui)
	{
		char str[64];
		sprintf(str, "%u", ui);
		write(str);
	}
	void write(double r)
	{
		char str[128];
		sprintf(str, "%20.20f", r);
		write(str);
	}

	CLog& operator<<(double r)
	{
		write(r);
		return *this;
	}
	CLog& operator<<(int r)
	{
		write(r);
		return *this;
	}
	CLog& operator<<(ulong r)
	{
		write(r);
		return *this;
	}
	CLog& operator<<(const CString& r)
	{
		write(r);
		return *this;
	}
};

};

#endif // !defined(AFX_OVRLLOG_H__92FDEC01_AEB0_11D6_8083_D516DD2EE818__INCLUDED_)
