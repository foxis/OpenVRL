#include "system/ovrlsystem.h"
#include "pipeline/pipeline.h"
#include "pipeline/dx9/rendertarget_dx9.h"

namespace openvrl 
{

CRenderTarget_DX9::CRenderTarget_DX9(LPDIRECT3DDEVICE9 dev)
	:	m_pd3dDevice(dev)
{
	OVRL_ASSERT(dev);
	m_RenderToSurface = 0;
	m_Surface = 0;
	m_Texture = 0;
	m_LockTexture = 0;
	m_LockSurface = 0;
	m_pLockedData = 0;
	OVRL_memset(&m_LockRect, 0, sizeof(m_LockRect));
}

CRenderTarget_DX9::~CRenderTarget_DX9()
{
	Release();
}

void CRenderTarget_DX9::Release()
{
	if ( m_pLockedData ) Unlock(m_pLockedData);
	if ( m_RenderToSurface!=0 ) { m_RenderToSurface->Release(); m_RenderToSurface=0; }
	if( m_Surface!= 0 ) { m_Surface->Release(); m_Surface = 0; }
	if ( m_Texture!=0 ) { m_Texture->unuse(); m_Texture = 0; } 
	if( m_LockSurface!= 0 ) { m_LockSurface->Release(); m_LockSurface = 0; }
	if ( m_LockTexture!=0 ) { m_LockTexture->unuse(); m_LockTexture = 0; } 
}

void CRenderTarget_DX9::Prepare()
{
    D3DSURFACE_DESC desc;
	OVRL_ASSERT(m_Texture);

    ((LPDIRECT3DTEXTURE9)m_Texture->hTX()->hBase)->GetSurfaceLevel( 0, &m_Surface );

	if ( m_LockTexture )
		((LPDIRECT3DTEXTURE9)m_LockTexture->hTX()->hBase)->GetSurfaceLevel( 0, &m_LockSurface );

    m_Surface->GetDesc( &desc );

	HRESULT hr = D3DXCreateRenderToSurface( m_pd3dDevice, 
		                            desc.Width, 
		                            desc.Height, 
		                            desc.Format, 
		                            TRUE, 
		                            D3DFMT_D16, 
		                            &m_RenderToSurface );

    OVRL_ASSERT(!FAILED(hr));
}

void CRenderTarget_DX9::Attach(CxfTexture* t, CxfTexture* l)
{
	OVRL_ASSERT(m_pLockedData==0);
	OVRL_ASSERT(m_Texture==0);
	OVRL_ASSERT(t);
	if ( m_Texture!=0 ) m_Texture->unuse();
	m_Texture = t;
	if ( t ) t->use();

	if ( m_LockTexture!=0 ) m_LockTexture->unuse();
	m_LockTexture = l;
	if ( l ) l->use();
}

void CRenderTarget_DX9::Attach(const CString& path, const CString& path1)
{
	OVRL_ASSERT_EX(false, NOTIMPLEMENTED, "not implemented!");
}

int CRenderTarget_DX9::BeginScene()
{
	OVRL_ASSERT(m_pLockedData==0);
	HRESULT hr = m_RenderToSurface->BeginScene(m_Surface, NULL);
	return (int)hr;
}

int CRenderTarget_DX9::EndScene()
{
	OVRL_ASSERT(m_pLockedData==0);
	HRESULT hr = m_RenderToSurface->EndScene(0);
	return (int)hr;
}

int CRenderTarget_DX9::Clear()
{
	OVRL_ASSERT(m_pLockedData==0);
	HRESULT hr = m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER  , 0x0000f0f0, 1.0f, 0L );
	return (int)hr;
}

void* CRenderTarget_DX9::Lock()
{
	OVRL_ASSERT(m_LockTexture);
	OVRL_ASSERT(m_pLockedData==0);

	HRESULT hr = D3DXLoadSurfaceFromSurface(      
		m_LockSurface, 0, 0, m_Surface, 0, 0, D3DX_FILTER_NONE, 0 );
	
	if ( hr!=D3D_OK ) return 0;

	hr = m_LockSurface->LockRect(&m_LockRect, 0, 0);

	if ( hr!=D3D_OK )  return 0;

	m_pLockedData = m_LockRect.pBits;
	return m_pLockedData;
}

void CRenderTarget_DX9::Unlock(void*p)
{
	OVRL_ASSERT(m_LockTexture);
	OVRL_ASSERT(m_pLockedData && m_pLockedData==p);

	m_LockSurface->UnlockRect();
	m_pLockedData = 0;
}

};