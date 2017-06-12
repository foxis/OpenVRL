#include "system/ovrlsystem.h"
#include "pipeline/dx9/ovrlpipeline_dx9.h"
#include "pipeline/dx9/rendertarget_dx9.h"

namespace openvrl {


/**
 * CPipeline_DX9 class
 */
CPipeline_DX9::CPipeline_DX9(CSystem* system)
	:IPipeline(system), m_pd3dDevice(system->d3dDevice())
{
}

CPipeline_DX9::CPipeline_DX9(CSystem* system, LPDIRECT3DDEVICE9 d3d, HWND hWnd)
	:IPipeline(system), m_pd3dDevice(d3d)
{
}

CPipeline_DX9::~CPipeline_DX9()
{
}

bool CPipeline_DX9::Initialize()
{
	return IPipeline::Initialize();
}

bool CPipeline_DX9::CreateDevice()
{
	return false;
}

IRenderTarget* CPipeline_DX9::CreateRenderTarget()
{
	return new CRenderTarget_DX9(m_pd3dDevice);
}


bool CPipeline_DX9::SetStates()
{
    SetRenderState( RS_CULLMODE, CULL_CCW );
    SetRenderState( RS_LIGHTING, TRUE );
    SetRenderState( RS_ZENABLE, TRUE );
    SetRenderState( RS_ZWRITEENABLE, TRUE);
	SetRenderState( RS_SPECULARENABLE, TRUE );
    SetRenderState( RS_SHADEMODE, SHADE_GOURAUD );
	SetRenderState( RS_NORMALIZENORMALS, TRUE );
	SetRenderState( RS_FILLMODE, D3DFILL_SOLID );
	return false;
}

bool CPipeline_DX9::CleanupDevices()
{
	return false;
}

bool CPipeline_DX9::Cleanup()
{
	return IPipeline::Cleanup();
}

bool CPipeline_DX9::BeginScene()
{//D3DCLEAR_ZBUFFER
	return false;
}


bool CPipeline_DX9::EndScene()
{
	return false;
}

int CPipeline_DX9::UpdateLightList(real time_step, IWorld* w)
{
	return IPipeline::UpdateLightList(time_step, w);
}

int CPipeline_DX9::UpdateCameraList(real time_step, IWorld* w)
{
	return IPipeline::UpdateCameraList(time_step, w);
}

int CPipeline_DX9::UpdateRenderableList(real time_step, IWorld* w)
{
	return IPipeline::UpdateRenderableList(time_step, w);
}

int CPipeline_DX9::ProcessRenderables(IBasicCamera* camera)
{
	std::vector<IBasicLight*>::iterator L;
	ulong l;
	IRenderTarget *rt = 0;

	// set device states
	SetStates();

	// assume default camera
    if ( camera==0 ) 
	{
	    m_pd3dDevice->BeginScene();
		m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x0000f0f0, 1.0f, 0L );

		D3DXMATRIX matView;
		D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 0.0f,-20.0f ),
                                  &D3DXVECTOR3( 0.0f, 0.0f, 2.5f ),
                                  &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
		m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

