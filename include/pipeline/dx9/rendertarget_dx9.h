/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/dx9/rendertarget_dx9.h,v $
 * $Implementation: $
 * $Revision: 1.1 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:57 $
 * $Description: $
 *
 * $Log: rendertarget_dx9.h,v $
 * Revision 1.1  2005/02/23 12:30:57  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 *
 */



#if !defined(__RENDERTARGET_DX9_HPP)
#define __RENDERTARGET_DX9_HPP

#include "common/all.h"
#include "pipeline/rendertarget.h"
#include "pipeline/pipeline.h"
#include <d3dx9.h>

namespace openvrl {

class OVRLIBAPI CRenderTarget_DX9 : public IRenderTarget
{
	LPDIRECT3DDEVICE9       m_pd3dDevice;
	LPD3DXRENDERTOSURFACE   m_RenderToSurface;
	LPDIRECT3DSURFACE9      m_Surface;
	LPDIRECT3DSURFACE9      m_LockSurface;
	CxfTexture*			m_Texture;
	CxfTexture*			m_LockTexture;
	void*			m_pLockedData;
	D3DLOCKED_RECT	m_LockRect;

public:
	CRenderTarget_DX9(LPDIRECT3DDEVICE9);
	virtual ~CRenderTarget_DX9();

	virtual void Release();
	virtual void Prepare();

	virtual void Attach(CxfTexture*,CxfTexture*);
	virtual void Attach(const CString&, const CString&);

	virtual int BeginScene();
	virtual int EndScene();
	virtual int Clear();

	virtual void* Lock();
	virtual void Unlock(void*);

	virtual void* GetLockedBits() { return m_LockRect.pBits; }
	virtual ulong GetLockedPitch() { return m_LockRect.Pitch; }
};

};

#endif /* __OVRLVSPOOL_DX8_HPP */
