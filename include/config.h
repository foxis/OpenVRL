/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/config.h,v $
 * $Implementation: $
 * $Revision: 1.5 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description:  $
 *
 * $Log: config.h,v $
 * Revision 1.5  2005/03/04 13:21:16  foxis
 * no message
 *
 * Revision 1.4  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(__OpenVRL_CONFIG_H_INCLUDED)
#define __OpenVRL_CONFIG_H_INCLUDED

/** This library can't be compiled in real mode or 16bit protected mode or not for Win32 executable
 */
#if !( defined(__32BIT__) || defined(WIN32) )
#error Sorry, can't compile in 16bit mode...
#endif

#if !defined(__STATIC_OVRL) && !defined(__DYNAMIC_OVRL)
# if defined(_LIB)
#  define __STATIC_OVRL
# else 
#  if defined(_DLL)
#   define __DYNAMIC_OVRL
#  else
#   error Must by either static or dynamic lib
#  endif
# endif
#endif

/***** 
 *
 * Current OpenVRL Port specific defines
 *
 */

/** OpenVRL Version Number xxyyzzaa
 */
#define OpenVRL_VERSION 0x0005000a
#define OPENVRL_VERSION OpenVRL_VERSION
#define OPENVRL_VERSION_STR		"00.05.00.0a"

/** OpenVRL Release Date
 */
#define OPENVRL_RELEASE_DATE	"2002 08 15"

/** OpenVRL Build Date
 */
#define OPENVRL_LAST_BUILD_DATE		__DATE__

/** OpenVRL Port OS
 */
#define OPENVRL_OS "Windows XP"

/** OpenVRL Port Pipeline Platform
 */
#define OPENVRL_PIPELINE "Direct3D v9.0x"

/** OpenVRL Port Was Made By...
 */
#define OPENVRL_PORTED_BY "Andrius a.k.a. Fox`IS"

/** OpenVRL Port Number 
 *
 *  Obtain this number from OpenVRL Author:
 *
 *	Andrius a.k.a. FoxiE
 *	email: vienas@delfi.lt
 *	mob.#: +37067054190
 *
 */
#define OPENVRL_PORT_ID 0x00


/*****
 *
 *  general
 *
 */

/** Turns on namespace declarations
 */
#define USE_NAMESPACES          1

/**
 */
#define USE_OWN_STD_CLASSES	1

/** turns on verbose code generation
 */
#define VERBOSE                 1

/** Turns off some error checking code
 */
//#define LESS_CHECKINGS        1

/** Halts an application on memory errors
 */
#define STOP_ON_MEM_ERRORS      1

/** Includes zlib support
 */
#define USE_ZLIB 1

/**
 */
#define MAX_NAME_LEN             32
#define MAX_PATH_LEN             256
#define MAX_ARRAY_LEN            512
#define MAX_CALC_STACK_LEN       8192
#define MAX_DEFINE_LEN           128
#define MAX_DEFINES              32
#define MAX_FRUSTUM_PLANES       16
//#define SBUFFER_MAX_SPANS        1024

#define IODEV_DEF_BUF_SIZE       65535U
#define TMP_BUF_SIZE             65530U
#define BITIO_ADD_SIZE           10240
#define HEAP_DEFAULT_SIZE        (1024L*8L*1024L)

/*****
 *
 *  file io
 *
 */
#define FIO_BUFFER_SIZE         65535U           /* 64kb is ok */


/******
 *
 *   mathematics
 *
 */
/** Use inline mathematics functions
 */
#define MATH_INLINE     1


/******
 *
 *   pipeline driver selection
 *
 */

/*
    1 - software
    2 - software using sbuffer
*/
#define PIPELINE_MAX_TEXTURES	8
#define PIPELINE_MAX_LIGHTS		255
#define PIPELINE_DRIVER_CLASS_INT 2


//#define PIPELINE_USE_DX8	1
#define PIPELINE_USE_DX9	1
//#define PIPELINE_USE_OPENGL	1

/**
 *	other config
 */
#define snprintf _snprintf
#define vsnprintf _vsnprintf


#define USE_STDAFX_HEADERS 1

#endif /* !defined(__OpenVRL_CONFIG_H_INCLUDED) */
