/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/world/camera.h,v $
 * $Implementation:  $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/07/14 11:33:57 $
 * $Description:  $
 *
 * $Log: camera.h,v $
 * Revision 1.2  2005/07/14 11:33:57  foxis
 * implemented: CCamera::SetLookAt
 *
 * Revision 1.1  2005/02/23 12:30:57  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 */

#if !defined(__ovrl_CAMERA_HPP)
#define __ovrl_CAMERA_HPP

#include "world/basicentity.h"
#include "world/worldsector.h"
#include "physics/engine.h"

namespace openvrl {

class CCamera : public CBasicEntity, public IBasicCamera
{
	CxfCamera* m_Camera;
	IRenderTarget* m_RenderTarget;

	real m_Mass;
	C3DVector m_MassCenter;
	C4x4Matrix m_InertiaTensor;

	ulong m_TypeBits;

	C4x4Matrix 
		m_Projection,
		m_View;

public:
	CCamera();
	virtual ~CCamera();

	virtual IBasicPipelineEntity* GetPipelineEntity(ulong caps) { return (caps&OVRL_CAPS_CAMERA)?this:0; }

	virtual void SetLookAt(const C3DVector& pos, const C3DVector& target, real);

	virtual C4x4Matrix& GetProjectionMatrix() { return m_Projection; }
	virtual C4x4Matrix& GetViewMatrix() { return m_View; }

	virtual void SetDefaultPipelineStates(IPipeline*) {}

	//
	// IBasicWorldEntity
	//
	virtual ulong what() const	{ return ORW_CAMERA; }
	virtual CHAR* get_name() const { return "Camera"; }
	virtual ulong caps() const	{ return OVRL_CAPS_CAMERA; }

	virtual void Prepare();
	virtual void Release();
	virtual int Update(real time_step);

	//
	// IBasicCamera
	//
	virtual void Attach(CxfCamera* camera);
	virtual void Attach(const CString& path, int what) ;

	virtual CxfCamera* GetCamera() { return m_Camera; }
	virtual IRenderTarget *GetRenderTarget() { return m_RenderTarget; }
	virtual void SetRenderTarget(IRenderTarget*);

	//
	//
	//
	virtual void UpdatePhysics(real time_step);

};

}

#endif
