/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/vspool.h,v $
 * $Implementation: ~/src/pipeline/VSpool.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:20 $
 * $Description: 3DGraphics Pipeline::VSPool $
 *
 * $Log: vspool.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:20  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design
 *
 */



#if !defined(__OVRLVSPOOL_HPP)
#define __OVRLVSPOOL_HPP

#include "common/all.h"
#include "pipeline/basepool.h"

namespace openvrl {

class OVRLIBAPI CplVSPool;
typedef CBasePoolEntry<CplVSPool> *HVS;

/**
 *  CplVSPool class
 */
class OVRLIBAPI CplVSPool : public CplBasePool< CBasePoolEntry<CplVSPool> >
{
protected:
	//
	// virtual void freeup_entry(PoolEntry);
	//

public:
	virtual HVS create(DWORD handler) = 0;
	virtual HVS expand(HVS) = 0;
	virtual BYTE* lock(HVS, ulong offset=0, ulong size=0) = 0;
	virtual bool unlock(HVS hVS) = 0;
	virtual bool release(HVS hVS, DWORD usage) = 0;

	/**
	 *
	 */
	CplVSPool(HVS head);
	~CplVSPool();
};

};

#endif /* __OVRLVSPOOL_HPP */
