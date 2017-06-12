/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/pipeline.h,v $
 * $Implementation: ~/src/pipeline/pipeline.cc $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:56 $
 * $Description: 3DGraphics Pipeline $
 *
 * $Log: pipeline.h,v $
 * Revision 1.2  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.1.1.1  2005/02/02 15:39:20  foxis
 * sources import
 *
 * Revision 0.1  20020129  10:32:00 FoxiE
 * Started completely new Pipeline Design
 *
 * Revision 0.1  20010913  14:01:17 FoxiE
 * y
 *
 */



#if !defined(__ovrl_OVRLPIPELINE_HPP)
#define __ovrl_OVRLPIPELINE_HPP

#include <vector>
#include <list>

#include "common/all.h"
#include "xfactory/xfactory.h"
#include "pipeline/vbpool.h"
#include "pipeline/ibpool.h"
#include "pipeline/vspool.h"
#include "pipeline/txpool.h"
#include "pipeline/bpentity.h"
#include "pipeline/rendertarget.h"
#include "pipeline/basicmesh.h"
#include "pipeline/basiclight.h"
#include "pipeline/basiccamera.h"
#include "world/world.h"

namespace openvrl {

class IWorld;

//
//
//
class OVRLIBAPI IPipeline : public CxFactory
{
	static	ulong				s_THIS_count;

public:
	static	IPipeline*		s_THIS;

	enum PRIMITIVE_TYPE {
		PRIMITIVE_POINTLIST             = 1,
		PRIMITIVE_LINELIST              = 2,
		PRIMITIVE_LINESTRIP             = 3,
		PRIMITIVE_TRIANGLELIST          = 4,
		PRIMITIVE_TRIANGLESTRIP         = 5,
		PRIMITIVE_TRIANGLEFAN           = 6,
		PRIMITIVE_FORCE_DWORD = 0x7FFFFFFF
	};

	enum TRANSFORM_TYPE {
		TRANSFORM_VIEW            =  2,
		TRANSFORM_PROJECTION      =  3,
		TRANSFORM_TEXTURE0        = 16,
		TRANSFORM_TEXTURE1        = 17,
		TRANSFORM_TEXTURE2        = 18,
		TRANSFORM_TEXTURE3        = 19,
		TRANSFORM_TEXTURE4        = 20,
		TRANSFORM_TEXTURE5        = 21,
		TRANSFORM_TEXTURE6        = 22,
		TRANSFORM_TEXTURE7        = 23,

		TRANSFORM_WORLD				= 256,
		TRANSFORM_WORLD1				= 257,
		TRANSFORM_WORLD2				= 258,
		TRANSFORM_WORLD3				= 259,
		TRANSFORM_WORLD4				= 260,

		TRANSFORM_FORCE_DWORD = 0x7FFFFFFF
	};
	TRANSFORM_TYPE TRANSFORM_WORLDn(BYTE i=0)
	{
		return (TRANSFORM_TYPE)(i+256);
	}

