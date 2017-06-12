/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/tpltypes.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/03/09 12:24:08 $
 * $Description: Declares most common types $
 *
 * $Log: tpltypes.h,v $
 * Revision 1.2  2005/03/09 12:24:08  foxis
 * . fixed memory leaks
 * . fixed OVRL_ASSERT issue in release mode
 *   [still to fix: TPL_ASSERT, now - just a hack]
 *
 * Revision 1.1.1.1  2005/02/02 15:39:22  foxis
 * sources import
 *
 * Revision 0.1  20020111  11:52:40 FoxiE
 *  ;-)
 *
 */



#if !defined(__tpl_TYPES_H)
#define __tpl_TYPES_H

#include "tpllib/tplconf.h"

namespace openvrl {

/**
 *
 */
typedef char                    TPL_CHAR;
typedef unsigned char           TPL_BYTE;
typedef unsigned short int      TPL_WORD;
typedef unsigned long           TPL_DWORD;
typedef double                  TPL_QWORD;
typedef TPL_BYTE               TPL_BOOL;
typedef TPL_WORD               TPL_ANSICH;
typedef void*                   TPL_LPVOID;
typedef TPL_CHAR*              TPL_LPSTR;
typedef TPL_BYTE*                   TPL_LPBYTE;
typedef TPL_WORD*                   TPL_LPWORD;
typedef TPL_DWORD*                  TPL_LPDWORD;
typedef TPL_ANSICH*                 TPL_LPANSISTR;
typedef const void*             TPL_LPCVOID;
typedef const TPL_CHAR*             TPL_LPCSTR;
typedef const TPL_BYTE*             TPL_LPCBYTE;
typedef const TPL_WORD*             TPL_LPCWORD;
typedef const TPL_DWORD*            TPL_LPCDWORD;
typedef const TPL_ANSICH*           TPL_LPCANSISTR;
typedef signed char             TPL_SBYTE;
typedef signed short int        TPL_SWORD;
typedef signed long             TPL_SDWORD;
typedef unsigned int            TPL_uint;
typedef unsigned short          TPL_ushort;
typedef unsigned long           TPL_ulong;
typedef unsigned char           TPL_uchar;
typedef long double             TPL_long_real;
typedef double                  TPL_real;
typedef float                   TPL_float;
typedef signed long             TPL_fixed;
typedef TPL_DWORD                   TPL_HANDLER;
typedef TPL_HANDLER                 TPL_HDEV;
typedef TPL_HANDLER                 TPL_HTHREAD;
typedef TPL_uint	uint;
typedef TPL_ushort	ushort;
typedef TPL_ulong	ulong;
typedef TPL_uchar	uchar;
typedef TPL_fixed	fixed;


/********************
 *
 */
struct TPL_2dvector_struct
{
	TPL_float x;
	TPL_float y;
};

struct TPL_3dvector_struct
{
	TPL_float x;
	TPL_float y;
	TPL_float z;
};
struct TPL_quaternion_struct
{
	TPL_float x;
	TPL_float y;
	TPL_float z;
	TPL_float w;
};

struct TPL_DRGB_struct
{
        TPL_float       red;
        TPL_float       green;
        TPL_float       blue;
        TPL_float       alpha;
};

struct TPL_RGB_struct
{
        TPL_BYTE    red;
        TPL_BYTE    green;
        TPL_BYTE    blue;
        TPL_BYTE    alpha;
};

struct TPL_time_struct
{
        TPL_WORD    year;
        TPL_BYTE    month;
        TPL_BYTE    day;
        TPL_BYTE    hour;
        TPL_BYTE    minute;
        TPL_BYTE    second;
        TPL_BYTE    millisecond;
};

typedef struct TPL_2dvector_struct TPL_2dvector_t;
typedef struct TPL_3dvector_struct TPL_3dvector_t;
typedef struct TPL_quaternion_struct TPL_quaternion_t;
typedef TPL_float	TPL_4x4matrix_t[16];
typedef struct TPL_DRGB_struct TPL_DRGB_t;
typedef struct TPL_RGB_struct TPL_RGB_t;
typedef struct TPL_time_struct TPL_time_t;

};

#endif /* if !defined(__TPL_TYPES_H) */
