/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/Log.h,v $
 * $Implementation: ~/src/lib/log.c $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:11 $
 * $Description: Debuginimui skirtas modulis... $
 *
 * $Log: Log.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:11  foxis
 * sources import
 *
 * Revision 0.4  20020107  20:22:21 FoxiE
 * visus prefixus pakeiciau i ovrl_
 *
 * Revision 0.3  20010818  16:16:22 FoxiE
 * pridejau OVRL_dump* funkcijas...
 *
 * Revision 0.2  20010428  17:04:23 FoxiE
 * parasiau OVRL_error, OVRL_warning, OVRL_panic, OVRL_fatal fun-jas.
 *
 * Revision 0.1  20010409  11:52:40 FoxiE
 * Pradejau rasyti logus :)
 *
 */


#if !defined(__ovrl_LOG_H)
#define __ovrl_LOG_H

#include "common/types.h"

namespace openvrl {

#if defined(DEBUG)
#define do_log(a, b, c, d) ovrl_do_log(a,b,c,d)
#else
#define do_log(a,b,c,d)
#endif

#define DUMP_PLAIN      1
#define DUMP_HEX        2
#define DUMP_HEX_PLAIN  3

typedef DWORD ( *dump_callback_t )(FILE* __fp, const void* data);

#if defined(__cplusplus)
extern "C" {
#endif

/**
 *  Iraso i log.txt cwd stringa ir tris sveikuosius skaicius...
 */
void OVRLIBAPI ovrl_do_log(CHAR*, real, real, real);

/**
 *
 */
void OVRLIBAPI ovrl_assert(const CHAR*msg, const CHAR* cond, const CHAR* file, int line);

/**
 *  Tells a warning to the user. Do not exit
 */
void OVRLIBAPI ovrl_warning(const CHAR* msg);

/**
 *  Tells about an error. Exits current thread;
 */
void OVRLIBAPI ovrl_error(const CHAR* msg);

/**
 *  Tells about a fatal error, terminates current procces immediatelly
 */
void OVRLIBAPI ovrl_fatal(const CHAR* msg, const CHAR* src, const CHAR* ln);

/**
 *  Tells about a kernel panic. shutdowns kernel
 */
void OVRLIBAPI ovrl_panic(const CHAR* msg, const CHAR* src, const CHAR* ln);


/**
 *  Data dumping fun-ons
 */
void OVRLIBAPI ovrl_dump(const void* dump, DWORD size);
void OVRLIBAPI ovrl_dump_ex(FILE* where, const void* dump, DWORD size, uint how);
void OVRLIBAPI ovrl_dump_to_file(const CHAR* file, const void* dump, DWORD size);
void OVRLIBAPI ovrl_dump_to_file_ex(const CHAR* file, uint flags, const void* dump, DWORD size, uint how);
void OVRLIBAPI ovrl_dump_ex1(FILE* where, const void* dump, DWORD size, dump_callback_t callback);
void OVRLIBAPI ovrl_dump_to_file_ex1(const CHAR* file, uint flags, const void* dump, DWORD size, dump_callback_t callback);
void OVRLIBAPI ovrl_dump_str(const CHAR* dump);
void OVRLIBAPI ovrl_dump_str_ex(FILE* where, const CHAR* dump, uint how);
void OVRLIBAPI ovrl_dump_str_to_file(const CHAR* file, const CHAR* dump);
void OVRLIBAPI ovrl_dump_str_to_file_ex(const CHAR* file, uint flags, const CHAR* dump, uint how);

#if defined(__cplusplus)
};
#endif

};

#endif /* !defined(__ovrl_LOG_H) */