		D3DXMATRIX matProj;
		D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 10000.0f );
		m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	}
	else
	{
		// set camera on the device
		CxfCamera* c = camera->GetCamera();
		rt = camera->GetRenderTarget();
		OVRL_ASSERT(c);

		C4x4Matrix View = camera->GetViewMatrix();
		C4x4Matrix Projection = camera->GetProjectionMatrix();
HRESULT hr;
		if ( rt==0 )
		{
			m_pd3dDevice->BeginScene();
			hr = m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER |D3DCLEAR_STENCIL, 0x0000f0f0, 1.0f, 0L );
		}
		else
		{
			rt->BeginScene();
			rt->Clear();
		}

		SetTransform(TRANSFORM_VIEW, View);
		SetTransform(TRANSFORM_PROJECTION, Projection);
	}

	LightEnable( 0, FALSE );
	SetRenderState( RS_AMBIENT, 0x00202020 );
	DrawGeometry();	

	L = m_Lights->begin();
	for ( l=0;l<PIPELINE_MAX_LIGHTS && L!=m_Lights->end();l++,L++ )
	{
//		DrawShadows(
//		DrawGeometry();
	}
	if ( m_Lights->size()==0 )
	{
		// assume default light
		D3DXVECTOR3 vecDir;
		D3DLIGHT9 light;
		ZeroMemory( &light, sizeof(D3DLIGHT9) );
		light.Type       = D3DLIGHT_DIRECTIONAL;
		light.Ambient.r  = 0.1f;
		light.Ambient.g  = 0.1f;
		light.Ambient.b  = 0.1f;
		light.Diffuse.r  = 0.9f;
		light.Diffuse.g  = 0.9f;
		light.Diffuse.b  = 0.9f;
		light.Specular.r  = 0.5f;
		light.Specular.g  = 0.5f;
		light.Specular.b  = 0.5f;
		vecDir = D3DXVECTOR3(-1, -2, 5 );
		D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
		light.Range       = 1000.0f;
		m_pd3dDevice->SetLight( 0, &light );


		//////////////// shadows
		// Disable z-buffer writes (note: z-testing still occurs), and enable the
		// stencil-buffer
		SetRenderState( RS_ZWRITEENABLE,  FALSE );
		SetRenderState( RS_STENCILENABLE, TRUE );

		// Dont bother with interpolating color
		SetRenderState( RS_SHADEMODE,    SHADE_FLAT );

		// Set up stencil compare fuction, reference value, and masks.
		// Stencil test passes if ((ref & mask) cmpfn (stencil & mask)) is true.
		// Note: since we set up the stencil-test to always pass, the STENCILFAIL
		// renderstate is really not needed.
		SetRenderState( RS_STENCILFUNC,  CMP_ALWAYS );
		SetRenderState( RS_STENCILZFAIL, STENCILOP_KEEP );
		SetRenderState( RS_STENCILFAIL,  STENCILOP_KEEP );

		// If ztest passes, inc/decrement stencil buffer value
		SetRenderState( RS_STENCILREF,       0x1 );
		SetRenderState( RS_STENCILMASK,      0xffffffff );
		SetRenderState( RS_STENCILWRITEMASK, 0xffffffff );
		SetRenderState( RS_STENCILPASS,      STENCILOP_INCR );

		// Make sure that no pixels get drawn to the frame buffer
		SetRenderState( RS_ALPHABLENDENABLE, TRUE );
		SetRenderState( RS_SRCBLEND,  BLEND_ZERO );
		SetRenderState( RS_DESTBLEND, BLEND_ONE );

		DrawShadows(C3DVector(1000,2000,-5000));

		// Restore render states
		SetRenderState( RS_SHADEMODE, SHADE_GOURAUD );
		SetRenderState( RS_CULLMODE,  CULL_CCW );
		SetRenderState( RS_ZWRITEENABLE,     TRUE );
		SetRenderState( RS_STENCILENABLE,    FALSE );
		SetRenderState( RS_ALPHABLENDENABLE, FALSE );



		// Set renderstates (disable z-buffering, enable stencil, disable fog, and
		// turn on alphablending)
		SetRenderState( RS_ZENABLE,          TRUE );
		SetRenderState( RS_STENCILENABLE,    TRUE );
		SetRenderState( RS_FOGENABLE,        FALSE );
		SetRenderState( RS_ALPHABLENDENABLE, TRUE );
		SetRenderState( RS_SRCBLEND,  D3DBLEND_SRCALPHA );
		SetRenderState( RS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		// Only write where stencil val >= 1 (count indicates # of shadows that
		// overlap that pixel)
		SetRenderState( RS_STENCILREF,  0 );
		SetRenderState( RS_STENCILFUNC, CMP_GREATEREQUAL );
		SetRenderState( RS_STENCILPASS, STENCILOP_REPLACE );

		LightEnable( 0, TRUE );
		DrawGeometry();

		//////////////// shadows
	}


	if ( rt==0 )
		m_pd3dDevice->EndScene();
	else
		rt->EndScene();
	m_pd3dDevice->Present( NULL, NULL, NULL, NULL );

	return 0;
}

