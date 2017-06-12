/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/system/ovrlsystem.h,v $
 * $Implementation: /include/system.cc $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:57 $
 * $Description: System class (Win32 Version, VC++ 6.0) $
 *
 * $Log: ovrlsystem.h,v $
 * Revision 1.3  2005/02/23 12:30:57  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.2  2005/02/02 15:55:33  foxis
 * some changes in the config file
 *
 * Revision 1.1.1.1  2005/02/02 15:39:21  foxis
 * sources import
 *
 * Revision 0.1  20020105  11:52:40 FoxiE
 *  :)
 *
 */


#if !defined(__ovrl_SYSTEM_H)
#define __ovrl_SYSTEM_H

#include "common/all.h"
#include "system/ovrlwindow.h"
#include "system/ovrlfpscounter.h"

#if defined(PIPELINE_USE_DX9)
#include "pipeline/dx9/ovrlpipeline_dx9.h"
#define PIPELINE_CLASS CPipeline_DX9
#endif
#if defined(PIPELINE_USE_DX8)
//#include "pipeline/dx8/ovrlpipeline_dx8.h"
#define PIPELINE_CLASS CPipeline_DX8
#endif
#if defined(PIPELINE_USE_OPENGL)
//#include "pipeline/opengl/ovrlpipeline_opengl.h"
#define PIPELINE_CLASS CPipeline_OpenGL
#endif

#include "world/world.h"

namespace openvrl {


class OVRLIBAPI IPipeline;

class OVRLIBAPI PIPELINE_CLASS;	
// btw, other changes has to be made... 
// System class must be rewritten to use other devices and so on


/**
 *	CSystem class
 */
class OVRLIBAPI CSystem : public CWindow
{
protected:
	IPipeline		*m_Pipeline;
	IWorld			*m_World;

	LPDIRECT3D9         m_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9   m_pd3dDevice; // Our rendering device

	CString 		m_szCmdLine;
	CFPSCounter 	m_FPS;
	bool			m_Active;

public: 
	void setActive(bool a=true) { m_Active = a; }
	bool isActive() const { return m_Active; }

	virtual void print_information() const {};
	virtual void print_information(CString& str) const {};

	IPipeline* Pipeline() const { return m_Pipeline; }
	IPipeline* get_Pipeline() const { return m_Pipeline; }

	IWorld* World() const { return m_World; }
	IWorld* get_world() const { return m_World; }

	LPDIRECT3DDEVICE9 d3dDevice() const { return m_pd3dDevice; }
	LPDIRECT3DDEVICE9 get_d3dDevice() const { return m_pd3dDevice; }

	/**
	 *
	 */
	CSystem();
	CSystem(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        const CString& szCmdLine, int nCmdShow, uint X, uint Y, uint Width, uint Height);
	CSystem(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        const CString& szCmdLine, int nCmdShow, const CString& szWinTitle, 
		const CString& szWinClass,
		uint X, uint Y, uint Width, uint Height);
	~CSystem();

	/** */
	virtual int run(bool nOwnLoop = true);


	virtual CFPSCounter& FPS() { return m_FPS; }
	virtual CFPSCounter FPS() const { return m_FPS; }

	/** */
	virtual int BeginScene();
	virtual int EndScene();

	virtual LRESULT WndProc(UINT m, WPARAM w, LPARAM l);

protected:
	virtual bool InitSystem();
	virtual bool InitD3D();
	virtual bool FrameCalculate();
	virtual bool FrameRender();
	virtual bool ReleaseD3D();
	virtual bool ReleaseSystem();

private:
	virtual IPipeline* create_Pipeline() { return new PIPELINE_CLASS(this); }
	virtual IWorld* create_World() { return new CWorld(this); }

	virtual void delete_Pipeline(IPipeline* pl) { delete pl; }
	virtual void delete_World(IWorld* w) { delete w; }
};

};

#endif
