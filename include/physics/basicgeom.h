/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/physics/basicgeom.h,v $
 * $Implementation: $
 * $Revision: 1.4 $
 * $Author: foxis $
 * $Date: 2005/02/11 11:02:50 $
 * $Description:  $
 *
 * $Log: basicgeom.h,v $
 * Revision 1.4  2005/02/11 11:02:50  foxis
 * fixed many bugs
 * added joints
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

#if !defined(__ovrl__BASICGEOM_H_DEFINED)
#define __ovrl__BASICGEOM_H_DEFINED


#include "common/all.h"
#include "physics/engine.h"
#include "physics/body.h"
#include <ode/ode.h>

namespace openvrl
{

class OVRLIBAPI IBasicBody;
class OVRLIBAPI IBasicSpace;
//
//  basic geometry interface
//
class OVRLIBAPI IBasicGeom
{
public:
	virtual dGeomID GetGeom() = 0;	// can only change childs of this class
	virtual IBasicBody* GetBody() = 0;

public:
	virtual ~IBasicGeom() =  0 {}

	virtual dGeomID GetGeom() const = 0;
	virtual IBasicBody* GetBody() const = 0;

	virtual IBasicSpace* GetParent() const = 0;
	virtual IBasicSpace* GetParent() = 0;

	virtual void onInsert(IBasicSpace*) = 0;
	virtual void onRemove(IBasicSpace*) = 0;

	virtual void Create() = 0;
	virtual void Create(IBasicBody*) = 0;
	virtual void Release() = 0;
	virtual void Attach(IBasicBody*) = 0;
	virtual void Prepare() = 0;
	virtual void Update() = 0;

	virtual bool IsPlaceable() const = 0;
	virtual void Enable(bool en) = 0;
	virtual bool IsEnabled() const = 0;

	virtual ulong GetCategoryBits() const = 0;
	virtual ulong GetCollideBits() const = 0;
	virtual C3DVector GetPosition() const = 0;
	virtual C3DVector GetOrientation() const = 0;
	virtual C4x4Matrix GetOrientationMatrix() const = 0;
	virtual const void* GetUserData() const = 0;
	virtual C3DBoundingVolume GetBoudingVolume() const = 0;

	virtual void SetCategoryBits(ulong) = 0;
	virtual void SetCollideBits(ulong) = 0;
	virtual void SetPosition(const C3DVector&) = 0;
	virtual void SetOrientation(const C3DVector&) = 0;
	virtual void SetOrientationMatrix(const C4x4Matrix&) = 0;
	virtual void SetUserData(void*) = 0;
};

//
// basic geometry space interface
//
class OVRLIBAPI IBasicSpace : public IBasicGeom
{
protected:
	virtual void SetSpace(dSpaceID) = 0;

public:
	virtual ~IBasicSpace() = 0 {}

	virtual void Add(IBasicGeom*) = 0;
	virtual void Remove(IBasicGeom*) = 0;
	virtual void Clear() = 0;

	virtual dSpaceID GetSpace() const = 0;
	virtual dSpaceID GetSpace() = 0;
};

};

#endif