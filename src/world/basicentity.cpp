#include "system/ovrlsystem.h"
#include "world/worldsector.h"
#include "world/basicentity.h"

namespace openvrl {

CBasicEntity::CBasicEntity()
{
	m_Sector = 0;
	m_Physics = 0;
	m_Body = 0;
	m_Geom = 0;
	m_Mass = 0;
	m_Pipeline = 0;
	m_World = 0;
	m_MassCenter = C3DVector::ZERO();
	m_InertiaTensor= C4x4Matrix::zero();
	m_TypeBits = OVRL_BT_MOVEABLE | OVRL_BT_PHYSICSABLE | OVRL_BT_CANAFFECTOTHERS;
}

CBasicEntity::~CBasicEntity()
{
	Release();
}

ulong CBasicEntity::onInsert(IBasicWorldEntity* e)
{
	OVRL_ASSERT(m_Sector==0);
	OVRL_ASSERT(e);
	OVRL_ASSERT(e->what()==ORW_WORLD_SECTOR);

	m_Sector = e;
	AddRef();

	return 0;
}

ulong CBasicEntity::onRemove(IBasicWorldEntity* e)
{
	OVRL_ASSERT(m_Sector!=0);
	OVRL_ASSERT(m_Sector==e);
	OVRL_ASSERT(e->what()!=ORW_WORLD_SECTOR);

	m_Sector =0;

	DelRef();
	return 0;
}

ulong CBasicEntity::onInsert(CPhysicsEngine* e)
{
	OVRL_ASSERT(m_Physics==0);
	OVRL_ASSERT(e);
	m_Physics = e;
	return 0;
}

ulong CBasicEntity::onRemove(CPhysicsEngine* e)
{
	OVRL_ASSERT(m_Physics!=0);
	OVRL_ASSERT(m_Physics==e);
	OVRL_ASSERT(e);
	m_Physics = 0;
	return 0;
}

void CBasicEntity::Release()
{
	if ( m_Body ) { dBodyDestroy(m_Body); m_Body =0; }
	if ( m_Geom ) { m_Geom->Attach(0); }//m_Geom->Release(); delete m_Geom; m_Geom =0; }
	IBasicWorldEntity::Release();
}

void CBasicEntity::SetGeom(IBasicGeom* g)
{
	OVRL_ASSERT(m_Geom==0);
	OVRL_ASSERT(g);
	m_Geom = g;
}

void CBasicEntity::Prepare()
{
	OVRL_ASSERT(m_Body==0);
	m_Body = dBodyCreate(m_Physics->GetEngine());
	m_Pipeline = GetSector()->GetPipeline(); 
	m_World = GetSector()->GetWorld(); 
}

void CBasicEntity::PreparePhysics()
{
	OVRL_ASSERT(m_Physics);
	if ( m_Geom ) m_Geom->Prepare();
}

int CBasicEntity::Update(real time_step)
{
	if ( GetGeom() ) GetGeom()->Update();
	return 0;
}


real CBasicEntity::GetMass() const
{
	return m_Mass;
}

C4x4Matrix CBasicEntity::GetInertiaTensor() const
{
	return m_InertiaTensor;
}

C3DVector CBasicEntity::GetMassCenter() const
{
	return m_MassCenter;
}

C3DVector CBasicEntity::GetPosition() const 
{
	OVRL_ASSERT(m_Body);
	const dReal *dv;
	dv = dBodyGetPosition(m_Body);
	return C3DVector(dv[0], dv[1], dv[2]);
}

C3DVector CBasicEntity::GetOrientation() const 
{
	OVRL_ASSERT(m_Body);
	const dReal *dv;
	C4x4Matrix m;
	C3DVector v(0,0,1);
	dv = dBodyGetRotation(m_Body);
	m.set(dv[0], dv[4], dv[8], 0, dv[1],dv[5],dv[9], 0, dv[2],dv[6],dv[10], 0, 0,0,0,1);
//	m.set(dv[0], dv[1], dv[2], 0, dv[4],dv[5],dv[6], 0, dv[8],dv[9],dv[10], 0, 0,0,0,1);
	v.mul(m);
	return v;
}
CQuaternion CBasicEntity::GetOrientationQuaternion() const 
{
	OVRL_ASSERT(m_Body);
	const dReal *dv;
	dv = dBodyGetQuaternion(m_Body);
	return CQuaternion(dv[1],dv[2],dv[3],dv[0]);
}

C4x4Matrix CBasicEntity::GetOrientationMatrix() const 
{
	OVRL_ASSERT(m_Body);
	const dReal *dv;
	C4x4Matrix m;
	dv = dBodyGetRotation(m_Body);
	m.set(dv[0], dv[4], dv[8], 0, dv[1],dv[5],dv[9], 0, dv[2],dv[6],dv[10], 0, 0,0,0,1);
//	m.set(dv[0], dv[1], dv[2], 0, dv[4],dv[5],dv[6], 0, dv[8],dv[9],dv[10], 0, 0,0,0,1);
	return m;
}

C3DVector CBasicEntity::GetLinearVelocity() const 
{
	OVRL_ASSERT(m_Body);
	const dReal *dv;
	dv = dBodyGetLinearVel(m_Body);
	return C3DVector(dv[0], dv[1], dv[2]);
}
C3DVector CBasicEntity::GetAngularVelocity() const 
{
	OVRL_ASSERT(m_Body);
	const dReal *dv;
	dv = dBodyGetAngularVel(m_Body);
	return C3DVector(dv[0], dv[1], dv[2]);
}
C3DVector CBasicEntity::GetForce() const 
{ 
	OVRL_ASSERT(m_Body);
	const dReal* v = dBodyGetForce(m_Body);
	return C3DVector(v[0], v[1],v[2]); 
}
C3DVector CBasicEntity::GetTorque() const 
{ 
	OVRL_ASSERT(m_Body);
	const dReal* v = dBodyGetTorque(m_Body);
	return C3DVector(v[0], v[1],v[2]); 
}
C3DVector CBasicEntity::GetLinearMomentum() const { return C3DVector::ZERO(); }
C3DVector CBasicEntity::GetAngularMomentum() const { return C3DVector::ZERO(); }

void CBasicEntity::SetMass(real m)
{
	OVRL_ASSERT(m_Body);
	dMass dm;
	dBodyGetMass(m_Body, &dm);
	m_Mass = m;
	dm.mass = m;
	dBodySetMass(m_Body, &dm);
}

void CBasicEntity::SetMassCenter(const C3DVector& dv)
{
	OVRL_ASSERT(m_Body);
	dMass dm;
	dBodyGetMass(m_Body, &dm);
	m_MassCenter = dv;
	dm.c[0] = dv.x();
	dm.c[1] = dv.x();
	dm.c[2] = dv.x();
	dBodySetMass(m_Body, &dm);
}

void CBasicEntity::SetInertiaTensor(const C4x4Matrix& m)
{
	OVRL_ASSERT(m_Body);
	dMass dm;
	m_InertiaTensor = m;
	dBodyGetMass(m_Body, &dm);
//	OVRL_memset(&dm.I, 0, sizeof(dm.I));
	dm.I[0] = m.data()[0];
	dm.I[1] = m.data()[4];
	dm.I[2] = m.data()[8];
	dm.I[4] = m.data()[1];
	dm.I[5] = m.data()[5];
	dm.I[6] = m.data()[9];
	dm.I[8] = m.data()[2];
	dm.I[9] = m.data()[6];
	dm.I[10] = m.data()[10];
	dBodySetMass(m_Body, &dm);
}

void CBasicEntity::SetPosition(const C3DVector& dv) 
{
	OVRL_ASSERT(m_Body);
	dBodySetPosition(m_Body, dv.x(), dv.y(), dv.z());
}

void CBasicEntity::SetOrientation(const C3DVector& dv)  
{
	OVRL_ASSERT(m_Body);
	C4x4Matrix m;
	dMatrix3 dm;
	m.set_rotate(dv.x(), dv.y(), dv.z());
	OVRL_memset(&dm, 0, sizeof(dm));
	dm[0] = m.data()[0];
	dm[1] = m.data()[4];
	dm[2] = m.data()[8];
	dm[4] = m.data()[1];
	dm[5] = m.data()[5];
	dm[6] = m.data()[9];
	dm[8] = m.data()[2];
	dm[9] = m.data()[6];
	dm[10] = m.data()[10];
	dBodySetRotation(m_Body, dm);
}
void CBasicEntity::SetOrientationQuaternion(const CQuaternion& q) 
{
	OVRL_ASSERT(m_Body);
	dReal dv[4] = {q.w(),q.x(),q.y(),q.z()};
	dBodySetQuaternion(m_Body, dv);
}
void CBasicEntity::SetOrientationMatrix(const C4x4Matrix& m)  
{
	OVRL_ASSERT(m_Body);
	dMatrix3 dm;
	OVRL_memset(&dm, 0, sizeof(dm));
	dm[0] = m.data()[0];
	dm[1] = m.data()[4];
	dm[2] = m.data()[8];
	dm[4] = m.data()[1];
	dm[5] = m.data()[5];
	dm[6] = m.data()[9];
	dm[8] = m.data()[2];
	dm[9] = m.data()[6];
	dm[10] = m.data()[10];
	dBodySetRotation(m_Body, dm);
}

void CBasicEntity::SetLinearVelocity(const C3DVector& dv)
{
	OVRL_ASSERT(m_Body);
	dBodySetLinearVel(m_Body, dv.x(), dv.y(), dv.z());
}

void CBasicEntity::SetAngularVelocity(const C3DVector& dv)
{
	OVRL_ASSERT(m_Body);
	dBodySetAngularVel(m_Body, dv.x(), dv.y(), dv.z());
}

void CBasicEntity::AddForce(const C3DVector& f, bool relative)
{
	OVRL_ASSERT(m_Body);
	if ( relative )
		dBodyAddRelForce(m_Body, f.x(), f.y(), f.z());
	else
		dBodyAddForce(m_Body, f.x(), f.y(), f.z());
}

void CBasicEntity::AddForceAt(const C3DVector& f, const C3DVector& p, bool relative)
{
	OVRL_ASSERT(m_Body);
	if ( relative )
		dBodyAddRelForceAtPos(m_Body, f.x(), f.y(), f.z(), p.x(),p.y(),p.z());
	else
		dBodyAddForceAtPos(m_Body, f.x(), f.y(), f.z(), p.x(),p.y(),p.z());
}

void CBasicEntity::AddTorque(const C3DVector& f, bool relative)
{
	OVRL_ASSERT(m_Body);
	if ( relative )
		dBodyAddRelTorque(m_Body, f.x(), f.y(), f.z());
	else
		dBodyAddTorque(m_Body, f.x(), f.y(), f.z());
}

void CBasicEntity::SetForce(const C3DVector& f)
{
	OVRL_ASSERT(m_Body);
	dBodySetForce(m_Body, f.x(), f.y(), f.z());
}

void CBasicEntity::SetTorque(const C3DVector& f)
{
	OVRL_ASSERT(m_Body);
	dBodySetTorque(m_Body, f.x(), f.y(), f.z());
}

void CBasicEntity::SetLinearMomentum(const C3DVector&) 
{
	OVRL_ASSERT(m_Body);
}

void CBasicEntity::SetAngularMomentum(const C3DVector&)
{
	OVRL_ASSERT(m_Body);
}

void CBasicEntity::EnablePhysics(bool en)
{
	if ( en )
		dBodyEnable(m_Body);
	else
		dBodyDisable(m_Body);
}

bool CBasicEntity::IsEnabledPhysics() const
{
	return dBodyIsEnabled(m_Body)==1;
}

}