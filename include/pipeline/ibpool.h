/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/ibpool.h,v $
 * $Implementation: ~/src/pipeline/ibpool.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:19 $
 * $Description: 3DGraphics Pipeline::IBPool $
 *
 * $Log: ibpool.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:19  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design
 *
 */



#if !defined(__OVRLIBPOOL_HPP)
#define __OVRLIBPOOL_HPP

#include "common/all.h"
#include "pipeline/basepool.h"

namespace openvrl {

class OVRLIBAPI CplIBPool;
typedef CBasePoolEntry<CplIBPool> *HIB;

/**
 *  CplIBPool class
 */
class OVRLIBAPI CplIBPool : public CplBasePool< CBasePoolEntry<CplIBPool> >
{
protected:
	//
	// virtual void freeup_entry(PoolEntry);
	//

public:
	virtual HIB create(ulong length, WORD format, DWORD usage, const BYTE* buf=0) = 0;
	virtual HIB expand(HIB) = 0;
	virtual BYTE* lock(HIB, ulong offset=0, ulong size=0) = 0;
	virtual bool unlock(HIB hIB) = 0;
	virtual bool release(HIB hIB, DWORD usage) = 0;

	/**
	 *
	 */
	CplIBPool(HIB head);
	~CplIBPool();
};

};

#endif /* __OVRLIBPOOL_HPP */
