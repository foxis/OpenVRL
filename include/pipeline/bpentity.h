/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/bpentity.h,v $
 * $Implementation:  $
 * $Revision: 1.1 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:56 $
 * $Description:  $
 *
 * $Log: bpentity.h,v $
 * Revision 1.1  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 *
 */


#if !defined(__ovrl_BASICPIPELINEENTITY_HPP)
#define __ovrl_BASICPIPELINEENTITY_HPP

#include "xfactory/xfactory.h"

namespace openvrl {

class OVRLIBAPI IPipeline;
class OVRLIBAPI IBasicPipelineEntity 
{
public:
	virtual ~IBasicPipelineEntity() = 0 {}

	virtual void SetDefaultPipelineStates(IPipeline*) = 0;

	virtual ulong pipeline_caps() const = 0;
};


};

#endif // !defined(__ovrl_OVRLRENDEROBJECT_HPP)