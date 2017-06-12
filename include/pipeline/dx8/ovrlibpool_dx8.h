/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/dx8/ovrlibpool_dx8.h,v $
 * $Implementation: ~/src/pipeline/ibpool.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:20 $
 * $Description: 3DGraphics Pipeline::IBPool $
 *
 * $Log: ovrlibpool_dx8.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:20  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design [DX8 version]
 *
 */



#if !defined(__OVRLIBPOOL_DX8_HPP)
#define __OVRLIBPOOL_DX8_HPP

#include "common/all.h"
#include "pipeline/ovrlibpool.h"
#include <d3dx8.h>

namespace openvrl {

/**
 *  CplIBPool class
 */
class OVRLIBAPI CplIBPool_DX8 : public CplIBPool
{
protected:
	LPDIRECT3DDEVICE8 m_pd3dDevice;

	virtual bool freeup_entry(HIB hIB);

public:
	virtual HIB create(ulong length, WORD format, DWORD usage, const BYTE* buf=0);
	virtual HIB expand(HIB);
	virtual BYTE* lock(HIB, ulong offset=0, ulong size=0);
	virtual bool unlock(HIB hIB);
	virtual bool release(HIB hIB, DWORD usage);

	/**
	 *
	 */
	CplIBPool_DX8(LPDIRECT3DDEVICE8 lpd3d);
	~CplIBPool_DX8();

	virtual ulong what() const 
	{
		return ORW_IBPOOL;
	}

	virtual CHAR* get_name() const 
	{
		return "OpenVRL Pipeline IndexBuffer Pool DX8";
	}
};

};

#endif /* __OVRLIBPOOL_DX8_HPP */
