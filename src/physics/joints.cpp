#include "physics/joints.h"


namespace openvrl
{

//
// Null Joint group wrapper
//
CNullJointGroup::CNullJointGroup()
{
	m_Joints = new std::list<IBasicJoint*>;
	m_Group = 0;
}

CNullJointGroup::~CNullJointGroup()
{
	Release();
	delete m_Joints;
}

void CNullJointGroup::Add(IBasicJoint*j)
{
	OVRL_ASSERT(j);
	OVRL_ASSERT(m_Group);
	j->onInsert(this);
	m_Joints->insert(m_Joints->end(), j);
}

void CNullJointGroup::Remove(IBasicJoint* j)
{
	OVRL_ASSERT(m_Group);
	OVRL_ASSERT(j);
	j->onRemove(this);
	m_Joints->remove(j);
}

void CNullJointGroup::Prepare()
{
	std::list<IBasicJoint*>::iterator I;

	I = m_Joints->begin();

	while ( I!=m_Joints->end() )
	{
		if ( *I )
			(*I)->Prepare();
		I++;
	}
}

void CNullJointGroup::Release()
{
	std::list<IBasicJoint*>::iterator I;

	I = m_Joints->begin();

	while ( I!=m_Joints->end() )
	{
		if ( *I )
			(*I)->Release();
		delete *I;
		I++;
	}
	m_Joints->clear();
}

void CNullJointGroup::Create()
{
	OVRL_ASSERT(m_Group==0);
}

void CNullJointGroup::Update()
{
	std::list<IBasicJoint*>::iterator I;

	I = m_Joints->begin();

	while ( I!=m_Joints->end() )
	{
		if ( *I )
			(*I)->Update();
		I++;
	}
}

void CNullJointGroup::onInsert(CPhysicsEngine* e)
{
	OVRL_ASSERT(e);
	m_Engine = e;
}

void CNullJointGroup::onRemove(CPhysicsEngine* e)
{
	OVRL_ASSERT(e);
	OVRL_ASSERT(m_Engine==e);
	m_Engine = 0;
}

//
// Basic ODE Joint group wrapper
//
CBasicODEJointGroup::CBasicODEJointGroup()
	:CNullJointGroup()
{
}

CBasicODEJointGroup::~CBasicODEJointGroup()
{
}

void CBasicODEJointGroup::Release()
{
	CNullJointGroup::Release();
	if ( GetGroup() )
	{
		dJointGroupEmpty(GetGroup());
		dJointGroupDestroy(GetGroup());
		SetGroup(0);
	}
}

void CBasicODEJointGroup::Create()
{
	OVRL_ASSERT(GetGroup()==0);
	SetGroup(dJointGroupCreate(0));
}


//
// Basic ODE Joint wrapper
//
CBasicODEJoint::CBasicODEJoint()
{
	m_Joint = 0;
	m_Group = 0;
	m_Body1 = m_Body2 = 0;
}

CBasicODEJoint::~CBasicODEJoint()
{
	Release();
}

void CBasicODEJoint::Prepare()
{
}

void CBasicODEJoint::Release()
{
}

void CBasicODEJoint::Create()
{
}

void CBasicODEJoint::Attach(IBasicBody* b1, IBasicBody* b2)
{
	OVRL_ASSERT(b1 || b2);
	OVRL_ASSERT(m_Body1==0 && m_Body2==0);
	
	m_Body1 = b1;
	m_Body2 = b2;
	dJointAttach(GetJoint(), b1?b1->GetBody():0, b2?b2->GetBody():0);
}

void CBasicODEJoint::Update()
{
}

void CBasicODEJoint::onInsert(IBasicJointGroup* jg)
{
	OVRL_ASSERT(jg);
	OVRL_ASSERT(m_Group == 0);
	m_Group = jg;
}

void CBasicODEJoint::onRemove(IBasicJointGroup* jg)
{
	OVRL_ASSERT(jg);
	OVRL_ASSERT(m_Group==jg);
	m_Group = 0;
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
void CFixedJoint::onInsert(IBasicJointGroup* jg)
{
	CBasicODEJoint::onInsert(jg);
	SetJoint(dJointCreateFixed(jg->GetPhysicsEngine()->GetEngine(), jg->GetGroup()));
}

void CFixedJoint::onRemove(IBasicJointGroup* jg)
{
	CBasicODEJoint::onRemove(jg);
}

void CFixedJoint::Fix()
{
	dJointSetFixed(GetJoint());
}

//
// CSliderJoint
//
void CSliderJoint::onInsert(IBasicJointGroup* jg)
{
	CBasicODEJoint::onInsert(jg);
	SetJoint(dJointCreateSlider(jg->GetPhysicsEngine()->GetEngine(), jg->GetGroup()));
}

void CSliderJoint::onRemove(IBasicJointGroup* jg)
{
	CBasicODEJoint::onRemove(jg);
}

void CSliderJoint::SetAxis(const C3DVector& a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetSliderAxis (GetJoint(), a.x(), a.y(), a.z());
}

C3DVector CSliderJoint::GetAxis() const
{
	dVector3 v;
	OVRL_ASSERT(GetJoint());
	dJointGetSliderAxis (GetJoint(), v);

	return C3DVector(v[0], v[1], v[2]);
}

void CSliderJoint::SetStops(real lo,real hi)
{
	OVRL_ASSERT(GetJoint());
	dJointSetSliderParam(GetJoint(), dParamHiStop, hi);
	dJointSetSliderParam(GetJoint(), dParamLoStop, lo);
}
void CSliderJoint::SetHiStop(real b)
{
	OVRL_ASSERT(GetJoint());
	dJointSetSliderParam(GetJoint(), dParamHiStop, b);
}
void CSliderJoint::SetLoStop(real a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetSliderParam(GetJoint(), dParamLoStop, a);
}

real CSliderJoint::GetPos() const
{
	OVRL_ASSERT(GetJoint());
	return dJointGetSliderPosition(GetJoint());
}
real CSliderJoint::GetPosRate() const
{
	OVRL_ASSERT(GetJoint());
	return dJointGetSliderPositionRate(GetJoint());
}

//
//
//
void CHingeJoint::onInsert(IBasicJointGroup* jg)
{
	CBasicODEJoint::onInsert(jg);
	SetJoint(dJointCreateHinge(jg->GetPhysicsEngine()->GetEngine(), jg->GetGroup()));
}

void CHingeJoint::onRemove(IBasicJointGroup* jg)
{
	CBasicODEJoint::onRemove(jg);
}

void CHingeJoint::SetAnchor(const C3DVector& a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHingeAnchor (GetJoint(), a.x(), a.y(), a.z());
}

void CHingeJoint::SetAxis(const C3DVector& a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHingeAxis (GetJoint(), a.x(), a.y(), a.z());
}

void CHingeJoint::SetHiStop(real a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHingeParam(GetJoint(), dParamHiStop, a);
}

void CHingeJoint::SetLoStop(real a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHingeParam(GetJoint(), dParamLoStop, a);
}

void CHingeJoint::SetStops(real a,real b)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHingeParam(GetJoint(), dParamHiStop, b);
	dJointSetHingeParam(GetJoint(), dParamLoStop, a);
}

void CHingeJoint::SetAngularVelocity(real v)
{
	OVRL_ASSERT(GetJoint());
    dJointSetHingeParam (GetJoint(),dParamVel,v);
}

void CHingeJoint::SetMaxForce(real f)
{
	OVRL_ASSERT(GetJoint());
    dJointSetHingeParam (GetJoint(),dParamFMax,f);
}


void CHingeJoint::SetTorque(real t)
{
	OVRL_ASSERT(GetJoint());
	dJointAddHingeTorque(GetJoint(), t);
}

real CHingeJoint::GetAngle() const
{
	OVRL_ASSERT(GetJoint());
	return dJointGetHingeAngle(GetJoint());
}

real CHingeJoint::GetAngleRate() const
{
	OVRL_ASSERT(GetJoint());
	return dJointGetHingeAngleRate(GetJoint());
}

//
//
//
void CHinge2Joint::onInsert(IBasicJointGroup* jg)
{
	CBasicODEJoint::onInsert(jg);
	SetJoint(dJointCreateHinge2(jg->GetPhysicsEngine()->GetEngine(), jg->GetGroup()));
}

void CHinge2Joint::onRemove(IBasicJointGroup* jg)
{
	CBasicODEJoint::onRemove(jg);
}

void CHinge2Joint::SetAnchor(const C3DVector& a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHinge2Anchor (GetJoint(), a.x(), a.y(), a.z());
}

void CHinge2Joint::SetAxis1(const C3DVector& a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHinge2Axis1 (GetJoint(), a.x(), a.y(), a.z());
}
void CHinge2Joint::SetAxis2(const C3DVector& a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHinge2Axis2 (GetJoint(), a.x(), a.y(), a.z());
}

void CHinge2Joint::SetHiStop(real a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHinge2Param(GetJoint(), dParamHiStop, a);
}

void CHinge2Joint::SetLoStop(real a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHinge2Param(GetJoint(), dParamLoStop, a);
}

void CHinge2Joint::SetStops1(real a,real b)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHinge2Param(GetJoint(), dParamHiStop, b);
	dJointSetHinge2Param(GetJoint(), dParamLoStop, a);
}
void CHinge2Joint::SetStops2(real a,real b)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHinge2Param(GetJoint(), dParamHiStop2, b);
	dJointSetHinge2Param(GetJoint(), dParamLoStop2, a);
}
void CHinge2Joint::SetStops3(real a,real b)
{
	OVRL_ASSERT(GetJoint());
	dJointSetHinge2Param(GetJoint(), dParamHiStop3, b);
	dJointSetHinge2Param(GetJoint(), dParamLoStop3, a);
}