void CPipeline_DX9::DrawGeometry()
{
	std::vector<IBasicMesh*>::iterator I;	
	ulong i;

	I = m_Renderables->begin();
	while ( I!=m_Renderables->end() )
	{
		IBasicMesh* tmp = *I;
		OVRL_ASSERT(tmp);
		CxfMesh* m = tmp->GetMesh();
		OVRL_ASSERT(m);

		tmp->PrecalculateWorldMatrix();

		tmp->SetDefaultPipelineStates(this);

		// set states&streams
		SetVerteces(0, m->VB());
		SetIndeces(0, m->IB());
		SetVertexShader(m->VB()->get_VertexShader());

		// render subsets
		for ( i=0;i<m->numSubsets();i++ )
		{
			C4x4Matrix WMatrix;
			CxfMesh::Subset& ss= m->getSubset(i);

			WMatrix.set(ss.matrix());
			WMatrix.mul(tmp->GetPrecalculatedWorldMatrix());
			SetTransform(TRANSFORM_WORLD, WMatrix);
			SetMaterial(ss.material());

			DrawIndexedPrimitives(PRIMITIVE_TRIANGLELIST, 
				ss.VB_index(), ss.VB_size(), ss.IB_index(), ss.IB_size()/3); 
		}
		I++;
	}
}

void CPipeline_DX9::DrawShadows(const C3DVector& l)
{
	std::vector<IBasicMesh*>::iterator I;	
	ulong i;

	I = m_Renderables->begin();
	while ( I!=m_Renderables->end() )
	{
		IBasicMesh* tmp = *I;
		OVRL_ASSERT(tmp);
		CxfMesh* m = tmp->GetMesh();
		OVRL_ASSERT(m);
		C4x4Matrix WMatrix;
		IBasicShadowVolume *sv;

		// shadows :))
		for ( i=0;i<m->numSubsets();i++ )
		{
			CxfMesh::Subset& ss= m->getSubset(i);
			sv = ss.shadowVolume();

			if ( sv==0 ) continue;

			WMatrix.set(ss.matrix());
			WMatrix.mul(tmp->GetPrecalculatedWorldMatrix());
			SetTransform(TRANSFORM_WORLD, WMatrix);

			C4x4Matrix tm(WMatrix);
			tm.inverse(WMatrix);
			C3DVector v(l);
			v.mul(tm);

			sv->Build(v , 100);


			SetVerteces(0, sv->VB());
			SetIndeces(0, sv->IB());
			SetVertexShader(sv->VB()->get_VertexShader());

			SetRenderState( RS_CULLMODE,   CULL_CCW );
			SetRenderState( RS_STENCILPASS, STENCILOP_INCR );
			DrawIndexedPrimitives(PRIMITIVE_TRIANGLELIST, 
				0, sv->VB_length(), 0, sv->IB_length()/3); 

			SetRenderState( RS_CULLMODE,   CULL_CW );
			SetRenderState( RS_STENCILPASS, STENCILOP_DECR );
			DrawIndexedPrimitives(PRIMITIVE_TRIANGLELIST, 
				0, sv->VB_length(), 0, sv->IB_length()/3); 
		}
		I++;
	}
}


bool CPipeline_DX9::RendereScene() 
{
	return 0;
}

bool CPipeline_DX9::Idle() 
{
	return false;
}


	// Viewport functions
bool CPipeline_DX9::SetViewport(const C2DRect& rc, real minZ, real maxZ)
{
	D3DVIEWPORT9 vp;
	vp.X = rc.left();
	vp.Y = rc.top();
	vp.Width = rc.width();
	vp.Height = rc.height();
	vp.MinZ = minZ;
	vp.MaxZ = maxZ;
	return !!m_pd3dDevice->SetViewport(&vp);
}

bool CPipeline_DX9::GetViewport(C2DRect& rc, real& minZ, real& maxZ)
{
	D3DVIEWPORT9 vp;
	m_pd3dDevice->SetViewport(&vp);
	rc.left() = vp.X;
	rc.top() = vp.Y;
	rc.right() = vp.X+vp.Width;
	rc.bottom() = vp.Y+vp.Height;
	minZ = vp.MinZ;
	maxZ = vp.MaxZ;
	return false;
}

