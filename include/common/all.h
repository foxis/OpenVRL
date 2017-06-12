/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/all.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/03 11:24:24 $
 * $Description:  $
 *
 * $Log: all.h,v $
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(__ovrl_ALL_H)
#define __ovrl_ALL_H

#include "common/config.h"
#include "common/defs.h"
#include "common/types.h"
#include "common/errors.h"
#include "common/styles.h"
#include "common/colors.h"
#include "common/clsreg.h"
#include "common/classes.h"
#include "common/log.h"

namespace openvrl {
//
//
//
enum FORMAT_TYPE
{
	FMT_UNKNOWN 			 =	0,

	FMT_R8G8B8				 = 20,
	FMT_A8R8G8B8			 = 21,
	FMT_X8R8G8B8			 = 22,
	FMT_R5G6B5				 = 23,
	FMT_X1R5G5B5			 = 24,
	FMT_A1R5G5B5			 = 25,
	FMT_A4R4G4B4			 = 26,
	FMT_R3G3B2				 = 27,
	FMT_A8					 = 28,
	FMT_A8R3G3B2			 = 29,
	FMT_X4R4G4B4			 = 30,
	FMT_A2B10G10R10 		 = 31,
	FMT_G16R16				 = 34,

	FMT_A8P8				 = 40,
	FMT_P8					 = 41,

	FMT_L8					 = 50,
	FMT_A8L8				 = 51,
	FMT_A4L4				 = 52,

	FMT_V8U8				 = 60,
	FMT_L6V5U5				 = 61,
	FMT_X8L8V8U8			 = 62,
	FMT_Q8W8V8U8			 = 63,
	FMT_V16U16				 = 64,
	FMT_W11V11U10			 = 65,
	FMT_A2W10V10U10 		 = 67,

	FMT_UYVY				 = MAKEFOURCC('U', 'Y', 'V', 'Y'),
	FMT_YUY2				 = MAKEFOURCC('Y', 'U', 'Y', '2'),
	FMT_DXT1				 = MAKEFOURCC('D', 'X', 'T', '1'),
	FMT_DXT2				 = MAKEFOURCC('D', 'X', 'T', '2'),
	FMT_DXT3				 = MAKEFOURCC('D', 'X', 'T', '3'),
	FMT_DXT4				 = MAKEFOURCC('D', 'X', 'T', '4'),
	FMT_DXT5				 = MAKEFOURCC('D', 'X', 'T', '5'),

	FMT_D16_LOCKABLE		 = 70,
	FMT_D32 				 = 71,
	FMT_D15S1				 = 73,
	FMT_D24S8				 = 75,
	FMT_D16 				 = 80,
	FMT_D24X8				 = 77,
	FMT_D24X4S4 			 = 79,


	FMT_VERTEXDATA			 =100,
	FMT_INDEX16 			 =101,
	FMT_INDEX32 			 =102,