	enum RENDERSTATE_TYPE
	{
		RS_ZENABLE                   =   7,
		RS_FILLMODE                  =   8,
		RS_SHADEMODE                 =   9,
		RS_LINEPATTERN               =  10,
		RS_ZWRITEENABLE              =  14,
		RS_ALPHATESTENABLE           =  15,
		RS_LASTPIXEL                 =  16,
		RS_SRCBLEND                  =  19,
		RS_DESTBLEND                 =  20,
		RS_CULLMODE                  =  22,
		RS_ZFUNC                     =  23,
		RS_ALPHAREF                  =  24,
		RS_ALPHAFUNC                 =  25,
		RS_DITHERENABLE              =  26,
		RS_ALPHABLENDENABLE          =  27,
		RS_FOGENABLE                 =  28,
		RS_SPECULARENABLE            =  29,
		RS_ZVISIBLE                  =  30,
		RS_FOGCOLOR                  =  34,
		RS_FOGTABLEMODE              =  35,
		RS_FOGSTART                  =  36,
		RS_FOGEND                    =  37,
		RS_FOGDENSITY                =  38,
		RS_EDGEANTIALIAS             =  40,
		RS_ZBIAS                     =  47,
		RS_RANGEFOGENABLE            =  48,
		RS_STENCILENABLE             =  52,
		RS_STENCILFAIL               =  53,
		RS_STENCILZFAIL              =  54,
		RS_STENCILPASS               =  55,
		RS_STENCILFUNC               =  56,
		RS_STENCILREF                =  57,
		RS_STENCILMASK               =  58,
		RS_STENCILWRITEMASK          =  59,
		RS_TEXTUREFACTOR             =  60,
		RS_WRAP0                     = 128,
		RS_WRAP1                     = 129,
		RS_WRAP2                     = 130,
		RS_WRAP3                     = 131,
		RS_WRAP4                     = 132,
		RS_WRAP5                     = 133,
		RS_WRAP6                     = 134,
		RS_WRAP7                     = 135,
		RS_CLIPPING                  = 136,
		RS_LIGHTING                  = 137,
		RS_AMBIENT                   = 139,
		RS_FOGVERTEXMODE             = 140,
		RS_COLORVERTEX               = 141,
		RS_LOCALVIEWER               = 142,
		RS_NORMALIZENORMALS          = 143,
		RS_DIFFUSEMATERIALSOURCE     = 145,
		RS_SPECULARMATERIALSOURCE    = 146,
		RS_AMBIENTMATERIALSOURCE     = 147,
		RS_EMISSIVEMATERIALSOURCE    = 148,
		RS_VERTEXBLEND               = 151,
		RS_CLIPPLANEENABLE           = 152,
		RS_SOFTWAREVERTEXPROCESSING  = 153,
		RS_POINTSIZE                 = 154,
		RS_POINTSIZE_MIN             = 155,
		RS_POINTSPRITEENABLE         = 156,
		RS_POINTSCALEENABLE          = 157,
		RS_POINTSCALE_A              = 158,
		RS_POINTSCALE_B              = 159,
		RS_POINTSCALE_C              = 160,
		RS_MULTISAMPLEANTIALIAS      = 161,
		RS_MULTISAMPLEMASK           = 162,
		RS_PATCHEDGESTYLE            = 163,
		RS_PATCHSEGMENTS             = 164,
		RS_DEBUGMONITORTOKEN         = 165,
		RS_POINTSIZE_MAX             = 166,
		RS_INDEXEDVERTEXBLENDENABLE  = 167,
		RS_COLORWRITEENABLE          = 168,
		RS_TWEENFACTOR               = 170,
		RS_BLENDOP                   = 171,    
		RS_POSITIONORDER             = 172,
		RS_NORMALORDER               = 173,

		RS_FORCE_DWORD               = 0x7fffffff
	};

	enum ZBUFFER_TYPE {
		ZB_FALSE                 = 0,
		ZB_TRUE                  = 1,
		ZB_USEW                  = 2,

		ZB_FORCE_DWORD           = 0x7fffffff
	};

	enum FILLMODE_TYPE {
	    FILL_POINT               = 1,
		FILL_WIREFRAME           = 2,
		FILL_SOLID               = 3,

		FILL_FORCE_DWORD         = 0x7fffffff
	};

	enum SHADEMODE_TYPE {
		SHADE_FLAT               = 1,
		SHADE_GOURAUD            = 2,
		SHADE_PHONG              = 3,

		SHADE_FORCE_DWORD        = 0x7fffffff
	};

	enum BLEND_TYPE {
		BLEND_ZERO               =  1,
		BLEND_ONE                =  2,
		BLEND_SRCCOLOR           =  3,
		BLEND_INVSRCCOLOR        =  4,
		BLEND_SRCALPHA           =  5,
		BLEND_INVSRCALPHA        =  6,
		BLEND_DESTALPHA          =  7,
		BLEND_INVDESTALPHA       =  8,
		BLEND_DESTCOLOR          =  9,
		BLEND_INVDESTCOLOR       = 10,
		BLEND_SRCALPHASAT        = 11,
		BLEND_BOTHSRCALPHA       = 12,
		BLEND_BOTHINVSRCALPHA    = 13,

		BLEND_FORCE_DWORD        = 0x7fffffff
	};

	enum CULL_TYPE {
		CULL_NONE                = 1,
		CULL_CW                  = 2,
		CULL_CCW                 = 3,

