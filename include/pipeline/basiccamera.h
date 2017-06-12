/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/basiccamera.h,v $
 * $Implementation:  $
 * $Revision: 1.1 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:56 $
 * $Description:  $
 *
 * $Log: basiccamera.h,v $
 * Revision 1.1  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 *
 */


#if !defined(__ovrl_BASICCAMERA_HPP)
#define __ovrl_BASICCAMERA_HPP

#include "xfactory/xfactory.h"
#include "pipeline/bpentity.h"
#include "pipeline/rendertarget.h"

namespace openvrl {

#define OVRL_CAPS_CAMERA 0x00000002

class OVRLIBAPI IPipeline;
class OVRLIBAPI IBasicCamera : public IBasicPipelineEntity
{
public:
	virtual ~IBasicCamera() = 0 {}

	virtual CxfCamera *GetCamera() = 0;
	virtual IRenderTarget *GetRenderTarget() = 0;
	virtual void SetRenderTarget(IRenderTarget*) = 0;

	virtual void SetDefaultPipelineStates(IPipeline*) = 0;

	virtual C4x4Matrix& GetViewMatrix() = 0;
	virtual C4x4Matrix& GetProjectionMatrix() = 0;

	virtual void Attach(CxfCamera*) = 0;
	virtual void Attach(const CString&, int) = 0;

	virtual ulong pipeline_caps() const { return OVRL_CAPS_CAMERA; }
};


};

#endif // !defined(__ovrl_OVRLRENDEROBJECT_HPP)