bool CPipeline_DX9::SetCamera(IBasicCamera* cam)
{
	//if ( m_current_camera != cam ) 
	//if ( !cam ) 
	//{
	//	if ( m_current_camera ) m_current_camera;
	//	m_current_camera = cam;
	//	return false;
	//} else
	//	m_current_camera = cam;

	//if ( !cam ) return false;

	SetTransform( TRANSFORM_VIEW, cam->GetViewMatrix() );	// view matrix
	SetTransform( TRANSFORM_PROJECTION, cam->GetProjectionMatrix() );	// projection matrix

	return false;
}

	// Render State functions
bool CPipeline_DX9::SetRenderState(RENDERSTATE_TYPE state, DWORD value) 
{
	return !!m_pd3dDevice->SetRenderState(state_OVRL_to_D3D(state), value);
}

bool CPipeline_DX9::GetRenderState(RENDERSTATE_TYPE state, DWORD& value)
{
	return !!m_pd3dDevice->GetRenderState(state_OVRL_to_D3D(state), &value);
}
//bool CPipeline_DX9::SetRenderTarget(CxfSurface* target, CxfSurface* zstencil);

	// Transform functions
bool CPipeline_DX9::SetTransform(TRANSFORM_TYPE type, const C4x4Matrix& m)
{
	D3DMATRIX mm;
	mm._11 = m.data()[0]; mm._21 = m.data()[4]; mm._31 = m.data()[8]; mm._41 = m.data()[12];
	mm._12 = m.data()[1]; mm._22 = m.data()[5]; mm._32 = m.data()[9]; mm._42 = m.data()[13];
	mm._13 = m.data()[2]; mm._23 = m.data()[6]; mm._33 = m.data()[10]; mm._43 = m.data()[14];
	mm._14 = m.data()[3]; mm._24 = m.data()[7]; mm._34 = m.data()[11]; mm._44 = m.data()[15];
	return !!m_pd3dDevice->SetTransform(transform_OVRL_to_D3D(type), &mm);
}

bool CPipeline_DX9::GetTransform(TRANSFORM_TYPE type, C4x4Matrix& m)
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
bool CPipeline_DX9::LightEnable(ulong num, bool enable)
{
	return !!m_pd3dDevice->LightEnable(num, enable);
}
bool CPipeline_DX9::GetLightEnable(ulong num) 
{
	::BOOL	bl;
	m_pd3dDevice->GetLightEnable(num, &bl);
	return !!bl;
}

bool CPipeline_DX9::SetLight(ulong num, IBasicLight* light)
{
	//if ( m_current_light[num] != light ) 
	//{
	//	if ( light==0 ) 
	//	{
	//		m_current_light[num] = light;
	//		LightEnable( num, FALSE );
	//		return false;
	//	}
	//	m_current_light[num] = light;
	//}

	//if ( !m_current_light[num] ) return false;

	D3DXVECTOR3 vecDir;
	D3DLIGHT9 lght;
	C3DVector dir;
	C3DPoint pos;
	CxfLight* l;
	ZeroMemory( &lght, sizeof(D3DLIGHT9) );
	l = light->GetLight();
	OVRL_ASSERT(l);

	switch ( l->type )
	{
	case LIGHT_DIRECTIONAL: 
		lght.Type       = D3DLIGHT_DIRECTIONAL;
		break;
	}
//	pos = light->getPosition();
//	dir = light->getDirection();
	dir.normalize();
	lght.Diffuse.r  = l->diffuse.r;
	lght.Diffuse.g  = l->diffuse.g;
	lght.Diffuse.b  = l->diffuse.b;
	lght.Ambient.r  = l->ambient.r;
	lght.Ambient.g  = l->ambient.g;
	lght.Ambient.b  = l->ambient.b;
	lght.Specular.r  = l->specular.r;
	lght.Specular.g  = l->specular.g;
	lght.Specular.b  = l->specular.b;
	lght.Position.x = pos.x();
	lght.Position.y = pos.y();
	lght.Position.z = pos.z();
	lght.Direction.x = dir.x();
	lght.Direction.y = dir.y();
	lght.Direction.z = dir.z();
	lght.Range       = l->cut_off;

	m_pd3dDevice->SetLight( num, &lght );
	LightEnable( num, TRUE );

	return 0;
}

	// Texture functions
bool CPipeline_DX9::SetTextureStageState(ulong stage, TEXTURESTAGESTATE_TYPE state, DWORD value)
{
	return !!m_pd3dDevice->SetTextureStageState(stage, stagestate_OVRL_to_D3D(state), value);
}