		CULL_FORCE_DWORD         = 0x7fffffff
	};

	enum CMPFUNC_TYPE {
		CMP_NEVER                = 1,
		CMP_LESS                 = 2,
		CMP_EQUAL                = 3,
		CMP_LESSEQUAL            = 4,
		CMP_GREATER              = 5,
		CMP_NOTEQUAL             = 6,
		CMP_GREATEREQUAL         = 7,
		CMP_ALWAYS               = 8,

		CMP_FORCE_DWORD          = 0x7fffffff
	};

	enum FOGMODE_TYPE {
		FOG_NONE                 = 0,
		FOG_EXP                  = 1,
		FOG_EXP2                 = 2,
		FOG_LINEAR               = 3,

		FOG_FORCE_DWORD          = 0x7fffffff
	};

	enum STENCILOP_TYPE {
		STENCILOP_KEEP           = 1,
		STENCILOP_ZERO           = 2,
		STENCILOP_REPLACE        = 3,
		STENCILOP_INCRSAT        = 4,
		STENCILOP_DECRSAT        = 5,
		STENCILOP_INVERT         = 6,
		STENCILOP_INCR           = 7,
		STENCILOP_DECR           = 8,

		STENCILOP_FORCE_DWORD    = 0x7fffffff
	};

	enum MATERIALCOLORSOURCE_TYPE {
		MCS_MATERIAL         = 0,
		MCS_COLOR1           = 1,
		MCS_COLOR2           = 2,

		MCS_FORCE_DWORD      = 0x7fffffff
	};

	enum VERTEXBLENDFLAGS_TYPE {
		VBF_DISABLE  =   0,
		VBF_1WEIGHTS =   1,
		VBF_2WEIGHTS =   2,
		VBF_3WEIGHTS =   3,
		VBF_TWEENING = 255,
		VBF_0WEIGHTS = 256
	};

	enum PATCHEDGESTYLE_TYPE {
		PATCHEDGE_DISCRETE    = 0,
		PATCHEDGE_CONTINUOUS  = 1,

		PATCHEDGE_FORCE_DWORD = 0x7fffffff,
	};

	enum BLENDOP_TYPE {
		BLENDOP_ADD              = 1,
		BLENDOP_SUBTRACT         = 2,
		BLENDOP_REVSUBTRACT      = 3,
		BLENDOP_MIN              = 4,
		BLENDOP_MAX              = 5,

		BLENDOP_FORCE_DWORD      = 0x7fffffff
	};

	enum TEXTURESTAGESTATE_TYPE {
		TSS_COLOROP               =  1,
		TSS_COLORARG1             =  2,
		TSS_COLORARG2             =  3,
		TSS_ALPHAOP               =  4,
		TSS_ALPHAARG1             =  5,
		TSS_ALPHAARG2             =  6,
		TSS_BUMPENVMAT00          =  7,
		TSS_BUMPENVMAT01          =  8,
		TSS_BUMPENVMAT10          =  9,
		TSS_BUMPENVMAT11          = 10,
		TSS_TEXCOORDINDEX         = 11,
		TSS_ADDRESSU              = 13,
		TSS_ADDRESSV              = 14,
		TSS_BORDERCOLOR           = 15,
		TSS_MAGFILTER             = 16,
		TSS_MINFILTER             = 17,
		TSS_MIPFILTER             = 18,
		TSS_MIPMAPLODBIAS         = 19,
		TSS_MAXMIPLEVEL           = 20,
		TSS_MAXANISOTROPY         = 21,
		TSS_BUMPENVLSCALE         = 22,
		TSS_BUMPENVLOFFSET        = 23,
		TSS_TEXTURETRANSFORMFLAGS = 24,
		TSS_ADDRESSW              = 25,
		TSS_COLORARG0             = 26,
		TSS_ALPHAARG0             = 27,
		TSS_RESULTARG             = 28,

		TSS_FORCE_DWORD           = 0x7fffffff
	};

