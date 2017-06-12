/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/pl_mtrl.hpp,v $
 * $Implementation: $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:22 $
 * $Description: *.tpl library. Material support $
 *
 * Revision 0.1  20020115  13:39:12 FoxiE
 * started :)
 *
 */


#if !defined(__TPL_PL_MTRL_HPP) && defined(__TPL_INCLUDE_SUPPORT_PLUGINS) && \
    defined(TPL_SUPPORTED_MATERIALS)
#define __TPL_PL_MTRL_HPP


protected:
        TPL_ulong	material_offs;
		std::vector<TPL_MAT>	material_buf;

	/**
	 *
	 */
    TPLPLUGIN(int) read_materials();

	/**
	 *
	 */
    TPLPLUGIN(TPL_ulong) write_materials(TPL_DWORD offs);

public:
	/**
	 *
	 */
	TPLPLUGIN(int) material_ctor();
	TPLPLUGIN(int) material_dtor();

	/**
	 *
	 */
    TPLPLUGIN(const TPL_MAT&) material(TPL_ulong i) const
    {
		return material_buf[i];
    }

    TPLPLUGIN(TPL_MAT*) material(TPL_ulong i) 
    {
	return &material_buf[i];
    }

    TPLPLUGIN(TPL_ulong) materials() const
    {
	return (TPL_ulong)material_buf.size();
    }

	/**
	 *
	 */
    TPLPLUGIN(int) material_read(TPL_MAT* m, TPL_ulong index);
    TPLPLUGIN(int) material_write(const TPL_MAT& m, TPL_ulong index);

	/**
	 *
	 */
    TPLPLUGIN(int) material_add(const TPL_MAT& m);
    TPLPLUGIN(int) material_insert(const TPL_MAT& m, TPL_ulong index);
    TPLPLUGIN(int) material_delete(TPL_ulong index);

#endif
