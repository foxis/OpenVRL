/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/dx9/ovrlvbpool_dx9.h,v $
 * $Implementation: ~/src/pipeline/vbpool.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:20 $
 * $Description: 3DGraphics Pipeline::VBPool $
 *
 * $Log: ovrlvbpool_dx9.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:20  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design [DX8 version]
 *
 */



#if !defined(__OVRLVBPOOL_DX9_HPP)
#define __OVRLVBPOOL_DX9_HPP

#include "common/all.h"
#include "pipeline/vbpool.h"
#include <d3dx9.h>

namespace openvrl {

/**
 *  CplVBPool class
 */
class OVRLIBAPI CplVBPool_DX9 : public CplVBPool
{
protected:
	LPDIRECT3DDEVICE9 m_pd3dDevice;

	virtual bool freeup_entry(HVB hVB);

public:
	virtual HVB create(ulong length, WORD format, DWORD usage, const BYTE* buf=0);
	virtual HVB expand(HVB);
	virtual BYTE* lock(HVB, ulong offset=0, ulong size=0);
	virtual bool unlock(HVB hVB);
	virtual bool release(HVB hVB, DWORD usage);

	/**
	 *
	 */
	CplVBPool_DX9(LPDIRECT3DDEVICE9 lpd3d);
	~CplVBPool_DX9();
};

};

#endif /* __OVRLVBPOOL_DX8_HPP */
