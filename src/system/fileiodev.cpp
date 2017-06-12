#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#include "iosystem/iosystem.h"

namespace openvrl {



int CFileIOD::open(const CHAR* path, uint access)
{
	uint a=0;
        if ( mFile>0 ) return 1;

	if ( access&IOD_RDONLY ) a |= O_RDONLY;
	if ( access&IOD_WRONLY ) a |= O_WRONLY;
	if ( access&IOD_TRUNC ) a |= O_TRUNC;
	if ( access&IOD_RDWR ) a |= O_RDWR;
#if !defined(__WINDOWS__)
        if ( (mFile = ::open(path, a|O_BINARY))<1 ) return 1;
#else
        if ( (mFile = ::open(path, a|O_BINARY))<1 ) return 1;
#endif /* !defined(__WINDOWS__) */
        if ( (mPath = new CHAR[strlen(path)+1])==0 ) return 1;
        strcpy(mPath, path);
        flush();
        return 0;
}

int CFileIOD::create(const CHAR* path, uint access)
{
	uint a=0;
        if ( mFile>0 ) return 1;
	if ( access&IOD_RDONLY ) a |= O_RDONLY;
	if ( access&IOD_WRONLY ) a |= O_WRONLY;
	if ( access&IOD_TRUNC ) a |= O_TRUNC;
	if ( access&IOD_RDWR ) a |= O_RDWR;
#if !defined(__WINDOWS__)
        if ( (mFile = ::open(path, a|O_BINARY|O_CREAT, S_IREAD|S_IWRITE))<1 ) return 1;
#else
        if ( (mFile = ::open(path, a|O_BINARY|O_CREAT, S_IREAD|S_IWRITE))<1 ) return 1;
#endif /* !defined(__WINDOWS__) */
        mPath = new CHAR[strlen(path)+1];
        strcpy(mPath, path);
        flush();
        return 0;
}

int CFileIOD::create_new(const CHAR* path, uint access)
{
	uint a=0;
	if ( mFile>0 ) return 1;
	if ( access&IOD_RDONLY ) a |= O_RDONLY;
	if ( access&IOD_WRONLY ) a |= O_WRONLY;
	if ( access&IOD_TRUNC ) a |= O_TRUNC;
	if ( access&IOD_RDWR ) a |= O_RDWR;
#if !defined(__WINDOWS__)
        if ( (mFile = ::open(path, a|O_TRUNC|O_BINARY|O_CREAT, S_IREAD|S_IWRITE))<1 ) return 1;
#else
        if ( (mFile = ::open(path, a|O_TRUNC|O_BINARY|O_CREAT, S_IREAD|S_IWRITE))<1 ) return 1;
#endif /* !defined(__WINDOWS__) */
        mPath = new CHAR[strlen(path)+1];
        strcpy(mPath, path);
        flush();
        return 0;
}

ulong CFileIOD::write(const void* buf, ulong size)
{
        ulong len, len1, i;
        if ( mFile<1 ) return 0;

        if ( buf_ptr==0 )
        {
                return ::write(mFile, buf, size);
        } else {
                len1 = buf_read - buf_pos;
                if ( size < len1 )
                {
                  memcpy(buf_ptr+buf_pos, buf, size);
                  buf_pos += size;
                  return size;
                } else
                {
                  i = 0;
                  while ( size > len1 ) {
                    len = buf_read - buf_pos;
                    memcpy(buf_ptr+buf_pos, ((BYTE*)buf)+i, len);
                    i += len;
                    size-= len;
                    if ( flush() ) return i;
                  }
                  memcpy(buf_ptr+buf_pos, ((BYTE*)buf)+i, size);
                  buf_pos += size;
                  return i;
                }
        }
        return 1;
}

ulong CFileIOD::read(void* buf, ulong size)
{
        ulong len, len1, i;
        if ( mFile==0 ) return 0;

        if ( buf_ptr==0 )
        {
                return ::read(mFile, buf, size);
        } else
        {
                len1 = buf_read - buf_pos;
                if ( size < len1 )
                {
                  memcpy(buf_ptr+buf_pos, buf, size);
                  buf_pos += size;
                  return size;
                } else
                {
                  i = 0;
                  while ( size > len1 ) {
                        len = buf_read - buf_pos;
                        memcpy(buf_ptr+buf_pos, ((BYTE*)buf)+i, len);
                        i += len;
                        size-= len;
                        if ( flush() )   return i;
                  }
                  memcpy(buf_ptr+buf_pos, ((BYTE*)buf)+i, size);
                  buf_pos += size;
                  return i;
                }
        }
}

ulong CFileIOD::seek(ulong pos, uint how)
{
//        ulong len;
        if ( mFile==0 ) return 0;

        if ( buf_ptr==0 )
        {
                return ::lseek(mFile, pos, how);
        } else
        {
                switch ( how ) {
                  case SEEK_SET:
                    if ( pos<dev_pos || pos>dev_pos+buf_read )
                       flush();
                    dev_pos = pos;
                    flush();
                    break;

                  case SEEK_END:
//                    if ( pos<H(h)->dev_pos || pos>(H(h)->dev_pos+H(h)->buf_pos) )
//                       devio_flush(h);
//                    H(h)->dev_pos = pos;
                    flush();
                    break;

                  case SEEK_CUR:
                    if ( pos+buf_pos>dev_pos+buf_read )
                       flush();
                    dev_pos = buf_pos+pos;
                    flush();
                    break;

                  default:
                    return ( dev_pos+buf_pos );
                }
        }
        return 0;
}

ulong CFileIOD::tell() const
{
        return ::tell(mFile);
}

ulong CFileIOD::length() const
{
        ulong p, l;
        p = tell();
        l = lseek(mFile, 0, IOD_SEEK_END);
        lseek(mFile, p, SEEK_SET);
        return l;
}

int CFileIOD::flush()
{
//        ulong len;
        if ( mFile==0 ) return 1;

        if ( buf_ptr==0 )
        {
//                ::flush(mFile);
                return 0;
        } else
        {
//                if ( H(h)->modified )
//                  if ( H(h)->device->flush(hd, H(h)->dev_pos, H(h)->buf_ptr, H(h)->buf_read, FLUSH_WRITE) ) return 1;
//                if ( H(h)->device->seek(hd, H(h)->dev_pos, SEEK_SET, &(H(h)->dev_pos)) ) return 1;
//                if ( H(h)->device->read(hd, H(h)->buf_ptr, H(h)->buf_size, &(H(h)->buf_read)) ) return 1;
                buf_pos = 0;
        }
        return 0;
}

int CFileIOD::close()
{
        flush();
        ::close(mFile);
        mFile = 0;
        delete[] mPath;
        mPath = 0;
        return 0;
}

int CFileIOD::lock()
{
  return 1;
}
int CFileIOD::unlock()
{
  return 1;
}

int CFileIOD::exists(const CHAR* path) const
{
  return 0;
}

int CFileIOD::reset()
{
  return 1;
}

int CFileIOD::remove(const CHAR* path)
{
  return 1;
}


}