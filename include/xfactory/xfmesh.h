/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xfmesh.h,v $
 * $Implementation: /src/xfactory/xfMesh.cc $
 * $Revision: 1.6 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:08 $
 * $Description: Mesh class $
 *
 * $Log: xfmesh.h,v $
 * Revision 1.6  2005/07/14 12:14:08  foxis
 * no message
 *
 * Revision 1.5  2005/05/16 12:36:46  foxis
 * several CString & xFactory bugfixes
 *
 * Revision 1.4  2005/03/09 12:24:08  foxis
 * . fixed memory leaks
 * . fixed OVRL_ASSERT issue in release mode
 *   [still to fix: TPL_ASSERT, now - just a hack]
 *
 * Revision 1.3  2005/03/04 13:21:16  foxis
 * no message
 *
 * Revision 1.2  2005/03/01 18:21:16  foxis
 * Pipeline: shadows now working more or less. need to handle special cases.
 * C4x4Matrix: added inverse method + others
 *
 * Revision 1.1.1.1  2005/02/02 15:39:24  foxis
 * sources import
 *
 * Revision 0.1  20020117  20:30:00 FoxiE
 *  :)
 *
 */



#if !defined(__ovrl_XFMESH_HPP)
#define __ovrl_XFMESH_HPP

#include "common/all.h"
//#include "system/ovrlsystem.h"
#include "xfactory/xftemplate.h"
#include "xfactory/xfvertexbuf.h"
#include "xfactory/xfindexbuf.h"
#include "xfactory/xfmaterial.h"
#include "xfactory/xfactory.h"
#include "tpllib/tpl.hpp"
#include "pipeline/basicshadowvolume.h"

namespace openvrl {


class OVRLIBAPI CxFactory;
class OVRLIBAPI CxfMesh;
class OVRLIBAPI IBasicShadowVolume;
/**
 * CxfMeshList class
 */
class OVRLIBAPI CxfMeshList : public CxFactoryListTemplate<CxfMesh, CxfMeshList>
{
public:
	virtual CxfMesh* create(const CString& name)
	{
		CxfMesh* tmp = find(name);
		return (tmp)?(tmp):(CxFactoryListTemplate<CxfMesh, CxfMeshList>::create(name));
	}
	virtual CxfMesh* create(const CTPLLib::CTPL_RAW& m,
		DWORD vtype=0, 
		DWORD vusage=OVRL_VB_WRITEONLY,
		DWORD itype=0, 
		DWORD iusage=OVRL_IB_WRITEONLY);
	virtual CxfMesh* create(const CString& _name, 
		CxfVertexBuffer* vb,
		CxfIndexBuffer* ib);
	virtual CxfMesh* create(const CString&	_name,
		ulong vnum, DWORD vtype, 
		ulong inum, DWORD itype, 
		DWORD vusage=OVRL_VB_WRITEONLY,
		DWORD iusage=OVRL_IB_WRITEONLY);

	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int save_library(const CString& path);
	virtual int save_library(CTPLLib* tpl);

	/** 
	 *
	 */
	CxfMeshList(CxFactory* xf);
	virtual ~CxfMeshList();
};

/**
 * CxfMesh class
 */
class OVRLIBAPI CxfMesh : public CxFactoryTemplate<CxfMeshList, CxfMesh>
{
public:
	typedef struct vertex_struct { short_real x,y,z;} vertex_t;
	typedef struct face_struct { ushort a, b, c;} face_t;

	class OVRLIBAPI Subset
	{
		CxfMaterial*		m_material;
		IBasicShadowVolume  *m_ShadowVolume;
		ulong				m_type;
		ulong				m_VB_index;
		ulong				m_VB_size;
		ulong				m_IB_index;
		ulong				m_IB_size;
		C4x4Matrix			m_matrix;

	public:
		Subset() 
		{
			material() = 0;
			matrix().set_identity();
			VB_index() = 0;
			IB_index() = 0;
			VB_size() = 0;
			IB_size() = 0;
			type() = 0;
			shadowVolume() = 0;
		}
		Subset(CxfMaterial* m, const C4x4Matrix& matrx, ulong VBi, ulong VBs, ulong IBi, ulong IBs, ulong tp=0) 
		{
			material() = m;
			if ( m_material ) m_material->use();
			matrix().set(matrx);
			VB_index() = VBi;
			IB_index() = IBi;
			VB_size() = VBs;
			IB_size() = IBs;
			type() = tp;
			shadowVolume() = 0;
		}
		Subset(const Subset& s) { *this = s; }
		~Subset() { Release(); }

