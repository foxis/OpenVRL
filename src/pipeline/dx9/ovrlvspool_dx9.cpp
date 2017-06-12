#include "pipeline/dx9/ovrlvspool_dx9.h"

namespace openvrl {


static DWORD convert_to_DX9_format(DWORD fmt);
static DWORD convert_to_DX9_usage(DWORD fmt);

/**
 * CplVSPool class
 */
CplVSPool_DX9::CplVSPool_DX9(LPDIRECT3DDEVICE9 lpd3d)
	:CplVSPool(0), m_pd3dDevice(lpd3d)
{
}

CplVSPool_DX9::~CplVSPool_DX9()
{
}


HVS CplVSPool_DX9::create(DWORD handler)
{
	HVS hVS;

	hVS = new_entry();
	if ( hVS==0 ) return 0;
	hVS->pool = this;	// couldn't find another way to set this one...

	hVS->dwFormat = convert_to_DX9_format(handler);
	hVS->ulSize = 0;
	hVS->ulIndex = 0;
	hVS->pLocked = 0;

	hVS->hBase = hVS->dwFormat;

	return hVS;
}

HVS CplVSPool_DX9::expand(HVS) 
{
	return 0;
}

BYTE* CplVSPool_DX9::lock(HVS hVS, ulong offset, ulong size)
{
	if ( hVS==0 || hVS->pLocked ) return 0;
	return hVS->pLocked;
}

bool CplVSPool_DX9::unlock(HVS hVS) 
{
	if ( hVS==0 || hVS->pLocked==0 ) return true;
	hVS->pLocked = 0;
	return false;
}

bool CplVSPool_DX9::release(HVS hVS, DWORD usage) 
{
	del_entry(hVS);
	return false;
}

bool CplVSPool_DX9::freeup_entry(HVS hVS)
{
	if ( hVS==0 || hVS->pLocked!=0 ) return true;
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