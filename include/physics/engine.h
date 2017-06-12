/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/physics/engine.h,v $
 * $Implementation: ~/src/ $
 * $Revision: 1.5 $
 * $Author: foxis $
 * $Date: 2005/02/11 11:02:50 $
 * $Description:  $
 *
 * $Log: engine.h,v $
 * Revision 1.5  2005/02/11 11:02:50  foxis
 * fixed many bugs
 * added joints
 *
 * Revision 1.4  2005/02/04 20:33:19  foxis
 * physics + collision now at last works!
 * left implementing: IBasicJoint and CBasicODEJoint and so on
 * incapsulating geoms. so that one body can have many geoms.
 *
 * Revision 1.3  2005/02/03 17:52:55  foxis
 * made IBasicGeom and it's derivatives to work.
 * now physics engine recognizes collisions.
 *
 * however geom management should be rethought.
 *
 * Revision 1.2  2005/02/02 20:03:45  foxis
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

#if !defined(AFX_PHYSICSENGINE_H__A528A041_A3CB_11D6_8083_F90B0B38421A__INCLUDED_)
#define AFX_PHYSICSENGINE_H__A528A041_A3CB_11D6_8083_F90B0B38421A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common/all.h"
#include "common/constants.h"
#include "physics/body.h"
#include "physics/basicjoint.h"
#include "physics/engine.h"
#include <ode/ode.h>

#include <list>

namespace openvrl {

class IBasicBody;
class IBasicGeom;
class IBasicSpace;
class IBasicJoint;

class OVRLIBAPI CPhysicsEngine 
{
	std::list<IBasicBody*>*	m_Bodies;
	std::list<IBasicJointGroup*>*	m_Groups;
	IBasicSpace*	m_Space;

	dWorldID	m_Engine;
	dJointGroupID m_ContactGroup;

public:
	CPhysicsEngine();
	virtual ~CPhysicsEngine();

	void Add(IBasicBody* b);
	void Add(IBasicJointGroup* j);

	void Remove(IBasicBody* b);
	void Remove(IBasicJointGroup* j);

	void Delete(IBasicJointGroup* j);

	virtual IBasicSpace* CreateSpace();
	virtual dWorldID CreateEngine();
	virtual dJointGroupID CreateJointGroup();


	virtual int Update(real time_step);	
	virtual void Release();
	virtual void Prepare();

	dWorldID GetEngine() { return m_Engine; }
	IBasicSpace* GetSpace() { return m_Space; }	

	virtual void collidedGeoms(IBasicGeom *g1, IBasicGeom *g2);
};

};

#endif // !defined(AFX_PHYSICSENGINE_H__A528A041_A3CB_11D6_8083_F90B0B38421A__INCLUDED_)