	FMT_FORCE_DWORD 		 =0x7fffffff
};

//
//
//
/* Usages */
#define USAGE_RENDERTARGET       (0x00000001L)
#define USAGE_DEPTHSTENCIL       (0x00000002L)

/* Usages for Vertex/Index buffers */
#define USAGE_WRITEONLY          (0x00000008L)
#define USAGE_SOFTWAREPROCESSING (0x00000010L)
#define USAGE_DONOTCLIP          (0x00000020L)
#define USAGE_POINTS             (0x00000040L)
#define USAGE_RTPATCHES          (0x00000080L)
#define USAGE_NPATCHES           (0x00000100L)
#define USAGE_DYNAMIC            (0x00000200L)
#define USAGE_MASK		 (0x0FFFFFFFL)
#define USAGE_CONTAINS_LOCAL	 (0x10000000L)
#define USAGE_LOCAL_ONLY	 (0x30000000L)


/**
 * Vertex Buffer usage styles
 *
 * 
 */
#define OVRL_VB_SOFTWARE	USAGE_SOFTWAREPROCESSING
#define OVRL_VB_DYNAMIC		USAGE_DYNAMIC
#define OVRL_VB_DONOTCLIP		USAGE_DONOTCLIP
#define OVRL_VB_WRITEONLY	USAGE_WRITEONLY
#define OVRL_VB_RTPATCHES	USAGE_RTPATCHES
#define OVRL_VB_NTPATCHES	USAGE_NTPATCHES
#define OVRL_VB_POINTS	USAGE_POINTS
#define OVRL_VB_CONTAINS_LOCAL		USAGE_CONTAINS_LOCAL
#define OVRL_VB_LOCAL_ONLY		USAGE_LOCAL_ONLY

/**
 * Vertex Buffer vertex format styles
 *
 * OVRL_VB_XYZ    - {float, float, float}
 * OVRL_VB_RHW    - {float}
 * OVRL_VB_B1     - {float}
 * OVRL_VB_B2     - {float}
 * OVRL_VB_B3     - {float}
 * OVRL_VB_B4     - {float}
 * OVRL_VB_NORMAL - {float, float, float}
 * OVRL_VB_PSIZE  - {float}
 * OVRL_VB_DIFFUSE	- {BYTE, BYTE, BYTE, BYTE}
 * OVRL_VB_SPECULAR	- {BYTE, BYTE, BYTE, BYTE}
 * OVRL_VB_TX1    - {float, float, float}
 * OVRL_VB_TX2    - {float, float, float}
 * OVRL_VB_TX3    - {float, float, float}
 * OVRL_VB_TX4    - {float, float, float}
 * OVRL_VB_MASS   - {float}
 * OVRL_VB_BONE_ID - {DWORD}
 * 
 */
#define OVRL_VB_XYZ    0x0001 
#define OVRL_VB_RHW    0x0002
#define OVRL_VB_B1     0x0004
#define OVRL_VB_B2     0x0008
#define OVRL_VB_B3     0x0010
#define OVRL_VB_B4     0x0020
#define OVRL_VB_NORMAL 0x0040
#define OVRL_VB_PSIZE  0x0080
#define OVRL_VB_DIFFUSE	0x0100
#define OVRL_VB_SPECULAR	0x0200
#define OVRL_VB_TX1    0x0400
#define OVRL_VB_TX2    0x0800
#define OVRL_VB_TX3    0x1000
#define OVRL_VB_TX4    0x2000
#define OVRL_VB_MASS   0x4000
#define OVRL_VB_BONE_ID	0x8000

/**
 * Index Buffer usage styles
 *
 * 
 */
#define OVRL_IB_SOFTWARE	USAGE_SOFTWAREPROCESSING
#define OVRL_IB_DYNAMIC		USAGE_DYNAMIC
#define OVRL_IB_DONOTCLIP		USAGE_DONOTCLIP
#define OVRL_IB_WRITEONLY	USAGE_WRITEONLY
#define OVRL_IB_RTPATCHES	USAGE_RTPATCHES
#define OVRL_IB_NTPATCHES	USAGE_NTPATCHES
#define OVRL_IB_POINTS	USAGE_POINTS
#define OVRL_IB_CONTAINS_LOCAL		USAGE_CONTAINS_LOCAL
#define OVRL_IB_LOCAL_ONLY		USAGE_LOCAL_ONLY

/**
 * Index Buffer index format styles
 *
 * OVRL_IB_16   - {WORD}
 * OVRL_IB_32 - {DWORD}
 * 
 */
#define OVRL_IB_16    0x0001 
#define OVRL_IB_32    0x0002

/**
 * Texture usage styles
 *
 * OVRL_TX_SOFTWARE	- Tells vertex buffer pipeline to process it in  
 *	software
 * OVRL_TX_DYNAMIC	- vertex buffer is dynamic 
 * OVRL_TX_DISCARD	- 
 * OVRL_TX_WRITEONLY	- no read operations
 * OVRL_TX_READONLY	- no write operations
 * OVRL_TX_LOCAL	- TX is created on the local heap
 * 
 */
#define OVRL_TX_SOFTWARE	USAGE_SOFTWAREPROCESSING
#define OVRL_TX_DYNAMIC		USAGE_DYNAMIC
#define OVRL_TX_RENDERTARGET		USAGE_RENDERTARGET
#define OVRL_TX_WRITEONLY	USAGE_WRITEONLY
#define OVRL_TX_DEPTHSTENCIL	USAGE_DEPTHSTENCIL
#define OVRL_TX_CONTAINS_LOCAL		USAGE_CONTAINS_LOCAL
#define OVRL_TX_LOCAL_ONLY		USAGE_LOCAL_ONLY

//
//	material texture map type
//
enum MATERIALMAP_TYPE
{
	MMAP_AMBIENT			= 1,
	MMAP_DIFFUSE			= 2,
	MMAP_SPECULAR			= 3,
	MMAP_STRENGTH			= 4,
	MMAP_FILTER				= 5,
	MMAP_BUMP				= 6,
	MMAP_OPACITY			= 7,
	MMAP_REFRACTION			= 8,
	MMAP_STATIC_FRICTION	= 9,
	MMAP_SLIDING_FRICTION	= 10,

	MMAP_FORCE_DWORD = 0x7FFFFFFF
};

//
//
//
enum LIGHT_TYPE
{
	LIGHT_AMBIENT           = 0x01,
	LIGHT_DIRECTIONAL       = 0x02,
	LIGHT_POINT             = 0x03,
	LIGHT_SPOT              = 0x04,
	LIGHT_PROJECTOR         = 0x05,

	LIGHT_FORCEDWORD        = 0x7FFFFFFF
};

enum LIGHTMAP_TYPE
{
	LIGHTMAP_PARTICLE	= 0,
	LIGHTMAP_FLARE		= 1,
	LIGHTMAP_SHINE		= 2,
	LIGHTMAP_PROJECTOR	= 3,

	LIGHTMAP_FORCEDWORD        = 0x7FFFFFFF
};

};

#endif /* !defined(__ovrl_ALL_HPP) */

