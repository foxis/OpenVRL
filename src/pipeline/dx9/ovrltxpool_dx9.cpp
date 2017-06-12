#include "system/ovrlsystem.h"
#include "pipeline/dx9/ovrltxpool_dx9.h"

namespace openvrl {


static DWORD convert_to_DX9_format(DWORD fmt);
static DWORD convert_to_DX9_usage(DWORD fmt);

/**
 * CplTXPool class
 */
CplTXPool_DX9::CplTXPool_DX9(LPDIRECT3DDEVICE9 lpd3d)
	:CplTXPool(0), m_pd3dDevice(lpd3d)
{
}

CplTXPool_DX9::~CplTXPool_DX9()
{
}


HTX CplTXPool_DX9::create(ulong Width, ulong Height, ulong Levels, DWORD Usage, DWORD Format)
{
	HTX hTX;
	LPDIRECT3DTEXTURE9 pTX;

	hTX = new_entry();
	if ( hTX==0 ) return 0;
	hTX->pool = this;

	Usage = convert_to_DX9_usage(Usage);
	hTX->dwFormat = convert_to_DX9_format(Format);
	hTX->ulSize = 0;
	hTX->ulIndex = 0;
	hTX->pLocked = 0;


	//if ( !(Usage&USAGE_RENDERTARGET) )
	//{
	//	if( FAILED( m_pd3dDevice->CreateTexture(Width, Height, Levels, Usage, (D3DFORMAT)hTX->dwFormat, D3DPOOL_MANAGED, &pTX,0 ) ) )
	//	{
	//		del_entry(hTX);
	//		return 0;
	//	}
	//}
	//else
		if( FAILED( m_pd3dDevice->CreateTexture(Width, Height, Levels, Usage, (D3DFORMAT)hTX->dwFormat, D3DPOOL_DEFAULT, &pTX,0 ) ) )
		{
			del_entry(hTX);
			return 0;
		}

	hTX->hBase = (HANDLER)pTX;

	return hTX;
}

HTX CplTXPool_DX9::load(const CHAR* path)
{
	HTX hTX;
	LPDIRECT3DTEXTURE9 pTX;

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

HTX CplTXPool_DX9::expand(HTX) 
{
	return 0;
}

BYTE* CplTXPool_DX9::lock(HTX hTX, ulong level, ulong* pitch)
{
	LPDIRECT3DTEXTURE9 pTX;
	D3DLOCKED_RECT	lr;
	if ( hTX==0 || hTX->pLocked!=0 ) return 0;
	pTX = (LPDIRECT3DTEXTURE9)hTX->hBase;
	HRESULT hr =pTX->LockRect(level, &lr, 0, D3DLOCK_DISCARD);
	if ( hr==D3D_OK ) // @todo support lock flags
	{
		if ( pitch ) *pitch = lr.Pitch;
		hTX->pLocked = (BYTE*)lr.pBits;
		return (BYTE*)lr.pBits;
	}
	else
		return 0;
}

BYTE* CplTXPool_DX9::lock_rect(HTX hTX, ulong level, ulong left, ulong top, ulong right, ulong bottom, ulong* pitch)
{
	LPDIRECT3DTEXTURE9 pTX;
	D3DLOCKED_RECT	lr;
	RECT	rt;
	if ( hTX==0 || hTX->pLocked!=0 ) return 0;
	pTX = (LPDIRECT3DTEXTURE9)hTX->hBase;
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

bool CplTXPool_DX9::unlock(HTX hTX, ulong level) 
{
	LPDIRECT3DTEXTURE9 pTX;
	if ( hTX==0 || hTX->pLocked==0 ) return true;
	pTX = (LPDIRECT3DTEXTURE9)hTX->hBase;
    pTX->UnlockRect(level);
	hTX->pLocked = 0;
	return false;
}

bool CplTXPool_DX9::release(HTX hTX, DWORD usage) 
{
	del_entry(hTX);
	return false;
}

bool CplTXPool_DX9::freeup_entry(HTX hTX)
{
	LPDIRECT3DTEXTURE9 pTX;
	if ( hTX==0 || hTX->pLocked!=0 ) return true;
	pTX = (LPDIRECT3DTEXTURE9)hTX->hBase;
	if ( pTX )
	{
		pTX->Release();
//		delete pTX;
	}
	return false;
}


/******/
DWORD convert_to_DX9_format(DWORD fmt)
{
	return (D3DFORMAT)fmt;
}

/******/
DWORD convert_to_DX9_usage(DWORD fmt)
{
	return fmt;
}

}