/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/dx8/ovrltxpool_dx8.h,v $
 * $Implementation: ~/src/pipeline/txpool.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:20 $
 * $Description: 3DGraphics Pipeline::TXPool $
 *
 * $Log: ovrltxpool_dx8.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:20  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design [DX8 version]
 *
 */



#if !defined(__OVRLTXPOOL_DX8_HPP)
#define __OVRLTXPOOL_DX8_HPP

#include "common/all.h"
#include "pipeline/ovrltxpool.h"
#include <d3dx8.h>

namespace openvrl {

/**
 *  CplTXPool class
 */
class OVRLIBAPI CplTXPool_DX8 : public CplTXPool
{
protected:
	LPDIRECT3DDEVICE8 m_pd3dDevice;

	virtual bool freeup_entry(HTX hTX);

public:
	virtual HTX create(ulong Width, ulong Height, ulong Levels, DWORD Usage, DWORD Format);
	virtual HTX load(const CHAR* path);
	virtual HTX expand(HTX);
	virtual BYTE* lock(HTX, ulong level, ulong* pitch);
	virtual BYTE* lock_rect(HTX, ulong level, ulong left, ulong top, ulong right, ulong bottom, ulong* pitch);
	virtual bool unlock(HTX hTX, ulong level);
	virtual bool release(HTX hTX, DWORD usage);

	/**
	 *
	 */
	CplTXPool_DX8(LPDIRECT3DDEVICE8 lpd3d);
	~CplTXPool_DX8();

	virtual ulong what() const {	return ORW_TXPOOL;}
	virtual CHAR* get_name() const 	{ return "OpenVRL Pipeline VertexBuffer Pool DX8"; }
};

};

#endif /* __OVRLTXPOOL_DX8_HPP */