	enum TEXTUREOP_TYPE {
		TOP_DISABLE                   =  1,
		TOP_SELECTARG1                =  2,
		TOP_SELECTARG2                =  3,
		TOP_MODULATE                  =  4,
		TOP_MODULATE2X                =  5,
		TOP_MODULATE4X                =  6,
		TOP_ADD                       =  7,
		TOP_ADDSIGNED                 =  8,
		TOP_ADDSIGNED2X               =  9,
		TOP_SUBTRACT                  = 10,
		TOP_ADDSMOOTH                 = 11,
		TOP_BLENDDIFFUSEALPHA         = 12,
		TOP_BLENDTEXTUREALPHA         = 13,
		TOP_BLENDFACTORALPHA          = 14,
		TOP_BLENDTEXTUREALPHAPM       = 15,
		TOP_BLENDCURRENTALPHA         = 16,
		TOP_PREMODULATE               = 17,
		TOP_MODULATEALPHA_ADDCOLOR    = 18,
		TOP_MODULATECOLOR_ADDALPHA    = 19,
		TOP_MODULATEINVALPHA_ADDCOLOR = 20,
		TOP_MODULATEINVCOLOR_ADDALPHA = 21,
		TOP_BUMPENVMAP                = 22,
	    TOP_BUMPENVMAPLUMINANCE       = 23,
	    TOP_DOTPRODUCT3               = 24,
	    TOP_MULTIPLYADD               = 25,
	    TOP_LERP                      = 26,

	    TOP_FORCE_DWORD               = 0x7fffffff,
	};

	enum TEXTUREADDRESS_TYPE {
		TADDRESS_WRAP            = 1,
		TADDRESS_MIRROR          = 2,
		TADDRESS_CLAMP           = 3,
		TADDRESS_BORDER          = 4,
		TADDRESS_MIRRORONCE      = 5,

		TADDRESS_FORCE_DWORD     = 0x7fffffff
	};

	enum TEXTUREFILTER_TYPE {
		TEXF_NONE            = 0,
		TEXF_POINT           = 1,
		TEXF_LINEAR          = 2,
		TEXF_ANISOTROPIC     = 3,
		TEXF_FLATCUBIC       = 4,
		TEXF_GAUSSIANCUBIC   = 5,

		TEXF_FORCE_DWORD     = 0x7fffffff
	};

	enum TEXTURETRANSFORMFLAGS_TYPE {
		TTFF_DISABLE         =   0,
		TTFF_COUNT1          =   1,
		TTFF_COUNT2          =   2,
		TTFF_COUNT3          =   3,
		TTFF_COUNT4          =   4,
		TTFF_PROJECTED       = 256,

		TTFF_FORCE_DWORD     = 0x7fffffff
	};

protected:
	CplVBPool	*m_VBPool;	// vertex buffer
	CplIBPool	*m_IBPool;	// index buffer
	CplTXPool	*m_TXPool;	// textures
	CplVSPool	*m_VSPool;	// vertex shaders

	virtual CplVBPool* create_VBPool() const =0;
	virtual bool delete_VBPool(CplVBPool* vb) const { delete vb; return false; }

	virtual CplIBPool* create_IBPool() const =0;
	virtual bool delete_IBPool(CplIBPool* vb) const { delete vb; return false; }

	virtual CplTXPool* create_TXPool() const =0;
	virtual bool delete_TXPool(CplTXPool* vb) const { delete vb; return false; }

	virtual CplVSPool* create_VSPool() const =0;
	virtual bool delete_VSPool(CplVSPool* vb) const { delete vb; return false; }


	//
	// rendering pipeline data
	//
	std::vector<IBasicMesh*>* m_Renderables;
	std::vector<IBasicCamera*>* m_Cameras;
	std::vector<IBasicLight*>* m_Lights;

public:
	const CplVBPool* VBPool() const { return m_VBPool; }
	const CplVBPool* get_VBPool() const { return m_VBPool; }
	CplVBPool* VBPool() { return m_VBPool; }
	CplVBPool* get_VBPool() { return m_VBPool; }
	const CplIBPool* IBPool() const { return m_IBPool; }
	const CplIBPool* get_IBPool() const { return m_IBPool; }
	CplIBPool* IBPool() { return m_IBPool; }
	CplIBPool* get_IBPool() { return m_IBPool; }
	const CplVSPool* VSPool() const { return m_VSPool; }
	const CplVSPool* get_VSPool() const { return m_VSPool; }
	CplVSPool* VSPool() { return m_VSPool; }
	CplVSPool* get_VSPool() { return m_VSPool; }
	const CplTXPool* TXPool() const { return m_TXPool; }
	const CplTXPool* get_TXPool() const { return m_TXPool; }
	CplTXPool* TXPool() { return m_TXPool; }
	CplTXPool* get_TXPool() { return m_TXPool; }

