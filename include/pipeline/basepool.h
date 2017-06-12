/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/basepool.h,v $
 * $Implementation: ~/src/pipeline/basepool.cc $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/03/09 12:24:08 $
 * $Description: 3DGraphics Pipeline::*Pool $
 *
 * $Log: basepool.h,v $
 * Revision 1.2  2005/03/09 12:24:08  foxis
 * . fixed memory leaks
 * . fixed OVRL_ASSERT issue in release mode
 *   [still to fix: TPL_ASSERT, now - just a hack]
 *
 * Revision 1.1.1.1  2005/02/02 15:39:19  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design
 *
 */



#if !defined(__OVRLBASEPOOL_HPP)
#define __OVRLBASEPOOL_HPP

#include "common/all.h"

namespace openvrl {

//
// base pool entry class
//
template<class BasePool>
class OVRLIBAPI CBasePoolEntry
{
public:
	HANDLER hBase;
	DWORD dwFormat;
	ulong ulIndex;
	ulong ulSize;
	BYTE* pLocked;

	CBasePoolEntry* next;
	CBasePoolEntry* prev;

	BasePool*		pool;
	friend BasePool;

	void clear(BasePool* p=0);

	//
	CBasePoolEntry(BasePool* p=0) : pool(p) { }
	~CBasePoolEntry() { }
};


//
// Base Pool class
//
template < class PoolEntry >
class OVRLIBAPI CplBasePool 
{
protected:
	PoolEntry*	m_Head;

	bool add_entry(PoolEntry* hBase);
	bool del_entry(PoolEntry* hBase);
	PoolEntry* new_entry();
	virtual bool freeup_entry(PoolEntry* hBase) = 0;

public:
	bool optimize();
	bool freeup();
	/**
	 *
	 */
	CplBasePool(PoolEntry* head) : m_Head(head)
	{	}
	~CplBasePool()
	{	}
};

#include "pipeline/ovrlbasepool.inl"

};

#endif	//
