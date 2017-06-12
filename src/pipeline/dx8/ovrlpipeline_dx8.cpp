#include "stdafx.h"

#include "system/ovrlsystem.h"
#include "pipeline/dx8/ovrlpipeline_dx8.h"
#include "pipeline/ovrlrenderobject.h"
#include "pipeline/ovrllightobject.h"
#include "pipeline/ovrlcameraobject.h"

namespace openvrl {


/**
 * CPipeline_DX8 class
 */
CPipeline_DX8::CPipeline_DX8(CSystem* system)
	:CPipeline(system), m_pd3dDevice(system->d3dDevice())
{
}

CPipeline_DX8::CPipeline_DX8(CSystem* system, LPDIRECT3DDEVICE8 d3d, HWND hWnd)
	:CPipeline(system), m_pd3dDevice(d3d)
{
}

CPipeline_DX8::~CPipeline_DX8()
{
}

bool CPipeline_DX8::Initialize()
{
	return IPipeline::Initialize();
}

bool CPipeline_DX8::CreateDevice()
{
	return false;
}

bool CPipeline_DX8::SetStates()
{
    // Turn off culling, so we see the front and back of the triangle
    SetRenderState( RS_CULLMODE, CULL_NONE );
    SetRenderState( RS_LIGHTING, TRUE );
    SetRenderState( RS_ZENABLE, TRUE );
	SetRenderState( RS_SPECULARENABLE, TRUE );
    SetRenderState( RS_SHADEMODE, SHADE_GOURAUD );
	SetRenderState( RS_NORMALIZENORMALS, TRUE );
	return false;
}

bool CPipeline_DX8::CleanupDevices()
{
	return false;
}

bool CPipeline_DX8::Cleanup()
{
	return IPipeline::Cleanup();
}

bool CPipeline_DX8::BeginScene()
{
    m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,128), 1.0f, 0 );
	return FAILED(m_pd3dDevice->BeginScene());
}


bool CPipeline_DX8::EndScene()
{
    m_pd3dDevice->EndScene();
    m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
	return false;
}


bool CPipeline_DX8::RendereScene() 
{
	ulong ii, j;
	std::list<CplRenderableObject*>::iterator i(m_objects.begin());
	
	SetStates();

    if ( m_current_camera==0 ) // for debugging purposes
	{
		D3DXMATRIX matView;
		D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 10.0f,-10.0f ),
                                  &D3DXVECTOR3( 0.0f, 0.0f, 2.5f ),
                                  &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
		m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
//zaxis = normal(At - Eye)
//xaxis = normal(cross(Up, zaxis))
//yaxis = cross(zaxis, xaxis)
//
// xaxis.x           yaxis.x           zaxis.x          0
// xaxis.y           yaxis.y           zaxis.y          0
// xaxis.z           yaxis.z           zaxis.z          0
//-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1


		D3DXMATRIX matProj;
		D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
		m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
//h = cos(fov/2) / sin(fov/2);
//w = h / aspect;

//2*zn/w  0       0              0
//0       2*zn/h  0              0
//0       0       zf/(zf-zn)     1
//0       0       zn*zf/(zn-zf)  0
	}
	else
		m_current_camera->Apply();

	for ( j=0,ii=0;ii<PIPELINE_MAX_LIGHTS;ii++ ) if ( m_current_light[ii] ) 
		m_current_light[ii]->Apply(j++);

	if ( !j ) // for debugging purposes
	{
		D3DXVECTOR3 vecDir;
		D3DLIGHT8 light;
		ZeroMemory( &light, sizeof(D3DLIGHT8) );
		light.Type       = D3DLIGHT_DIRECTIONAL;
		light.Ambient.r  = 1.0f;
		light.Ambient.g  = 1.0f;
		light.Ambient.b  = 1.0f;
		light.Diffuse.r  = 1.0f;
		light.Diffuse.g  = 1.0f;
		light.Diffuse.b  = 1.0f;
		light.Specular.r  = 1.0f;
		light.Specular.g  = 1.0f;
		light.Specular.b  = 1.0f;
		vecDir = D3DXVECTOR3(1, 0, 1 );
		D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
		light.Range       = 1000.0f;
		m_pd3dDevice->SetLight( 0, &light );

		LightEnable( 0, TRUE );
		SetRenderState( RS_AMBIENT, 0x00202020 );
	}

	// Finally, rendere objects
	while ( i!=m_objects.end() )
	{
		(*(i++))->Render(m_current_camera);
	}

	return 0;
}