void CHinge2Joint::SetAngularVelocity1(real v)
{
	OVRL_ASSERT(GetJoint());
    dJointSetHinge2Param (GetJoint(),dParamVel,v);
}

void CHinge2Joint::SetAngularVelocity2(real v)
{
	OVRL_ASSERT(GetJoint());
//    dJointSetHinge2Param (GetJoint(),dParamVel1,v);
}

void CHinge2Joint::SetMaxForce(real f)
{
	OVRL_ASSERT(GetJoint());
    dJointSetHinge2Param (GetJoint(),dParamFMax,f);
}

real CHinge2Joint::GetAngle1() const
{
	OVRL_ASSERT(GetJoint());
	return dJointGetHinge2Angle1(GetJoint());
}

real CHinge2Joint::GetAngle2() const
{
	OVRL_ASSERT(GetJoint());
	return 0;//dJointGetHinge2Angle2(GetJoint());
}

real CHinge2Joint::GetAngleRate1() const
{
	OVRL_ASSERT(GetJoint());
	return dJointGetHinge2Angle1Rate(GetJoint());
}

real CHinge2Joint::GetAngleRate2() const
{
	OVRL_ASSERT(GetJoint());
	return dJointGetHinge2Angle2Rate(GetJoint());
}

void CHinge2Joint::SetTorques(real t1, real t2)
{
	OVRL_ASSERT(GetJoint());
	dJointAddHinge2Torques(GetJoint(), t1,t2);
}

//
//
//
void CBallJoint::onInsert(IBasicJointGroup* jg)
{
	CBasicODEJoint::onInsert(jg);
	SetJoint(dJointCreateBall(jg->GetPhysicsEngine()->GetEngine(), jg->GetGroup()));
}

void CBallJoint::onRemove(IBasicJointGroup* jg)
{
	CBasicODEJoint::onRemove(jg);
}

void CBallJoint::SetAnchor(const C3DVector& a)
{
	OVRL_ASSERT(GetJoint());
	dJointSetBallAnchor(GetJoint(), a.x(), a.y(), a.z());
}

void CBallJoint::SetStops(const C3DVector&, const C3DVector&)
{
	OVRL_ASSERT(GetJoint());
}

void CBallJoint::SetHiStop(const C3DVector&)
{
	OVRL_ASSERT(GetJoint());
//	dJointSetBallParam(GetJoint(), 
}

void CBallJoint::SetLoStop(const C3DVector&)
{
	OVRL_ASSERT(GetJoint());
}

}
