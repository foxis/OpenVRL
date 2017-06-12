/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/3dbvl.h,v $
 * $Implementation: ~/src/ $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:10 $
 * $Description:  $
 *
 * $Log: 3dbvl.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:10  foxis
 * sources import
 *
 * Revision 0.3  20010411  :: FoxiE
 *
 */

#if !defined(AFX_COM3DBVL_H__AD53EB61_AD2D_11D6_8083_83FE36408134__INCLUDED_)
#define AFX_COM3DBVL_H__AD53EB61_AD2D_11D6_8083_83FE36408134__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common/vector.h"
#include "common/shapes.h"
#include "common/matrix.h"

namespace openvrl {

//
// 3DVolume
//
class OVRLIBAPI C3DBoundingVolume  
{
public:
	enum BoundingVolume_enum
	{
		VOLUME_AABB,
		VOLUME_OBB,
		VOLUME_BS,
		UNINITIALIZED = 0xFFFFFFFE,
		FORCE_DWORD = 0xFFFFFFFF
	};

protected:
	BoundingVolume_enum	m_type;
	struct OVRLIBAPI BoundingVolume_union
	{
		C3DBox	m_AABB;		// axis alligned bounding box
		C3DOrientedBox	m_OBB;	// oriented bounding box
		C3DSphere		m_BS;	// bounding sphere
		// more comming...
	} m_volume;

public:
	C3DBoundingVolume()
	{
		m_type = UNINITIALIZED;
	}
	C3DBoundingVolume(const C3DBox& box)
	{
		m_type = VOLUME_AABB;
		m_volume.m_AABB = box;
	}
	C3DBoundingVolume(const C3DOrientedBox& obox)
	{
		m_type = VOLUME_OBB;
		m_volume.m_OBB = obox;
	}
	C3DBoundingVolume(const C3DSphere& sphere)
	{
		m_type = VOLUME_BS;
		m_volume.m_BS = sphere;
	}
	C3DBoundingVolume(const C3DBoundingVolume& v)
	{
		*this = v;
	}
	~C3DBoundingVolume()
	{
	}

	//////////
	//
	int create(const C3DPoint* p, ulong n, BoundingVolume_enum=VOLUME_OBB);

	//////////
	BoundingVolume_enum	type() const { return m_type; }
	BoundingVolume_enum&	type() { return m_type; }

	C3DBox	AABB() const { return m_volume.m_AABB; }
	C3DOrientedBox	OBB() const { return m_volume.m_OBB; }
	C3DSphere	BS() const { return m_volume.m_BS; }

	C3DBox&	AABB() { return m_volume.m_AABB; }
	C3DOrientedBox&	OBB() { return m_volume.m_OBB; }
	C3DSphere&	BS() { return m_volume.m_BS; }

protected:
	int create_OBB(const C3DPoint* p, ulong n);
	int create_AABB(const C3DPoint* p, ulong n);
	int create_BS(const C3DPoint* p, ulong n);
};

//
//
//
template<class BV, class T>
class OVRLIBAPI CQuadTreeNode
{
public:
	enum type_enum { leaf, node, illegal } m_type;
	union OVRLIBAPI {
		CQuadTreeNode	*m_pointers[4];
		T		m_leaf_data;
	};
	BV	m_bounding_volume;

public:
	CQuadTreeNode() 
	{
		m_type = leaf;
	}
	~CQuadTreeNode() 
	{
		Destroy();
	}

	//
	//
	//
	void Destroy()
	{
		if ( type()==node )
		{
			if ( m_pointers[0] ) m_pointers[0]->Destroy();
			if ( m_pointers[1] ) m_pointers[1]->Destroy();
			if ( m_pointers[2] ) m_pointers[2]->Destroy();
			if ( m_pointers[3] ) m_pointers[3]->Destroy();
		} else if ( type()==leaf )
			leaf_data().Destroy();
	}

	//
	// member data access functions
	//
	type_enum type() const { return m_type; }
	type_enum& type() { return m_type; }
	T leaf_data() const { return m_leaf_data; }
	T& leaf_data() { return m_leaf_data; }
	BV bounding_volume() const { return m_bounding_volume; }
	BV& bounding_volume() { return m_bounding_volume; }
};

//
// AABB quad tree
//
class OVRLIBAPI CAABBTree
{
	class OVRLIBAPI LeafData {
	public:
		ulong	num_triangles;
		ulong	*triangles;

		void Destroy()
		{
			delete[] triangles;
		}
	};

protected:
	CQuadTreeNode<C3DBox, LeafData>	m_root;
	ulong	m_num_points;	//
	ulong	m_num_triangles;
	real	*m_points;		// size = num_points*3;
	ulong	*m_triangles;	// size = num_triangles*3;
	C4x4Matrix	m_matrix;

public:
	CAABBTree();
	~CAABBTree();

	virtual int build();
};

};

#endif // !defined(AFX_COM3DBVL_H__AD53EB61_AD2D_11D6_8083_83FE36408134__INCLUDED_)
