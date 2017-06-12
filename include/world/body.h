/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/world/body.h,v $
 * $Implementation: ~/src/engine/objroot.cc $
 * $Revision: 1.13 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description: objRoot class $
 *
 * $Log: body.h,v $
 * Revision 1.13  2005/03/04 13:21:16  foxis
 * no message
 *
 * Revision 1.12  2005/03/01 18:21:16  foxis
 * Pipeline: shadows now working more or less. need to handle special cases.
 * C4x4Matrix: added inverse method + others
 *
 * Revision 1.11  2005/02/23 12:30:57  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.10  2005/02/11 11:02:50  foxis
 * fixed many bugs
 * added joints
 *
 * Revision 1.9  2005/02/07 19:06:55  foxis
 * minor changes
 *
 * Revision 1.8  2005/02/06 10:06:02  foxis
 * Is/Set Moved renamed to more general Get/Set TypeBits
 * removed old sources
 *
 * Revision 1.7  2005/02/04 21:16:45  foxis
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
 * Revision 1.3  2005/02/02 20:59:31  foxis
 * misc, dont remember :)
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


#if !defined(__ovrl_BODY_HPP)
#define __ovrl_BODY_HPP

#include "world/basicentity.h"
#include "world/worldsector.h"
#include "physics/engine.h"

namespace openvrl {

//
// ODE 
//12.4. How can an immovable body be created?
//In other words, how can you create a body that doesn't move, but that interacts with other bodies? 
//The answer is to create a geom only, without the corresponding rigid body object. The geom is 
//associated with a rigid body ID of zero. Then in the contact callback when you detect a collision 
//between two geoms with a nonzero body ID and a zero body ID, you can simply pass those two IDs to 
//the dJointAttach function as normal. This will create a contact between the rigid body and the 
//static environment.

class OVRLIBAPI CBody : public CBasicEntity, public IBasicMesh
{
	CxfMesh	*m_Mesh;
	C4x4Matrix m_TransformMatrix;		//	local
	C4x4Matrix m_WorldTransformMatrix;	// global - calculated on request
	C4x4Matrix m_PrecalculatedMatrix;

public:
	CBody();
	virtual ~CBody();

	virtual void Release();

	virtual IBasicPipelineEntity* GetPipelineEntity(ulong caps) { return (caps&OVRL_CAPS_MESH)?this:0; }

	//
	// IBasicWorldEntity
	//
	virtual ulong what() const	{ return ORW_BODY; }
	virtual CHAR* get_name() const { return "Static mesh body"; }
	virtual ulong caps() const	{ return OVRL_CAPS_MESH; }

	//
	// IBasicMesh
	//
	virtual C4x4Matrix& GetTransformMatrix();
	virtual C4x4Matrix& GetWorldTransformMatrix();
	virtual void PrecalculateWorldMatrix();
	virtual C4x4Matrix& GetPrecalculatedWorldMatrix() { return m_PrecalculatedMatrix; }

	virtual CxfMesh *GetMesh() { return m_Mesh; }

	virtual void SetDefaultPipelineStates(IPipeline*) {}

	void Attach(CxfMesh* mesh, bool shadowcaster=true);
	void Attach(const CString& path, int what, bool shadowcaster=true) ;

	//
	//
	//
	void UpdatePhysics(real time_step);
};

};

#endif /* if !defined(__ovrl_OVRLOBJROOT_HPP) */
