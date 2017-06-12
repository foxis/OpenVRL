/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/basiclight.h,v $
 * $Implementation:  $
 * $Revision: 1.1 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:56 $
 * $Description:  $
 *
 * $Log: basiclight.h,v $
 * Revision 1.1  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 *
 */

#if !defined(__ovrl_BASICLIGHT_HPP)
#define __ovrl_BASICLIGHT_HPP

#include "xfactory/xfactory.h"
#include "pipeline/bpentity.h"

namespace openvrl {

#define OVRL_CAPS_LIGHT 0x00000004

class OVRLIBAPI IPipeline;
class OVRLIBAPI IBasicLight : public IBasicPipelineEntity
{
public:
	virtual ~IBasicLight() = 0 {}

	virtual CxfLight *GetLight() = 0;

	virtual void SetDefaultPipelineStates(IPipeline*) = 0;

	virtual C4x4Matrix& GetTransformMatrix() = 0;
	virtual C4x4Matrix& GetWorldTransformMatrix() = 0;

	virtual void Attach(CxfLight*) = 0;
	virtual void Attach(const CString&, int) = 0;

	virtual ulong pipeline_caps() const { return OVRL_CAPS_LIGHT; }
};


};

#endif 