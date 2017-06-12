/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/defs.h,v $
 * $Implementation: $
 * $Revision: 1.4 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:07 $
 * $Description:  $
 *
 * $Log: defs.h,v $
 * Revision 1.4  2005/07/14 12:14:07  foxis
 * no message
 *
 * Revision 1.3  2005/03/01 18:21:15  foxis
 * Pipeline: shadows now working more or less. need to handle special cases.
 * C4x4Matrix: added inverse method + others
 *
 * Revision 1.2  2005/02/02 20:40:56  foxis
 * Basic ODE support - seems to work ok
 * basic CBody - seems to work
 * basic system overall - seems to work :)
 *
 * minor bugfixes, and changes in body managment code
 *
 * Revision 1.1.1.1  2005/02/02 15:39:11  foxis
 * sources import
 *
 * Revision 0.5  20010719  15:57:59 FoxiE
 * Idejau makrosus WINdows sistemai palaikyti...
 *
 * Revision 0.4  20010515  20:13:22 FoxiE
 * Idejau ONINTERVAL ir INSIDERECT, INSIDERECT1
 *
 * Revision 0.3  20010427  14:56:46 FoxiE
 * Kvaila klaida _16BIT_TO_RGB makrose,
 * (b) komponente stumti reikejo 5 bitais, o ne 4
 *
 * Revision 0.2  20010425  19:44:23 FoxiE
 * Kvaila klaida RGB_TO_32BIT makrose,
 * (r) komponente stumti reikejo 16 bitu, o ne 10(galvojau kad rasau hex) :-)
 *
 * Revision 0.1  20010409  11:52:40 FoxiE
 * Pradejau rasyti logus :)
 *
 */



#if !defined(__ovrl_DEFS_H)
#define __ovrl_DEFS_H

#include "config.h"

#if defined(__WINDOWS__)
#include <windows.h>
//#include <windowex.h>
#endif

#if !defined(NULL)
#       define NULL   0
#endif

#if !defined(FALSE)
#       define FALSE  0
#       define TRUE   1
#endif

#if defined(__STATIC_OVRL)
#define __EXPORT
#define __IMPORT
#define OVRLIBAPI 
#else
#define __EXPORT __declspec(dllexport)
#define __IMPORT __declspec(dllimport)
#endif

#if defined(__DYNAMIC_OVRL)
#define OVRLIBAPI __EXPORT
#else
#if !defined(__STATIC_OVRL)
#define OVRLIBAPI __IMPORT
#endif
#endif

//#if defined(_FASTTHIS) && !defined(__FLAT__)
//#       define __FASTTHIS __fastthis
//#else
//#       define __FASTTHIS
//#endif /* if defined(_FASTTHIS) && !defined(__FLAT__) */
//#if defined(__cplusplus)
//#      if !defined(__IMPORT_CLASSES)
//#               define OVRLIBCLASS __EXPORT __FASTTHIS
//#      else
//#               define OVRLIBCLASS __IMPORT __FASTTHIS
//#      endif /* ifdef __EXPORT_CLASSES */
//#endif /* ifdef __cplusplus */
//#else /* !defined(__WINDOWS__) && !defined(__WIN32__) */
//#define OVRLIBAPI
//#if !defined(__EXPORT)
//#define __EXPORT
//#endif
//#if !defined(__IMPORT)
//#define __IMPORT
//#endif

//#if defined(_FASTTHIS) && !defined(__FLAT__)
//#       define __FASTTHIS __fastthis
//#else
//#       define __FASTTHIS
//#endif /* if defined(_FASTTHIS) && !defined(__FLAT__) */

//#if defined(__cplusplus)
//#      if !defined(__IMPORT_CLASSES)
//#               define OVRLIBCLASS __EXPORT __FASTTHIS
//#      else
//#               define OVRLIBCLASS __IMPORT __FASTTHIS
//#      endif /* ifdef __EXPORT_CLASSES */
//#endif /* ifdef __cplusplus */

//#endif /* !defined(__WINDOWS__) && !defined(__WIN32__) */