bool CPipeline_DX8::Idle() 
{
	return false;
}


	// Viewport functions
bool CPipeline_DX8::SetViewport(const C2DRect& rc, real minZ, real maxZ)
{
	D3DVIEWPORT8 vp;
	vp.X = rc.left();
	vp.Y = rc.top();
	vp.Width = rc.width();
	vp.Height = rc.height();
	vp.MinZ = minZ;
	vp.MaxZ = maxZ;
	return !!m_pd3dDevice->SetViewport(&vp);
}

bool CPipeline_DX8::GetViewport(C2DRect& rc, real& minZ, real& maxZ)
{
	D3DVIEWPORT8 vp;
	m_pd3dDevice->SetViewport(&vp);
	rc.left() = vp.X;
	rc.top() = vp.Y;
	rc.right() = vp.X+vp.Width;
	rc.bottom() = vp.Y+vp.Height;
	minZ = vp.MinZ;
	maxZ = vp.MaxZ;
	return false;
}

bool CPipeline_DX8::SetCamera(CplCameraObject* cam)
{
	if ( m_current_camera != cam ) 
	if ( !cam ) 
	{
		if ( m_current_camera ) m_current_camera;
		m_current_camera = cam;
		return false;
	} else
		m_current_camera = cam;

	if ( !cam ) return false;

	SetTransform( TRANSFORM_VIEW, m_current_camera->getView() );
	SetTransform( TRANSFORM_PROJECTION, m_current_camera->getProjection() );

	return false;
}

	// Render State functions
bool CPipeline_DX8::SetRenderState(RENDERSTATE_TYPE state, DWORD value) 
{
	return !!m_pd3dDevice->SetRenderState(state_OVRL_to_D3D(state), value);
}

bool CPipeline_DX8::GetRenderState(RENDERSTATE_TYPE state, DWORD& value)
{
	return !!m_pd3dDevice->GetRenderState(state_OVRL_to_D3D(state), &value);
}
//bool CPipeline_DX8::SetRenderTarget(CxfSurface* target, CxfSurface* zstencil);

	// Transform functions
bool CPipeline_DX8::SetTransform(TRANSFORM_TYPE type, const C4x4Matrix& m)
{
	D3DMATRIX mm;
	mm._11 = m.data()[0]; mm._21 = m.data()[4]; mm._31 = m.data()[8]; mm._41 = m.data()[12];
	mm._12 = m.data()[1]; mm._22 = m.data()[5]; mm._32 = m.data()[9]; mm._42 = m.data()[13];
	mm._13 = m.data()[2]; mm._23 = m.data()[6]; mm._33 = m.data()[10]; mm._43 = m.data()[14];
	mm._14 = m.data()[3]; mm._24 = m.data()[7]; mm._34 = m.data()[11]; mm._44 = m.data()[15];
	return !!m_pd3dDevice->SetTransform(transform_OVRL_to_D3D(type), &mm);
}

bool CPipeline_DX8::GetTransform(TRANSFORM_TYPE type, C4x4Matrix& m)
{
	D3DMATRIX mm;
	m_pd3dDevice->GetTransform(transform_OVRL_to_D3D(type), &mm);
	m.data()[0] = mm._11; m.data()[4] = mm._21; m.data()[8] = mm._31; m.data()[12] = mm._41;
	m.data()[1] = mm._12; m.data()[5] = mm._22; m.data()[9] = mm._32; m.data()[13] = mm._42;
	m.data()[2] = mm._13; m.data()[6] = mm._23; m.data()[10] = mm._33; m.data()[14] = mm._43;
	m.data()[3] = mm._14; m.data()[7] = mm._24; m.data()[11] = mm._34; m.data()[15] = mm._44;
	return true;
}

	// Light functions
