/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/clsreg.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/03 11:24:24 $
 * $Description:  $
 *
 * $Log: clsreg.h,v $
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(__ovrl_CLSREG_H)
#define __ovrl_CLSREG_H

namespace openvrl {

// all registered classes
enum OVRL_ORW_TYPE {
	ORW_WORLD,
	ORW_WORLD_SECTOR,
	ORW_CAMERA,
	ORW_BODY,
	ORW_DYNAMIC_BODY,
	ORW_PARTICLE_SYSTEM,
	ORW_LIGHT,
	ORW_JOINT,

	ORW_FORCE_DWORD = 0x7FFFFFFF
};

// priorities
enum OVRL_ORP_TYPE {
	ORP_WORLD		= -1,

	ORP_TERRAIN		= 0,
	ORP_LEVEL		= 1,
	ORP_BODY		= 32,
	ORP_RIGIDBODY	= 255,
	ORP_PARTICLE	= 256,
	ORP_CAMERA	= 257,
	ORP_LIGHT	= 1024,

	ORP_FORCE_DWORD = 0x7FFFFFFF
};

};

#endif