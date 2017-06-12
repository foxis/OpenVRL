/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/world/basicentity.h,v $
 * $Implementation: ~/src/engine/objroot.cc $
 * $Revision: 1.6 $
 * $Author: foxis $
 * $Date: 2005/05/16 12:36:46 $
 * $Description: $
 *
 * $Log: basicentity.h,v $
 * Revision 1.6  2005/05/16 12:36:46  foxis
 * several CString & xFactory bugfixes
 *
 * Revision 1.5  2005/03/09 12:24:08  foxis
 * . fixed memory leaks
 * . fixed OVRL_ASSERT issue in release mode
 *   [still to fix: TPL_ASSERT, now - just a hack]
 *
 * Revision 1.4  2005/02/23 12:30:57  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.3  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 * Revision 1.2  2005/02/02 20:05:03  foxis
 * Basic ODE support - seems to work ok
 * basic CBody - seems to work
 * basic system overall - seems to work :)
 *
 * minor bugfixes, and changes in body managment code
 *
 * Revision 1.1.1.1  2005/02/02 15:39:22  foxis
 * sources import
 *
 * Revision 0.3  20011222  12:58:40 FoxiE
 * Pradejau igyvendint viena ideja; pradzia: kiekvienas mesh objektas
 * grazina pipeline savo geometrija, o ne pipeline istraukia.
 * geometrijos struktura: {RAW mesh data; material-list; textures-list;}
 *
 * Revision 0.2  20010814  10:12:07 FoxiE
 * Truputi modifikavau push_matrix fun-ja. Tuo tarpu pakeiciau ir kitas,
 * t.y. rotate, translate, scale matricas.
 *
 * Revision 0.1  20010409  11:52:40 FoxiE
 * Pradejau rasyti logus :)
 *
 */


#if !defined(__ovrl_BASICENTITY_HPP)
#define __ovrl_BASICENTITY_HPP

#include "common/all.h"
#include "common/classes.h"
#include "world/basicworldentity.h"
#include "world/worldsector.h"
#include "pipeline/basicmesh.h"
#include "physics/body.h"

namespace openvrl {

class OVRLIBAPI IBasicEntity : public IBasicWorldEntity, public IBasicBody
{
public:
	virtual ~IBasicEntity() = 0 {}

	virtual ulong onInsert(IBasicWorldEntity* e) = 0;
	virtual ulong onRemove(IBasicWorldEntity* e) = 0;

	virtual IBasicPipelineEntity* GetPipelineEntity(ulong caps) = 0;
};


//
//
//
class IWorldSector;
class IWorld;

class OVRLIBAPI CBasicEntity : public IBasicEntity
{
protected:
	IBasicWorldEntity* m_Sector;
	CPhysicsEngine*		m_Physics;
	IPipeline*			m_Pipeline;
	IWorld*				m_World;
	IBasicGeom* m_Geom;
	dBodyID m_Body;

	real m_Mass;
	C3DVector m_MassCenter;
	C4x4Matrix m_InertiaTensor;

	ulong m_TypeBits;

public:
	virtual void SetGeom(IBasicGeom* g);

	virtual dBodyID GetBody() { return m_Body; }
	virtual IBasicGeom* GetGeom() { return m_Geom; }
	virtual CPhysicsEngine* GetPhysicsEngine() { return m_Physics; }

protected:
	CBasicEntity();

public:
	virtual ~CBasicEntity();


	//
	// own members
	//
	virtual IWorldSector* GetSector() const { return (IWorldSector*)m_Sector; }

	//
	// IBasicEntity
	//
	virtual ulong onInsert(IBasicWorldEntity* e);
	virtual ulong onRemove(IBasicWorldEntity* e);

	//
	// IBasicWorldEntity
	//
	virtual void Prepare();
	virtual void Release();
	virtual int Update(real time_step);

	virtual IBasicWorldEntity* GetBase() { return m_Sector; };
	virtual IPipeline*	GetPipeline() { return m_Pipeline; } 
	virtual IWorld*	GetWorld() { return m_World; }

	virtual bool canInsert() const	{	return true;	}
	virtual bool canSort() const	{	return true;	}
	virtual bool canRender() const	{	return true;	}
	virtual bool canCalculate() const	{	return true;	}

	//
	// IBasicBody
	//
	virtual dBodyID GetBody() const { return m_Body; }
	virtual IBasicGeom* GetGeom() const { return m_Geom; }
	virtual CPhysicsEngine* GetPhysicsEngine() const { return m_Physics; }

	virtual ulong GetTypeBits() const { return m_TypeBits; }
	virtual void SetTypeBits(ulong tb)	{ m_TypeBits = tb; }

	virtual real GetMass() const;
	virtual C4x4Matrix GetInertiaTensor() const;
	virtual C3DVector GetMassCenter() const;
	virtual C3DVector GetPosition() const;
	virtual C3DVector GetOrientation() const;
	virtual CQuaternion GetOrientationQuaternion() const;
	virtual C4x4Matrix GetOrientationMatrix() const;
	virtual C3DVector GetLinearVelocity() const;
	virtual C3DVector GetAngularVelocity() const;
	virtual C3DVector GetForce() const;
	virtual C3DVector GetTorque() const;
	virtual C3DVector GetLinearMomentum() const ;
	virtual C3DVector GetAngularMomentum() const ;

	virtual void SetMass(real);
	virtual void SetInertiaTensor(const C4x4Matrix&);
	virtual void SetMassCenter(const C3DVector&);
	virtual void SetPosition(const C3DVector&);
	virtual void SetOrientation(const C3DVector&);
	virtual void SetOrientationQuaternion(const CQuaternion&);
	virtual void SetOrientationMatrix(const C4x4Matrix&);
	virtual void SetLinearVelocity(const C3DVector&);
	virtual void SetAngularVelocity(const C3DVector&);
	virtual void AddForce(const C3DVector&, bool relative=false);
	virtual void AddForceAt(const C3DVector&, const C3DVector&, bool relative=false);
	virtual void AddTorque(const C3DVector&, bool relative=false);
	virtual void SetForce(const C3DVector&);
	virtual void SetTorque(const C3DVector&);
	virtual void SetLinearMomentum(const C3DVector&);
	virtual void SetAngularMomentum(const C3DVector&);

	virtual ulong onInsert(CPhysicsEngine* e);
	virtual ulong onRemove(CPhysicsEngine* e);

	virtual void EnablePhysics(bool en);
	virtual bool IsEnabledPhysics() const;

	virtual void onCollide(IBasicBody& me, IBasicBody& other) { }
	virtual void PreparePhysics();
	virtual void UpdatePhysics(real time_step) {}
};

};

#endif 