bool CPipeline_DX8::LightEnable(ulong num, bool enable)
{
	return !!m_pd3dDevice->LightEnable(num, enable);
}
bool CPipeline_DX8::GetLightEnable(ulong num) 
{
	::BOOL	bl;
	m_pd3dDevice->GetLightEnable(num, &bl);
	return !!bl;
}

bool CPipeline_DX8::SetLight(ulong num, CplLightObject* light)
{
	if ( m_current_light[num] != light ) 
	{
		if ( light==0 ) 
		{
			m_current_light[num] = light;
			LightEnable( num, FALSE );
			return false;
		}
		m_current_light[num] = light;
	}

	if ( !m_current_light[num] ) return false;

	D3DXVECTOR3 vecDir;
	D3DLIGHT8 lght;
	C3DVector dir;
	C3DPoint pos;
	ZeroMemory( &lght, sizeof(D3DLIGHT8) );

	switch ( light->Light()->type )
	{
	case LIGHT_DIRECTIONAL: 
		lght.Type       = D3DLIGHT_DIRECTIONAL;
		break;
	}
	pos = light->getPosition();
	dir = light->getDirection();
	dir.normalize();
	lght.Diffuse.r  = light->Light()->diffuse.r;
	lght.Diffuse.g  = light->Light()->diffuse.g;
	lght.Diffuse.b  = light->Light()->diffuse.b;
	lght.Ambient.r  = light->Light()->ambient.r;
	lght.Ambient.g  = light->Light()->ambient.g;
	lght.Ambient.b  = light->Light()->ambient.b;
	lght.Specular.r  = light->Light()->specular.r;
	lght.Specular.g  = light->Light()->specular.g;
	lght.Specular.b  = light->Light()->specular.b;
	lght.Position.x = pos.x();
	lght.Position.y = pos.y();
	lght.Position.z = pos.z();
	lght.Direction.x = dir.x();
	lght.Direction.y = dir.y();
	lght.Direction.z = dir.z();
	lght.Range       = light->Light()->cut_off;

	m_pd3dDevice->SetLight( num, &lght );
	LightEnable( num, TRUE );

	return 0;
}

	// Texture functions
bool CPipeline_DX8::SetTextureStageState(ulong stage, TEXTURESTAGESTATE_TYPE state, DWORD value)
{
	return !!m_pd3dDevice->SetTextureStageState(stage, stagestate_OVRL_to_D3D(state), value);
}

DWORD CPipeline_DX8::GetTextureStageState(ulong stage, TEXTURESTAGESTATE_TYPE state)
{	
	DWORD value;
	m_pd3dDevice->GetTextureStageState(stage, stagestate_OVRL_to_D3D(state), &value);
	return value;
}
bool CPipeline_DX8::SetTexture(ulong stage, CxfTexture* tx)
{
	if ( m_current_texture[stage] == tx ) return false;
	if ( tx==0 ) 
	{
		if ( m_current_texture[stage] ) m_current_texture[stage]->unuse();
		m_current_texture[stage] = tx;
		return false;
	}
	m_current_texture[stage] = tx;
	return !!m_pd3dDevice->SetTexture(stage, (IDirect3DTexture8*)tx->hTX()->hBase );
}

	// Material
