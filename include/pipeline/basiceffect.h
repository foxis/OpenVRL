/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/basiceffect.h,v $
 * $Implementation: $
 * $Revision: 1.1 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description:  $
 *
 * $Log: basiceffect.h,v $
 * Revision 1.1  2005/03/04 13:21:16  foxis
 * no message
 *
 *
 */

#if !defined(__ovrl_BASICEFFECT_H)
#define __ovrl_BASICEFFECT_H

#include "common/all.h"

namespace openvrl {

class OVRLIBAPI IBasicEffect
{
public:
	virtual ~IBasicEffect() = 0 {}
};

};

#endif