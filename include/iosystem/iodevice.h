/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/iosystem/iodevice.h,v $
 * $Implementation:  $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/03/09 12:24:08 $
 * $Description: Constant class for IO devices $
 *
 * $Log: iodevice.h,v $
 * Revision 1.2  2005/03/09 12:24:08  foxis
 * . fixed memory leaks
 * . fixed OVRL_ASSERT issue in release mode
 *   [still to fix: TPL_ASSERT, now - just a hack]
 *
 * Revision 1.1.1.1  2005/02/02 15:39:14  foxis
 * sources import
 *
 * Revision 0.1  20011226  19:30:48 FoxiE
 * :)
 *
 */



#if !defined(__ovrl_IODEVICE_HPP)
#define __ovrl_IODEVICE_HPP

#include "common/all.h"

namespace openvrl {

/**  IO device type
 *
 * IODEV_IMAGE          - can be seeked, written, read, extended, etc
 * IODEV_STREAM         - can not be seeked read/write
 * IODEV_TTY            - can not be seeked, read/write
 *
 */
enum IO_DEV_TYPE_enum
{
        IODEV_IMAGE                     = 0,
        IODEV_STREAM                    = 1,
        IODEV_TTY                       = 2,
        IODEV_FORCE_DWORD               = 0xFFFFFFFF
};
typedef enum IO_DEV_TYPE_enum IO_DEV_TYPE_t;

/* permission flags */
#define IOD_PERM_READ           0x0001  /* can be read */
#define IOD_PERM_WRITE          0x0002  /* can be written */
#define IOD_PERM_READWRITE      0x0004  /* can be both read and written */
#define IOD_PERM_EXECUTE        0x0000  /* can be executed */


/* device creation flags */
#define IOD_RDONLY        0x0001  /* open for read only */
#define IOD_WRONLY        0x0002  /* open for write only */
#define IOD_RDWR          0x0004  /* open for read and write */
#define IOD_EXCL          0x0400  /* exclusive open */
#define IOD_APPEND        0x0800  /* writes done at end of file */
#define IOD_CREAT         0x0100  /* create new file */
#define IOD_TRUNC         0x0200  /* truncate existing file */
#define IOD_NOINHERIT     0x0080  /* file is not inherited by child process */
#define IOD_TEXT          0x4000  /* text file */
#define IOD_BINARY        0x8000  /* binary file */

/* seek flags */
#define IOD_SEEK_SET 0           /* Seek relative to the start of file   */
#define IOD_SEEK_END 1           /* Seek relative to current position    */
#define IOD_SEEK_CUR 2           /* Seek relative to the end of the file */

/* flush flags */
#define FLUSH_WRITE     0x00000001
#define FLUSH_READ      0x00000002

/* IODEV capabilities */
#define IOD_CAPS_READ           0x00000001
#define IOD_CAPS_WRITE          0x00000002
#define IOD_CAPS_SEEK           0x00000004
#define IOD_CAPS_EXECUTE        0x00000008
#define IOD_CAPS_TRUNCATE       0x00000010
#define IOD_CAPS_CREATE         0x00000020


/**
 *
 */
class OVRLIBAPI IIODevice {
protected:
       ulong            buf_size;
       ulong            buf_pos;
       ulong            dev_pos;
       ulong            buf_read;
       BYTE            *buf_ptr;

public:
        IIODevice()
        {
          buf_size = IODEV_DEF_BUF_SIZE;
          buf_pos = 0;
          dev_pos = 0;
          buf_read = 0;
          OVRL_NEW_EX(buf_ptr,BYTE,buf_size);
        }
        IIODevice(ulong buf_sz)
        {
          buf_size = buf_sz;
          buf_pos = 0;
          dev_pos = 0;
          buf_read = 0;
          OVRL_NEW_EX(buf_ptr,BYTE,buf_size);
        }
        IIODevice(ulong buf_sz, BYTE *buf)
        {
          buf_size = buf_sz;
          buf_pos = 0;
          dev_pos = 0;
          buf_read = 0;
          buf_ptr = buf;
        }
        virtual ~IIODevice()
        {
          OVRL_DELETE(buf_ptr);
        }

        virtual int open(const CHAR* path, uint access) = 0;
        virtual int create(const CHAR* path, uint access) = 0;
        virtual int create_new(const CHAR* path, uint access) = 0;
        virtual ulong write(const void* buf, ulong size) = 0;
        virtual ulong read(void* buf, ulong size) = 0;
        virtual ulong seek(ulong pos, uint how) = 0;
        virtual ulong tell() const = 0;
        virtual ulong length() const = 0;
        virtual int flush() = 0;
        virtual int close() = 0;

        virtual int lock() = 0;
        virtual int unlock() = 0;
        virtual int exists(const CHAR* path) const = 0;
        virtual int reset() = 0;
        virtual int remove(const CHAR* path) = 0;

        virtual char* get_name() const = 0;
        virtual IO_DEV_TYPE_t get_type() const = 0;
        virtual DWORD get_caps() const = 0;
};

};

#endif /* !defined(__ovrl_IODEVICE_HPP) */
