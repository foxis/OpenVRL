/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tpllib/pl_rwmsh.hpp,v $
 * $Implementation: $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:22 $
 * $Description: *.tpl library. Raw mesh $
 *
 * Revision 0.1  20020116  17:56:12 FoxiE
 * Pradejau :)
 *
 */


#if !defined(__TPL_PL_RWMSH_HPP) && defined(__TPL_INCLUDE_SUPPORT_PLUGINS) && \
    defined(TPL_SUPPORTED_RAW_MESHES)
#define __TPL_PL_RWMSH_HPP


/**
 *
 */
public:
	class CTPL_RAW : public TPL_RAW
	{
		std::vector<TPL_MESHSUBSET> _subsets;
		friend CTPLLib;

	public:
		TPL_BYTE* VB;
		TPL_BYTE* IB;
		bool del;

		const TPL_MESHSUBSET& get_subset(TPL_ulong i) const;
		TPL_MESHSUBSET& get_subset(TPL_ulong i);

		void cleanup();
		void create(TPL_ulong vbcb, TPL_ulong ibcb);

		void cleanupVB() {	if ( del&&VB ) delete[] VB;	}
		void createVB(TPL_ulong cb)	{ VB = new BYTE[cb];	del = true;	}
		void cleanupIB() {	if ( del&&IB ) delete[] IB;	}
		void createIB(TPL_ulong cb)	{ IB = new BYTE[cb];	del = true;	}

		CTPL_RAW() {VB=IB=0; del=0;}
		~CTPL_RAW() {}
		CTPL_RAW(const CTPL_RAW& t);
		CTPL_RAW(const TPL_RAW& t);

		CTPL_RAW& operator=(const CTPL_RAW& t);
	};

protected:
	std::vector<CTPL_RAW>	rawmesh_buf;
	TPL_DWORD	mesh_offs;

	 /**
	 *
	 */
	TPLPLUGIN(int) read_rawmesh();
	TPLPLUGIN(TPL_ulong) write_rawmesh(TPL_ulong offs);

public:
	/**
	 *
	 */
	TPLPLUGIN(int) rawmesh_ctor();
	TPLPLUGIN(int) rawmesh_dtor();
	 

	TPLPLUGIN(const CTPL_RAW&) rawmesh(TPL_ulong i) const
	{
		return rawmesh_buf[i];
	}
	TPLPLUGIN(CTPL_RAW*) rawmesh(TPL_ulong i)
	{
		return &rawmesh_buf[i];
	}
	TPLPLUGIN(TPL_ulong) rawmeshes() const
	{
		return (TPL_ulong)rawmesh_buf.size();
	}

	/**
	 *
	 */
    TPLPLUGIN(int) rawmesh_read(TPL_RAW* m, TPL_ulong i);
    TPLPLUGIN(int) rawmesh_write(const TPL_RAW& m, TPL_ulong i);
	TPLPLUGIN(const TPL_MESHSUBSET&) rawmesh_get_subset(TPL_ulong i, TPL_ulong j) const;
	TPLPLUGIN(TPL_MESHSUBSET&) rawmesh_get_subset(TPL_ulong i, TPL_ulong j);
	TPLPLUGIN(int) rawmesh_add_subset(TPL_ulong i, const TPL_MESHSUBSET& s);
	TPLPLUGIN(int) rawmesh_remove_subset(TPL_ulong i, TPL_ulong j);
	TPLPLUGIN(int) rawmesh_set_subsets(TPL_ulong i, const std::vector<TPL_MESHSUBSET>& sl);
	TPLPLUGIN(int) rawmesh_get_subsets(TPL_ulong i, std::vector<TPL_MESHSUBSET>& sl);

	/**
	 *
	 */
    TPLPLUGIN(int) rawmesh_add(const TPL_RAW& m, TPL_BYTE* VB, TPL_BYTE* IB, bool del=false);
    TPLPLUGIN(int) rawmesh_insert(const TPL_RAW& m, TPL_ulong index, TPL_BYTE* VB, TPL_BYTE* IB, bool del=false);
    TPLPLUGIN(int) rawmesh_delete(TPL_ulong index);

	/**
	 *
	 */
	TPLPLUGIN(int) rawmesh_write_VB0(TPL_ulong i, const TPL_BYTE* VB, TPL_DWORD cb, TPL_WORD flags);
	TPLPLUGIN(int) rawmesh_write_IB0(TPL_ulong i, const TPL_BYTE* IB, TPL_DWORD cb, TPL_WORD flags);
	TPLPLUGIN(int) rawmesh_read_VB0(TPL_ulong i, TPL_BYTE* VB, TPL_DWORD dest_cb)const; 
	TPLPLUGIN(int) rawmesh_read_IB0(TPL_ulong i, TPL_BYTE* IB, TPL_DWORD dest_cb)const;
	TPLPLUGIN(int) rawmesh_write_VB(TPL_ulong i, const TPL_BYTE* VB, TPL_DWORD cb, TPL_WORD flags);
	TPLPLUGIN(int) rawmesh_write_IB(TPL_ulong i, const TPL_BYTE* IB, TPL_DWORD cb, TPL_WORD flags);
	TPLPLUGIN(int) rawmesh_read_VB(TPL_ulong i, TPL_BYTE* VB, TPL_DWORD dest_cb, TPL_WORD dest_flags)const; 
	TPLPLUGIN(int) rawmesh_read_IB(TPL_ulong i, TPL_BYTE* IB, TPL_DWORD dest_cb, TPL_WORD dest_flags)const;

	TPLPLUGIN(TPL_ulong) calc_vertex_size(TPL_WORD flags)const;
	TPLPLUGIN(TPL_ulong) calc_face_size(TPL_WORD flags)const;
	TPLPLUGIN(TPL_ulong) rawmesh_copy_vertex(const TPL_BYTE* src, TPL_WORD sflg, TPL_BYTE* dst, TPL_WORD dflg) const;
	TPLPLUGIN(TPL_ulong) rawmesh_copy_face(const TPL_BYTE* src, TPL_WORD sflg, TPL_BYTE* dst, TPL_WORD dflg) const;

#endif