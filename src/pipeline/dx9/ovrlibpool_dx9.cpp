#include "pipeline/dx9/ovrlibpool_dx9.h"

namespace openvrl {


static DWORD convert_to_DX9_format(DWORD fmt);
static DWORD convert_to_DX9_usage(DWORD fmt);
static ulong calculate_index_size(DWORD fmt);

/**
 * CplIBPool class
 */
CplIBPool_DX9::CplIBPool_DX9(LPDIRECT3DDEVICE9 lpd3d)
	:CplIBPool(0), m_pd3dDevice(lpd3d)
{
}

CplIBPool_DX9::~CplIBPool_DX9()
{
}


HIB CplIBPool_DX9::create(ulong length, WORD format, DWORD usage, const BYTE* buf)
{
	HIB hIB;
	LPDIRECT3DINDEXBUFFER9 pIB;

	hIB = new_entry();
	if ( hIB==0 ) return 0;
	hIB->pool = this;

	usage = convert_to_DX9_usage(usage&USAGE_MASK);
	hIB->dwFormat = convert_to_DX9_format(format);
	hIB->ulSize = length*calculate_index_size(hIB->dwFormat);
	hIB->ulIndex = 0;
	hIB->pLocked = 0;
    // Create the index buffer.
    if( FAILED( m_pd3dDevice->CreateIndexBuffer( hIB->ulSize, usage, (enum _D3DFORMAT)hIB->dwFormat, D3DPOOL_DEFAULT, &pIB, 0 ) ) )
		return 0;

	hIB->hBase = (HANDLER)pIB;

	if ( buf!=0 )
	{
		BYTE* pIndeces;
		if( FAILED( pIB->Lock( 0, 0, (void**)&pIndeces, 0 ) ) )
			return 0;
		memcpy(pIndeces, buf, hIB->ulSize);
	    pIB->Unlock();
	}

	return hIB;
}

HIB CplIBPool_DX9::expand(HIB) 
{
	return 0;
}

BYTE* CplIBPool_DX9::lock(HIB hIB, ulong offset, ulong size)
{
	LPDIRECT3DINDEXBUFFER9 pIB;
	if ( hIB==0 || hIB->pLocked ) return 0;
	const ulong cb = calculate_index_size(hIB->dwFormat);
	pIB = (LPDIRECT3DINDEXBUFFER9)hIB->hBase;
    if( FAILED( pIB->Lock( offset*cb, size*cb, (void**)&(hIB->pLocked), 0 ) ) )
		return 0;
	return hIB->pLocked;
}

bool CplIBPool_DX9::unlock(HIB hIB) 
{
	LPDIRECT3DINDEXBUFFER9 pIB;
	if ( hIB==0 || hIB->pLocked==0 ) return true;
	pIB = (LPDIRECT3DINDEXBUFFER9)hIB->hBase;
    pIB->Unlock();
	hIB->pLocked = 0;
	return false;
}

bool CplIBPool_DX9::release(HIB hIB, DWORD usage) 
{
	del_entry(hIB);
	return false;
}

bool CplIBPool_DX9::freeup_entry(HIB hIB)
{
	LPDIRECT3DINDEXBUFFER9 pIB;
	if ( hIB==0 || hIB->pLocked!=0 ) return true;
	pIB = (LPDIRECT3DINDEXBUFFER9)hIB->hBase;
	if ( pIB )
	{
		pIB->Release();
//		delete pIB;
	}
	return false;
}


/******/
DWORD convert_to_DX9_format(DWORD fmt)
{
	DWORD nf = 0;

	if ( fmt&OVRL_IB_16 )		nf = D3DFMT_INDEX16;
	if ( fmt&OVRL_IB_32 )		nf = D3DFMT_INDEX32;

	return nf;
}

/******/
DWORD convert_to_DX9_usage(DWORD fmt)
{
	DWORD nf = 0;

	if ( fmt&OVRL_VB_SOFTWARE )		nf |= D3DUSAGE_SOFTWAREPROCESSING;
//	if ( fmt&OVRL_VB_DISCARD )		nf |= D3DUSAGE_DISCARD;
	if ( fmt&OVRL_VB_DYNAMIC )		nf |= D3DUSAGE_DYNAMIC;
	if ( fmt&OVRL_VB_WRITEONLY )		nf |= D3DUSAGE_WRITEONLY;
//	if ( fmt&OVRL_VB_READONLY )		nf |= D3DUSAGE_READONLY;

	return nf;
}

ulong calculate_index_size(DWORD fmt)
{
	ulong nf = 0;

	if ( fmt&D3DFMT_INDEX16 )		nf = 2;
	if ( fmt&D3DFMT_INDEX32 )		nf = 4;

	return nf;
}

}