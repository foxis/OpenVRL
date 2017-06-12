/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/physics/body.h,v $
 * $Implementation: ~/src/ $
 * $Revision: 1.11 $
 * $Author: foxis $
 * $Date: 2005/05/16 12:36:46 $
 * $Description:  $
 *
 * $Log: body.h,v $
 * Revision 1.11  2005/05/16 12:36:46  foxis
 * several CString & xFactory bugfixes
 *
 * Revision 1.10  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.9  2005/02/11 11:02:50  foxis
 * fixed many bugs
 * added joints
 *
 * Revision 1.8  2005/02/07 19:06:55  foxis
 * minor changes
 *
 * Revision 1.7  2005/02/06 09:58:35  foxis
 * Is/Set Moved renamed to more general Get/Set TypeBits
 *
 * Revision 1.6  2005/02/04 21:16:45  foxis
 * no message
 *
 * Revision 1.5  2005/02/04 20:33:19  foxis
 * physics + collision now at last works!
 * left implementing: IBasicJoint and CBasicODEJoint and so on
 * incapsulating geoms. so that one body can have many geoms.
 *
 * Revision 1.4  2005/02/03 17:52:55  foxis
 * made IBasicGeom and it's derivatives to work.
 * now physics engine recognizes collisions.
 *
 * however geom management should be rethought.
 *
 * Revision 1.3  2005/02/03 11:17:42  foxis
 * added IBasicGeom
 * and started ODE geom classes wrappers
 *
 * Revision 1.2  2005/02/02 20:03:25  foxis
 * Basic ODE support - seems to work ok
 * basic CBody - seems to work
 * basic system overall - seems to work :)
 *
 * minor bugfixes, and changes in body managment code
 *
 * Revision 1.1.1.1  2005/02/02 15:39:18  foxis
 * sources import
 *
 * Revision 0.3  20010411  :: FoxiE
 *
 */

#if !defined(AFX_PHYSICSBODY_H__5B5AFBC1_A30D_11D6_8083_AC5497E6FC73__INCLUDED_)
#define AFX_PHYSICSBODY_H__5B5AFBC1_A30D_11D6_8083_AC5497E6FC73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common/all.h"
#include "physics/engine.h"
#include "physics/basicgeom.h"
#include <ode/ode.h>

namespace openvrl {

#define OVRL_BT_MOVEABLE	0x00000001
#define OVRL_BT_PHYSICSABLE	0x00000002
#define OVRL_BT_CANAFFECTOTHERS	0x00000004
#define OVRL_BT_CANRECURSE	0x00000008

class CPhysicsEngine;
class IBasicGeom;

class OVRLIBAPI IBasicBody 
{
public: 
	virtual dBodyID GetBody() = 0;
	virtual IBasicGeom* GetGeom() = 0;
	virtual CPhysicsEngine* GetPhysicsEngine() = 0;

	virtual void SetGeom(IBasicGeom*) = 0;

public:
	virtual ~IBasicBody() = 0 {}

	virtual ulong onInsert(CPhysicsEngine* e) = 0;
	virtual ulong onRemove(CPhysicsEngine* e) = 0;

	virtual dBodyID GetBody() const = 0;
	virtual IBasicGeom* GetGeom() const = 0;
	virtual CPhysicsEngine* GetPhysicsEngine() const = 0;

	virtual ulong GetTypeBits() const = 0;
	virtual void SetTypeBits(ulong) = 0;

	virtual real GetMass() const = 0;
	virtual C4x4Matrix GetInertiaTensor() const = 0;
	virtual C3DVector GetMassCenter() const = 0;
	virtual C3DVector GetPosition() const = 0;
	virtual C3DVector GetOrientation() const = 0;
	virtual CQuaternion GetOrientationQuaternion() const = 0;
	virtual C4x4Matrix GetOrientationMatrix() const = 0;
	virtual C3DVector GetLinearVelocity() const = 0;
	virtual C3DVector GetAngularVelocity() const = 0;
	virtual C3DVector GetForce() const = 0;
	virtual C3DVector GetTorque() const = 0;
	virtual C3DVector GetLinearMomentum() const = 0;
	virtual C3DVector GetAngularMomentum() const = 0;

	virtual void EnablePhysics(bool en) = 0;
	virtual bool IsEnabledPhysics() const = 0;

	virtual void SetMass(real) = 0;
	virtual void SetInertiaTensor(const C4x4Matrix&) = 0;
	virtual void SetMassCenter(const C3DVector&) = 0;
	virtual void SetPosition(const C3DVector&) = 0;
	virtual void SetOrientation(const C3DVector&) = 0;
	virtual void SetOrientationQuaternion(const CQuaternion&) = 0;
	virtual void SetOrientationMatrix(const C4x4Matrix&) = 0;
	virtual void SetLinearVelocity(const C3DVector&) = 0;
	virtual void SetAngularVelocity(const C3DVector&) = 0;
	virtual void AddForce(const C3DVector&, bool relative=false) = 0;
	virtual void AddForceAt(const C3DVector& force, const C3DVector& at, bool relative=false) = 0;
	virtual void AddTorque(const C3DVector&, bool relative=false) = 0;
	virtual void SetForce(const C3DVector&) = 0;
	virtual void SetTorque(const C3DVector&) = 0;
	virtual void SetLinearMomentum(const C3DVector&) = 0;
	virtual void SetAngularMomentum(const C3DVector&) = 0;

	virtual void onCollide(IBasicBody& me, IBasicBody& other) = 0;
	virtual void PreparePhysics() = 0;
	virtual void UpdatePhysics(real time_step) = 0;
};

};

#endif // !defined(AFX_PHYSICSBODY_H__5B5AFBC1_A30D_11D6_8083_AC5497E6FC73__INCLUDED_)
