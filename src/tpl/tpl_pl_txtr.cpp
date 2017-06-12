#include <string.h>
#include "tpllib/tpl.hpp"
//#include "tpllib/pl_txtr.hpp"

namespace openvrl {

TPLPLUGIN1(TPL_ulong) tex::read(IIODevice* devio)
{
	TPL_ulong cb,cb1;
	TPL_BYTE *tmp;
	TPL_memset(&head, 0, sizeof(head));
	cb = devio->read(&head, sizeof(head));
	TPL_ASSERT(cb==sizeof(head));
	if ( strncmp(head.signature, TPL_TEX_SIG, TPL_MAX_SIG_LEN)!=0 ) return 0;
	TPL_ASSERT(head.version==TPL_TEX_VERSION);

	tmp = new TPL_BYTE[head.data_size];
	TPL_memset(tmp, 0, head.data_size);
	cb1 = devio->read(tmp, head.data_size);
	if ( cb1==0 || cb1!=head.data_size )
	{
		delete[] tmp;
		return 0;
	}

	if ( head.compression != TPL_COMPRESSION_NONE )
	{
		// perform decompression

		delete[] tmp;
		data = 0;
	}
	else
		data = tmp;

	return cb+cb1;
}

TPLPLUGIN1(TPL_ulong) tex::write(IIODevice* devio)
{
	TPL_ulong cb,cb1;
	cb = devio->write(&head, sizeof(TPL_TEX));
	if ( cb==0 ) return 0;

	if ( head.compression!=TPL_COMPRESSION_NONE )
	{
		// perform compression
		cb1 = 0;
	}
	else
		cb1 = devio->write(data, head.data_size);

	return cb1+cb;
}

/**
 *
 */
TPLPLUGIN1(int) read_textures()
{
	TPL_ulong cb=0, cb1=0;
	TPL_DWORD n;
	TPL_ulong i;
	tex t;


	if ( texture_offs==0 ) return 0;

	std::vector<tex>::iterator I(texture_buf.begin());
	while ( I!=texture_buf.end() )
		(*(I++)).cleanup();
	texture_buf.clear();

	devio->seek(texture_offs, IOD_SEEK_SET);
	cb = devio->read(&n, sizeof(n));
	for ( i=0;i<n;i++ ) {
		if ( (cb1 = t.read(devio))!=0 )
			texture_add(t);
		else return 1;
		cb+=cb1;
	}
	return 0;
}

/**
 *
 */
TPLPLUGIN1(TPL_ulong) write_textures(TPL_DWORD offs)
{
	TPL_ulong cb=0;
	TPL_ulong i;
	TPL_DWORD n;
	devio->seek(offs, IOD_SEEK_SET);
	texture_offs = offs;
	n = texture_buf.size();
	cb += devio->write(&n, sizeof(n));
	for ( i=0;i<texture_buf.size();i++ ) {
		cb += texture_buf[i].write(devio);
	}
	return cb;
}

/**
 *
 */
TPLPLUGIN1(int) texture_ctor()
{
	texture_offs = 0;
	return 0;
}

TPLPLUGIN1(int) texture_dtor()
{
	std::vector<tex>::iterator i(texture_buf.begin());
	while ( i!=texture_buf.end() )
		(*(i++)).cleanup();
	texture_buf.clear();
	return 0;
}

/**
 *
 */
TPLPLUGIN1(int) texture_read(tex* t, TPL_ulong index)
{
	if ( index>=texture_buf.size() ) return 1;
	*t = texture_buf[index];
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) texture_write(const tex& t, TPL_ulong index)
{
	if ( index>=material_buf.size() ) return 1;
	texture_buf[index] = t;
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) texture_add(const tex& t)
{
	texture_buf.push_back(t);
	return 0;
}

TPLPLUGIN1(int) texture_insert(const tex& t, TPL_ulong index)
{
	if ( index>=texture_buf.size() ) return 1;
	texture_buf.insert(texture_buf.begin()+ index, t);
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) texture_delete(TPL_ulong index)
{
	if ( index>=texture_buf.size() ) return 1;
	(texture_buf.begin() + index)->cleanup();
	texture_buf.erase(texture_buf.begin() + index);
	return 0;
}

}