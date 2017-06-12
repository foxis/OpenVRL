/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/dx8/ovrlpipeline_dx8.h,v $
 * $Implementation: ~/src/pipeline/pipeline.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:20 $
 * $Description: 3DGraphics Pipeline $
 *
 * $Log: ovrlpipeline_dx8.h,v $
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
#include "pipeline/dx8/ovrlvbpool_dx8.h"
#include "pipeline/dx8/ovrlibpool_dx8.h"
#include "pipeline/dx8/ovrlvspool_dx8.h"
#include "pipeline/dx8/ovrltxpool_dx8.h"
#include "pipeline/ovrlpipeline.h"
#include <d3dx8.h>

namespace openvrl {

/**
 *
 */
class OVRLIBAPI CPipeline_DX8 : public CPipeline
{
protected:
	LPDIRECT3DDEVICE8 m_pd3dDevice;

	virtual CplVBPool* create_VBPool() const { return new CplVBPool_DX8(m_pd3dDevice); }
	virtual CplIBPool* create_IBPool() const { return new CplIBPool_DX8(m_pd3dDevice); }
	virtual CplVSPool* create_VSPool() const { return new CplVSPool_DX8(m_pd3dDevice); }
	virtual CplTXPool* create_TXPool() const { return new CplTXPool_DX8(m_pd3dDevice); }


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


	// Viewport functions
	virtual bool SetViewport(const C2DRect& rc, real minZ, real maxZ);
	virtual bool GetViewport(C2DRect& rc, real& minZ, real& maxZ);
	virtual bool SetCamera(CplCameraObject* cam);

	// Render State functions
	virtual bool SetRenderState(RENDERSTATE_TYPE state, DWORD value);
	virtual bool GetRenderState(RENDERSTATE_TYPE state, DWORD& value);
//	virtual bool SetRenderTarget(CxfSurface* target, CxfSurface* zstencil);

	// Transform functions
	virtual bool SetTransform(TRANSFORM_TYPE type, const C4x4Matrix& m);
	virtual bool GetTransform(TRANSFORM_TYPE type, C4x4Matrix& m);

	// Light functions
	virtual bool LightEnable(ulong num, bool enable=true);
	virtual bool GetLightEnable(ulong num);
	virtual bool SetLight(ulong num, CplLightObject* light);

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
	CPipeline_DX8(CSystem* system);
	CPipeline_DX8(CSystem* system, LPDIRECT3DDEVICE8 d3d, HWND hWnd);
	~CPipeline_DX8();

	virtual ulong what() const { return ORW_PIPELINE; }
	virtual CHAR* get_name() const { return "OpenVRL Pipeline class"; }
};


};

#endif /* __ovrl_OVRLPIPELINE_DX8_HPP */
