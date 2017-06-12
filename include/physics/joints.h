/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/physics/joints.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/05/16 12:36:46 $
 * $Description:  $
 *
 * $Log: joints.h,v $
 * Revision 1.2  2005/05/16 12:36:46  foxis
 * several CString & xFactory bugfixes
 *
 * Revision 1.1  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 *
 *
 */

#if !defined(__ovrl__JOINTS_H_DEFINED)
#define __ovrl__JOINTS_H_DEFINED


#include "common/all.h"
#include "physics/engine.h"
#include "physics/BasicJoint.h"
#include <ode/ode.h>
#include <list>


namespace openvrl {


//
// Null Joint group
//
class OVRLIBAPI CNullJointGroup : public IBasicJointGroup
{
	std::list<IBasicJoint*>* m_Joints;
	dJointGroupID m_Group;
	CPhysicsEngine* m_Engine;

public:
	CNullJointGroup();
	virtual ~CNullJointGroup();

	virtual void SetGroup(dJointGroupID g) { m_Group = g; }
	virtual dJointGroupID GetGroup() const { return m_Group; }
	virtual dJointGroupID GetGroup() { return m_Group; }

	virtual void Add(IBasicJoint*);
	virtual void Remove(IBasicJoint*);

	virtual CPhysicsEngine* GetPhysicsEngine() { return m_Engine; }
	virtual CPhysicsEngine* GetPhysicsEngine() const { return m_Engine; }

	virtual void Prepare();
	virtual void Release();
	virtual void Create();
	virtual void Update();

	virtual void onInsert(CPhysicsEngine*);
	virtual void onRemove(CPhysicsEngine*);
};

//
// Basic ODE Joint group wrapper
//
class OVRLIBAPI CBasicODEJointGroup : public CNullJointGroup
{

public:
	CBasicODEJointGroup();
	virtual ~CBasicODEJointGroup();

	virtual void Release();
	virtual void Create();
};

//
// Basic ODE Joint wrapper
//
class OVRLIBAPI CBasicODEJoint : public IBasicJoint
{
	IBasicBody *m_Body1, *m_Body2;
	dJointID	m_Joint;
	IBasicJointGroup* m_Group;

public:
	CBasicODEJoint();
	virtual ~CBasicODEJoint();

	virtual void SetJoint(dJointID j) { m_Joint=j; }
	virtual dJointID GetJoint() const { return m_Joint; }
	virtual dJointID GetJoint() { return m_Joint; }

	virtual IBasicBody* GetBody1() const { return m_Body1; }
	virtual IBasicBody* GetBody2() const { return m_Body2; }
	virtual IBasicBody* GetBody1() { return m_Body1; }
	virtual IBasicBody* GetBody2() { return m_Body2; }

	virtual void Prepare();
	virtual void Release();
	virtual void Create();
	virtual void Attach(IBasicBody*, IBasicBody*);
	virtual void Update();

	virtual void onInsert(IBasicJointGroup*);
	virtual void onRemove(IBasicJointGroup*);
};

///////////////////////////////////////////////////////////////////////////////

class OVRLIBAPI CFixedJoint : public CBasicODEJoint
{
public:
	CFixedJoint() : CBasicODEJoint() {}
	virtual ~CFixedJoint() {}

	virtual void onInsert(IBasicJointGroup*);
	virtual void onRemove(IBasicJointGroup*);

	void Fix();
};


//
// CSliderJoint
//
class OVRLIBAPI CSliderJoint : public CBasicODEJoint
{
public:
	CSliderJoint() : CBasicODEJoint() {}
	virtual ~CSliderJoint() {}

	virtual void onInsert(IBasicJointGroup*);
	virtual void onRemove(IBasicJointGroup*);

	void SetAxis(const C3DVector&);
	C3DVector GetAxis() const;

	void SetStops(real hi,real lo);
	void SetHiStop(real);
	void SetLoStop(real);

	real GetPos() const;
	real GetPosRate() const;
};

//
// CHingeJoint
//
class OVRLIBAPI CHingeJoint : public CBasicODEJoint
{
public:
	CHingeJoint() : CBasicODEJoint() {}
	virtual ~CHingeJoint() {}

	virtual void onInsert(IBasicJointGroup*);
	virtual void onRemove(IBasicJointGroup*);

	void SetAnchor(const C3DVector&);
	void SetAxis(const C3DVector&);

	void SetStops(real hi,real lo);
	void SetHiStop(real);
	void SetLoStop(real);

	void SetAngularVelocity(real v);
	void SetTorque(real);
	void SetMaxForce(real);

	real GetAngle() const;
	real GetAngleRate() const;
};

//
// CHinge2Joint
//
class OVRLIBAPI CHinge2Joint : public CBasicODEJoint
{
public:
	CHinge2Joint() : CBasicODEJoint() {}
	virtual ~CHinge2Joint() {}

	virtual void onInsert(IBasicJointGroup*);
	virtual void onRemove(IBasicJointGroup*);

	void SetAnchor(const C3DVector&);
	void SetAxis1(const C3DVector&);
	void SetAxis2(const C3DVector&);

	void SetStops1(real hi,real lo);
	void SetStops2(real hi,real lo);
	void SetStops3(real hi,real lo);
	void SetHiStop(real);
	void SetLoStop(real);

	void SetAngularVelocity1(real v);
	void SetAngularVelocity2(real v);

	void SetMaxForce(real);

	real GetAngle1() const;
	real GetAngle2() const;

	real GetAngleRate1() const;
	real GetAngleRate2() const;

	void SetTorques(real,real);
};

//
// CBallJoint
//
class OVRLIBAPI CBallJoint : public CBasicODEJoint
{
public:
	CBallJoint() : CBasicODEJoint() {}
	virtual ~CBallJoint() {}

	virtual void onInsert(IBasicJointGroup*);
	virtual void onRemove(IBasicJointGroup*);

	void SetAnchor(const C3DVector&);
	void SetStops(const C3DVector&, const C3DVector&);
	void SetHiStop(const C3DVector&);
	void SetLoStop(const C3DVector&);
};

};

#endif