/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/shadowvolume.h,v $
 * $Implementation: $
 * $Revision: 1.1 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description:  $
 *
 * $Log: shadowvolume.h,v $
 * Revision 1.1  2005/03/04 13:21:16  foxis
 * no message
 *
 *
 */

#if !defined(__ovrl_SHADOWVOLUME_H)
#define __ovrl_SHADOWVOLUME_H

#include "common/all.h"
#include "pipeline/basicshadowvolume.h"
#include "pipeline/pipeline.h"
#include "xfactory/xfactory.h"

namespace openvrl {

class OVRLIBAPI CShadowVolume : public IBasicShadowVolume
{
	typedef struct vrtx_struct
	{
		float x, y, z;
	} vrtx_t;
	typedef struct fc_struct
	{
		ushort a, b, c;
	} fc_t;

	typedef struct EDGE_struct
	{
		ulong vertex[2];
	} EDGE_t;
	typedef struct ADJ_struct
	{
		ulong face[3];
	} ADJ_t;

	IPipeline* m_Pipeline;
	CxfMesh* m_Mesh;
	CxfMesh::Subset *m_Subset;
	CxfVertexBuffer* m_SVVB;
	CxfIndexBuffer*	m_SVIB;

	ADJ_t *m_Adjecency;
	ulong *m_Edge;
	ulong m_Edges;
	ulong m_IB_length;
	ulong m_VB_length;

	vector3d_t *m_Normal;
	vector3d_t *m_Normal1;
	vector3d_t *m_Origin;
	vector3d_t *m_Origin1;

protected:
	CShadowVolume();

public:
	CShadowVolume(IPipeline*);
	virtual ~CShadowVolume();

	virtual void Prepare(CxfMesh*, ulong subset);

	virtual void Build(const C3DVector&, real);
	virtual void Release();

	virtual CxfVertexBuffer* VB() { return m_SVVB; }
	virtual CxfIndexBuffer* IB() { return m_SVIB; }

	virtual ulong VB_length() const { return m_VB_length; }
	virtual ulong IB_length() const { return m_IB_length; }
};

};

#endif