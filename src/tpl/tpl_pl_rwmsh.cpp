#include <string.h>
#include "tpllib/tpl.hpp"

namespace openvrl {

/**
 *
 */
TPLPLUGIN1(int) rawmesh_ctor()
{
	return 0;
}

TPLPLUGIN1(int) rawmesh_dtor()
{
	std::vector<CTPL_RAW>::iterator i(rawmesh_buf.begin());
	while ( i!=rawmesh_buf.end() )
		(*(i++)).cleanup();
	rawmesh_buf.erase(rawmesh_buf.begin(), rawmesh_buf.end());
	return 0;
}
	 

/**
 *
 */
TPLPLUGIN1(TPL_ulong) rawmesh_copy_vertex(const TPL_BYTE* src, TPL_WORD sflg, TPL_BYTE* dst, TPL_WORD dflg) const
{
    if ( dflg&TPL_VB_XYZ ) { if ( sflg&TPL_VB_XYZ ) memcpy(dst, src, 3*sizeof(float)); else memset(dst, 0, 3*sizeof(float)); dst+=3*sizeof(float); }
    if ( sflg&TPL_VB_XYZ ) src+= 3*sizeof(float);
    if ( dflg&TPL_VB_RHW ) { if ( sflg&TPL_VB_RHW ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sflg&TPL_VB_RHW ) src+= sizeof(float);
    if ( dflg&TPL_VB_B1 ) { if ( sflg&TPL_VB_B1 ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sflg&TPL_VB_B1 ) src+= sizeof(float);
    if ( dflg&TPL_VB_B2 ) { if ( sflg&TPL_VB_B2 ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sflg&TPL_VB_B2 ) src+= sizeof(float);
    if ( dflg&TPL_VB_B3 ) { if ( sflg&TPL_VB_B3 ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sflg&TPL_VB_B3 ) src+= sizeof(float);
    if ( dflg&TPL_VB_B4 ) { if ( sflg&TPL_VB_B4 ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sflg&TPL_VB_B4 ) src+= sizeof(float);
    if ( dflg&TPL_VB_NORMAL ) { if ( sflg&TPL_VB_NORMAL ) memcpy(dst, src, 3*sizeof(float)); else memset(dst, 0, 3*sizeof(float)); dst+=3*sizeof(float); }
    if ( sflg&TPL_VB_NORMAL ) src+= 3*sizeof(float);
    if ( dflg&TPL_VB_PSIZE ) { if ( sflg&TPL_VB_PSIZE ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sflg&TPL_VB_PSIZE ) src+= sizeof(float);
    if ( dflg&TPL_VB_DIFFUSE ) { if ( sflg&TPL_VB_DIFFUSE ) memcpy(dst, src, 4*sizeof(TPL_BYTE)); else memset(dst, 0, 4*sizeof(TPL_BYTE)); dst+=4*sizeof(TPL_BYTE); }
    if ( sflg&TPL_VB_DIFFUSE ) src+= 4*sizeof(TPL_BYTE);
    if ( dflg&TPL_VB_SPECULAR ) { if ( sflg&TPL_VB_SPECULAR ) memcpy(dst, src, 4*sizeof(TPL_BYTE)); else memset(dst, 0, 4*sizeof(TPL_BYTE)); dst+=4*sizeof(TPL_BYTE); }
    if ( sflg&TPL_VB_SPECULAR ) src+= 4*sizeof(TPL_BYTE);
    if ( dflg&TPL_VB_TX1 ) { if ( sflg&TPL_VB_TX1 ) memcpy(dst, src, 2*sizeof(float)); else memset(dst, 0, 2*sizeof(float)); dst+=2*sizeof(float); }
    if ( sflg&TPL_VB_TX1 ) src+= 3*sizeof(float);
    if ( dflg&TPL_VB_TX2 ) { if ( sflg&TPL_VB_TX2 ) memcpy(dst, src, 2*sizeof(float)); else memset(dst, 0, 2*sizeof(float)); dst+=2*sizeof(float); }
    if ( sflg&TPL_VB_TX2 ) src+= 3*sizeof(float);
    if ( dflg&TPL_VB_TX3 ) { if ( sflg&TPL_VB_TX3 ) memcpy(dst, src, 2*sizeof(float)); else memset(dst, 0, 2*sizeof(float)); dst+=2*sizeof(float); }
    if ( sflg&TPL_VB_TX3 ) src+= 3*sizeof(float);
    if ( dflg&TPL_VB_TX4 ) { if ( sflg&TPL_VB_TX4 ) memcpy(dst, src, 2*sizeof(float)); else memset(dst, 0, 2*sizeof(float)); dst+=2*sizeof(float); }
    if ( sflg&TPL_VB_TX4 ) src+= 3*sizeof(float);
    if ( dflg&TPL_VB_MASS ) { if ( sflg&TPL_VB_MASS ) memcpy(dst, src, sizeof(double)); else memset(dst, 0, sizeof(double)); dst+=sizeof(double); }
    if ( sflg&TPL_VB_MASS ) src+= sizeof(float);
    if ( dflg&TPL_VB_BONE_ID ) { if ( sflg&TPL_VB_BONE_ID ) memcpy(dst, src, sizeof(TPL_DWORD)); else memset(dst, 0, sizeof(TPL_DWORD)); dst+=sizeof(TPL_DWORD); }
    if ( sflg&TPL_VB_BONE_ID ) src+= sizeof(TPL_DWORD);

	return calc_vertex_size(dflg);
}

/**
 *
 */
TPLPLUGIN1(TPL_ulong) rawmesh_copy_face(const TPL_BYTE* src, TPL_WORD sflg, TPL_BYTE* dst, TPL_WORD dflg) const
{
	if ( sflg&TPL_IB_32BIT || !(sflg&TPL_IB_SIZE_MASK) ) {
		if ( dflg&TPL_IB_A ) { if ( sflg&TPL_IB_A ) memcpy(dst, src, sizeof(TPL_DWORD)); else memset(dst, 0, sizeof(TPL_DWORD)); dst+=sizeof(TPL_DWORD); }
	    if ( sflg&TPL_IB_A ) src+= sizeof(TPL_DWORD);
		if ( dflg&TPL_IB_B ) { if ( sflg&TPL_IB_B ) memcpy(dst, src, sizeof(TPL_DWORD)); else memset(dst, 0, sizeof(TPL_DWORD)); dst+=sizeof(TPL_DWORD); }
	    if ( sflg&TPL_IB_B ) src+= sizeof(TPL_DWORD);
		if ( dflg&TPL_IB_C ) { if ( sflg&TPL_IB_C ) memcpy(dst, src, sizeof(TPL_DWORD)); else memset(dst, 0, sizeof(TPL_DWORD)); dst+=sizeof(TPL_DWORD); }
	    if ( sflg&TPL_IB_C ) src+= sizeof(TPL_DWORD);
		if ( dflg&TPL_IB_D ) { if ( sflg&TPL_IB_D ) memcpy(dst, src, sizeof(TPL_DWORD)); else memset(dst, 0, sizeof(TPL_DWORD)); dst+=sizeof(TPL_DWORD); }
	    if ( sflg&TPL_IB_D ) src+= sizeof(TPL_DWORD);
	} else if ( sflg&TPL_IB_24BIT ) {
		if ( dflg&TPL_IB_A ) { if ( sflg&TPL_IB_A ) memcpy(dst, src, 3*sizeof(TPL_BYTE)); else memset(dst, 0, 3*sizeof(TPL_BYTE)); dst+=3*sizeof(TPL_BYTE); }
	    if ( sflg&TPL_IB_A ) src+= 3*sizeof(TPL_BYTE);
		if ( dflg&TPL_IB_B ) { if ( sflg&TPL_IB_B ) memcpy(dst, src, 3*sizeof(TPL_BYTE)); else memset(dst, 0, 3*sizeof(TPL_BYTE)); dst+=3*sizeof(TPL_BYTE); }
	    if ( sflg&TPL_IB_B ) src+= 3*sizeof(TPL_BYTE);
		if ( dflg&TPL_IB_C ) { if ( sflg&TPL_IB_C ) memcpy(dst, src, 3*sizeof(TPL_BYTE)); else memset(dst, 0, 3*sizeof(TPL_BYTE)); dst+=3*sizeof(TPL_BYTE); }
	    if ( sflg&TPL_IB_C ) src+= 3*sizeof(TPL_BYTE);
		if ( dflg&TPL_IB_D ) { if ( sflg&TPL_IB_D ) memcpy(dst, src, 3*sizeof(TPL_BYTE)); else memset(dst, 0, 3*sizeof(TPL_BYTE)); dst+=3*sizeof(TPL_BYTE); }
	    if ( sflg&TPL_IB_D ) src+= 3*sizeof(TPL_BYTE);
	} else if ( sflg&TPL_IB_16BIT ) {
		if ( dflg&TPL_IB_A ) { if ( sflg&TPL_IB_A ) memcpy(dst, src, sizeof(TPL_WORD)); else memset(dst, 0, sizeof(TPL_WORD)); dst+=sizeof(TPL_WORD); }
	    if ( sflg&TPL_IB_A ) src+= sizeof(TPL_WORD);
		if ( dflg&TPL_IB_B ) { if ( sflg&TPL_IB_B ) memcpy(dst, src, sizeof(TPL_WORD)); else memset(dst, 0, sizeof(TPL_WORD)); dst+=sizeof(TPL_WORD); }
	    if ( sflg&TPL_IB_B ) src+= sizeof(TPL_WORD);
		if ( dflg&TPL_IB_C ) { if ( sflg&TPL_IB_C ) memcpy(dst, src, sizeof(TPL_WORD)); else memset(dst, 0, sizeof(TPL_WORD)); dst+=sizeof(TPL_WORD); }
	    if ( sflg&TPL_IB_C ) src+= sizeof(TPL_WORD);
		if ( dflg&TPL_IB_D ) { if ( sflg&TPL_IB_D ) memcpy(dst, src, sizeof(TPL_WORD)); else memset(dst, 0, sizeof(TPL_WORD)); dst+=sizeof(TPL_WORD); }
	    if ( sflg&TPL_IB_D ) src+= sizeof(TPL_WORD);
	} else if ( sflg&TPL_IB_08BIT ) {
		if ( dflg&TPL_IB_A ) { if ( sflg&TPL_IB_A ) memcpy(dst, src, sizeof(TPL_BYTE)); else memset(dst, 0, sizeof(TPL_BYTE)); dst+=sizeof(TPL_BYTE); }
	    if ( sflg&TPL_IB_A ) src+= sizeof(TPL_BYTE);
		if ( dflg&TPL_IB_B ) { if ( sflg&TPL_IB_B ) memcpy(dst, src, sizeof(TPL_BYTE)); else memset(dst, 0, sizeof(TPL_BYTE)); dst+=sizeof(TPL_BYTE); }
	    if ( sflg&TPL_IB_B ) src+= sizeof(TPL_BYTE);
		if ( dflg&TPL_IB_C ) { if ( sflg&TPL_IB_C ) memcpy(dst, src, sizeof(TPL_BYTE)); else memset(dst, 0, sizeof(TPL_BYTE)); dst+=sizeof(TPL_BYTE); }
	    if ( sflg&TPL_IB_C ) src+= sizeof(TPL_BYTE);
		if ( dflg&TPL_IB_D ) { if ( sflg&TPL_IB_D ) memcpy(dst, src, sizeof(TPL_BYTE)); else memset(dst, 0, sizeof(TPL_BYTE)); dst+=sizeof(TPL_BYTE); }
	    if ( sflg&TPL_IB_D ) src+= sizeof(TPL_BYTE);
	}
	if ( dflg&TPL_IB_MI ) { if ( sflg&TPL_IB_MI ) memcpy(dst, src, sizeof(TPL_DWORD)); else memset(dst, 0, sizeof(TPL_DWORD)); dst+=sizeof(TPL_DWORD); }
    if ( sflg&TPL_IB_MI ) src+= sizeof(TPL_DWORD);

	return calc_face_size(dflg);
}


/**
 *
 */
TPLPLUGIN1(int) read_rawmesh()
{
	TPL_DWORD vbcb, ibcb, n, i, j;
	TPL_RAW rw;
	TPL_MESHSUBSET rs;
	TPL_BYTE *VB, *IB;

	if ( mesh_offs==0 ) return 0;

	devio->seek(mesh_offs, IOD_SEEK_SET);
	devio->read(&n, sizeof(n));
	for ( i=0;i<n;i++ )
	{
		TPL_memset(&rw, 0, sizeof(rw));
		TPL_ASSERT(devio->read(&rw, sizeof(rw))==sizeof(rw));
		if ( strncmp(rw.signature, TPL_RAW_SIG, TPL_MAX_SIG_LEN)!=0 ) break;
		TPL_ASSERT(rw.version==TPL_RAW_VERSION);
		vbcb = rw.vertex_size*rw.verteces;
		ibcb = rw.face_size*rw.faces;
		VB = new TPL_BYTE[vbcb];
		IB = new TPL_BYTE[ibcb];
		TPL_ASSERT(VB);
		TPL_ASSERT(IB);
		TPL_ASSERT(devio->read(VB, vbcb)==vbcb);
		TPL_ASSERT(devio->read(IB, ibcb)==ibcb);
		rawmesh_add(rw, VB, IB, true);
		for ( j=0;j<rw.subsets;j++ )  
		{
			TPL_memset(&rs, 0, sizeof(rs));
			TPL_ASSERT(devio->read(&rs, sizeof(rs))==sizeof(rs));
			rawmesh(i)->_subsets.insert(rawmesh(i)->_subsets.end(), rs);
		}
	}

	return 0;
}

/**
 *
 */
TPLPLUGIN1(TPL_ulong) write_rawmesh(TPL_ulong offs)
{
	TPL_DWORD vbcb, ibcb, n, i, j, cb;

	n = rawmesh_buf.size();
	mesh_offs = offs;
	devio->seek(offs, IOD_SEEK_SET);
	cb = devio->write(&n, sizeof(n));
	for ( i=0;i<n;i++ )
	{
		rawmesh(i)->subsets = rawmesh(i)->_subsets.size();
		cb+=devio->write(rawmesh(i), sizeof(TPL_RAW));
		vbcb = rawmesh(i)->vertex_size*rawmesh(i)->verteces;
		ibcb = rawmesh(i)->face_size*rawmesh(i)->faces;
		cb += devio->write(rawmesh(i)->VB, vbcb);
		cb += devio->write(rawmesh(i)->IB, ibcb);
		for ( j=0;j<rawmesh(i)->_subsets.size();j++ )
			cb += devio->write(&(rawmesh(i)->_subsets[j]), sizeof(TPL_MESHSUBSET));
	}

	return cb;
}

/**
 *
 */
TPLPLUGIN1(int) rawmesh_read(TPL_RAW* m, TPL_ulong index)
{
	if ( index>=rawmesh_buf.size() ) return 1;
	memcpy(m, &rawmesh_buf[index].version, sizeof(TPL_RAW));
	return 0;
}

TPLPLUGIN1(int) rawmesh_write(const TPL_RAW& m, TPL_ulong index)
{
	if ( index>=rawmesh_buf.size() ) return 1;
	memcpy(&rawmesh_buf[index].version, &m, sizeof(TPL_RAW));
	return 0;
}

TPLPLUGIN1(const TPL_MESHSUBSET&) rawmesh_get_subset(TPL_ulong i, TPL_ulong j) const
{
	TPL_ASSERT(i>=rawmeshes());
	TPL_ASSERT(j>=rawmesh_buf[i]._subsets.size());
	return rawmesh_buf[i]._subsets[j];
}

TPLPLUGIN1(TPL_MESHSUBSET&) rawmesh_get_subset(TPL_ulong i, TPL_ulong j)
{
	TPL_ASSERT(i>=rawmeshes());
	TPL_ASSERT(j>=rawmesh_buf[i]._subsets.size());
	return rawmesh_buf[i]._subsets[j];
}

TPLPLUGIN1(int) rawmesh_add_subset(TPL_ulong i, const TPL_MESHSUBSET& s)
{
	if ( i>=rawmesh_buf.size() ) return 1;
	rawmesh_buf[i]._subsets.insert(rawmesh_buf[i]._subsets.begin(), s);
	return 0;
}

TPLPLUGIN1(int) rawmesh_remove_subset(TPL_ulong i, TPL_ulong j)
{
	if ( i>=rawmesh_buf.size() ) return 1;
	if ( j>=rawmesh_buf[i]._subsets.size() ) return 1;
	rawmesh_buf[i]._subsets.erase(rawmesh_buf[i]._subsets.begin()+j);
	return 0;
}

TPLPLUGIN1(int) rawmesh_set_subsets(TPL_ulong i, const std::vector<TPL_MESHSUBSET>& sl)
{
	if ( i>=rawmesh_buf.size() ) return 1;
	rawmesh_buf[i]._subsets.assign(sl.begin(), sl.end());
	return 0;
}

TPLPLUGIN1(int) rawmesh_get_subsets(TPL_ulong i, std::vector<TPL_MESHSUBSET>& sl)
{
	if ( i>=rawmesh_buf.size() ) return 1;
	sl.clear();
	sl.assign(rawmesh_buf[i]._subsets.begin(), rawmesh_buf[i]._subsets.end());
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) rawmesh_add(const TPL_RAW& m, TPL_BYTE* VB, TPL_BYTE* IB, bool del)
{
	rawmesh_buf.insert(rawmesh_buf.end(), m);
	rawmesh(rawmeshes()-1)->VB = VB;
	rawmesh(rawmeshes()-1)->IB = IB;
	rawmesh(rawmeshes()-1)->del = del;
	return 0;
}

TPLPLUGIN1(int) rawmesh_insert(const TPL_RAW& m, TPL_ulong index, TPL_BYTE* VB, TPL_BYTE* IB, bool del)
{
	if ( index>=rawmesh_buf.size() ) return 1;
	rawmesh_buf.insert(rawmesh_buf.begin() +index, m);
	rawmesh(index)->del = del;
	rawmesh(index)->VB = VB;
	rawmesh(index)->IB = IB;
	return 0;
}


/**
 *
 */
TPLPLUGIN1(int) rawmesh_delete(TPL_ulong index)
{
	if ( index>=rawmesh_buf.size() ) return 1;
	rawmesh(index)->cleanup();
	rawmesh_buf.erase(rawmesh_buf.begin()+index);
	return 0;
}

/**
 *
 */
TPLPLUGIN1(int) rawmesh_write_VB0(TPL_ulong i, const TPL_BYTE* VB, TPL_DWORD cb, TPL_WORD flags)
{
	TPL_ASSERT(VB);
	rawmesh(i)->cleanupVB();
	rawmesh(i)->createVB(cb);
	rawmesh(i)->VB_flags = flags;
	memcpy(rawmesh(i)->VB, VB, cb);
	return 0;
}

TPLPLUGIN1(int) rawmesh_write_IB0(TPL_ulong i, const TPL_BYTE* IB, TPL_DWORD cb, TPL_WORD flags)
{
	TPL_ASSERT(IB);
	rawmesh(i)->cleanupIB();
	rawmesh(i)->createIB(cb);
	rawmesh(i)->IB_flags = flags;
	memcpy(rawmesh(i)->IB, IB, cb);
	return 0;
}

TPLPLUGIN1(int) rawmesh_read_VB0(TPL_ulong i, TPL_BYTE* VB, TPL_DWORD dest_cb) const
{
	TPL_ASSERT(VB);
	memcpy(VB, rawmesh(i).VB, dest_cb);
	return 0;
}

TPLPLUGIN1(int) rawmesh_read_IB0(TPL_ulong i, TPL_BYTE* IB, TPL_DWORD dest_cb) const
{
	TPL_ASSERT(IB);
	memcpy(IB, rawmesh(i).IB, dest_cb);
	return 0;
}

/**
 *
 */
TPLPLUGIN1(int) rawmesh_write_VB(TPL_ulong i, const TPL_BYTE* VB, TPL_DWORD cb, TPL_WORD flags)
{
	const TPL_ulong ccb = calc_vertex_size(flags)*cb;
	TPL_ASSERT(VB);
	rawmesh(i)->cleanupVB();
	rawmesh(i)->createVB(ccb);
	rawmesh(i)->VB_flags = flags;
	memcpy(rawmesh(i)->VB, VB, ccb);
	return 0;
}

TPLPLUGIN1(int) rawmesh_write_IB(TPL_ulong i, const TPL_BYTE* IB, TPL_DWORD cb, TPL_WORD flags)
{
	const TPL_ulong ccb = calc_vertex_size(flags)*cb;
	TPL_ASSERT(IB);
	rawmesh(i)->cleanupIB();
	rawmesh(i)->createIB(ccb);
	rawmesh(i)->IB_flags = flags;
	memcpy(rawmesh(i)->IB, IB, ccb);
	return 0;
}

TPLPLUGIN1(int) rawmesh_read_VB(TPL_ulong i, TPL_BYTE* VB, TPL_DWORD dest_cb, TPL_WORD dest_flags) const
{
	const TPL_ulong ccb1 = calc_vertex_size(dest_flags);
	const TPL_ulong ccb2 = calc_vertex_size(rawmesh(i).VB_flags);
	TPL_ulong j;

	TPL_ASSERT(VB);
	for ( j=0;j<dest_cb;j++ )
		rawmesh_copy_vertex(rawmesh(i).VB+j*ccb2, rawmesh(i).VB_flags, VB + j*ccb1, dest_flags);

	return 0;
}

TPLPLUGIN1(int) rawmesh_read_IB(TPL_ulong i, TPL_BYTE* IB, TPL_DWORD dest_cb, TPL_WORD dest_flags) const
{
	const TPL_ulong ccb1 = calc_face_size(dest_flags);
	const TPL_ulong ccb2 = calc_face_size(rawmesh(i).IB_flags);
	TPL_ulong j;

	TPL_ASSERT(IB);
	for ( j=0;j<dest_cb;j++ )
		rawmesh_copy_face(rawmesh(i).IB+j*ccb2, rawmesh(i).IB_flags, IB + j*ccb1, dest_flags);

	return 0;
}


TPLPLUGIN1(TPL_ulong) calc_vertex_size(TPL_WORD flags) const
{
	TPL_WORD cb=0;
    if ( flags&TPL_VB_XYZ ) cb+= 3*sizeof(float);
    if ( flags&TPL_VB_RHW ) cb+= sizeof(TPL_DWORD);
    if ( flags&TPL_VB_B1 ) cb+= sizeof(float);
    if ( flags&TPL_VB_B2 ) cb+= sizeof(float);
    if ( flags&TPL_VB_B3 ) cb+= sizeof(float);
    if ( flags&TPL_VB_B4 ) cb+= sizeof(float);
    if ( flags&TPL_VB_NORMAL ) cb+= 3*sizeof(float);
    if ( flags&TPL_VB_PSIZE ) cb+= sizeof(float);
    if ( flags&TPL_VB_DIFFUSE ) cb+= 4*sizeof(BYTE);
    if ( flags&TPL_VB_SPECULAR ) cb+= 4*sizeof(BYTE);
    if ( flags&TPL_VB_TX1 ) cb+= 2*sizeof(float);
    if ( flags&TPL_VB_TX2 ) cb+= 2*sizeof(float);
    if ( flags&TPL_VB_TX3 ) cb+= 2*sizeof(float);
    if ( flags&TPL_VB_TX4 ) cb+= 2*sizeof(float);
    if ( flags&TPL_VB_MASS ) cb+= sizeof(double);
    if ( flags&TPL_VB_BONE_ID ) cb+= sizeof(DWORD);

	return cb;
}

TPLPLUGIN1(TPL_ulong) calc_face_size(TPL_WORD flags) const
{
	TPL_WORD cb=0;
	if ( flags&TPL_IB_32BIT || !(flags&TPL_IB_SIZE_MASK) ) {
		if ( flags&TPL_IB_A ) cb+=sizeof(TPL_DWORD);
		if ( flags&TPL_IB_B ) cb+=sizeof(TPL_DWORD);
		if ( flags&TPL_IB_C ) cb+=sizeof(TPL_DWORD);
		if ( flags&TPL_IB_D ) cb+=sizeof(TPL_DWORD);
	} else if ( flags&TPL_IB_24BIT ) {
		if ( flags&TPL_IB_A ) cb+=3*sizeof(TPL_BYTE);
		if ( flags&TPL_IB_B ) cb+=3*sizeof(TPL_BYTE);
		if ( flags&TPL_IB_C ) cb+=3*sizeof(TPL_BYTE);
		if ( flags&TPL_IB_D ) cb+=3*sizeof(TPL_BYTE);
	} else if ( flags&TPL_IB_16BIT ) {
		if ( flags&TPL_IB_A ) cb+=sizeof(TPL_WORD);
		if ( flags&TPL_IB_B ) cb+=sizeof(TPL_WORD);
		if ( flags&TPL_IB_C ) cb+=sizeof(TPL_WORD);
		if ( flags&TPL_IB_D ) cb+=sizeof(TPL_WORD);
	} else if ( flags&TPL_IB_08BIT ) {
		if ( flags&TPL_IB_A ) cb+=sizeof(TPL_BYTE);
		if ( flags&TPL_IB_B ) cb+=sizeof(TPL_BYTE);
		if ( flags&TPL_IB_C ) cb+=sizeof(TPL_BYTE);
		if ( flags&TPL_IB_D ) cb+=sizeof(TPL_BYTE);
	}
	if ( flags&TPL_IB_MI ) cb+=sizeof(TPL_DWORD);

	return cb;
}


TPLPLUGIN1(void) CTPL_RAW::cleanup()
{
	cleanupVB();
	cleanupIB();
	_subsets.erase(_subsets.begin(), _subsets.end());
}
TPLPLUGIN1(void) CTPL_RAW::create(TPL_ulong vbcb, TPL_ulong ibcb)
{
	createVB(vbcb);
	createIB(ibcb);
	del = true;
}

TPLPLUGIN1(TPL_MESHSUBSET&) CTPL_RAW::get_subset(TPL_ulong i)
{
	return _subsets[i];
}
TPLPLUGIN1(const TPL_MESHSUBSET&) CTPL_RAW::get_subset(TPL_ulong i) const
{
	return _subsets[i];
}

TPLPLUGIN1c CTPL_RAW::CTPL_RAW(const CTPL_RAW& t)
{
	*this = t;
}
TPLPLUGIN1c CTPL_RAW::CTPL_RAW(const TPL_RAW& t)
{
	memcpy(&version, &t, sizeof(TPL_RAW));
	VB=IB=0; del=0;
}

TPLPLUGIN1(CTPLLib::CTPL_RAW&) CTPL_RAW::operator=(const CTPLLib::CTPL_RAW& t)
{
	memcpy(&version, &t.version, sizeof(TPL_RAW));
	VB = t.VB;
	IB = t.IB;
	del = t.del;
	_subsets.assign(t._subsets.begin(), t._subsets.end());
	return *this;
}

}
