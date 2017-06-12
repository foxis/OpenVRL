/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/world/world.h,v $
 * $Implementation: ~/src/engine/world.hpp $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:57 $
 * $Description: World class $
 *
 * $Log: world.h,v $
 * Revision 1.3  2005/02/23 12:30:57  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.2  2005/02/02 20:05:03  foxis
 * Basic ODE support - seems to work ok
 * basic CBody - seems to work
 * basic system overall - seems to work :)
 *
 * minor bugfixes, and changes in body managment code
 *
 * Revision 1.1.1.1  2005/02/02 15:39:23  foxis
 * sources import
 *
 * Revision 0.3  20010411  :: FoxiE
 * Idejau texture_list, material_list ir object_list
 * Anksciau buvo taip, jog kiekvienas _3DObject laike _visa_ objekta
 * su visom jo property. Dabar gi, kiekvienas _3DObject laiko tik
 * transformacijos matricas bei material_index_list bei objekto
 * indexa object_index...
 *
 * Revision 0.2  20010409  12:10:33 FoxiE
 * Ispletimas .cpp pakeistas i .cc
 *
 * Revision 0.1  20010409  11:52:40 FoxiE
 * Pradejau rasyti logus :)
 *
 */


#if !defined(__ovrl_OVRLWORLD_HPP)
#define __ovrl_OVRLWORLD_HPP

#include <list>

#include "common/all.h"
#include "system/ovrlsystem.h"
#include "world/worldsector.h"
#include "world/BasicEntity.h"

namespace openvrl {

class OVRLIBAPI CSystem;

//
// IWorld
//
class IWorld : public IBasicWorldEntity
{
public:
	virtual ~IWorld() = 0 {}

	virtual void AddSector(IWorldSector* s) = 0;
	virtual void RemoveSector(IWorldSector* s) = 0;
	virtual void DeleteSector(IWorldSector* s) = 0;

	virtual std::list<IWorldSector*>* GetSectorList() = 0;
};

//
// world class 
//
class OVRLIBAPI CWorld : public IWorld
{
	CWorld();

protected:
	CSystem*	m_System;
	std::list<IWorldSector*>*	m_Sectors;

public:
	CWorld(CSystem* system);
	virtual ~CWorld();

	//
	// own members
	//
	virtual int Load(const CString& path);
	virtual int Save(const CString& path);

	//
	// IWorld members
	//
	virtual void AddSector(IWorldSector* s);
	virtual void RemoveSector(IWorldSector* s);
	virtual void DeleteSector(IWorldSector* s);

	virtual std::list<IWorldSector*>* GetSectorList() { return m_Sectors; } 

	//
	// IBasicWorldEntity
	//
	virtual IBasicWorldEntity* GetBase() { return 0; }
	virtual IPipeline*	GetPipeline() ;
	virtual IWorld*	GetWorld() { return this; }

	virtual int Update(real time_step);
	virtual void Prepare();
	
	virtual void Release();

	virtual ulong what() const { return ORW_WORLD; };
	virtual CHAR* get_name() const { return "World class"; }
	virtual ulong caps() const { return 0; }

	virtual bool canInsert() const	{	return false;	}
	virtual bool canSort() const	{	return false;	}
	virtual bool canRender() const	{	return false;	}
	virtual bool canCalculate() const	{	return false;	}
};

};

#endif // if !defined(__ovrl_OVRLWORLD_HPP)
