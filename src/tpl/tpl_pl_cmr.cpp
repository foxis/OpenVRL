#include <string.h>
#include "tpllib/tpl.hpp"

namespace openvrl {


/**
 *
 */
TPLPLUGIN1(int) read_cameras()
{
	TPL_ulong cb=0, cb1=0;
	TPL_DWORD n;
	TPL_ulong i;
	TPL_CAMERA m;

	if ( camera_offs==0 ) return 0;

	camera_buf.erase(camera_buf.begin(), camera_buf.end());
	devio->seek(camera_offs, IOD_SEEK_SET);
	cb = devio->read(&n, sizeof(n));
	for ( i=0;i<n;i++ ) {
		TPL_memset(&m, 0, sizeof(m));
		cb1 = devio->read(&m, sizeof(m));
		TPL_ASSERT(cb1==sizeof(m));
		if ( strncmp(m.signature, TPL_CAMERA_SIG, TPL_MAX_SIG_LEN)!=0 ) break;
		TPL_ASSERT(m.version==TPL_CAMERA_VERSION);
		camera_add(m);
		cb+=cb1;
	}
	return 0;
}

/**
 *
 */
TPLPLUGIN1(TPL_ulong) write_cameras(TPL_DWORD offs)
{
	TPL_ulong cb=0;
	TPL_ulong i;
	TPL_DWORD n;
	devio->seek(offs, IOD_SEEK_SET);
	camera_offs = offs;
	n = camera_buf.size();
	cb += devio->write(&n, sizeof(n));
	for ( i=0;i<camera_buf.size();i++ ) {
		cb += devio->write(camera(i), sizeof(TPL_CAMERA));
	}

	return cb;
}

/**
 *
 */
TPLPLUGIN1(int) camera_ctor()
{
	camera_offs = 0;
	return 0;
}

TPLPLUGIN1(int) camera_dtor()
{
	camera_buf.erase(camera_buf.begin(), camera_buf.end());
	return 0;
}

/**
 *
 */
TPLPLUGIN1(int) camera_read(TPL_CAMERA* m, TPL_ulong index)
{
	if ( index>=camera_buf.size() ) return 1;
	*m = camera_buf[index];
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) camera_write(const TPL_CAMERA& m, TPL_ulong index)
{
	if ( index>=camera_buf.size() ) return 1;
	camera_buf[index] = m;
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) camera_add(const TPL_CAMERA& m)
{
	camera_buf.insert(camera_buf.begin(), m);
	return 0;
}

TPLPLUGIN1(int) camera_insert(const TPL_CAMERA& m, TPL_ulong index)
{
	if ( index>=camera_buf.size() ) return 1;
	camera_buf.insert(camera_buf.begin() +index, m);
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) camera_delete(TPL_ulong index)
{
	if ( index>=camera_buf.size() ) return 1;
	light_buf.erase(light_buf.begin() +index);
	return 0;
}

}