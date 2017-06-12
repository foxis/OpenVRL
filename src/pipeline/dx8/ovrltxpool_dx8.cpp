#include "stdafx.h"

#include "system/ovrlsystem.h"
#include "pipeline/dx8/ovrltxpool_dx8.h"

namespace openvrl {


static DWORD convert_to_DX8_format(DWORD fmt);
static DWORD convert_to_DX8_usage(DWORD fmt);

/**
 * CplTXPool class
 */
CplTXPool_DX8::CplTXPool_DX8(LPDIRECT3DDEVICE8 lpd3d)
	:CplTXPool(0), m_pd3dDevice(lpd3d)
{
}

CplTXPool_DX8::~CplTXPool_DX8()
{
}


HTX CplTXPool_DX8::create(ulong Width, ulong Height, ulong Levels, DWORD Usage, DWORD Format)
{
	HTX hTX;
	LPDIRECT3DTEXTURE8 pTX;

	hTX = new_entry();
	if ( hTX==0 ) return 0;
	hTX->pool = this;

	Usage = convert_to_DX8_usage(Usage);
	hTX->dwFormat = convert_to_DX8_format(Format);
	hTX->ulSize = 0;
	hTX->ulIndex = 0;
	hTX->pLocked = 0;

    if( FAILED( m_pd3dDevice->CreateTexture(Width, Height, Levels, Usage, (D3DFORMAT)hTX->dwFormat, D3DPOOL_MANAGED, &pTX ) ) )
	{
		del_entry(hTX);
		return 0;
	}

	hTX->hBase = (HANDLER)pTX;

	return hTX;
}

HTX CplTXPool_DX8::load(const CHAR* path)
{
	HTX hTX;
	LPDIRECT3DTEXTURE8 pTX;

	hTX = new_entry();
	if ( hTX==0 ) return 0;
	hTX->pool = this;

	hTX->dwFormat = 0;
	hTX->ulSize = 0;
	hTX->ulIndex = 0;
	hTX->pLocked = 0;

	if( FAILED( D3DXCreateTextureFromFile( m_pd3dDevice, path, &pTX ) ) )
	{
		del_entry(hTX);
		return 0;
	}
 
	hTX->hBase = (HANDLER)pTX;

	return hTX;
}

HTX CplTXPool_DX8::expand(HTX) 
{
	return 0;
}

BYTE* CplTXPool_DX8::lock(HTX hTX, ulong level, ulong* pitch)
{
	LPDIRECT3DTEXTURE8 pTX;
	D3DLOCKED_RECT	lr;
	if ( hTX==0 || hTX->pLocked==0 ) return 0;
	pTX = (LPDIRECT3DTEXTURE8)hTX->hBase;
	if ( pTX->LockRect(level, &lr, 0, 0)==D3D_OK ) // @todo support lock flags
	{
		if ( pitch ) *pitch = lr.Pitch;
		hTX->pLocked = (BYTE*)lr.pBits;
		return (BYTE*)lr.pBits;
	}
	else
		return 0;
}

BYTE* CplTXPool_DX8::lock_rect(HTX hTX, ulong level, ulong left, ulong top, ulong right, ulong bottom, ulong* pitch)
{
	LPDIRECT3DTEXTURE8 pTX;
	D3DLOCKED_RECT	lr;
	RECT	rt;
	if ( hTX==0 || hTX->pLocked==0 ) return 0;
	pTX = (LPDIRECT3DTEXTURE8)hTX->hBase;
	rt.top = top; rt.left = left; rt.bottom = bottom; rt.right = right;
	if ( pTX->LockRect(level, &lr, &rt, 0)==D3D_OK ) // @todo support lock flags
	{
		if ( pitch ) *pitch = lr.Pitch;
		hTX->pLocked = (BYTE*)lr.pBits;
		return (BYTE*)lr.pBits;
	}
	else
		return 0;
}

bool CplTXPool_DX8::unlock(HTX hTX, ulong level) 
{
	LPDIRECT3DTEXTURE8 pTX;
	if ( hTX==0 || hTX->pLocked==0 ) return true;
	pTX = (LPDIRECT3DTEXTURE8)hTX->hBase;
    pTX->UnlockRect(level);
	hTX->pLocked = 0;
	return false;
}

bool CplTXPool_DX8::release(HTX hTX, DWORD usage) 
{
	del_entry(hTX);
	return false;
}

bool CplTXPool_DX8::freeup_entry(HTX hTX)
{
	LPDIRECT3DTEXTURE8 pTX;
	if ( hTX==0 || hTX->pLocked==0 ) return true;
	pTX = (LPDIRECT3DTEXTURE8)hTX->hBase;
	if ( pTX )
	{
		pTX->Release();
		delete pTX;
	}
	return false;
}


/******/
DWORD convert_to_DX8_format(DWORD fmt)
{
	return (D3DFORMAT)fmt;
}

/******/
DWORD convert_to_DX8_usage(DWORD fmt)
{
	return fmt;
}

}