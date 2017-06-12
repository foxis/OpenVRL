/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/system/ovrlclock.h,v $
 * $Implementation: /src/clock.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:21 $
 * $Description: Clock class $
 *
 * $Log: ovrlclock.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:21  foxis
 * sources import
 *
 * Revision 0.1  20020105  18:27:36 FoxiE
 * Pradejau rasyti logus :)
 *
 */


#if !defined(__ovrl_OVRLCLOCK_HPP)
#define __ovrl_OVRLCLOCK_HPP

#include "common/all.h"

namespace openvrl {

#if !defined(__WINDOWS__) && !defined (WIN32)
#define GetTickCount() clock()
#endif

class OVRLIBAPI CClock 
{
protected:
        ulong m_ticks;
        ulong m_hold_ticks;
	bool m_hold;

public:
        virtual void reset()     { m_ticks = ticks(); unhold(); }
        virtual ulong elapsed() const  { return ticks()-m_ticks; }
        virtual ulong on_start() const { return m_ticks; }
	virtual ulong ticks() const  { return (m_hold)?m_hold_ticks:GetTickCount(); }
	virtual ulong hold() 
	{ 
		m_hold = true; 
		m_hold_ticks = GetTickCount();
		return elapsed();
	}
	virtual void unhold()
	{
		m_hold = false;
	}

	virtual void NOOP(void) const 
	{
		Sleep(0);
	}

	virtual void noops(ulong n)
	{
		while ( !m_hold && elapsed()<n ) NOOP();
	}

	//
        CClock() { reset(); }
};

};

#endif /* !defined(__ovrl_OVRLCLOCK_HPP) */
