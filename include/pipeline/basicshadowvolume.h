/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/basicshadowvolume.h,v $
 * $Implementation: $
 * $Revision: 1.1 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description:  $
 *
 * $Log: basicshadowvolume.h,v $
 * Revision 1.1  2005/03/04 13:21:16  foxis
 * no message
 *
 *
 */

#if !defined(__ovrl_BASICSHADOWVOLUME_H)
#define __ovrl_BASICSHADOWVOLUME_H

#include "common/all.h"
#include "xfactory/xfactory.h"

namespace openvrl {

class OVRLIBAPI CxfMesh;

class OVRLIBAPI IBasicShadowVolume
{
public:
	virtual ~IBasicShadowVolume() = 0 {}

	virtual void Prepare(CxfMesh*, ulong) = 0;

	virtual void Build(const C3DVector&, real) = 0;
	virtual void Release() = 0;

	virtual CxfVertexBuffer* VB() =0;
	virtual CxfIndexBuffer* IB() =0;

	virtual ulong VB_length() const =0;
	virtual ulong IB_length() const =0;
};

};

#endif