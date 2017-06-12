/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/pattern.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/03 11:24:24 $
 * $Description:  $
 *
 * $Log: pattern.h,v $
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(__COMPTTRN_H)
#define __COMPTTRN_H

#include "common/string.h"

namespace openvrl {

class CPattern : public CString
{
public:
	CPattern(const CString& pattern)
		: CString(pattern)
	{ }
	CPattern(const CPattern& pattern)
		: CString(pattern)
	{ }
	~CPattern() 
	{ }

	virtual int operator==(const CString& a) const;
};

};

#endif // !defined(__COMPTTRN_H)