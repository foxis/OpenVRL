/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/rendertarget.h,v $
 * $Implementation: $
 * $Revision: 1.1 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:56 $
 * $Description: $
 *
 * $Log: rendertarget.h,v $
 * Revision 1.1  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 *
 */

#if !defined(__ovrl_RENDERTARGET_HPP)
#define __ovrl_RENDERTARGET_HPP

#include "xfactory/xfactory.h"

namespace openvrl {

class OVRLIBAPI IPipeline;
class OVRLIBAPI IRenderTarget
{
public:
	virtual ~IRenderTarget() = 0 {}

	virtual void Release() = 0;
	virtual void Prepare() = 0;

	virtual void Attach(CxfTexture*,CxfTexture*)=0;
	virtual void Attach(const CString&, const CString&)=0;

	virtual int BeginScene()=0;
	virtual int EndScene()=0;
	virtual int Clear()=0;

	virtual void* Lock() = 0;
	virtual void Unlock(void*) = 0;
	virtual void* GetLockedBits() = 0;
	virtual ulong GetLockedPitch() = 0;
};


};

#endif 