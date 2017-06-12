/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/pl_txtr.hpp,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description: *.tpl library. Texture support $
 *
 * Revision 0.1  20020116  13:39:12 FoxiE
 * started :)
 *
 */

#if !defined(__TPL_PL_TXTR_HPP) && defined(__TPL_INCLUDE_SUPPORT_PLUGINS) && \
    defined(TPL_SUPPORTED_TEXTURES)
#define __TPL_PL_TXTR_HPP

public:
	class TPL_API tex
	{
	public:
		TPL_TEX head;
		void *data;

	public:
		tex() { data =0; TPL_memset(&head, 0, sizeof(head)); }
		tex(const TPL_TEX &h)
		{
			TPL_memcpy(&head, &h, sizeof(head));
			data = 0;
		}
		tex(const tex& t)
		{
			*this = t;
		}
		~tex() { }

		tex& operator=(const tex& t)
		{
			memcpy(&head, &t.head, sizeof(head));
			data = t.data;
			return *this;
		}

		void cleanup()
		{
			if (data) delete[] data;
			data = 0;
		}
		TPL_ulong read(IIODevice*);
		TPL_ulong write(IIODevice*);
	};

protected:
        TPL_ulong	texture_offs;

	std::vector<tex>	texture_buf;

	/**
	 *
	 */
    TPLPLUGIN(int) read_textures();

	/**
	 *
	 */
    TPLPLUGIN(TPL_ulong) write_textures(TPL_DWORD offs);

public:
	/**
	 *
	 */
	TPLPLUGIN(int) texture_ctor();
	TPLPLUGIN(int) texture_dtor();

	/**
	 *
	 */
    TPLPLUGIN(tex) texture(TPL_ulong i) const
    {
		return texture_buf[i];
    }

    TPLPLUGIN(tex*) texture(TPL_ulong i) 
    {
		return &texture_buf[i];
    }

    TPLPLUGIN(TPL_ulong) textures() const
    {
		return (TPL_ulong)texture_buf.size();
    }

	/**
	 *
	 */
    TPLPLUGIN(int) texture_read(tex* t, TPL_ulong index);

	/**
	 *
	 */
    TPLPLUGIN(int) texture_write(const tex& t, TPL_ulong index);

	/**
	 *
	 */
    TPLPLUGIN(int) texture_add(const tex& t);
    TPLPLUGIN(int) texture_insert(const tex& t, TPL_ulong index);

	/**
	 *
	 */
    TPLPLUGIN(int) texture_delete(TPL_ulong index);

#endif
