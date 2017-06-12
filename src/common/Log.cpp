#include <process.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <io.h>

#include "common/log.h"

namespace openvrl {

static CHAR string[128];

void ovrl_do_log(CHAR*s, real a, real b, real c)
{
  int f;
  if ( !s ) return;
  sprintf(string, "%s [%f, %f, %f]\n", s, a, b, c);
  f = open("log.txt", O_CREAT|O_WRONLY|O_APPEND|O_TEXT, S_IREAD|S_IWRITE);
  write(f, string, strlen(string));
  close(f);
}

void ovrl_assert(const CHAR*msg, const CHAR* cond, const CHAR* file, int line)
{
#if defined(_DEBUG)
	CHAR buf[512];
	sprintf(buf, "%s\nCondition: %s\nFile: %s\nAt Line: %lu\n",
		msg, cond, file, line);
	ovrl_warning(buf);
#else
	CHAR buf[512], ln[32];
	sprintf(buf, "%s\nCondition: %s", msg, cond);
	sprintf(ln, "%lu", line);
	ovrl_panic(buf, file, ln);
#endif
}

void ovrl_warning(const CHAR* msg)
{
#if !defined(__WINDOWS__)
        fprintf(stderr, "WARNING: %s\n", msg);
#else
		if ( MessageBox(0, msg, "OpenVRL Warning!", MB_YESNOCANCEL)==IDNO )
			exit(-1);
#endif
}

void ovrl_error(const CHAR* msg)
{
#if !defined(__WINDOWS__)
        fprintf(stderr, "ERROR: %s\n", msg);
#else
		MessageBox(0, msg, "OpenVRL Error!", MB_OK);
#endif
        exit(-1);
}

void ovrl_fatal(const CHAR* msg, const CHAR* src, const CHAR* ln)
{
#if !defined(__WINDOWS__)
        fprintf(stderr, "FATAL: %s\nFATAL: file: %s\nFATAL: line: %s\nABORTING...\n",
                       msg, src, ln);
#else
		char buf[128];
        sprintf(buf, "FATAL: %s\nFATAL: file: %s\nFATAL: line: %s\nABORTING...\n",
                       msg, src, ln);
		MessageBox(0, buf, "OpenVRL Fatal Error!", MB_OK);
#endif
        exit(-1);
}

void ovrl_panic(const CHAR* msg, const CHAR* src, const CHAR* ln)
{
#if !defined(__WINDOWS__)
        fprintf(stderr, "PANIC: %s\nPANIC: file: %s\nPANIC: line: %s\nBYE bye...\n",
                       msg, src, ln);
#else
		char buf[128];
        sprintf(buf, "PANIC: %s\nPANIC: file: %s\nPANIC: line: %s\nBYE bye...\n",
                       msg, src, ln);
		MessageBox(0, buf, "OpenVRL Panic!", MB_OK);
#endif
        exit(-1);
}



/********************************************************************/
/**
 *
 */
static WORD ovrl_dump_hex_line(FILE* __fp, const BYTE* lz, WORD cb, WORD cb1, bool spaces)
{
        DWORD i;

        cb = (cb>cb1)?cb1:cb;
        if ( spaces ) {
                for ( i=0;i<cb;i++ ) fprintf(__fp, " %02X", lz[i]);
                if ( i<cb1 ) for ( i*=3;i<cb1*3;i++ ) fprintf(__fp, " ");
        } else {
                for ( i=0;i<cb;i++ ) fprintf(__fp, "%02X", lz[i]);
                if ( i<cb1 ) for ( i*=2;i<cb1*2;i++ ) fprintf(__fp, " ");
        }

        return i;
}

static WORD ovrl_dump_hex_line_p(FILE* __fp, const BYTE* lz, WORD cb)
{
        DWORD i;
        cb = (cb<=16)?cb:16;
        fprintf(__fp, "%08lX |", (DWORD)lz);
//        for ( i=0;i<cb;i++ ) fprintf(__fp, " %02X", lz[i]);
//        if ( i<16 ) for ( i*=3;i<16*3;i++ ) fprintf(__fp, " ");
        ovrl_dump_hex_line(__fp, lz, cb, 16, true);
        fprintf(__fp, " | ");
        for ( i=0;i<cb;i++ ) fprintf(__fp, "%c", (lz[i]>=' ')?lz[i]:'.');
        if ( i<16 ) for ( ;i<16;i++ ) fprintf(__fp, " ");
        fprintf(__fp, " |\n");

        return i;
}

/**
 *
 */
void OVRLIBAPI ovrl_dump(const void* dump, DWORD size)
{
        ovrl_dump_ex(stdout, dump, size, DUMP_PLAIN);
}

void OVRLIBAPI ovrl_dump_to_file(const CHAR* file, const void* dump, DWORD size)
{
        ovrl_dump_to_file_ex(file, 0, dump, size, DUMP_PLAIN);
}


/**
 */
void OVRLIBAPI ovrl_dump_str(const CHAR* dump)
{
        ovrl_dump_str_ex(stdout, dump, DUMP_PLAIN);
}

void OVRLIBAPI ovrl_dump_str_ex(FILE* where, const CHAR* dump, uint how)
{
        ovrl_dump_ex(where, dump, strlen(dump), how);
}

void OVRLIBAPI ovrl_dump_str_to_file(const CHAR* file, const CHAR* dump)
{
        ovrl_dump_str_to_file_ex(file, 0, dump, DUMP_PLAIN);
}

void OVRLIBAPI ovrl_dump_str_to_file_ex(const CHAR* file, uint flags, const CHAR* dump, uint how)
{
        ovrl_dump_to_file_ex(file, flags, dump, strlen(dump), how);
}

void OVRLIBAPI ovrl_dump_to_file_ex(const CHAR* file, uint flags, const void* dump, DWORD size, uint how)
{
        FILE* f;
        f = fopen(file, "a+");
        if ( f==0 ) return;
		ovrl_dump_ex(f, dump, size, how);
		fflush(f);
        fclose(f);
}

void OVRLIBAPI ovrl_dump_to_file_ex1(const CHAR* file, uint flags, const void* dump, DWORD size, dump_callback_t callback)
{
        FILE* f;
        f = fopen(file, "a+");
        if ( f==0 ) return;
        ovrl_dump_ex1(f, dump, size, callback);
        fclose(f);
}

/**
 *
 */
void OVRLIBAPI ovrl_dump_ex(FILE* where, const void* dump, DWORD size, uint how)
{
        DWORD i;
        if ( how == DUMP_PLAIN )
           for ( i=0;i<size;i++ ) fputc( ((BYTE*)dump)[i], where );
        else if ( how == DUMP_HEX )
        {
           i = 0;
           fprintf(where, "BEGIN dump of address 0x%08lX of size %lu bytes\n", dump, size);
           while ( i<size ) i+=ovrl_dump_hex_line_p(where, ((BYTE*)dump)+i, ((size-i)<=16)?(size-i):16);
        } else if ( how == DUMP_HEX_PLAIN )
        {
           i = 0;
           fprintf(where, "BEGIN dump of address 0x%08lX of size %lu bytes\n", dump, size);
           while ( i<size ) {
                 fprintf(where, "$");
                 i+=ovrl_dump_hex_line(where, ((BYTE*)dump)+i, ((size-i)<=32)?(size-i):32, 32, false);
                 fprintf(where, "$\n");
           }
        }
}

void OVRLIBAPI ovrl_dump_ex1(FILE* where, const void* dump, DWORD size, dump_callback_t callback)
{
        DWORD cb, cb1;
        BYTE *ptr;

        if ( where==0 ) return;
        ptr = (BYTE*)dump;
        cb = 0;
        cb1 = 1;
        while ( cb<size && cb1!=0 ) {
              cb1 = ( *callback )(where, ptr+cb);
              cb += cb1;
        }
}
}