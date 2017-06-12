/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/physics/geoms.h,v $
 * $Implementation: $
 * $Revision: 1.7 $
 * $Author: foxis $
 * $Date: 2005/03/09 12:24:08 $
 * $Description:  $
 *
 * $Log: geoms.h,v $
 * Revision 1.7  2005/03/09 12:24:08  foxis
 * . fixed memory leaks
 * . fixed OVRL_ASSERT issue in release mode
 *   [still to fix: TPL_ASSERT, now - just a hack]
 *
 * Revision 1.6  2005/02/18 09:24:19  foxis
 * added cylinder geom,
 * some misc changes
 *
 * Revision 1.5  2005/02/11 11:02:50  foxis
 * fixed many bugs
 * added joints
 *
 * Revision 1.4  2005/02/05 13:10:05  foxis
 * added CEncapsulatedGeom
 *
 * Revision 1.3  2005/02/04 20:33:19  foxis
 * physics + collision now at last works!
 * left implementing: IBasicJoint and CBasicODEJoint and so on
 * incapsulating geoms. so that one body can have many geoms.
 *
 * Revision 1.2  2005/02/03 17:52:55  foxis
 * made IBasicGeom and it's derivatives to work.
 * now physics engine recognizes collisions.
 *
 * however geom management should be rethought.
 *
 * Revision 1.1  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(__ovrl__GEOMS_H_DEFINED)
#define __ovrl__GEOMS_H_DEFINED

#include "physics/body.h"
#include "physics/basicgeom.h"


namespace openvrl
{

//
// Basic ODE Geom wrapper
//
class OVRLIBAPI CBasicODEGeom : public IBasicGeom
{
protected:
	dGeomID	m_Geom;
	IBasicBody* m_Body;
	IBasicSpace* m_Parent;

public:
	virtual dGeomID GetGeom() { return m_Geom; }
	virtual IBasicBody* GetBody() { return m_Body; }

protected:
	virtual void SetGeom(dGeomID);

	virtual IBasicSpace* GetParent() const { return m_Parent; }
	virtual IBasicSpace* GetParent() { return m_Parent; }

public:
	CBasicODEGeom();
	virtual ~CBasicODEGeom();

	//
	// IBasicGeom
	//
	virtual dGeomID GetGeom() const { return m_Geom; }
	virtual IBasicBody* GetBody() const { return m_Body; }

	virtual void onInsert(IBasicSpace*);
	virtual void onRemove(IBasicSpace*);

	virtual void Create(IBasicBody*);
	virtual void Create() {}
	virtual void Release();
	virtual void Attach(IBasicBody*);
	virtual void Update();
	virtual void Prepare();

	virtual bool IsPlaceable() const;
	virtual void Enable(bool en);
	virtual bool IsEnabled() const;

	virtual C3DVector GetPosition() const;
	virtual C3DVector GetOrientation() const;
	virtual C4x4Matrix GetOrientationMatrix() const;
	virtual const void* GetUserData() const;
	virtual C3DBoundingVolume GetBoudingVolume() const;

	virtual void SetPosition(const C3DVector&);
	virtual void SetOrientation(const C3DVector&);
	virtual void SetOrientationMatrix(const C4x4Matrix&);
	virtual void SetUserData(void*);

	virtual ulong GetCategoryBits() const;
	virtual ulong GetCollideBits() const;

	virtual void SetCategoryBits(ulong);
	virtual void SetCollideBits(ulong);
};

//
// Basic ODE Geom Space wrapper
//
class OVRLIBAPI CBasicODESpace : public IBasicSpace
{
	dSpaceID	m_Space;
	IBasicBody* m_Body;
	IBasicSpace* m_Parent;
	std::list<IBasicGeom*>* m_Geoms;

public:
	virtual dGeomID GetGeom() { return (dGeomID)m_Space; }
	virtual IBasicBody* GetBody() { return m_Body; }
	virtual dSpaceID GetSpace() { return m_Space; }

	virtual IBasicSpace* GetParent() const { return m_Parent; }
	virtual IBasicSpace* GetParent() { return m_Parent; }

protected:
	virtual void SetGeom(dGeomID);
	virtual void SetSpace(dSpaceID);

public:
	CBasicODESpace();
	virtual ~CBasicODESpace();

	//
	// IBasicSpace
	//
	virtual void Add(IBasicGeom*);
	virtual void Remove(IBasicGeom*);

	virtual void Clear();

	//
	// IBasicGeom
	//
	virtual dGeomID GetGeom() const { return (dGeomID)m_Space; }
	virtual dSpaceID GetSpace() const { return m_Space; }
	virtual IBasicBody* GetBody() const { return m_Body; }

	virtual void onInsert(IBasicSpace*);
	virtual void onRemove(IBasicSpace*);

