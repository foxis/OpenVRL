/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/pl_lght.hpp,v $
 * $Implementation: $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:21 $
 * $Description: *.tpl library. Light support $
 *
 * Revision 0.1  20020816  13:39:12 FoxiE
 * started :)
 *
 */


#if !defined(__TPL_PL_LGHT_HPP) && defined(__TPL_INCLUDE_SUPPORT_PLUGINS) && \
    defined(TPL_SUPPORTED_LIGHTS)
#define __TPL_PL_LGHT_HPP


protected:
        TPL_ulong	light_offs;
	std::vector<TPL_LIGHT>	light_buf;

	/**
	 *
	 */
    TPLPLUGIN(int) read_lights();

	/**
	 *
	 */
    TPLPLUGIN(TPL_ulong) write_lights(TPL_DWORD offs);

public:
	/**
	 *
	 */
	TPLPLUGIN(int) light_ctor();
	TPLPLUGIN(int) light_dtor();

	/**
	 *
	 */
    TPLPLUGIN(const TPL_LIGHT&) light(TPL_ulong i) const
    {
		return light_buf[i];
    }

    TPLPLUGIN(TPL_LIGHT*) light(TPL_ulong i) 
    {
	return &light_buf[i];
    }

    TPLPLUGIN(TPL_ulong) lights() const
    {
	return (TPL_ulong)light_buf.size();
    }

	/**
	 *
	 */
    TPLPLUGIN(int) light_read(TPL_LIGHT* m, TPL_ulong index);
    TPLPLUGIN(int) light_write(const TPL_LIGHT& m, TPL_ulong index);

	/**
	 *
	 */
    TPLPLUGIN(int) light_add(const TPL_LIGHT& m);
    TPLPLUGIN(int) light_insert(const TPL_LIGHT& m, TPL_ulong index);
    TPLPLUGIN(int) light_delete(TPL_ulong index);

#endif
