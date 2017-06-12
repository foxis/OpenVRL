#include <string.h>
#include "tpllib/tpl.hpp"

namespace openvrl {

TPLPLUGIN1(int) header_ctor(const TPL_CHAR* nm, TPL_DWORD ver, TPL_WORD _UID, TPL_WORD _GID)
{
    version = ver;
    strncpy(signature, TPL_SIGNATURE, TPL_MAX_SIG_LEN);
	if ( nm ) strncpy(name, nm, TPL_MAX_NAME_LEN);
	else
		memset(name, 0, TPL_MAX_NAME_LEN);
    comment = 0; 
    UID = _UID;
    GID = _GID;
    type =0;
	comment = 0;
    compression = 0;
    header_off = 0;
    original_size = 0;
    compressed_size = 0;
//    time;
	return 0;
}

TPLPLUGIN1(int) header_dtor()
{
	if ( comment ) delete[] comment;
	return 0;
}

/**
 *
 */
TPLPLUGIN1(int) header_read()
{
	TPL_HDR hdr;
	TPL_memset(&hdr, 0, sizeof(hdr));

	devio->seek(0, IOD_SEEK_SET);
	if ( devio->read(&hdr, sizeof(hdr)) <sizeof(hdr) )
		return 1;

	TPL_ASSERT(hdr.version==TPL_VERSION);
	if ( strncmp(hdr.signature, TPL_SIGNATURE, TPL_MAX_SIG_LEN)!=0 )
		return 1;

	version = hdr.version;
	strncpy(signature, hdr.signature, TPL_MAX_SIG_LEN);
	strncpy(name, hdr.name, TPL_MAX_NAME_LEN);
	UID = hdr.UID;
	GID = hdr.GID;
	type = hdr.type;
//	comment_size = strlen(comment);
	compression = hdr.compression;
	original_size = hdr.original_size;
	compressed_size = hdr.compressed_size;
	//time = hdr.time;

	mesh_offs = hdr.mesh_offs;
	material_offs = hdr.material_offs;
	light_offs = hdr.light_offs;
	camera_offs = hdr.camera_offs;
	texture_offs = hdr.texture_offs;
//	cue_points_offs = hdr.cue_points_offs;
//	bones_offs = hdr.bones_offs;
//	animation_offs = hdr.animation_offs;
	return 0;
}

/**
 *
 */
TPLPLUGIN1(TPL_ulong) header_write()
{
	ulong n;
	TPL_HDR hdr;

	memset(&hdr, 0, sizeof(hdr));

	hdr.version = TPL_VERSION;
	strncpy(hdr.signature, TPL_SIGNATURE, TPL_MAX_SIG_LEN);
	strncpy(hdr.name, name, TPL_MAX_NAME_LEN);
	hdr.UID = UID;
	hdr.GID = GID;
	hdr.type = type;
//	hdr.comment_size = strlen(comment);
	hdr.compression = compression;
	hdr.original_size = original_size;
	hdr.compressed_size = compressed_size;
//	hdr.time = time;

	hdr.mesh_offs = mesh_offs;
	hdr.material_offs = material_offs;
	hdr.light_offs = light_offs;
	hdr.camera_offs = camera_offs;
	hdr.texture_offs = texture_offs;
//	hdr.cue_points_offs = cue_points_offs;
//	hdr.bones_offs = bones_offs;
//	hdr.animation_offs = animation_offs;

	devio->seek(0, IOD_SEEK_SET);
	n = devio->write(&hdr, sizeof(hdr));
	if ( n<sizeof(hdr) )
		return 0;
	else if ( comment ) 
		return n+devio->write(comment, strlen(comment)+1);
	else 
		return n;
}

/**
 *
 */
TPLPLUGIN1(ulong) header_write(const TPL_HDR& hdr)
{
	devio->seek(0, IOD_SEEK_SET);
	return devio->write(&hdr, sizeof(hdr));
}

}