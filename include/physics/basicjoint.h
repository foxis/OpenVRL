/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/physics/basicjoint.h,v $
 * $Implementation: $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/02/11 11:02:50 $
 * $Description:  $
 *
 * $Log: basicjoint.h,v $
 * Revision 1.3  2005/02/11 11:02:50  foxis
 * fixed many bugs
 * added joints
 *
 * Revision 1.2  2005/02/04 20:33:19  foxis
 * physics + collision now at last works!
 * left implementing: IBasicJoint and CBasicODEJoint and so on
 * incapsulating geoms. so that one body can have many geoms.
 *
 * Revision 1.1  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(__ovrl__BASICJOINT_H_DEFINED)
#define __ovrl__BASICJOINT_H_DEFINED


#include "common/all.h"
#include "physics/engine.h"
#include "physics/BasicJoint.h"
#include <ode/ode.h>


namespace openvrl
{

class IBasicBody;
class CPhysicsEngine;
class IBasicJoint;

class IBasicJointGroup
{
public:
	virtual ~IBasicJointGroup() = 0 {}

	virtual void SetGroup(dJointGroupID)= 0;
	virtual dJointGroupID GetGroup() const = 0;
	virtual dJointGroupID GetGroup() = 0;

	virtual CPhysicsEngine* GetPhysicsEngine() = 0;
	virtual CPhysicsEngine* GetPhysicsEngine() const = 0;

	virtual void Add(IBasicJoint*) = 0;
	virtual void Remove(IBasicJoint*) = 0;

	virtual void Prepare() = 0;
	virtual void Release() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;

	virtual void onInsert(CPhysicsEngine*) = 0;
	virtual void onRemove(CPhysicsEngine*) = 0;
};


class IBasicJoint 
{
public:
	virtual ~IBasicJoint() = 0 {}

	virtual void SetJoint(dJointID) = 0;
	virtual dJointID GetJoint() const = 0;
	virtual dJointID GetJoint() = 0;

	virtual IBasicBody* GetBody1() const =0;
	virtual IBasicBody* GetBody2() const =0;
	virtual IBasicBody* GetBody1() =0;
	virtual IBasicBody* GetBody2() =0;

	virtual void Prepare() = 0;
	virtual void Release() = 0;
	virtual void Create() = 0;
	virtual void Attach(IBasicBody*, IBasicBody*) = 0;
	virtual void Update() = 0;

	virtual void onInsert(IBasicJointGroup*) = 0;
	virtual void onRemove(IBasicJointGroup*) = 0;
};



};

#endif