	virtual void Create(IBasicBody*);
	virtual void Create() {}
	virtual void Release();
	virtual void Attach(IBasicBody*);
	virtual void Update();
	virtual void Prepare();

	virtual bool IsPlaceable() const;
	virtual void Enable(bool en);
	virtual bool IsEnabled() const;

	virtual C3DVector GetPosition() const;
	virtual C3DVector GetOrientation() const;
	virtual C4x4Matrix GetOrientationMatrix() const;
	virtual const void* GetUserData() const;
	virtual C3DBoundingVolume GetBoudingVolume() const;

	virtual void SetPosition(const C3DVector&);
	virtual void SetOrientation(const C3DVector&);
	virtual void SetOrientationMatrix(const C4x4Matrix&);
	virtual void SetUserData(void*);

	virtual ulong GetCategoryBits() const;
	virtual ulong GetCollideBits() const;

	virtual void SetCategoryBits(ulong);
	virtual void SetCollideBits(ulong);
};

///////////////////////////////////////////////////////////////////////////////

//
// Simple space
//
class OVRLIBAPI CSimpleSpace : public CBasicODESpace
{
public:
	CSimpleSpace();
	virtual ~CSimpleSpace();

	virtual void Create();

	virtual void Update();
};

//
// Hash table space
//
class OVRLIBAPI CHashSpace : public CBasicODESpace
{
public:
	CHashSpace();
	virtual ~CHashSpace();

	virtual void Create();

	virtual void Update();
};

//
// Quad Tree space
//
//class OVRLIBAPI CQTSpace : public CBasicODESpace
//{
//public:
//	CQTSpace();
//	virtual ~CQTSpace();
//
//	virtual void Create();
//
//	virtual void Update();
//};

//////////////////////////////////////////////////////////////////////////////

//
// Encapsulated geometry
//

class OVRLIBAPI CEncapsulatedGeom : public CBasicODEGeom
{
	IBasicGeom* m_Encapsulated;

public:
	CEncapsulatedGeom();
	virtual ~CEncapsulatedGeom();

	virtual void Create();
	virtual void Release();
	virtual void Attach(IBasicBody*);

	virtual IBasicGeom* GetEncasulated() const { return m_Encapsulated; }
	virtual IBasicGeom* GetEncasulated() { return m_Encapsulated; }

	virtual void Set(IBasicGeom*);
};

//////////////////////////////////////////////////////////////////////////////

//
// Sphere geometry
//
class OVRLIBAPI CSphereGeom : public CBasicODEGeom 
{
public:
	CSphereGeom();
	virtual ~CSphereGeom();

	virtual void Create();

	virtual real GetRadius() const;
	virtual void SetRadius(real);
	virtual real GetDepth(const C3DVector&) const;

	virtual void Update();
};

//
// Box geometry
//
class OVRLIBAPI CBoxGeom : public CBasicODEGeom 
{
public:
	CBoxGeom();
	virtual ~CBoxGeom();

	virtual void Create();

	virtual C3DVector GetLengths() const;
	virtual void SetLengths(const C3DVector&);
	virtual real GetDepth(const C3DVector&) const;

	virtual void Update();
};

//
// Capped Cylinder geometry (alligned along Z axis)
//
class OVRLIBAPI CCappedCylinderGeom : public CBasicODEGeom 
{
public:
	CCappedCylinderGeom();
	virtual ~CCappedCylinderGeom();

	virtual void Create();

	virtual real GetLength() const;
	virtual real GetCapRadius() const;
	virtual real GetDepth(const C3DVector&) const;
	virtual void SetLength(real);
	virtual void SetCapRadius(real);

	virtual void Update();
};

//
// Normal Cylinder geometry (alligned along Y axis)
//
class OVRLIBAPI CCylinderGeom : public CBasicODEGeom 
{
public:
	CCylinderGeom();
	virtual ~CCylinderGeom();

	virtual void Create();

	virtual real GetLength() const;
	virtual real GetRadius() const;
	virtual real GetDepth(const C3DVector&) const;
	virtual void SetLength(real);
	virtual void SetRadius(real);

	virtual void Update();
};

//
// Plane geometry
//
class OVRLIBAPI CPlaneGeom : public CBasicODEGeom 
{
public:
	CPlaneGeom();
	virtual ~CPlaneGeom();

	virtual void Create();
	virtual void SetParams(const C3DVector&, real);
	virtual real GetDepth(const C3DVector&);

	virtual void Attach(IBasicBody*);

	virtual void Update();
};

//
// Triangle Mesh geometry
//
class OVRLIBAPI CTriangleMeshGeom : public CBasicODEGeom 
{
public:
	CTriangleMeshGeom();
	virtual ~CTriangleMeshGeom();

	virtual void Create();

	virtual void Update();
};

};

#endif