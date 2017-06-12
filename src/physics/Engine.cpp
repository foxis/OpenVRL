#include "physics/engine.h"
#include "physics/body.h"
#include "physics/geoms.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define MAX_CONTACTS 64

void peNearCallback (void *data, dGeomID o1, dGeomID o2)
{
	IBasicBody 
		*b1 = reinterpret_cast<IBasicBody*>(dGeomGetData(o1)), 
		*b2 = reinterpret_cast<IBasicBody*>(dGeomGetData(o2));

	if (dGeomIsSpace (o1) || dGeomIsSpace (o2)) 
	{
		// colliding a space with something
		dSpaceCollide2 (o1,o2,data,&peNearCallback);

		// collide all geoms internal to the space(s)
		if ( dGeomIsSpace (o1) && ( b1==0 || (b1->GetTypeBits()&OVRL_BT_CANRECURSE) ) ) dSpaceCollide ((dSpaceID)o1,data,&peNearCallback);
		if ( dGeomIsSpace (o2) && ( b2==0 || (b2->GetTypeBits()&OVRL_BT_CANRECURSE) ) ) dSpaceCollide ((dSpaceID)o2,data,&peNearCallback);
	}
	else 
	{
		CPhysicsEngine* engine = (CPhysicsEngine*)data;
		OVRL_ASSERT(engine);
		OVRL_ASSERT(b1 && b2);
		
		if ( (b1->GetTypeBits()&OVRL_BT_MOVEABLE) || (b2->GetTypeBits()&OVRL_BT_MOVEABLE))
			engine->collidedGeoms(b1->GetGeom(),b2->GetGeom());
	}
}
CPhysicsEngine::CPhysicsEngine()
{
	m_Bodies = new std::list<IBasicBody*>;
	m_Groups = new std::list<IBasicJointGroup*>;

	m_Engine = 0;
	m_Space = 0;
	m_ContactGroup = 0;

	m_Engine = CreateEngine();	// create root ODE World
	m_Space = CreateSpace();	// create root ODE collision space
	m_ContactGroup = CreateJointGroup();
}

CPhysicsEngine::~CPhysicsEngine()
{
	Release();
	delete m_Bodies;
	delete m_Groups;
	OVRL_ASSERT(m_Engine);
	OVRL_ASSERT(m_Space);
	OVRL_ASSERT(m_ContactGroup);
	dWorldDestroy(m_Engine);
	m_Space->Release();
	delete m_Space;
	dJointGroupDestroy(m_ContactGroup);
	m_Engine = 0;
	m_Space = 0;
	m_ContactGroup = 0;
}

IBasicSpace* CPhysicsEngine::CreateSpace()
{
	IBasicSpace* bs;
	bs = new CSimpleSpace();
	bs->Create();
	return bs;
}

dWorldID CPhysicsEngine::CreateEngine()
{
	return dWorldCreate();
}

dJointGroupID CPhysicsEngine::CreateJointGroup()
{
	return dJointGroupCreate(0);
}



void CPhysicsEngine::Add(IBasicBody* b)
{
	OVRL_ASSERT(b);
	OVRL_ASSERT(m_Bodies);

	b->onInsert(this);
	m_Bodies->insert(m_Bodies->end(), b);
}

void CPhysicsEngine::Remove(IBasicBody* b)
{
	OVRL_ASSERT(b);
	OVRL_ASSERT(m_Bodies);

	b->onRemove(this);
	m_Bodies->remove(b);
}

void CPhysicsEngine::Release()
{
	std::list<IBasicJointGroup*>::iterator I;
	OVRL_ASSERT(m_Bodies);
	OVRL_ASSERT(m_Groups);

	I = m_Groups->begin();
	while ( I!=m_Groups->end() )
	{
		OVRL_ASSERT(*I);
		(*I)->Release();
		delete *I;
		I++;
	}

	m_Groups->clear();
	m_Bodies->clear();
	// do ode cleanup
	dJointGroupEmpty(m_ContactGroup);
}

