/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/dx9/ovrlvspool_dx9.h,v $
 * $Implementation: ~/src/pipeline/VSpool.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:20 $
 * $Description: 3DGraphics Pipeline::VSPool $
 *
 * $Log: ovrlvspool_dx9.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:20  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design [DX8 version]
 *
 */



#if !defined(__OVRLVSPOOL_DX9_HPP)
#define __OVRLVSPOOL_DX9_HPP

#include "common/all.h"
#include "pipeline/vspool.h"
#include <d3dx9.h>

namespace openvrl {

/**
 *  CplVSPool class
 */
class OVRLIBAPI CplVSPool_DX9 : public CplVSPool
{
protected:
	LPDIRECT3DDEVICE9 m_pd3dDevice;

	virtual bool freeup_entry(HVS hVS);

public:
	virtual HVS create(DWORD handler);
	virtual HVS expand(HVS);
	virtual BYTE* lock(HVS, ulong offset=0, ulong size=0);
	virtual bool unlock(HVS hVS);
	virtual bool release(HVS hVS, DWORD usage);

	/**
	 *
	 */
	CplVSPool_DX9(LPDIRECT3DDEVICE9 lpd3d);
	~CplVSPool_DX9();
};

};

#endif /* __OVRLVSPOOL_DX8_HPP */
