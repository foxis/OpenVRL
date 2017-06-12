/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/Types.h,v $
 * $Implementation: $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:13 $
 * $Description: Declares most common types $
 *
 * $Log: Types.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:13  foxis
 * sources import
 *
 * Revision 0.7  20010911  16:37:59 FoxiE
 * Idejau quaternion_t
 *
 * Revision 0.6  20010820  12:01:28 FoxiE
 * idejau sphere_t, box_t, cylinder_t, cone_t, clipped_cone_t
 * double ir float pakeiciau i real ir float;
 *
 * Revision 0.5  20010428  12:16:20 FoxiE
 * prie _visu_ tipu pridejau `_t`
 *
 * Revision 0.4  20010427  19:20:58 FoxiE
 * Pridejau rect_t bei clip_region_t
 *
 * Revision 0.3  20010427  19:20:00 FoxiE
 * SWORD pakeiciau i int
 *
 * Revision 0.2  20010411  16:21:13 FoxiE
 * Ismeciau visus USE_FAR/USE_HUGE ifdef'us...
 *
 * Revision 0.1  20010409  11:52:40 FoxiE
 * Pradejau rasyti logus :)
 *
 */



#if !defined(__TYPES_H)
#define __TYPES_H

#include "config.h"
#include "defs.h"

