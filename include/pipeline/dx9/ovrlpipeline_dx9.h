/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/dx9/ovrlpipeline_dx9.h,v $
 * $Implementation: ~/src/pipeline/pipeline.cc $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/03/01 18:21:15 $
 * $Description: 3DGraphics Pipeline $
 *
 * $Log: ovrlpipeline_dx9.h,v $
 * Revision 1.3  2005/03/01 18:21:15  foxis
 * Pipeline: shadows now working more or less. need to handle special cases.
 * C4x4Matrix: added inverse method + others
 *
 * Revision 1.2  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.1.1.1  2005/02/02 15:39:20  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design [DX8 version]
 *
 * Revision 0.1  20010913  14:01:17 FoxiE
 * y
 *
 */



#if !defined(__ovrl_OVRLPIPELINE_DX8_HPP)
#define __ovrl_OVRLPIPELINE_DX8_HPP

#include "common/all.h"
#include "pipeline/dx9/ovrlvbpool_dx9.h"
#include "pipeline/dx9/ovrlibpool_dx9.h"
#include "pipeline/dx9/ovrlvspool_dx9.h"
#include "pipeline/dx9/ovrltxpool_dx9.h"
#include "pipeline/pipeline.h"
#include <d3dx9.h>

namespace openvrl {

/**
 *
 */
class OVRLIBAPI CPipeline_DX9 : public IPipeline
{
protected:
	LPDIRECT3DDEVICE9 m_pd3dDevice;

	virtual CplVBPool* create_VBPool() const { return new CplVBPool_DX9(m_pd3dDevice); }
	virtual CplIBPool* create_IBPool() const { return new CplIBPool_DX9(m_pd3dDevice); }
	virtual CplVSPool* create_VSPool() const { return new CplVSPool_DX9(m_pd3dDevice); }
	virtual CplTXPool* create_TXPool() const { return new CplTXPool_DX9(m_pd3dDevice); }


	D3DTRANSFORMSTATETYPE transform_OVRL_to_D3D(TRANSFORM_TYPE type) const
	{
		return (D3DTRANSFORMSTATETYPE)type;
	}

	D3DPRIMITIVETYPE primitive_OVRL_to_D3D(PRIMITIVE_TYPE type) const
	{
		return (D3DPRIMITIVETYPE)type;
	}

	D3DRENDERSTATETYPE state_OVRL_to_D3D(RENDERSTATE_TYPE type) const
	{
		return (D3DRENDERSTATETYPE)type;
	}

	D3DTEXTURESTAGESTATETYPE  stagestate_OVRL_to_D3D(TEXTURESTAGESTATE_TYPE type) const
	{
		return (D3DTEXTURESTAGESTATETYPE )type;
	}

public:

	virtual bool Initialize();
	virtual bool CreateDevice();
	virtual bool SetStates();
	virtual bool CleanupDevices();
	virtual bool Cleanup();

	virtual bool BeginScene();
	virtual bool EndScene();
	virtual bool RendereScene();
	virtual bool Idle();

	virtual int UpdateLightList(real time_step, IWorld* w);
	virtual int UpdateCameraList(real time_step, IWorld* w);
	virtual int UpdateRenderableList(real time_step, IWorld* w);
	virtual int ProcessRenderables(IBasicCamera* camera);

	void DrawGeometry();
	void DrawShadows(const C3DVector&);

	// Viewport functions
	virtual bool SetViewport(const C2DRect& rc, real minZ, real maxZ);
	virtual bool GetViewport(C2DRect& rc, real& minZ, real& maxZ);
	virtual bool SetCamera(IBasicCamera* cam);

	// Render State functions
	virtual bool SetRenderState(RENDERSTATE_TYPE state, DWORD value);
	virtual bool GetRenderState(RENDERSTATE_TYPE state, DWORD& value);
//	virtual bool SetRenderTarget(CxfSurface* target, CxfSurface* zstencil);
	virtual IRenderTarget* CreateRenderTarget();

	// Transform functions
	virtual bool SetTransform(TRANSFORM_TYPE type, const C4x4Matrix& m);
	virtual bool GetTransform(TRANSFORM_TYPE type, C4x4Matrix& m);

	// Light functions
	virtual bool LightEnable(ulong num, bool enable=true);
	virtual bool GetLightEnable(ulong num);
	virtual bool SetLight(ulong num, IBasicLight* light);

	// Texture functions
	virtual bool SetTextureStageState(ulong stage, TEXTURESTAGESTATE_TYPE state, DWORD value);
	virtual bool SetTexture(ulong stage, CxfTexture* tx);
	virtual DWORD GetTextureStageState(ulong stage, TEXTURESTAGESTATE_TYPE state);

	// Material
	virtual bool SetMaterial(CxfMaterial* material);

	// Geometry
	virtual bool SetIndeces(ulong n, CxfIndexBuffer* ib);
	virtual bool SetVerteces(ulong n, CxfVertexBuffer* vb);

	// Drawing functions
	virtual int DrawPrimitives(PRIMITIVE_TYPE type, ulong startv, ulong num);
	virtual int DrawIndexedPrimitives(PRIMITIVE_TYPE type, ulong startv, ulong numv, ulong starti, ulong numi);

	// Vertex Shader/Pixel functions
	virtual bool SetVertexShaderConstant(ulong reg, const void* data, ulong cb);
	virtual bool SetVertexShader(CxfVertexShader* vs);
	virtual bool GetVertexShaderConstant(ulong reg, void* data, ulong cb);
//	virtual bool SetPixelShaderConstant(ulong reg, const void* data, ulong cb) =0 ;
//	virtual bool SetPixelShader(CxfPixelShader* vs) = 0;
//	virtual bool GetPixelShaderConstant(ulong reg, void* data, ulong cb) =0 ;
//	virtual CxfPixelShader* GetPixelShader() { return m_current_pixelshader; }
	
	/**
	 *
	 */
	CPipeline_DX9(CSystem* system);
	CPipeline_DX9(CSystem* system, LPDIRECT3DDEVICE9 d3d, HWND hWnd);
	~CPipeline_DX9();
};


};

#endif /* __ovrl_OVRLPIPELINE_DX8_HPP */