/************************************************************************/
/* some usefull macros...                                               */
#define OVRL_INT2FIXED(a)  ( (OVRL_fixed)( (OVRL_fixed)(a) << 16L ) )
#define OVRL_FIXED2INT(a)  ( (OVRL_fixed)( (a) >> 16L ) )
#define OVRL_FLOAT2FIXED(a)  ( (OVRL_fixed)( (a) * 65536L ) )
#define OVRL_FIXED2FLOAT(a)  ( ((OVRL_fixed)(a)) / 65536.0 )
#define OVRL_SWAP(a,b)  { (a)^=(b); (b)^=(a); (a)^=(b); }
#define OVRL_SWAP1(a,b,c) { c=a; a=b; b=c; }
#define OVRL_MAX(a,b) ( ((a)>(b))?(a):(b) )
#define OVRL_MIN(a,b) ( ((a)<(b))?(a):(b) )
#define OVRL_MIN3(a, b, c) ( ((a)<(b) && (a)<(c))?(a):( ((b)<(a) && (b)<(c))?(b):(c) ) )
#define OVRL_MAX3(a, b, c) ( ((a)>(b) && (a)>(c))?(a):( ((b)>(a) && (b)>(c))?(b):(c) ) )
#define OVRL_BYTEHI(b) (OVRL_BYTE)( (OVRL_WORD)(b)>>8 )
#define OVRL_BYTELO(b) (OVRL_BYTE)( (OVRL_WORD)(b)&0xff )
#define OVRL_WORDHI(w) (OVRL_WORD)( (OVRL_DWORD)(b)>>16 )
#define OVRL_WORDLO(w) (OVRL_WORD)( (OVRL_DWORD)(b)&0xffff )
#define OVRL_MK_FPTR(seg, ofs) ( (void*)((OVRL_DWORD)(seg)<<16L | (OVRL_WORD)(ofs)) )

#define OVRL_ONINTERVAL(a,b,c) ( (a)>=(b) && (a)<=(c) )
#define OVRL_ININTERVAL(a,b,c) ( (a)>(b) && (a)<(c) )
#define OVRL_INSIDERECT(x,y,x1,y1,x2,y2) \
        ( OVRL_ONINTERVAL(x,OVRL_MIN(x1,x2),OVRL_MAX(x1,x2)) && \
          OVRL_ONINTERVAL(y,OVRL_MIN(y1,y2),OVRL_MAX(y1,y2)) \
        )
#define OVRL_INSIDERECT1(p,p1,p2) \
        ( OVRL_ONINTERVAL(p.x,OVRL_MIN(p1.x,p2.x),OVRL_MAX(p1.x,p2.x)) && \
          OVRL_ONINTERVAL(p.y,OVRL_MIN(p1.y,p2.y),OVRL_MAX(p1.y,p2.y)) \
        )
#define OVRL_OUTSIDERECT(x,y,x1,y1,x2,y2) ( !OVRL_INSIDERECT(x,y,x1,y1,x2,y2) )
#define OVRL_OUTSIDERECT1(p,p1,p2) ( !OVRL_INSIDERECT1(p,p1,p2) )

#define OVRL_RGB_TO_15BIT(r,g,b) (OVRL_WORD)(((OVRL_DWORD)(b)&0x1f) | (((OVRL_DWORD)(g)&0x1f)<<5L) | (((DWORD)(r)&0x1f)<<10L))
#define OVRL_RGB_TO_16BIT(r,g,b) (OVRL_WORD)(((OVRL_DWORD)(b)&0x1f) | (((OVRL_DWORD)(g)&0x3f)<<5L) | (((DWORD)(r)&0x1f)<<11L))
#define OVRL_RGB_TO_32BIT(r,g,b) (OVRL_DWORD)(((OVRL_DWORD)(b)&0xff) | (((OVRL_DWORD)(g)&0xff)<<8L) | (((DWORD)(r)&0xff)<<16L))
#define OVRL__15BIT_TO_RGB(a) (((OVRL_DWORD)(a)&0x1f) | (((OVRL_DWORD)(a)&0x3e0)<<3) | (((DWORD)(a)&0x7c00)<<6))
#define OVRL_16BIT_TO_RGB(a) (((OVRL_DWORD)(a)&0x1f) | (((OVRL_DWORD)(a)&0x7e0)<<3) | (((DWORD)(a)&0xf800)<<5))

