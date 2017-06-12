/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/pl_cmr.hpp,v $
 * $Implementation: $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:21 $
 * $Description: *.tpl library. Camera support $
 *
 * Revision 0.1  20020115  13:39:12 FoxiE
 * started :)
 *
 */


#if !defined(__TPL_PL_CMR_HPP) && defined(__TPL_INCLUDE_SUPPORT_PLUGINS) && \
    defined(TPL_SUPPORTED_CAMERAS)
#define __TPL_PL_CMR_HPP


protected:
        TPL_ulong	camera_offs;
		std::vector<TPL_CAMERA>	camera_buf;

	/**
	 *
	 */
    TPLPLUGIN(int) read_cameras();

	/**
	 *
	 */
    TPLPLUGIN(TPL_ulong) write_cameras(TPL_DWORD offs);

public:
	/**
	 *
	 */
	TPLPLUGIN(int) camera_ctor();
	TPLPLUGIN(int) camera_dtor();

	/**
	 *
	 */
    TPLPLUGIN(const TPL_CAMERA&) camera(TPL_ulong i) const
    {
		return camera_buf[i];
    }

    TPLPLUGIN(TPL_CAMERA*) camera(TPL_ulong i) 
    {
	return &camera_buf[i];
    }

    TPLPLUGIN(TPL_ulong) cameras() const
    {
	return (TPL_ulong)camera_buf.size();
    }

	/**
	 *
	 */
    TPLPLUGIN(int) camera_read(TPL_CAMERA* m, TPL_ulong index);
    TPLPLUGIN(int) camera_write(const TPL_CAMERA& m, TPL_ulong index);

	/**
	 *
	 */
    TPLPLUGIN(int) camera_add(const TPL_CAMERA& m);
    TPLPLUGIN(int) camera_insert(const TPL_CAMERA& m, TPL_ulong index);
    TPLPLUGIN(int) camera_delete(TPL_ulong index);

#endif
