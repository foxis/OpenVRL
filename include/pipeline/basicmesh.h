/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/basicmesh.h,v $
 * $Implementation: ~/src/pipeline/renderobject.cc $
 * $Revision: 1.4 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description: renderable object abstract class $
 *
 * $Log: basicmesh.h,v $
 * Revision 1.4  2005/03/04 13:21:16  foxis
 * no message
 *
 * Revision 1.3  2005/03/01 18:21:15  foxis
 * Pipeline: shadows now working more or less. need to handle special cases.
 * C4x4Matrix: added inverse method + others
 *
 * Revision 1.2  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.1.1.1  2005/02/02 15:39:19  foxis
 * sources import
 *
 * Revision 0.1  20020813  22:02:00 FoxiE
 * y
 *
 */

#if !defined(__ovrl_BASICMESH_HPP)
#define __ovrl_BASICMESH_HPP

#include "xfactory/xfactory.h"
#include "pipeline/bpentity.h"

#include "pipeline/basicshadowvolume.h"
#include "pipeline/basiceffect.h"

namespace openvrl {

#define OVRL_CAPS_MESH	0x00000001

class OVRLIBAPI IPipeline;
class OVRLIBAPI IBasicMesh : public IBasicPipelineEntity
{
public:
	virtual ~IBasicMesh() = 0 {}

	virtual CxfMesh *GetMesh() = 0;

	virtual void SetDefaultPipelineStates(IPipeline*) = 0;

	virtual C4x4Matrix& GetTransformMatrix() = 0;
	virtual C4x4Matrix& GetWorldTransformMatrix() = 0;
	virtual void PrecalculateWorldMatrix() = 0;
	virtual C4x4Matrix& GetPrecalculatedWorldMatrix() = 0;

// not needed?
//	virtual void Attach(CxfMesh* mesh) = 0;
//	virtual void Attach(const CString& path, int what) = 0;

	virtual ulong pipeline_caps() const { return OVRL_CAPS_MESH; }
};


};

#endif 