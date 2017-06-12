/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/pl_hdr.hpp,v $
 * $Implementation: $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:21 $
 * $Description: *.tpl library. Header support $
 *
 * Revision 0.1  20020115  13:39:12 FoxiE
 * started :)
 *
 */


#if !defined(__TPL_PL_HDR_HPP) && defined(__TPL_INCLUDE_SUPPORT_PLUGINS) && \
    defined(TPL_SUPPORTED_HEADER)
#define __TPL_PL_HDR_HPP


protected:
        TPL_DWORD           version;
        TPL_CHAR            signature[TPL_MAX_SIG_LEN];
        TPL_CHAR            name[TPL_MAX_NAME_LEN];
        TPL_CHAR*           comment;
        TPL_WORD            UID;
        TPL_WORD            GID;
        TPL_DWORD           type;
        TPL_DWORD           compression;
        TPL_ulong           header_off;
        TPL_ulong           original_size;
        TPL_ulong       compressed_size;
        TPL_time_t		time;

public:
	/**
	 *
	 */
	TPLPLUGIN(int) header_ctor(const TPL_CHAR* nm, TPL_DWORD ver, TPL_WORD _UID, TPL_WORD _GID);
	TPLPLUGIN(int) header_dtor();
	 
	 /**
	 *
	 */
	TPLPLUGIN(int) header_read();

	/**
	 *
	 */
	TPLPLUGIN(TPL_ulong) header_write();

	/**
	 *
	 */
	TPLPLUGIN(TPL_ulong) header_write(const TPL_HDR& hdr);

	/**
	 *
	 */
	TPLPLUGIN(TPL_DWORD) header_version() const { return version; }
	TPLPLUGIN(TPL_DWORD&) header_version() { return version; }
	TPLPLUGIN(const TPL_CHAR*) header_signature() const { return (TPL_CHAR*)signature; }
	TPLPLUGIN(TPL_CHAR*) header_signature() { return (TPL_CHAR*)signature; }
	TPLPLUGIN(const TPL_CHAR*) header_name() const { return (TPL_CHAR*)name; }
	TPLPLUGIN(TPL_CHAR*) header_name() { return (TPL_CHAR*)name; }
	TPLPLUGIN(const TPL_CHAR*) header_comment() const { return (TPL_CHAR*)comment; }
	TPLPLUGIN(TPL_CHAR*) header_comment() { return (TPL_CHAR*)comment; }
	TPLPLUGIN(TPL_WORD) header_UID() const { return UID; }
	TPLPLUGIN(TPL_WORD&) header_UID() { return UID; }
	TPLPLUGIN(TPL_WORD) header_GID() const { return GID; }
	TPLPLUGIN(TPL_WORD&) header_GID() { return GID; }
	TPLPLUGIN(TPL_DWORD) header_type() const { return type; }
	TPLPLUGIN(TPL_DWORD&) header_type() { return type; }
	TPLPLUGIN(TPL_DWORD) header_compression() const { return compression; }
	TPLPLUGIN(TPL_DWORD&) header_compression() { return compression; }
	TPLPLUGIN(TPL_ulong) header_offset() const { return header_off; }
	TPLPLUGIN(TPL_ulong&) header_offset() { return header_off; }
	TPLPLUGIN(TPL_ulong) header_original_size() const { return original_size; }
	TPLPLUGIN(TPL_ulong&) header_original_size() { return original_size; }
	TPLPLUGIN(TPL_ulong) header_compressed_size() const { return compressed_size; }
	TPLPLUGIN(TPL_ulong&) header_compressed_size() { return compressed_size; }
	TPLPLUGIN(TPL_time_t) header_time() const { return time; }
	TPLPLUGIN(TPL_time_t&) header_time() { return time; }

#endif
