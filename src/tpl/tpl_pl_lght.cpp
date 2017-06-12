#include <string.h>
#include "tpllib/tpl.hpp"

namespace openvrl {


/**
 *
 */
TPLPLUGIN1(int) read_lights()
{
	TPL_ulong cb=0, cb1=0;
	TPL_DWORD n;
	TPL_ulong i;
	TPL_LIGHT m;

	if ( light_offs==0 ) return 0;

	light_buf.erase(light_buf.begin(), light_buf.end());
	devio->seek(light_offs, IOD_SEEK_SET);
	cb = devio->read(&n, sizeof(n));
	for ( i=0;i<n;i++ ) {
		TPL_memset(&m, 0, sizeof(m));
		cb1 = devio->read(&m, sizeof(m));
		TPL_ASSERT(cb1==sizeof(m));
		if ( strncmp(m.signature, TPL_LIGHT_SIG, TPL_MAX_SIG_LEN)!=0 ) break;
		TPL_ASSERT(m.version==TPL_LIGHT_VERSION);
		light_add(m);
		cb+=cb1;
	}
	return 0;
}

/**
 *
 */
TPLPLUGIN1(TPL_ulong) write_lights(TPL_DWORD offs)
{
	TPL_ulong cb=0;
	TPL_ulong i;
	TPL_DWORD n;
	devio->seek(offs, IOD_SEEK_SET);
	light_offs = offs;
	n = light_buf.size();
	cb += devio->write(&n, sizeof(n));
	for ( i=0;i<light_buf.size();i++ ) {
		cb += devio->write(light(i), sizeof(TPL_LIGHT));
	}

	return cb;
}

/**
 *
 */
TPLPLUGIN1(int) light_ctor()
{
	light_offs = 0;
	return 0;
}

TPLPLUGIN1(int) light_dtor()
{
	light_buf.erase(light_buf.begin(), light_buf.end());
	return 0;
}

/**
 *
 */
TPLPLUGIN1(int) light_read(TPL_LIGHT* m, TPL_ulong index)
{
	if ( index>=light_buf.size() ) return 1;
	*m = light_buf[index];
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) light_write(const TPL_LIGHT& m, TPL_ulong index)
{
	if ( index>=light_buf.size() ) return 1;
	light_buf[index] = m;
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) light_add(const TPL_LIGHT& m)
{
	light_buf.insert(light_buf.begin(), m);
	return 0;
}

TPLPLUGIN1(int) light_insert(const TPL_LIGHT& m, TPL_ulong index)
{
	if ( index>=light_buf.size() ) return 1;
	light_buf.insert(light_buf.begin() +index, m);
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) light_delete(TPL_ulong index)
{
	if ( index>=light_buf.size() ) return 1;
	light_buf.erase(light_buf.begin() +index);
	return 0;
}

}