		Subset& operator=(const Subset& s)
		{
			material() = s.material();
			if ( m_material ) m_material->use();
			matrix().set(s.matrix());
			VB_index() = s.VB_index();
			IB_index() = s.IB_index();
			VB_size() = s.VB_size();
			IB_size() = s.IB_size();
			type() = s.type();
			shadowVolume() = s.shadowVolume();
//			if ( shadowVolume() ) shadowVolume()->use();
			return *this;
		}

		void Release()
		{
			if ( m_material ) { m_material->unuse(); m_material = 0; }
			if ( m_ShadowVolume ) { m_ShadowVolume->Release(); m_ShadowVolume = 0; }
		}

		ulong				type() const { return m_type; }
		CxfMaterial*	material() const { return m_material; }
		IBasicShadowVolume*	shadowVolume() const { return m_ShadowVolume; }
		C4x4Matrix			matrix() const { return m_matrix; }
		ulong				VB_index() const { return m_VB_index; }
		ulong				VB_size() const { return m_VB_size; }
		ulong				IB_index() const { return m_IB_index; }
		ulong				IB_size() const { return m_IB_size; }
		ulong&				type() { return m_type; }
		CxfMaterial*&	material() { return m_material; }
		IBasicShadowVolume*&	shadowVolume() { return m_ShadowVolume; }
		C4x4Matrix&			matrix() { return m_matrix; }
		ulong&				VB_index() { return m_VB_index; }
		ulong&				VB_size() { return m_VB_size; }
		ulong&				IB_index() { return m_IB_index; }
		ulong&				IB_size() { return m_IB_size; }
	};

protected:
	CxfVertexBuffer* m_VB;
	CxfIndexBuffer* m_IB;
	std::vector<Subset>	m_Subset;
	bool	m_initialized;
	bool	m_initialized_normals;
	bool	m_initialized_btree;
	bool	m_states[8];

public:
	const CxfVertexBuffer* VB() const { return m_VB; }
	const CxfIndexBuffer* IB() const { return m_IB; }
	const std::vector<Subset>& Subsets() const { return m_Subset; }
	const Subset& getSubset(ulong i) const { return m_Subset[i]; }
	CxfVertexBuffer*& VB() { return m_VB; }
	CxfIndexBuffer*& IB() { return m_IB; }
	std::vector<Subset>& Subsets() { return m_Subset; }
	Subset& getSubset(ulong i) { return m_Subset[i]; }

	ulong numSubsets() const { return (TPL_ulong)Subsets().size(); }

	void add_subset(const Subset& s) {	m_Subset.push_back(s); }
	void erase_subsets() {	m_Subset.erase(m_Subset.begin(), m_Subset.end()); }
	Subset& get_subset(ulong i) { return m_Subset[i]; }

	/**
	 *
	 */
	virtual int lock();
	virtual int unlock();
	virtual int create();
	virtual int free();
	virtual void release();

	bool locked() const { return m_VB->locked()&&m_IB->locked(); }
	bool created() const { return m_VB&&m_IB; }
	bool local_created() const { return true; }

	virtual int create(const CTPLLib::CTPL_RAW& m,
		DWORD vtype=0, 
		DWORD vusage=OVRL_VB_WRITEONLY,
		DWORD itype=0, 
		DWORD iusage=OVRL_IB_WRITEONLY);
	virtual int create(const CString& _name, 
		CxfVertexBuffer* vb,
		CxfIndexBuffer* ib);
	virtual int create(const CString&	_name,
		ulong vnum, DWORD vtype, 
		ulong inum, DWORD itype, 
		DWORD vusage=OVRL_VB_WRITEONLY,
		DWORD iusage=OVRL_IB_WRITEONLY);

	virtual int Initialize();
	virtual int SetShadowVolumeForSubset(ulong, IBasicShadowVolume*);

	//
	static void calc_normal(const C3DVector& a, const C3DVector& b, const C3DVector& c, C3DVector& n);

	//
	CxfMesh(CxfMeshList* xfl);
	virtual ~CxfMesh();
};

inline 
void CxfMesh::calc_normal(const C3DVector& a, const C3DVector& b, const C3DVector& c, C3DVector& n)
{
	C3DVector na,nb;
	na = a-b;
	nb = a-c;
	n =	na.cross(nb);
	n.normalize();
}

};

#endif /* !defined(__ovrl_XFMESH_HPP) */