void CPhysicsEngine::Add(IBasicJointGroup* j)
{
	OVRL_ASSERT(j);
	OVRL_ASSERT(m_Groups);

	j->onInsert(this);
	m_Groups->insert(m_Groups->end(), j);
}
void CPhysicsEngine::Remove(IBasicJointGroup* j)
{
	OVRL_ASSERT(j);
	OVRL_ASSERT(m_Groups);

	j->onRemove(this);
	m_Groups->remove(j);
}
void CPhysicsEngine::Delete(IBasicJointGroup* j)
{
	OVRL_ASSERT(j);
	OVRL_ASSERT(m_Groups);

	j->onRemove(this);
	m_Groups->remove(j);
	j->Release();
	delete j;
}

int CPhysicsEngine::Update(real time_step)
{
	std::list<IBasicBody*>::iterator I;
	std::list<IBasicJointGroup*>::iterator J;
	OVRL_ASSERT(m_Bodies);
	OVRL_ASSERT(m_Space);
	OVRL_ASSERT(m_Engine);

	J = m_Groups->begin();
	while ( J!=m_Groups->end() )
	{
		OVRL_ASSERT(*J);
		(*J)->Update();
		J++;
	}

	dSpaceCollide(m_Space->GetSpace(), this, peNearCallback);	// @todo: manage multiple collision spaces
//	dWorldQuickStep(m_Engine, time_step);
	dWorldStepFast1(m_Engine, time_step, 40);
	dJointGroupEmpty(m_ContactGroup);

	I = m_Bodies->begin();
	while ( I!=m_Bodies->end() )
	{
		OVRL_ASSERT(*I);
		(*I)->UpdatePhysics(time_step);
		I++;
	}

	return 0;
}

void CPhysicsEngine::Prepare()
{
	std::list<IBasicBody*>::iterator I;
	std::list<IBasicJointGroup*>::iterator J;
	OVRL_ASSERT(m_Engine);
	OVRL_ASSERT(m_Space);
	OVRL_ASSERT(m_ContactGroup);

	dWorldSetGravity (m_Engine, 0, -9.81, 0);
//	dWorldSetERP (m_Engine, .4);
//	dWorldSetCFM (m_Engine, .08);

	m_Space->Prepare();

	I = m_Bodies->begin();
	while ( I!=m_Bodies->end() )
	{
		OVRL_ASSERT(*I);
		(*I)->PreparePhysics();
		I++;
	}
	J = m_Groups->begin();
	while ( J!=m_Groups->end() )
	{
		OVRL_ASSERT(*J);
		(*J)->Prepare();
		J++;
	}
}

void CPhysicsEngine::collidedGeoms(IBasicGeom*g1, IBasicGeom*g2)
{
	OVRL_ASSERT(g1 && g2);
	IBasicBody *b1, *b2;
	dContact c[MAX_CONTACTS];
	ushort num;

	b1 = g1->GetBody();
	b2 = g2->GetBody();
	OVRL_ASSERT(b1 && b2);

	num = dCollide(g1->GetGeom(),g2->GetGeom(),(ushort)MAX_CONTACTS,&c[0].geom,sizeof(dContact));

	if ( num>0 )
	{
		b1->onCollide(*b1,*b2);
		b2->onCollide(*b2,*b1);

		// manage contact points
		ushort i;

		for ( i=0;i<num;i++ )
		{
			c[i].surface.mode = dContactBounce | dContactSlip1 | dContactSlip2 | dContactApprox1;// | dContactSoftERP | dContactSoftCFM;
			c[i].surface.mu = dInfinity;
			c[i].surface.slip1 = .001;
			c[i].surface.slip2 = .001;
			c[i].surface.bounce = 0;
//			c[i].surface.soft_cfm = 0.000000803; 
//			c[i].surface.soft_erp = 0.00005; 

			dBodyID _b1=0, _b2=0;
			const ulong 
				tb1 = b1->GetTypeBits(),
				tb2 = b2->GetTypeBits();

			if ( tb1&OVRL_BT_MOVEABLE )
				_b1 = b1->GetBody();
			if ( tb2&OVRL_BT_MOVEABLE )
				_b2 = b2->GetBody();

//			if ( !(tb1&OVRL_BT_CANAFFECTOTHERS) )
//				_b2 = 0;
//			if ( !(tb2&OVRL_BT_CANAFFECTOTHERS) )
//				_b1 = 0;

			if ( _b1 || _b2 )
			{
				dJointID j = dJointCreateContact(m_Engine, m_ContactGroup, c+i);
				dJointAttach(j, _b1, _b2);
			}
		}
	}
}

};