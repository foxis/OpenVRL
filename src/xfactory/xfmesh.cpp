#include "common/all.h"
#include "system/ovrlsystem.h"
#include "xfactory/xfmesh.h"
#include "iosystem/fileiodev.h"
#include "common/pattern.h"
#include "system/ovrllog.h"

namespace openvrl {

/******************************************************************************
 * CxfMeshList class
 *****************************************************************************/
CxfMeshList::CxfMeshList(CxFactory* xf)
	:CxFactoryListTemplate<CxfMesh, CxfMeshList>(xf)
{
}

CxfMeshList::~CxfMeshList()
{
}

CxfMesh* CxfMeshList::create(const CTPLLib::CTPL_RAW& m,
		DWORD vtype, DWORD vusage,
		DWORD itype, DWORD iusage)
{
	CxfMesh* tmp = create(m.name);
	OVRL_ASSERT(tmp);
//	printf("xfMesh: create: %p, '%s'\n", tmp, m.name);
	tmp->create(m, vtype, vusage, itype, iusage);
//	printf("xfMesh: create: done\n", tmp, m.name);
	return tmp;
}

CxfMesh* CxfMeshList::create(const CString& _name, 
		CxfVertexBuffer* vb,
		CxfIndexBuffer* ib)
{
	CxfMesh* tmp = create(_name);
	OVRL_ASSERT(tmp);
	tmp->create(_name, vb, ib);
	return tmp;
}

CxfMesh* CxfMeshList::create(const CString&	_name,
		ulong vnum, DWORD vtype, 
		ulong inum, DWORD itype, 
		DWORD vusage,	DWORD iusage)
{
	CxfMesh* tmp = create(_name);
	OVRL_ASSERT(tmp);
	tmp->create(_name, vnum, vtype, inum, itype, vusage, iusage);
	return tmp;
}

int CxfMeshList::load_library(const CString& path, const CString& pattern, DWORD flags)
{
	CFileIOD f(0);
	CTPLLib	tpl(&f, 0, 1, 1);
	int rc;

	if ( tpl.open(path.c_str(), IOD_RDWR) )
	{
			ovrl_warning("xfMeshList: Couldn't open template...");
			return 1;
	}

	rc = load_library(&tpl, pattern, flags);
	tpl.close();
	return rc;
}

int CxfMeshList::load_library(CTPLLib* tpl, const CString& pattern, DWORD flags)
{
	ulong i;
	for ( i=0;i<tpl->rawmeshes();i++ )
	{
//		printf("xfMesh: probe %s\n", tpl->rawmesh(i)->name);
	if ( CPattern(pattern) == tpl->rawmesh(i)->name ) 
//		printf("xfMesh: recreating: %s\n", tpl->rawmesh(i)->name);
		create(*tpl->rawmesh(i), OVRL_VB_NORMAL, flags|USAGE_CONTAINS_LOCAL|USAGE_WRITEONLY, 0, flags|USAGE_CONTAINS_LOCAL|USAGE_WRITEONLY);
//		printf("xfMesh: recreating done\n", tpl->rawmesh(i)->name);
	}
	
	return 0;
}

int CxfMeshList::save_library(const CString& path)
{
	CFileIOD f(0);
	CTPLLib	tpl(&f, "Test TPL file", 1, 1);
	int rc;

	if ( tpl.open(path.c_str(), IOD_RDWR) )
	{
			ovrl_warning("xfMesh: Couldn't open template...");
			return 1;
	}

	rc = save_library(&tpl);
	tpl.close();
	return rc;
}
int CxfMeshList::save_library(CTPLLib* tpl)
{
	return 1;
}


/******************************************************************************
 * CxfMesh class
 *****************************************************************************/
CxfMesh::CxfMesh(CxfMeshList* xfl)
	: CxFactoryTemplate<CxfMeshList,CxfMesh>(xfl)
{
	m_initialized = false;
	m_initialized_normals = false;
	m_initialized_btree = false;
	OVRL_memset(m_states, 0, sizeof(m_states));
}

CxfMesh::~CxfMesh()
{
}

int CxfMesh::create()
{
	return 1;
}

int CxfMesh::create(const CTPLLib::CTPL_RAW& m,
		DWORD vtype, DWORD vusage,
		DWORD itype, DWORD iusage)
{
	ulong i;
	CxfMaterial* mat;
	C4x4Matrix	mtrx;

//	printf("cxfmesh: create\n");

	name() = m.name;

	vtype|=m.VB_flags;
	itype|=m.IB_flags;

//	printf("cxfmesh: create VB %p %p %p\n", xList(),xList()->xFactory(),xList()->xFactory()->vertex_buffers);
	VB() = xList()->xFactory()->vertex_buffers->create(m.verteces, (WORD)vtype, vusage);
//	printf("cxfmesh: create IB\n");
	IB() = xList()->xFactory()->index_buffers->create(m.faces*3, (WORD)itype, iusage);
	OVRL_ASSERT_EX(VB(),GENERAL,"No VB found");
	OVRL_ASSERT_EX(IB(),GENERAL,"No IB found");
	VB()->use();
	IB()->use();

//	printf("cxfmesh: vb/ib: %p/%p\n", VB(), IB());

	if ( m.VB_flags&OVRL_VB_NORMAL ) m_initialized_normals = true;
	
	// load verteces/indices
	//printf("cxfmesh: copy VB\n");
	VB()->lock();
	if ( vusage&OVRL_VB_CONTAINS_LOCAL ) 
		VB()->copy_to_local(m.VB, m.verteces, m.VB_flags);
	else
		VB()->copy_to_VB(m.VB, m.verteces, m.VB_flags);
	VB()->unlock();

	////	printf("cxfmesh: copy IB\n");
	IB()->lock();
	if ( iusage&OVRL_IB_CONTAINS_LOCAL ) 
		IB()->copy_to_local(m.IB, m.faces*3, m.IB_flags);
	else
		IB()->copy_to_IB(m.IB, m.faces*3, m.IB_flags);
	IB()->unlock();

	// load subsets
	for ( i=0;i<m.subsets;i++ )
	{
		TPL_MESHSUBSET ms = m.get_subset(i);
		mat = xList()->xFactory()->materials->find(ms.material);
//		printf("cxfmesh: subset: %p, %s\n", mat, ms.material);
		OVRL_ASSERT_EX(mat, GENERAL, "Could not find material");

		mtrx.data()[0] = ms.transform[0];	mtrx.data()[8] = ms.transform[8];
		mtrx.data()[1] = ms.transform[1];	mtrx.data()[9] = ms.transform[9];
		mtrx.data()[2] = ms.transform[2];	mtrx.data()[10] = ms.transform[10];
		mtrx.data()[3] = ms.transform[3];	mtrx.data()[11] = ms.transform[11];
		mtrx.data()[4] = ms.transform[4];	mtrx.data()[12] = ms.transform[12];
		mtrx.data()[5] = ms.transform[5];	mtrx.data()[13] = ms.transform[13];
		mtrx.data()[6] = ms.transform[6];	mtrx.data()[14] = ms.transform[14];
		mtrx.data()[7] = ms.transform[7];	mtrx.data()[15] = ms.transform[15];
		add_subset(Subset(mat, mtrx, ms.VB_index, ms.VB_size, ms.IB_index, ms.IB_size, ms.type));
	}

	return 0;
}

int CxfMesh::create(const CString& _name, 
		CxfVertexBuffer* vb,
		CxfIndexBuffer* ib)
{
	OVRL_ASSERT(vb);
	OVRL_ASSERT(ib);
	name() = _name;
	m_VB = vb;
	m_IB = ib;
	VB()->use();
	IB()->use();
	return 0;
}

int CxfMesh::create(const CString&	_name,
		ulong vnum, DWORD vtype, 
		ulong inum, DWORD itype, 
		DWORD vusage,	DWORD iusage)
{
	name() = _name;
	VB() = xList()->xFactory()->vertex_buffers->create(vnum, (WORD)vtype, vusage);
	IB() = xList()->xFactory()->index_buffers->create(inum, (WORD)itype, iusage);
	OVRL_ASSERT_EX(VB(), GENERAL, "No VB found");
	OVRL_ASSERT_EX(IB(), GENERAL, "No IB found");
	VB()->use();
	IB()->use();
	return 0;
}

int CxfMesh::lock()
{
	VB()->lock();
	IB()->lock();
	return 0;
}

int CxfMesh::unlock()
{
	IB()->unlock();
	VB()->unlock();
	return 0;
}

int CxfMesh::free()
{
	if ( VB() ) VB()->unuse();
	if ( IB() ) IB()->unuse();
	return 0;
}

int CxfMesh::SetShadowVolumeForSubset(ulong i, IBasicShadowVolume* sv)
{
	IBasicShadowVolume* tmp;
	if ( m_Subset.size()<=i )
		return 1;
	tmp = m_Subset[i].shadowVolume();
	if ( tmp ) { tmp->Release(); }
	m_Subset[i].shadowVolume() = sv;
	return 0;
}

#define V(nvb, ni) ( (vertex_t*)( ((BYTE*)(nvb)) + (ni)*(vcb) ) )

int CxfMesh::Initialize()
{
	vertex_t *vb, *tn;
	face_t *fb;

	if ( m_initialized ) return 0;
	OVRL_ASSERT(VB());
	OVRL_ASSERT(IB());

	if ( !(VB()->usage()&OVRL_VB_CONTAINS_LOCAL) ||
		!(IB()->usage()&OVRL_IB_CONTAINS_LOCAL) )
		return 1;

	if ( !(VB()->format()&OVRL_VB_NORMAL) )
		return 0;

	VB()->lock();
	IB()->lock();
	vb = (vertex_t*)VB()->local_pVB();
	fb = (face_t*)IB()->local_pIB();
	if ( m_initialized_normals==false )
	{
		const ulong vcb = VB()->vertex_size();
		const ulong fcb = IB()->index_size();
		const ulong fn = IB()->length()/3;
		const ulong vn = VB()->length();
		ulong *cvb = new ulong[vn];
		vertex_t	*nvb = new vertex_t[vn];
		ulong i;
		C3DVector a, b, c, n, na, nb;

		// initialize verteces&faces;
		OVRL_memset(VB()->pVB(), 0, VB()->length()*VB()->vertex_size());
		OVRL_memset(IB()->pIB(), 0, IB()->length()*IB()->index_size());
		OVRL_memset(cvb, 0, sizeof(ulong)*vn);
		OVRL_memset(nvb, 0, vn*sizeof(vertex_t));
		IB()->copy_local_to_IB();
		VB()->copy_local_to_VB();

		// initialize normals;

		for ( i=0;i<fn;i++ )
		{
			const ulong 
				A=fb[i].a,B=fb[i].b,C=fb[i].c;

			a = C3DVector(V(vb, A)->x, V(vb, A)->y, V(vb, A)->z);
			b = C3DVector(V(vb, B)->x, V(vb, B)->y, V(vb, B)->z);
			c = C3DVector(V(vb, C)->x, V(vb, C)->y, V(vb, C)->z);

			calc_normal(a,b,c,n);

			cvb[A]++;	cvb[B]++;	cvb[C]++;
			a = C3DVector(nvb[A].x, nvb[A].y, nvb[A].z) + n;
			b = C3DVector(nvb[B].x, nvb[B].y, nvb[B].z) + n;
			c = C3DVector(nvb[C].x, nvb[C].y, nvb[C].z) + n;

			//
			// @warning loosing precision
			//
			nvb[A].x = (short_real)a.x(); nvb[A].y = (short_real)a.y(); nvb[A].z = (short_real)a.z();
			nvb[B].x = (short_real)b.x(); nvb[B].y = (short_real)b.y(); nvb[B].z = (short_real)b.z();
			nvb[C].x = (short_real)c.x(); nvb[C].y = (short_real)c.y(); nvb[C].z = (short_real)c.z();
		}

		for ( i=0;i<vn;i++ )
		{
			const real s0 = 1;//1.0/(real)cvb[i];
			const real 
				x = nvb[i].x*s0,
				y = nvb[i].y*s0,
				z = nvb[i].z*s0;
			const real l = (real)(x*x+y*y+z*z);
			const real sl = 1.0/(l?sqrt(l):1.0); 

			tn = V(VB()->pVB(), i)+1;

			tn->x = (short_real)(x*sl);
			tn->y = (short_real)(y*sl);
			tn->z = (short_real)(z*sl);
		}

		delete[] cvb;
		delete[] nvb;

		m_initialized_normals = true;
	}
	IB()->unlock();
	VB()->unlock();

	for ( ulong i=0;i<m_Subset.size();i++ )
	{
		IBasicShadowVolume* tmp = m_Subset[i].shadowVolume();
		if ( tmp ) tmp->Prepare(this, i);
	}

	m_initialized = true;
	return 0;
}

void CxfMesh::release()
{
	delete this;
}

}