	//
	virtual bool Initialize();
	virtual bool CreateDevice();
	virtual bool CleanupDevices();
	virtual bool Cleanup();

	//
	virtual int Update(real time_step, IWorld* w);

	virtual int UpdateLightList(real time_step, IWorld* w);
	virtual int UpdateCameraList(real time_step, IWorld* w);
	virtual int UpdateRenderableList(real time_step, IWorld* w);
	virtual int ProcessRenderables(IBasicCamera* camera) = 0;

	//
	virtual bool SetStates() = 0;
	virtual bool BeginScene() = 0;
	virtual bool RendereScene() = 0;
	virtual bool EndScene() = 0;
	virtual bool Idle() = 0;

	// Viewport/Camera functions
	virtual bool SetViewport(const C2DRect& rc, real minZ, real maxZ) = 0;
	virtual bool GetViewport(C2DRect& rc, real& minZ, real& maxZ) = 0;
	virtual bool SetCamera(IBasicCamera* cam) = 0;

	// Render State functions
	virtual bool SetRenderState(RENDERSTATE_TYPE state, DWORD value) =0 ;
	virtual bool GetRenderState(RENDERSTATE_TYPE state, DWORD& value) =0 ;
//	virtual bool SetRenderTarget(IRenderTarget* rt) =0 ;

	virtual IRenderTarget* CreateRenderTarget() = 0;

	// Transform functions
	virtual bool SetTransform(TRANSFORM_TYPE type, const C4x4Matrix& m) = 0;
	virtual bool GetTransform(TRANSFORM_TYPE type, C4x4Matrix& m) = 0;

	// Light functions
	virtual bool LightEnable(ulong num, bool enable=true) =0 ;
	virtual bool GetLightEnable(ulong num) =0 ;
	virtual bool SetLight(ulong num, IBasicLight* light) = 0;

	// Texture functions
	virtual bool SetTextureStageState(ulong stage, TEXTURESTAGESTATE_TYPE state, DWORD value) =0 ;
	virtual bool SetTexture(ulong stage, CxfTexture* tx) =0 ;
	virtual DWORD GetTextureStageState(ulong stage, TEXTURESTAGESTATE_TYPE state) =0 ;

	// Material
	virtual bool SetMaterial(CxfMaterial* material) = 0;

	// Geometry
	virtual bool SetIndeces(ulong n, CxfIndexBuffer* ib) = 0;
	virtual bool SetVerteces(ulong n, CxfVertexBuffer* vb) = 0;

	// Drawing functions
	virtual int DrawPrimitives(PRIMITIVE_TYPE type, ulong startv, ulong num) = 0;
	virtual int DrawIndexedPrimitives(PRIMITIVE_TYPE type, ulong startv, ulong numv, ulong starti, ulong numi) = 0;

	// Vertex Shader/Pixel functions
	virtual bool SetVertexShaderConstant(ulong reg, const void* data, ulong cb) =0 ;
	virtual bool SetVertexShader(CxfVertexShader* vs) = 0;
	virtual bool GetVertexShaderConstant(ulong reg, void* data, ulong cb) =0 ;
//	virtual CxfVertexShader* GetVertexShader() { return m_current_vertexshader; }
//	virtual bool SetPixelShaderConstant(ulong reg, const void* data, ulong cb) =0 ;
//	virtual bool SetPixelShader(CxfPixelShader* vs) = 0;
//	virtual bool GetPixelShaderConstant(ulong reg, void* data, ulong cb) =0 ;
//	virtual CxfPixelShader* GetPixelShader() { return m_current_pixelshader; }


	/**
	 *
	 */
	IPipeline(CSystem* system);
	virtual ~IPipeline();
};

};

#endif 