DWORD CPipeline_DX9::GetTextureStageState(ulong stage, TEXTURESTAGESTATE_TYPE state)
{	
	DWORD value;
	m_pd3dDevice->GetTextureStageState(stage, stagestate_OVRL_to_D3D(state), &value);
	return value;
}
bool CPipeline_DX9::SetTexture(ulong stage, CxfTexture* tx)
{
	if ( tx )
		return !!m_pd3dDevice->SetTexture(stage, (IDirect3DTexture9*)tx->hTX()->hBase );
	else
		return !!m_pd3dDevice->SetTexture(stage, 0 );
}

	// Material
bool CPipeline_DX9::SetMaterial(CxfMaterial* material)
{
	D3DMATERIAL9 mt;
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
	for ( int i=0;i<OVRL_MATERIAL_MAX_MAPS;i++ )
//		if ( material->maps[i] )
		SetTexture(i, material->maps[i]);
	return false;
}

	// Geometry
bool CPipeline_DX9::SetIndeces(ulong n, CxfIndexBuffer* ib)
{
	//if ( m_current_indexbuf == ib ) return false;
	//if ( ib==0 ) 
	//{
	//	if ( m_current_indexbuf ) m_current_indexbuf->unuse();
	//	m_current_indexbuf = ib;
	//	return false;
	//}
	//m_current_indexbuf = ib;
	return !!m_pd3dDevice->SetIndices((IDirect3DIndexBuffer9*)ib->hIB()->hBase ); // n
}

bool CPipeline_DX9::SetVerteces(ulong n, CxfVertexBuffer* vb)
{
	//if ( m_current_vertexbuf == vb ) return false;
	//if ( vb==0 ) 
	//{
	//	if ( m_current_vertexbuf ) m_current_vertexbuf->unuse();
	//	m_current_vertexbuf = vb;
	//	return false;
	//}
	//m_current_vertexbuf = vb;
	return !!m_pd3dDevice->SetStreamSource(n, (IDirect3DVertexBuffer9*)vb->hVB()->hBase, 0, vb->vertex_size() );
}

	// Drawing functions
int CPipeline_DX9::DrawPrimitives(PRIMITIVE_TYPE type, ulong startv, ulong num)
{
	return m_pd3dDevice->DrawPrimitive(primitive_OVRL_to_D3D(type), startv, num);
}

int CPipeline_DX9::DrawIndexedPrimitives(PRIMITIVE_TYPE type, ulong startv, ulong numv, ulong starti, ulong numi)
{
	// @todo: numv = base+startv + number of vertices
	return m_pd3dDevice->DrawIndexedPrimitive(primitive_OVRL_to_D3D(type), 0, startv, numv, starti, numi);
}

	// Vertex Shader/Pixel functions
bool CPipeline_DX9::SetVertexShaderConstant(ulong reg, const void* data, ulong cb)
{
	return false;//!!m_pd3dDevice->SetVertexShaderConstant(reg, data, cb);
}

bool CPipeline_DX9::SetVertexShader(CxfVertexShader* vs)
{
	//if ( m_current_vertexshader == vs ) return false;
	//if ( vs==0 ) 
	//{
	//	if ( m_current_vertexshader ) m_current_vertexshader->unuse();
	//	m_current_vertexshader = vs;
	//	return false;
	//}
	//m_current_vertexshader = vs;
	m_pd3dDevice->SetFVF( vs->hVS()->hBase );
	return false;//!!m_pd3dDevice->SetVertexShader((IDirect3DVertexShader9*)vs->hVS()->hBase);
}

bool CPipeline_DX9::GetVertexShaderConstant(ulong reg, void* data, ulong cb)
{
	return false;//!!m_pd3dDevice->GetVertexShaderConstant(reg, data, cb);
}

//	virtual bool SetPixelShaderConstant(ulong reg, const void* data, ulong cb) =0 ;
//	virtual bool SetPixelShader(CxfPixelShader* vs) = 0;
//	virtual bool GetPixelShaderConstant(ulong reg, void* data, ulong cb) =0 ;
//	virtual CxfPixelShader* GetPixelShader() { return m_current_pixelshader; }



}