#define SWAP_WORDS(a) ( (((OVRL_DWORD)(a)>>16)&0x0000ffff) | (((OVRL_DWORD)(a)<<16)&0xffff0000) )
#define SWAP_BYTES(a) ( (((OVRL_WORD)(a)>>8)&0x00ff) | (((OVRL_WORD)(a)<<8)&0xff00) )

#define OVRL_memcpy(d, s, n) memcpy(d, s, n)
#define OVRL_memmove(d, s, n) memmove(d, s, n)
#define OVRL_memset(d, c, n) memset(d, c, n)

#if !defined(random)
#define OVRL_random(num) (uint)(((ulong)rand()*(num))/(RAND_MAX+1))
#if !defined(__WINDOWS__)
#define OVRL_randomize()     srand(clock())
#else
#define OVRL_randomize()     srand(GetTickCount())
#endif // !defined(__WINDOWS__)
#endif // !defined(random)

#define OVRL_DELETE(VAR) { if ( VAR!=0 ) delete VAR; VAR = 0; }
#define OVRL_DELETE1(VAR) { if ( VAR!=0 ) delete[] VAR; VAR = 0; }
#define OVRL_NEW(T, CB) new T[(CB)]
#define OVRL_NEW_EX(VAR, T, CB) if ( CB ) {VAR = new T[CB]; OVRL_ASSERT_EX(VAR, MEMORY, "Failed alocating array of type ##T##" );} else VAR = 0;
//#define OVRL_NEW(VAR, T, CB, ERR) (VAR) = new (T)[(CB)]; OVRL_ASSERT(VAR, ERR)
//#define OVRL_NEW1(VAR, T, ERR) { VAR = new (T); OVRL_ASSERT(VAR, ERR) }
//#define OVRL_NEW_EX(VAR, T, CB) VAR = new (T)[CB];
//#define OVRL_NEW1_EX(VAR, T) VAR = new (T);
#define OVRL_COPY(DST, SRC, T, CB, ERR) if ( DST!=0 ) __memcpy(DST, SRC, sizeof(T)*(CB)); else ERR;
#define OVRL_COPY_EX(DST, SRC, T, CB) __memcpy(DST, SRC, sizeof(T)*(CB));
#define OVRL_RETURN(SMTH)    {return SMTH;}
#define OVRL_ISSTREMPTY(s) ((s)==0 || (*(s))==0)

#if defined(_DEBUG)
	#define OVRL_ASSERT(val) \
		openvrl::CException::exception_assert((val)==0, openvrl::CException::GENERAL, "", __FILE__, __LINE__) 
	#define OVRL_ASSERT_EX(val, type, msg) \
		openvrl::CException::exception_assert((val)==0, openvrl::CException::type, msg, __FILE__, __LINE__) 
	#define OVRL_BOUNDARY_ASSERT(i,min,max)	\
		openvrl::CException::exception_assert(i,min,max,"",__FILE__,__LINE__)
#else
	#define OVRL_ASSERT(a)
	#define OVRL_ASSERT_EX(val, type, msg) 
	#define OVRL_BOUNDARY_ASSERT(i,min,max)	
#endif

#if !defined(MAKEFOURCC)
#define MAKEFOURCC(ch0, ch1, ch2, ch3) ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) | ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))
#endif

//
// Disable those annoying "debug symbol truncated to 255" warnings
//
#pragma warning( disable : 4786 )

//
// disable dll-interface warnings, (they bug me off :])
//
#if !defined(__STATIC_OVRL)
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
//
// " '' storage-class or type specifier(s) unexpected here; ignored" warning
//
#pragma warning( disable : 4518 )
#endif

#endif /* ifndef __DEFS_H */