bool CPipeline_DX8::SetMaterial(CxfMaterial* material)
{
	D3DMATERIAL8 mt;
	if ( m_current_material == material ) return false;
	if ( !material ) 
	{
		if ( m_current_material ) m_current_material->unuse();
		m_current_material = material;
		return false;
	}
	mt.Diffuse.r = material->diffuse.r;		mt.Diffuse.g = material->diffuse.g;
	mt.Diffuse.b = material->diffuse.b;		mt.Diffuse.a = material->diffuse.a;
	mt.Ambient.r = material->ambient.r;		mt.Ambient.g = material->ambient.g;
	mt.Ambient.b = material->ambient.b;		mt.Ambient.a = material->ambient.a;
	mt.Specular.r = material->specular.r;	mt.Specular.g = material->specular.g;
	mt.Specular.b = material->specular.b;	mt.Specular.a = material->specular.a;
	mt.Emissive.r = material->filter.r;		mt.Emissive.g = material->filter.g;
	mt.Emissive.b = material->filter.b;		mt.Emissive.a = material->filter.a;
	mt.Power = material->shiness;
	m_pd3dDevice->SetMaterial(&mt);
	// also set textures/maps, etc, vertex shaders...
	if ( m_current_material ) m_current_material->unuse();
	m_current_material = material;
	material->use();
	return false;
}

	// Geometry
bool CPipeline_DX8::SetIndeces(ulong n, CxfIndexBuffer* ib)
{
	if ( m_current_indexbuf == ib ) return false;
	if ( ib==0 ) 
	{
		if ( m_current_indexbuf ) m_current_indexbuf->unuse();
		m_current_indexbuf = ib;
		return false;
	}
	m_current_indexbuf = ib;
	return !!m_pd3dDevice->SetIndices((IDirect3DIndexBuffer8*)ib->hIB()->hBase, n );
}

bool CPipeline_DX8::SetVerteces(ulong n, CxfVertexBuffer* vb)
{
	if ( m_current_vertexbuf == vb ) return false;
	if ( vb==0 ) 
	{
		if ( m_current_vertexbuf ) m_current_vertexbuf->unuse();
		m_current_vertexbuf = vb;
		return false;
	}
	m_current_vertexbuf = vb;
	return !!m_pd3dDevice->SetStreamSource(n, (IDirect3DVertexBuffer8*)vb->hVB()->hBase, vb->vertex_size() );
}

	// Drawing functions
int CPipeline_DX8::DrawPrimitives(PRIMITIVE_TYPE type, ulong startv, ulong num)
{
	return m_pd3dDevice->DrawPrimitive(primitive_OVRL_to_D3D(type), startv, num);
}

int CPipeline_DX8::DrawIndexedPrimitives(PRIMITIVE_TYPE type, ulong startv, ulong numv, ulong starti, ulong numi)
{
	return m_pd3dDevice->DrawIndexedPrimitive(primitive_OVRL_to_D3D(type), startv, numv, starti, numi);
}

	// Vertex Shader/Pixel functions
bool CPipeline_DX8::SetVertexShaderConstant(ulong reg, const void* data, ulong cb)
{
	return !!m_pd3dDevice->SetVertexShaderConstant(reg, data, cb);
}

bool CPipeline_DX8::SetVertexShader(CxfVertexShader* vs)
{
	if ( m_current_vertexshader == vs ) return false;
	if ( vs==0 ) 
	{
		if ( m_current_vertexshader ) m_current_vertexshader->unuse();
		m_current_vertexshader = vs;
		return false;
	}
	m_current_vertexshader = vs;
	return !!m_pd3dDevice->SetVertexShader(vs->hVS()->hBase);
}

bool CPipeline_DX8::GetVertexShaderConstant(ulong reg, void* data, ulong cb)
{
	return !!m_pd3dDevice->GetVertexShaderConstant(reg, data, cb);
}

//	virtual bool SetPixelShaderConstant(ulong reg, const void* data, ulong cb) =0 ;
//	virtual bool SetPixelShader(CxfPixelShader* vs) = 0;
//	virtual bool GetPixelShaderConstant(ulong reg, void* data, ulong cb) =0 ;
//	virtual CxfPixelShader* GetPixelShader() { return m_current_pixelshader; }



}