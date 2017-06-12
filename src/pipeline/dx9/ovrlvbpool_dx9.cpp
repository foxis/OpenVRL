#include "pipeline/dx9/ovrlvbpool_dx9.h"

namespace openvrl {


static DWORD convert_to_DX9_format(DWORD fmt);
static DWORD convert_to_DX9_usage(DWORD fmt);
static ulong calculate_vertex_size(DWORD fmt);

/**
 * CplVBPool class
 */
CplVBPool_DX9::CplVBPool_DX9(LPDIRECT3DDEVICE9 lpd3d)
	:CplVBPool(0), m_pd3dDevice(lpd3d)
{
}

CplVBPool_DX9::~CplVBPool_DX9()
{
}


HVB CplVBPool_DX9::create(ulong length, WORD format, DWORD usage, const BYTE* buf)
{
	HVB hVB;
	LPDIRECT3DVERTEXBUFFER9 pVB;

	hVB = new_entry();
	if ( hVB==0 ) return 0;
	hVB->pool = this;	// couldn't find another way to set this one...

	usage = convert_to_DX9_usage(usage&USAGE_MASK);
	hVB->dwFormat = convert_to_DX9_format(format);
	hVB->ulSize = length*calculate_vertex_size(hVB->dwFormat);
	hVB->ulIndex = 0;
	hVB->pLocked = 0;
    // Create the vertex buffer.
    if( FAILED( m_pd3dDevice->CreateVertexBuffer( hVB->ulSize, usage, hVB->dwFormat, D3DPOOL_DEFAULT, &pVB, 0 ) ) )
		return 0;

	hVB->hBase = (HANDLER)pVB;

	if ( buf )
	{
		BYTE* pVertices;
		if( FAILED( pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
			return 0;
		memcpy(pVertices, buf, hVB->ulSize);
	    pVB->Unlock();
	}

	return hVB;
}

HVB CplVBPool_DX9::expand(HVB) 
{
	return 0;
}

BYTE* CplVBPool_DX9::lock(HVB hVB, ulong offset, ulong size)
{
	LPDIRECT3DVERTEXBUFFER9 pVB;
	if ( hVB==0 || hVB->pLocked ) return 0;
	const ulong cb = calculate_vertex_size(hVB->dwFormat);
	pVB = (LPDIRECT3DVERTEXBUFFER9)hVB->hBase;
    if( FAILED( pVB->Lock( offset*cb, size*cb, (void**)&(hVB->pLocked), 0 ) ) )
		return 0;
	return hVB->pLocked;
}

bool CplVBPool_DX9::unlock(HVB hVB) 
{
	LPDIRECT3DVERTEXBUFFER9 pVB;
	if ( hVB==0 || hVB->pLocked==0 ) return true;
	pVB = (LPDIRECT3DVERTEXBUFFER9)hVB->hBase;
    pVB->Unlock();
	hVB->pLocked = 0;
	return false;
}

bool CplVBPool_DX9::release(HVB hVB, DWORD usage) 
{
	del_entry(hVB);
	return false;
}

bool CplVBPool_DX9::freeup_entry(HVB hVB)
{
	LPDIRECT3DVERTEXBUFFER9 pVB;
	if ( hVB==0 || hVB->pLocked!=0 ) return true;
	pVB = (LPDIRECT3DVERTEXBUFFER9)hVB->hBase;
	if ( pVB ) 
	{
		pVB->Release();
//		delete pVB;
	}
	return false;
}


/******/
DWORD convert_to_DX9_format(DWORD fmt)
{
	DWORD nf = 0;

	if ( fmt&OVRL_VB_XYZ )		nf |= D3DFVF_XYZ;
	if ( fmt&OVRL_VB_RHW )		nf |= D3DFVF_XYZRHW;
	if ( fmt&OVRL_VB_B1  )		nf |= D3DFVF_XYZB1;
	if ( fmt&OVRL_VB_B2  )		nf |= D3DFVF_XYZB2;
	if ( fmt&OVRL_VB_B3  )		nf |= D3DFVF_XYZB3;
	if ( fmt&OVRL_VB_B4  )		nf |= D3DFVF_XYZB4;
	if ( fmt&OVRL_VB_NORMAL )	nf |= D3DFVF_NORMAL;
	if ( fmt&OVRL_VB_PSIZE  )	nf |= D3DFVF_PSIZE;
	if ( fmt&OVRL_VB_DIFFUSE )	nf |= D3DFVF_DIFFUSE;
	if ( fmt&OVRL_VB_SPECULAR )	nf |= D3DFVF_SPECULAR;
	if ( fmt&OVRL_VB_TX1 )		nf |= D3DFVF_TEX1;
	if ( fmt&OVRL_VB_TX2 )		nf |= D3DFVF_TEX2;
	if ( fmt&OVRL_VB_TX3 )		nf |= D3DFVF_TEX3;
	if ( fmt&OVRL_VB_TX4 )		nf |= D3DFVF_TEX4;
	if ( fmt&OVRL_VB_MASS )		nf |= D3DFVF_XYZB3;
	if ( fmt&OVRL_VB_BONE_ID )	nf |= D3DFVF_XYZB4;

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

ulong calculate_vertex_size(DWORD fmt)
{
	ulong nf = 0;

	if ( fmt&D3DFVF_XYZ || fmt&D3DFVF_XYZRHW )		nf += sizeof(float)*3;
	if ( fmt&D3DFVF_XYZRHW )		nf += sizeof(float);
	if ( fmt&D3DFVF_XYZB1  )		nf += sizeof(float);
	if ( fmt&D3DFVF_XYZB2  )		nf += sizeof(float)*2;
	if ( fmt&D3DFVF_XYZB3  )		nf += sizeof(float)*3;
	if ( fmt&D3DFVF_XYZB4  )		nf += sizeof(float)*4;
	if ( fmt&D3DFVF_NORMAL )	nf += sizeof(float)*3;
	if ( fmt&D3DFVF_PSIZE  )	nf += sizeof(float);
	if ( fmt&D3DFVF_DIFFUSE )	nf += 4;
	if ( fmt&D3DFVF_SPECULAR )	nf += 4;
	if ( fmt&D3DFVF_TEX1 )		nf += sizeof(float)*2;
	if ( fmt&D3DFVF_TEX2 )		nf += sizeof(float)*2;
	if ( fmt&D3DFVF_TEX3 )		nf += sizeof(float)*2;
	if ( fmt&D3DFVF_TEX4 )		nf += sizeof(float)*2;

	return nf;
}

}