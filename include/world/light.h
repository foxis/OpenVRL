/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/world/light.h,v $
 * $Implementation:  $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/03/01 18:21:16 $
 * $Description:  $
 *
 * $Log: light.h,v $
 * Revision 1.2  2005/03/01 18:21:16  foxis
 * Pipeline: shadows now working more or less. need to handle special cases.
 * C4x4Matrix: added inverse method + others
 *
 * Revision 1.1  2005/02/23 12:30:57  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 */

#if !defined(__ovrl_LIGHT_HPP)
#define __ovrl_LIGHT_HPP

#include "world/basicentity.h"
#include "world/worldsector.h"
#include "physics/engine.h"

namespace openvrl {

class CLight : public CBasicEntity, public IBasicLight
{
	CxfLight* m_Light;

	real m_Mass;
	C3DVector m_MassCenter;
	C4x4Matrix m_InertiaTensor;

	ulong m_TypeBits;

	C4x4Matrix
		m_TransformMatrix,
		m_WorldTransformMatrix;

public:
	CLight();
	virtual ~CLight();

	virtual IBasicPipelineEntity* GetPipelineEntity(ulong caps) { return (caps&OVRL_CAPS_LIGHT)?this:0; }

	virtual void SetDefaultPipelineStates(IPipeline*) {}

	//
	// IBasicWorldEntity
	//
	virtual ulong what() const	{ return ORW_LIGHT; }
	virtual CHAR* get_name() const { return "Light"; }
	virtual ulong caps() const	{ return OVRL_CAPS_LIGHT; }

	virtual void Prepare();
	virtual void Release();
	virtual int Update(real time_step);

	//
	// IBasicLight
	//
	virtual C4x4Matrix& GetTransformMatrix() { return m_TransformMatrix; } 
	virtual C4x4Matrix& GetWorldTransformMatrix() { return m_WorldTransformMatrix; }

	virtual void Attach(CxfLight*);
	virtual void Attach(const CString&, int);

	virtual CxfLight* GetLight() { return m_Light; }

	//
	//
	//
	virtual void UpdatePhysics(real time_step);

};

}

#endif
