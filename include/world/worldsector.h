/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/world/worldsector.h,v $
 * $Implementation: $
 * $Revision: 1.11 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:57 $
 * $Description:  $
 *
 * $Log: worldsector.h,v $
 * Revision 1.11  2005/02/23 12:30:57  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.10  2005/02/11 11:02:51  foxis
 * fixed many bugs
 * added joints
 *
 * Revision 1.9  2005/02/07 19:06:56  foxis
 * minor changes
 *
 * Revision 1.8  2005/02/06 10:06:02  foxis
 * Is/Set Moved renamed to more general Get/Set TypeBits
 * removed old sources
 *
 * Revision 1.7  2005/02/04 21:16:46  foxis
 * no message
 *
 * Revision 1.6  2005/02/04 20:33:19  foxis
 * physics + collision now at last works!
 * left implementing: IBasicJoint and CBasicODEJoint and so on
 * incapsulating geoms. so that one body can have many geoms.
 *
 * Revision 1.5  2005/02/03 17:52:55  foxis
 * made IBasicGeom and it's derivatives to work.
 * now physics engine recognizes collisions.
 *
 * however geom management should be rethought.
 *
 * Revision 1.4  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(__ovrl_WORLDSECTOR_H_INCLUDED)
#define __ovrl_WORLDSECTOR_H_INCLUDED

#include <list>

#include "world/basicworldentity.h"
#include "world/basicentity.h"
#include "physics/engine.h"

namespace openvrl {

//
//
//
class OVRLIBAPI IWorldSector : public IBasicWorldEntity
{
public:
	virtual ~IWorldSector() = 0 {}

	virtual CPhysicsEngine* GetPhysicsEngine() =0;

	virtual ulong onInsert(IBasicWorldEntity* e) = 0;
	virtual ulong onRemove(IBasicWorldEntity* e) = 0;

	virtual void Add(IBasicEntity* e) = 0;
	virtual void Remove(IBasicEntity* e) = 0;
	virtual void Delete(IBasicEntity* e) = 0;

	virtual std::list<IBasicEntity*>* GetEntityList() = 0;
};

//
//
//
class OVRLIBAPI CWorldSector : public IWorldSector, public CPhysicsEngine
{
private:
	std::list<IBasicEntity*>*	m_Entities;
	IBasicWorldEntity* m_Base;
	C4x4Matrix m_TransformMatrix;
	C4x4Matrix m_WorldTransformMatrix;

public:
	virtual CPhysicsEngine* GetPhysicsEngine() { return this; }

public:
	CWorldSector();
	virtual ~CWorldSector();

	//
	// IWorldSector
	//
	void Add(IBasicEntity* e);
	void Remove(IBasicEntity* e);
	void Delete(IBasicEntity* e);

	virtual std::list<IBasicEntity*>* GetEntityList() { return m_Entities; } 

	//
	// IWorldSector
	//
	virtual ulong onInsert(IBasicWorldEntity* e);
	virtual ulong onRemove(IBasicWorldEntity* e);

	//
	// IBasicWorldEntity
	//
	virtual ulong what() const { return ORW_WORLD_SECTOR; }
	virtual CHAR* get_name() const { return "World Sector"; }
	virtual ulong caps() const { return 0; }

	virtual void Prepare();
	virtual void Release();
	virtual int Update(real time_step);

	virtual IBasicWorldEntity* GetBase() { return m_Base; }
	virtual IPipeline* GetPipeline() { return m_Base->GetPipeline(); }
	virtual IWorld*	GetWorld() { return m_Base->GetWorld(); }
};

};

#endif
