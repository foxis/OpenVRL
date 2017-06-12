/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/iosystem/fileiodev.h,v $
 * $Implementation: ~/src/fileiodev.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:14 $
 * $Description: A Class for a std file system IO $
 *
 * $Log: fileiodev.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:14  foxis
 * sources import
 *
 * Revision 0.1  20011226  19:30:48 FoxiE
 * :)
 *
 */



#if !defined(__FILEIODEV_HPP)
#define __FILEIODEV_HPP

#include "common/all.h"
#include "iosystem/iodevice.h"

namespace openvrl {

/**
 *
 */
class OVRLIBAPI CFileIOD : public IIODevice {
       int              mFile;
       CHAR*            mPath;

public:
        CFileIOD() : IIODevice()
        {
          mPath = 0;
          mFile = 0;
        }

        CFileIOD(ulong buf_sz) : IIODevice(buf_sz)
        {
          mPath = 0;
          mFile = 0;
        }

        CFileIOD(ulong buf_sz, BYTE *buf) : IIODevice(buf_sz, buf)
        {
          mPath = 0;
          mFile = 0;
        }

        virtual ~CFileIOD()
        {
             close();
        }

        virtual int open(const CHAR* path, uint access);
        virtual int create(const CHAR* path, uint access);
        virtual int create_new(const CHAR* path, uint access);
        virtual ulong write(const void* buf, ulong size);
        virtual ulong read(void* buf, ulong size);
        virtual ulong seek(ulong pos, uint how);
        virtual ulong tell() const;
        virtual ulong length() const;
        virtual int flush();
        virtual int close();

        virtual int lock();
        virtual int unlock();
        virtual int exists(const CHAR* path) const;
        virtual int reset();
        virtual int remove(const CHAR* path);

        virtual char* get_name() const
        {
                return "OS-Independent FileSystem IO";
        }
        virtual IO_DEV_TYPE_t get_type() const
        {
                return IODEV_IMAGE;
        }
        virtual DWORD get_caps() const
        {
                return IOD_CAPS_READ|IOD_CAPS_WRITE|IOD_CAPS_SEEK|
                       IOD_CAPS_CREATE|IOD_CAPS_EXECUTE|IOD_CAPS_TRUNCATE;
        }
};

};

#endif /* !defined(__FILEIODEV_HPP */
