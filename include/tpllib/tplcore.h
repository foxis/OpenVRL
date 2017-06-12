/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/tplcore.h,v $
 * $Implementation:  $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description: *.tpl library's main defines $
 *
 * Revision 0.1  20010919  17:56:12 FoxiE
 * Pradejau rasyti logus :)
 *
 */


#if !defined(__tpl_TPLCORE_H)
#define __tpl_TPLCORE_H

#include "tpllib/tplconf.h"
#include "tpllib/tpltypes.h"

namespace openvrl {

#define TPL_COMPRESSION_NONE     0x00
#define TPL_COMPRESSION_RLE      0x01
#define TPL_COMPRESSION_LZW      0x02
#define TPL_COMPRESSION_ROW_RLE  0x03
#define TPL_COMPRESSION_ROW_LZW  0x04

/**
 *  Template type
 */
#define TPL_TYPE_MASK                  0x0000FFFFU
#define TPL_RAW_MESH                   0x00000001U
#define TPL_VIPM                       0x00000002U
#define TPL_VDPM                       0x00000003U
#define TPL_VOLUME                     0x00000004U
#define TPL_TERRAIN                    0x00000005U
#define TPL_SPACEWRAP                  0x00000008U
#define TPL_PARTICLES                  0x00000009U
#define TPL_ETC_BONES                  0x00040000U
#define TPL_ETC_CUE_POINTS             0x00080000U
#define TPL_ETC_ANIMATION              0x00100000U

#if defined(TPL_USE_PRAGMA_PACK)
#pragma pack(1)
#endif // if defined(TPL_USE_PRAGMA_PACK)

#define TPL_SIGNATURE                  "TPL"
typedef struct tpl_header_struct TPL_HDR;

struct TPL_API tpl_header_struct
{
        TPL_DWORD   version;
        TPL_CHAR    signature[TPL_MAX_SIG_LEN];
        TPL_CHAR    name[TPL_MAX_NAME_LEN];
        TPL_WORD    UID;
        TPL_WORD    GID;
        TPL_DWORD   type;
        TPL_DWORD   comment_size;
        TPL_DWORD   compression;
        TPL_DWORD   original_size;
        TPL_DWORD   compressed_size;
        TPL_time_t  time;

        TPL_DWORD   texture_offs;
        TPL_DWORD   material_offs;
        TPL_DWORD   light_offs;
        TPL_DWORD   camera_offs;
        TPL_DWORD   mesh_offs;
        TPL_DWORD   bones_offs;
        TPL_DWORD   animation_offs;
        TPL_BYTE    wasted[TPL_HDR_SIZE-14*4-sizeof(TPL_time_t)-TPL_MAX_SIG_LEN-TPL_MAX_NAME_LEN];
};

/* ------------------------------------------------------------------------- */
#define TPL_MAT_SIG                  "MAT"
#define TPL_MAT_VERSION              0x00010000
typedef struct tpl_material_struct TPL_MAT;
struct TPL_API tpl_material_struct
{
        TPL_DWORD           version;
        TPL_CHAR            signature[TPL_MAX_SIG_LEN];
        TPL_CHAR            name[TPL_MAX_NAME_LEN];
        TPL_DWORD           style;
        TPL_DWORD           flags;
        TPL_DRGB_t      ambient;
        TPL_DRGB_t      diffuse;
        TPL_DRGB_t      specular;
        TPL_DRGB_t      filter;
        TPL_DRGB_t      refraction;
        TPL_real        shiness;
        TPL_real        strength;
        TPL_real        self_illumination;
        TPL_real        opacity;
        TPL_real        bounce_coeficient;
        TPL_real        static_friction;
        TPL_real        sliding_friction;

        TPL_BYTE           wasted[20];
        TPL_DWORD           maps[TPL_MATERIAL_MAX_MAPS];
};


/* ------------------------------------------------------------------------- */
#define TPL_TEX_PATH     0x00
#define TPL_TEX_RAW      0x01
#define TPL_TEX_SRF      0x02
#define TPL_TEX_TEX      0x03
#define TPL_TEX_LIBNAME  0x04

#define TPL_TEX_SIG                    "TEX"
#define TPL_TEX_VERSION					0x00010000
typedef struct tpl_texture_struct TPL_TEX;
struct TPL_API tpl_texture_struct
{
        TPL_DWORD   version;
        TPL_CHAR    signature[TPL_MAX_SIG_LEN];
        TPL_CHAR    name[TPL_MAX_NAME_LEN];

        TPL_DWORD   width;
        TPL_DWORD   height;
        TPL_DWORD   bpl;                /* */
        TPL_WORD    bpp;
        TPL_WORD    compression;
        TPL_DWORD   styles;

        TPL_DWORD   data_size;
        TPL_DWORD   original_size;

        TPL_BYTE    wasted[20];

