#include <string.h>
#include "tpllib/tpl.hpp"

namespace openvrl {

/**
 *
 */
TPLPLUGIN1(int) read_materials()
{
	TPL_ulong cb=0, cb1=0;
	TPL_DWORD n;
	TPL_ulong i;
	TPL_MAT m;

	if ( material_offs==0 ) return 0;

	material_buf.erase(material_buf.begin(), material_buf.end());
	devio->seek(material_offs, IOD_SEEK_SET);
	cb = devio->read(&n, sizeof(n));
	for ( i=0;i<n;i++ ) {
		TPL_memset(&m, 0, sizeof(m));
		cb1 = devio->read(&m, sizeof(m));
		TPL_ASSERT(cb1==sizeof(m));
		if ( strncmp(m.signature, TPL_MAT_SIG, TPL_MAX_SIG_LEN)!=0 ) break;
		TPL_ASSERT(m.version==TPL_MAT_VERSION);
		material_add(m);
		cb+=cb1;
	}
	return 0;
}

/**
 *
 */
TPLPLUGIN1(TPL_ulong) write_materials(TPL_DWORD offs)
{
	TPL_ulong cb=0;
	TPL_ulong i;
	TPL_DWORD n;
	devio->seek(offs, IOD_SEEK_SET);
	material_offs = offs;
	n = material_buf.size();
	cb += devio->write(&n, sizeof(n));
	for ( i=0;i<material_buf.size();i++ ) {
		cb += devio->write(&material_buf[i], sizeof(TPL_MAT));
	}
	return cb;
}

/**
 *
 */
TPLPLUGIN1(int) material_ctor()
{
	material_offs = 0;
	return 0;
}

TPLPLUGIN1(int) material_dtor()
{
	material_buf.erase(material_buf.begin(), material_buf.end());
	return 0;
}

/**
 *
 */
TPLPLUGIN1(int) material_read(TPL_MAT* m, TPL_ulong index)
{
	if ( index>=material_buf.size() ) return 1;
	*m = material_buf[index];
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) material_write(const TPL_MAT& m, TPL_ulong index)
{
	if ( index>=material_buf.size() ) return 1;
	material_buf[index] = m;
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) material_add(const TPL_MAT& m)
{
	material_buf.insert(material_buf.begin(), m);
	return 0;
}

TPLPLUGIN1(int) material_insert(const TPL_MAT& m, TPL_ulong index)
{
	if ( index>=material_buf.size() ) return 1;
	material_buf.insert(material_buf.begin()+ index, m);
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) material_delete(TPL_ulong index)
{
	if ( index>=material_buf.size() ) return 1;
	material_buf.erase(material_buf.begin() + index);
	return 0;
}

}