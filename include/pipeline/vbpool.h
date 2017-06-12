/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/vbpool.h,v $
 * $Implementation: ~/src/pipeline/vbpool.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:20 $
 * $Description: 3DGraphics Pipeline::VBPool $
 *
 * $Log: vbpool.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:20  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design
 *
 */



#if !defined(__OVRLVBPOOL_HPP)
#define __OVRLVBPOOL_HPP

#include "common/all.h"
#include "pipeline/basepool.h"

namespace openvrl {

class OVRLIBAPI CplVBPool;
typedef CBasePoolEntry<CplVBPool> *HVB;

/**
 *  CplVBPool class
 */
class OVRLIBAPI CplVBPool : public CplBasePool< CBasePoolEntry<CplVBPool> >
{
protected:
	//
	// virtual void freeup_entry(PoolEntry);
	//

public:
	virtual HVB create(ulong length, WORD format, DWORD usage, const BYTE* buf=0) = 0;
	virtual HVB expand(HVB) = 0;
	virtual BYTE* lock(HVB, ulong offset=0, ulong size=0) = 0;
	virtual bool unlock(HVB hVB) = 0;
	virtual bool release(HVB hVB, DWORD usage) = 0;

	/**
	 *
	 */
	CplVBPool(HVB head);
	~CplVBPool();
};

};

#endif /* __OVRLVBPOOL_HPP */
