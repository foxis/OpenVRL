/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/openvrl.h,v $
 * $Implementation: $
 * $Revision: 1.6 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:56 $
 * $Description:  $
 *
 * $Log: openvrl.h,v $
 * Revision 1.6  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.5  2005/02/11 11:02:49  foxis
 * fixed many bugs
 * added joints
 *
 * Revision 1.4  2005/02/03 17:52:51  foxis
 * made IBasicGeom and it's derivatives to work.
 * now physics engine recognizes collisions.
 *
 * however geom management should be rethought.
 *
 * Revision 1.3  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(__OpenVRL_v040_H_INCLUDED)
#define __OpenVRL_v040_H_INCLUDED


/******************************************************************************
 *  OpenVRL library is declared in openvrl namescpace
 */
#include "config.h"
#include "common/all.h"
#include "iosystem/iosystem.h"
#include "tpllib/tpl.hpp"
#include "system/ovrlsystem.h"

#include "world/body.h"
#include "world/camera.h"
#include "world/light.h"

#include "physics/geoms.h"
#include "physics/joints.h"

namespace openvrl {

extern "C" OVRLIBAPI DWORD dllOpenVRL_Version(void);
extern "C" OVRLIBAPI DWORD dllOpenVRL_Description(CHAR* str, size_t max_cb);

};

#endif /* !defined(__OpenVRL_v040_H_INCLUDED) */
