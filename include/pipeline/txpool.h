/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/txpool.h,v $
 * $Implementation: ~/src/pipeline/txpool.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:20 $
 * $Description: 3DGraphics Pipeline::TXPool $
 *
 * $Log: txpool.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:20  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design
 *
 */



#if !defined(__OVRLTXPOOL_HPP)
#define __OVRLTXPOOL_HPP

#include "common/all.h"
#include "pipeline/basepool.h"

namespace openvrl {

class OVRLIBAPI CplTXPool;
typedef CBasePoolEntry<CplTXPool> *HTX;

/**
 *  CplTXPool class
 */
class OVRLIBAPI CplTXPool : public CplBasePool< CBasePoolEntry<CplTXPool> >
{
protected:
	//
	// virtual bool freeup_entry(PoolEntry);
	//

public:
	virtual HTX create(ulong Width, ulong Height, ulong Levels, DWORD Usage, DWORD Format) = 0;
	virtual HTX load(const CHAR* path) = 0;
	virtual HTX expand(HTX) = 0;
	virtual BYTE* lock(HTX, ulong level, ulong* pitch) = 0;
	virtual BYTE* lock_rect(HTX, ulong level, ulong left, ulong top, ulong right, ulong bottom, ulong* pitch) = 0 ;
	virtual bool unlock(HTX hTX, ulong level) = 0;
	virtual bool release(HTX hTX, DWORD usage) = 0;
	/**
	 *
	 */
	CplTXPool(HTX head);
	~CplTXPool();
};

};

#endif /* __OVRLTXPOOL_HPP */
