/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/tplconf.h,v $
 * $Implementation:  $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/03/09 12:24:08 $
 * $Description: *.tpl library's configuration $
 *
 * Revision 0.1  20010919  17:56:12 FoxiE
 * Pradejau rasyti logus :)
 *
 */


#if !defined(__tpl_TPLCONFIG_H)
#define __tpl_TPLCONFIG_H

#include "tpllib/tpltypes.h"
#include "common/defs.h"

#if !defined(TPLPLUGIN)
#define TPLPLUGIN(T) virtual T
#endif

#if !defined(TPLPLUGIN1)
#define TPLPLUGIN1(T) T CTPLLib::
#endif

#if !defined(TPLPLUGIN1c)
#define TPLPLUGIN1c CTPLLib::
#endif
#if !defined(TPLPLUGIN1d)
#define TPLPLUGIN1d CTPLLib::~
#endif

/**
 *  Version number  xxyyzzww
 *   xx - major version
 *   yy - minor version
 *   zz - bugfix
 *   ww - port
 */
#define TPL_VERSION                    0x0001000a
#define TPL_VERSION_STR                "00.01.00.a"

/**
 *
 */
#define TPL_OS 		"Windows9x"

#define TPL_PORTED_BY	"Andrius Mikonis a.k.a. FoxiE"

#define TPL_RELEASE_DATE "2002 08 15"

#define TPL_LAST_BUILD_DATE __DATE__

/**
 *  Template file signature
 */
#define TPL_MAX_SIG_LEN                4
#define TPL_MAX_NAME_LEN               32
#define TPL_HDR_SIZE                   256

/**
 *
 */
#define TPL_MATERIAL_MAX_MAPS           13
#define TPL_LIGHT_MAX_MAPS		4
#define TPL_LIGHT_MAX_ATTENUATIONS 	4


/****************************************************************************
 *  Template: configuration
 *
 ***************************************************************************/

/**
 *  includes support for TPL file header
 */
#define TPL_SUPPORTED_HEADER

/**
 *  includes support for Material storage in tpl
 */
#define TPL_SUPPORTED_MATERIALS

/**
 *  includes support for Lights storage in tpl
 */
#define TPL_SUPPORTED_LIGHTS

/**
 *  includes support for Texture storage in tpl
 */
#define TPL_SUPPORTED_TEXTURES

/**
 *  includes support for Lights storage in tpl
 */
#define TPL_SUPPORTED_CAMERAS

/**
 *  includes support for RAW mesh storage in tpl
 */
#define TPL_SUPPORTED_RAW_MESHES

/**
 *  includes support for terrain mesh storage in tpl
 */
//#define TPL_SUPPORTED_TERRAIN


//
//
//
#if !defined(__EXPORT) && !defined(__IMPORT)
#if defined(__STATIC_OVRL)
#define __EXPORT
#define __IMPORT
#define OVRLIBAPI 
#else
#define __EXPORT __declspec(dllexport)
#define __IMPORT __declspec(dllimport)
#endif
#endif

#if defined(_USRDLL)
#define TPL_API __EXPORT
#else
#if !defined(__STATIC_OVRL)
#define TPL_API __IMPORT
#else
#define TPL_API
#endif
#endif

#if defined(_DEBUG)
#define TPL_ASSERT OVRL_ASSERT
#else
// just a hack...
#define TPL_ASSERT(a) if (a) ;
#endif


#define TPL_memset(d,i,n) OVRL_memset(d,i,n)
#define TPL_memcpy(d,s,n) OVRL_memcpy(d,s,n)

//
// Disable those annoying "debug symbol truncated to 255" warnings
//
#pragma warning( disable : 4786 )

//
// disable dll-interface warnings, (they bug me off :])
//
#if !defined(__STATIC_OVRL)
#pragma warning( disable : 4251 )
#endif

#endif /* if !defined(__TPLCONFIG_H) */