        TPL_DWORD   srf_offs;           /* offs to the surface data */
        TPL_DWORD   srf_size;           /* surface data size */
        TPL_DWORD   lookup_offs;        /* lookup, if any, offset in the file */
        TPL_DWORD   lookup_size;        /* lookup, if any, data size */
};


/* ------------------------------------------------------------------------- */
#define TPL_RAW_SIG                    "RAW"
#define TPL_RAW_VERSION			0x00010000
typedef struct tpl_rawmesh_struct TPL_RAW;

#define TPL_RAW_TRIANGLELIST	0x01
#define TPL_RAW_TRIANGLESTRIP	0x02
#define TPL_RAW_TRIANGLEFAN		0x03
#define TPL_RAW_LINELIST	0x04
#define TPL_RAW_LINESTRIP	0x05
#define TPL_RAW_LINEFAN		0x06
#define	TPL_RAW_POINTS			0x07

#define TPL_VB_XYZ    0x0001 
#define TPL_VB_RHW    0x0002
#define TPL_VB_B1     0x0004
#define TPL_VB_B2     0x0008
#define TPL_VB_B3     0x0010
#define TPL_VB_B4     0x0020
#define TPL_VB_NORMAL 0x0040
#define TPL_VB_PSIZE  0x0080
#define TPL_VB_DIFFUSE	0x0100
#define TPL_VB_SPECULAR	0x0200
#define TPL_VB_TX1    0x0400
#define TPL_VB_TX2    0x0800
#define TPL_VB_TX3    0x1000
#define TPL_VB_TX4    0x2000
#define TPL_VB_MASS   0x4000
#define TPL_VB_BONE_ID	0x8000

#define TPL_IB_SIZE_MASK	0xFF00
#define TPL_IB_32BIT	0x0100
#define TPL_IB_24BIT	0x0200
#define TPL_IB_16BIT	0x0400
#define TPL_IB_08BIT	0x0800
#define TPL_IB_TYPE_MASK	0x00FF
#define TPL_IB_A	0x0001
#define TPL_IB_B	0x0002
#define TPL_IB_C	0x0004
#define TPL_IB_D	0x0008
#define TPL_IB_MI	0x0010
#define TPL_IB_LINE	(TPL_IB_A|TPL_IB_B)
#define TPL_IB_TRIANGLE	(TPL_IB_A|TPL_IB_B|TPL_IB_C)
#define TPL_IB_QUAD	(TPL_IB_A|TPL_IB_B|TPL_IB_C|TPL_IB_D)

struct TPL_API tpl_rawmesh_struct
{
	TPL_DWORD	version;
	TPL_CHAR	signature[TPL_MAX_SIG_LEN];
	TPL_CHAR	name[TPL_MAX_NAME_LEN];
	TPL_DWORD	type;
	TPL_WORD	VB_flags;
	TPL_WORD	IB_flags;
	TPL_DWORD	verteces;
	TPL_DWORD	faces;
	TPL_WORD	vertex_size;
	TPL_WORD	face_size;
	TPL_3dvector_t	center_mass;
	TPL_DWORD	subsets;
//	TPL_DWORD	data_size;
//	TPL_DWORD   original_size;
//	TPL_WORD	compression;
	TPL_BYTE	wasted[20];
};

#define TPL_MESHSUBSET_VERSION	0x00010000
typedef struct tpl_meshsubset_struct TPL_MESHSUBSET;

struct TPL_API tpl_meshsubset_struct
{
	TPL_DWORD	version;
	TPL_DWORD	type;
	TPL_DWORD	VB_index;
	TPL_DWORD	IB_index;
	TPL_DWORD	VB_size;
	TPL_DWORD	IB_size;
	TPL_CHAR	material[TPL_MAX_NAME_LEN];
	TPL_4x4matrix_t	transform;
	TPL_BYTE	wasted[8];
};

/* ------------------------------------------------------------------------- */
#define TPL_LIGHT_SIG                    "LGT"
#define TPL_LIGHT_VERSION			0x00010000
typedef struct tpl_light_struct TPL_LIGHT;

#define TPL_LIGHT_AMBIENT           0x01
#define TPL_LIGHT_DIRECTIONAL       0x02
#define TPL_LIGHT_POINT             0x03
#define TPL_LIGHT_SPOT              0x04
#define TPL_LIGHT_PROJECTOR         0x05

struct TPL_API tpl_light_struct
{
	TPL_DWORD			version;
	TPL_CHAR			signature[TPL_MAX_SIG_LEN];
        TPL_CHAR            name[TPL_MAX_NAME_LEN];
        TPL_DWORD			style;
        TPL_DRGB_t			ambient;
        TPL_DRGB_t			diffuse;
        TPL_DRGB_t			specular;

        TPL_float			cut_off;
        TPL_float			fall_off;
        TPL_float			theta;         /* spot light angles  */
        TPL_float			phi;           /*  */

		TPL_DWORD			reserved0;
        TPL_float			attenuation[TPL_LIGHT_MAX_ATTENUATIONS];
        TPL_DWORD			maps[TPL_LIGHT_MAX_MAPS];
};

/* ------------------------------------------------------------------------- */
#define TPL_CAMERA_SIG                    "CMR"
#define TPL_CAMERA_VERSION			0x00010000
typedef struct tpl_camera_struct TPL_CAMERA;

struct TPL_API tpl_camera_struct
{
	TPL_DWORD		version;
	TPL_CHAR		signature[TPL_MAX_SIG_LEN];
	TPL_CHAR		name[TPL_MAX_NAME_LEN];
	TPL_float		focus;              /* Effective camera focus [mm] */
	TPL_float		dx;                 /* Width of camera sensor element [mm] */
	TPL_float		dy;                 /* Height of camera sensor element [mm] */
	TPL_float		gamma;
	TPL_BYTE		brightness;
	TPL_BYTE		contrast;
	TPL_BYTE		whitepoint;
	TPL_BYTE		blackpoint;
	TPL_BYTE		wasted[4];
};


/* ------------------------------------------------------------------------- */

#if defined(TPL_USE_PRAGMA_PACK)
#pragma pack()
#endif /* if defined(TPL_USE_PRAGMA_PACK) */

};

#endif /* #if !defined(__tpl_TPLCORE_H) */