namespace openvrl {

// standart types ALL CAPS
typedef char                CHAR;
typedef int					INT;
typedef long				LONG;
typedef short				SHORT;
typedef unsigned char       UCHAR;
typedef unsigned int		UINT;
typedef unsigned long		ULONG;
typedef unsigned short		USHORT;
// standard types
typedef openvrl::UINT				uint;
typedef openvrl::USHORT				ushort;
typedef openvrl::ULONG				ulong;
typedef openvrl::UCHAR				uchar;
typedef long double         long_real;
typedef float				short_real;
typedef double              real;
//
typedef openvrl::UINT				size_t;
typedef openvrl::UINT				num_t;
typedef openvrl::UINT				index_t;

// other types
typedef openvrl::UCHAR				BYTE;
typedef openvrl::USHORT				WORD;
typedef openvrl::ULONG				DWORD;
typedef openvrl::real              QWORD;
typedef openvrl::BYTE               BOOL;
typedef openvrl::WORD               ANSICH;
typedef void*              LPVOID;
typedef openvrl::CHAR*              LPSTR;
typedef openvrl::BYTE*              LPBYTE;
typedef openvrl::WORD*              LPWORD;
typedef openvrl::DWORD*             LPDWORD;
typedef openvrl::ANSICH*            LPANSISTR;
typedef const void*             LPCVOID;
typedef const openvrl::CHAR*        LPCSTR;
typedef const openvrl::BYTE*        LPCBYTE;
typedef const openvrl::WORD*        LPCWORD;
typedef const openvrl::DWORD*       LPCDWORD;
typedef const openvrl::ANSICH*      LPCANSISTR;
typedef signed char             SBYTE;
typedef signed short int        SWORD;
typedef signed long             SDWORD;
typedef openvrl::DWORD              HANDLER;
typedef openvrl::HANDLER            HDEV;
typedef openvrl::HANDLER            HTHREAD;
/**
 *
 */

/*#if !defined(bool)
enum bool_enum
{
        true = 1,
        false = 0
};
typedef enum bool_enum bool_t; /* * /
typedef bool_t bool;      /* just to be polite:) * /
#endif
*/

/**
 *
 */
struct OVRLIBAPI vector4d_struct
{
        real x,y,z,q;
};

/**
 *
 */
struct OVRLIBAPI vector3d_struct
{
        real x,y,z;
};

/**
 *
 */
struct OVRLIBAPI plane3d_struct
{
        struct vector3d_struct origin;
        struct vector3d_struct normal;
};

/**
 *
 */
struct OVRLIBAPI vector2d_struct
{
        real x,y; 
};

/**
 *
 */
struct OVRLIBAPI int_vector4d_struct
{
        INT x,y,z,q;
};

/**
 *
 */
struct OVRLIBAPI int_vector3d_struct
{
        INT x,y,z;
};

/**
 *
 */
struct OVRLIBAPI int_vector2d_struct
{
        INT x,y;
};

/**
 *
 */
struct OVRLIBAPI rect_struct
{
        struct vector2d_struct top_left;
        struct vector2d_struct bottom_right;
};

/**
 *
 */
struct OVRLIBAPI int_rect_struct
{
        struct int_vector2d_struct top_left;
        struct int_vector2d_struct bottom_right;
};

/**
 *
 */
struct OVRLIBAPI sphere_struct
{
        struct vector3d_struct centre;
        struct vector3d_struct radius;
};

/**
 *
 */
struct OVRLIBAPI cylinder_struct
{
        struct vector3d_struct centre1;
        struct vector3d_struct normal;
        real   radius;
};

/**
 *
 */
struct OVRLIBAPI cone_struct
{
        struct vector3d_struct centre1;
        struct vector3d_struct normal;
        real   radius;
};

/**
 *
 */
struct OVRLIBAPI clipped_cone_struct
{
        struct vector3d_struct centre1;
        struct vector3d_struct normal;
        real   radius1;
        real   radius2;
};

/**
 *
 */
struct OVRLIBAPI box_struct
{
        struct vector3d_struct top_left;
        struct vector3d_struct bottom_right;
};

/**
 *
 */
struct OVRLIBAPI int_sphere_struct
{
        struct int_vector3d_struct centre;
        struct int_vector3d_struct radius;
};

/**
 *
 */
struct OVRLIBAPI int_box_struct
{
        struct int_vector3d_struct top_left;
        struct int_vector3d_struct bottom_right;
};

/**
 *
 */
struct OVRLIBAPI int_cylinder_struct
{
        struct int_vector3d_struct centre1;
        struct int_vector3d_struct normal;
        UINT   radius;
};

/**
 *
 */
struct OVRLIBAPI int_cone_struct
{
        struct int_vector3d_struct centre1;
        struct int_vector3d_struct normal;
        UINT   radius;
};

/**
 *
 */
struct OVRLIBAPI int_clipped_cone_struct
{
        struct int_vector3d_struct centre1;
        struct int_vector3d_struct normal;
        UINT   radius1;
        UINT   radius2;
};

/**
 *  Clip region structs
 */
enum OVRLIBAPI CLIP_REGION_TYPE_enum
{
        CLPRGN_DISABLED         =0 ,
        CLPRGN_UNION            =1 ,
        CLPRGN_DIFFERENCE       =2 ,
        CLPRGN_EXCLUDE          =3
};
typedef enum CLIP_REGION_TYPE_enum CLIP_REGION_TYPE_t;

/**
 *
 */
struct OVRLIBAPI clip_region_struct
{
        CLIP_REGION_TYPE_t type;
        struct rect_struct rect;
        struct clip_region_struct* next;
};

/**
 *
 */
struct OVRLIBAPI int_clip_region_struct
{
        CLIP_REGION_TYPE_t type;
        struct int_rect_struct rect;
        struct int_clip_region_struct* next;
};


/**
 *
 */
union OVRLIBAPI RGB_union {
        struct OVRLIBAPI {
              BYTE b, g, r, a;
        } bytes;
        DWORD abgr;
};

/**
 *
 */
struct OVRLIBAPI DRGB_struct {
        short_real r, g, b, a;
};

/**
 *
 */
struct OVRLIBAPI DDWORD_struct {
       DWORD ldw;
       DWORD hdw;
};

/**
 *
 */
struct OVRLIBAPI TIME_struct {
       BYTE hours;
       BYTE minutes;
       BYTE seconds;
       BYTE reserved;
};

/**
 *
 */
struct OVRLIBAPI DATE_struct {
       WORD year;
       BYTE month;
       BYTE day;
};


/**
 *
 */
typedef struct DDWORD_struct            DDWORD_t;
typedef struct vector4d_struct         vector4d_t;
typedef struct vector3d_struct         vector3d_t;
typedef struct vector2d_struct         vector2d_t;
typedef struct int_vector4d_struct     int_vector4d_t;
typedef struct int_vector3d_struct     int_vector3d_t;
typedef struct int_vector2d_struct     int_vector2d_t;
typedef struct plane3d_struct          plane3d_t;
typedef union RGB_union                 RGB_t;
typedef struct DRGB_struct             DRGB_t;
typedef struct rect_struct              rect_t;
typedef struct sphere_struct            sphere_t;
typedef struct box_struct               box_t;
typedef struct cylinder_struct          cylinder_t;
typedef struct cone_struct              cone_t;
typedef struct clipped_cone_struct      clipped_cone_t;
typedef struct int_rect_struct          int_rect_t;
typedef struct int_sphere_struct        int_sphere_t;
typedef struct int_box_struct           int_box_t;
typedef struct int_cylinder_struct      int_cylinder_t;
typedef struct int_cone_struct          int_cone_t;
typedef struct int_clipped_cone_struct  int_clipped_cone_t;
typedef struct clip_region_struct       clip_region_t;
typedef struct int_clip_region_struct   int_clip_region_t;
typedef struct TIME_struct              TIME_t;
typedef struct DATE_struct              DATE_t;

};

#endif /* if !defined(__TYPES_H) */
