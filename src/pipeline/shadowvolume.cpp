#include "common/all.h"
#include "system/ovrlsystem.h"
#include "pipeline/shadowvolume.h"

namespace openvrl {

#define V(nvb, ni) ( (CxfMesh::vertex_t*)( ((BYTE*)(nvb)) + (ni)*(vcb) ) )
#define V1(nvb, ni) ( (vrtx_t*)( ((BYTE*)(nvb)) + (ni)*(vcb1) ) )

CShadowVolume::CShadowVolume()
{
	m_Mesh = 0;
	m_SVVB = 0;
	m_SVIB = 0;

	m_Adjecency = 0;
	m_Edge = 0;
	m_Normal = 0;
	m_Normal1 = 0;
	m_Origin = 0;
	m_Origin1 = 0;
	m_Pipeline = 0;
}

CShadowVolume::CShadowVolume(IPipeline* pl)
{
	OVRL_ASSERT(pl);
	m_Mesh = 0;
	m_SVVB = 0;
	m_SVIB = 0;

	m_Adjecency = 0;
	m_Edge = 0;
	m_Normal = 0;
	m_Normal1 = 0;
	m_Origin = 0;
	m_Origin1 = 0;
	m_Pipeline = pl;
}

CShadowVolume::~CShadowVolume()
{
	Release();
}

void CShadowVolume::Prepare(CxfMesh* m, ulong subset)
{
	ulong f0, v0;
	ulong fn, vn;
	ulong i, j, vcb;
	ADJ_t* adj;
	CxfMesh::vertex_t *vb;
	CxfMesh::face_t *fb;
	C3DVector a,b,c,n,abc;

	OVRL_ASSERT(m_Mesh==0);
	OVRL_ASSERT(m);

	OVRL_ASSERT(m->Subsets().size()>subset);
	OVRL_ASSERT_EX(m->VB()->local_created(), GENERAL, "Local Vertex buffer must be created!");
	OVRL_ASSERT_EX(m->IB()->local_created(), GENERAL, "Local Index buffer must be created!");

	m_Mesh = m;

	m->use();

	m_Subset = &m_Mesh->getSubset(subset);

	f0 = m_Subset->VB_index();
	v0 = m_Subset->IB_index();
	vn = m_Subset->VB_size();
	fn = m_Subset->IB_size()/3;

	m_Normal = OVRL_NEW(vector3d_t, fn);
	m_Normal1 = OVRL_NEW(vector3d_t, fn);
	m_Origin = OVRL_NEW(vector3d_t, fn);
	m_Origin1 = OVRL_NEW(vector3d_t, fn);
	m_Adjecency = OVRL_NEW(ADJ_t, fn);
	m_Edge = OVRL_NEW(ulong, fn*12);
	OVRL_memset(m_Normal, 0, fn*sizeof(*m_Normal));
	OVRL_memset(m_Normal1, 0, fn*sizeof(*m_Normal1));
	OVRL_memset(m_Origin, 0, fn*sizeof(*m_Origin));
	OVRL_memset(m_Origin1, 0, fn*sizeof(*m_Origin1));
	OVRL_memset(m_Adjecency, 0, fn*sizeof(*m_Adjecency));
	OVRL_memset(m_Edge, 0, fn*12*sizeof(*m_Edge));

	vb = (CxfMesh::vertex_t*)m_Mesh->VB()->local_pVB() + v0;
	fb = (CxfMesh::face_t*)m_Mesh->IB()->local_pIB() + f0;
	vcb = m_Mesh->VB()->vertex_size();

	m_SVVB = m_Pipeline->vertex_buffers->create(fn*12, OVRL_VB_XYZ, USAGE_WRITEONLY);
	m_SVIB = m_Pipeline->index_buffers->create(fn*6, OVRL_IB_16, USAGE_WRITEONLY);
	OVRL_ASSERT(m_SVVB);
	OVRL_ASSERT(m_SVIB);
	m_SVVB->use();
	m_SVIB->use();

	// calc normals for every face
	// @todo
	for ( i=0;i<fn;i++ )
	{
		const ulong A=fb[i].a,B=fb[i].b,C=fb[i].c;

		a = C3DVector(V(vb, A)->x, V(vb, A)->y, V(vb, A)->z);
		b = C3DVector(V(vb, B)->x, V(vb, B)->y, V(vb, B)->z);
		c = C3DVector(V(vb, C)->x, V(vb, C)->y, V(vb, C)->z);
		abc = (a+b+c);

		CxfMesh::calc_normal(a,b,c,n);

		m_Normal[i].x = n.x();
		m_Normal[i].y = n.y();
		m_Normal[i].z = n.z();

		m_Origin[i].x = abc.x()/3.0;
		m_Origin[i].y = abc.y()/3.0;
		m_Origin[i].z = abc.z()/3.0;
	}

	OVRL_memcpy(m_Normal1, m_Normal, fn*sizeof(*m_Normal1));
	OVRL_memcpy(m_Origin1, m_Origin, fn*sizeof(*m_Origin1));

	// build face adjecency
	for ( adj=m_Adjecency,i=0;i<fn;i++,adj++ )
	{
		ulong a, b, f1=-1,f2=-1,f3=-1;

		a = fb[i].a;
		b = fb[i].b;
		for ( j=0;j<fn;j++ ) if ( j!=i )
		{
			if ( (fb[j].a==a || fb[j].b==a || fb[j].c==a) && 
				(fb[j].a==b || fb[j].b==b || fb[j].c==b) &&
				(fb[j].a!=fb[j].b && fb[j].a!=fb[j].c && fb[j].b!=fb[j].c) )
				if ( f1==-1 ) 
					f1 = j;
				else
					OVRL_ASSERT_EX(false, GENERAL, "found T junction!");
		}

		a = fb[i].b;
		b = fb[i].c;
		for ( j=0;j<fn;j++ ) if ( j!=i )
		{
			if ( (fb[j].a==a || fb[j].b==a || fb[j].c==a) && 
				(fb[j].a==b || fb[j].b==b || fb[j].c==b) &&
				(fb[j].a!=fb[j].b && fb[j].a!=fb[j].c && fb[j].b!=fb[j].c) )
				if ( f2==-1 ) 
					f2 = j;
				else
					OVRL_ASSERT_EX(false, GENERAL, "found T junction!");
		}

		a = fb[i].c;
		b = fb[i].a;
		for ( j=0;j<fn;j++ ) if ( j!=i )
		{
			if ( (fb[j].a==a || fb[j].b==a || fb[j].c==a) && 
				(fb[j].a==b || fb[j].b==b || fb[j].c==b) &&
				(fb[j].a!=fb[j].b && fb[j].a!=fb[j].c && fb[j].b!=fb[j].c) )
				if ( f3==-1 ) 
					f3 = j;
				else
					OVRL_ASSERT_EX(false, GENERAL, "found T junction!");
		}

		OVRL_ASSERT_EX(f1!=-1 && f2!=-1 && f3!=-1, GENERAL, "found triangle with less than 3 neighbours!");
		adj->face[0] = f1;
		adj->face[1] = f2;
		adj->face[2] = f3;
	}
}

void CShadowVolume::Build(const C3DVector& v, real r)
{
	OVRL_ASSERT(m_Mesh&&m_Adjecency&&m_Normal1&&m_Edge);
	CxfMesh::face_t *fb;
	CxfMesh::vertex_t *vb;
	fc_t *fb1;
	vrtx_t *vb1;
	ulong f0, v0;
	ulong fn, vn;
	ulong i, j, vcb, vcb1, vi, ii;
	C3DVector n, p;

	f0 = m_Subset->VB_index();
	v0 = m_Subset->IB_index();
	vn = m_Subset->VB_size();
	fn = m_Subset->IB_size()/3;

	vb = (CxfMesh::vertex_t*)m_Mesh->VB()->local_pVB() + v0;
	fb = (CxfMesh::face_t*)m_Mesh->IB()->local_pIB() + f0;
	vcb = m_Mesh->VB()->vertex_size();
	for ( i=0,j=0;i<fn;i++ )
	{
		const C3DVector
			n(m_Normal1[i].x,m_Normal1[i].y,m_Normal1[i].z),
			o(m_Origin1[i].x,m_Origin1[i].y,m_Origin1[i].z);

		p = o-v;

		real d = p.dot(n);

		if ( d>0 )
			continue;

		const ulong 
			a = m_Adjecency[i].face[0], 
			b = m_Adjecency[i].face[1], 
			c = m_Adjecency[i].face[2];
		const C3DVector
			na(m_Normal1[a].x,m_Normal1[a].y,m_Normal1[a].z),
			nb(m_Normal1[b].x,m_Normal1[b].y,m_Normal1[b].z),
			nc(m_Normal1[c].x,m_Normal1[c].y,m_Normal1[c].z);

		if ( na.dot(p)>0 ) 
		{
			// add the edge
			m_Edge[j] = fb[i].a;
			j++;
			m_Edge[j] = fb[i].b;
			j++;
		}
		if ( nb.dot(p)>0 ) 
		{
			// add the edge
			m_Edge[j] = fb[i].b;
			j++;
			m_Edge[j] = fb[i].c;
			j++;
		}
		if ( nc.dot(p)>0 ) 
		{
			// add the edge
			m_Edge[j] = fb[i].c;
			j++;
			m_Edge[j] = fb[i].a;
			j++;
		}
	}
	m_Edges = j>>1; // /2

	VB()->lock(0,VB()->length());
	IB()->lock(0,IB()->length());
	vb1 = (vrtx_t*)VB()->pVB();
	fb1 = (fc_t*)IB()->pIB();
	vcb1 = VB()->vertex_size();

	for ( i=j=vi=ii=0;i<m_Edges;i++ )
	{
		ulong
			_a = m_Edge[i*2],
			_b = m_Edge[i*2 + 1];
		C3DVector 
			a(V(vb, _a)->x,V(vb, _a)->y,V(vb, _a)->z),
			b(V(vb, _b)->x,V(vb, _b)->y,V(vb, _b)->z),
			c;

		OVRL_memcpy(V1(vb1, vi), V(vb,_a), sizeof(vrtx_t));
		OVRL_memcpy(V1(vb1, vi+1), V(vb,_b), sizeof(vrtx_t));

		c = b-v;
		c.normalize();
		c *= r;
		V1(vb1, vi+2)->x  = (short_real)(b+c).x();
		V1(vb1, vi+2)->y  = (short_real)(b+c).y();
		V1(vb1, vi+2)->z  = (short_real)(b+c).z();

		c = a-v;
		c.normalize();
		c *= r;
		V1(vb1, vi+3)->x  = (short_real)(a+c).x();
		V1(vb1, vi+3)->y  = (short_real)(a+c).y();
		V1(vb1, vi+3)->z  = (short_real)(a+c).z();

		fb1[ii].a = (ushort)vi+0; 
		fb1[ii].b = (ushort)vi+1; 
		fb1[ii].c = (ushort)vi+2;
		fb1[ii+1].a = (ushort)(vi+2); 
		fb1[ii+1].b = (ushort)(vi+3); 
		fb1[ii+1].c = (ushort)(vi+0);

		vi+=4;
		ii+=2;
	}

	m_VB_length = vi;
	m_IB_length = ii*3;

	//m_VB_length = 3;
	//m_IB_length = 3;
	//fb1[0].a = 0;
	//fb1[0].b = 1;
	//fb1[0].c = 2;
	//V1(vb1,0)->x = V1(vb1,0)->y = V1(vb1,0)->y = 0;
	//V1(vb1,1)->x = 0;
	//V1(vb1,1)->y = 0;
	//V1(vb1,1)->z = 10;
	//V1(vb1,2)->x = 10;
	//V1(vb1,2)->y = 0;
	//V1(vb1,2)->z = 10;

	VB()->unlock();
	IB()->unlock();
}

void CShadowVolume::Release()
{
	OVRL_ASSERT(m_Pipeline);
	if ( m_Mesh ) { m_Mesh->unuse(); m_Mesh = 0; }
	if ( m_SVVB ) { m_SVVB->unuse(); m_SVVB = 0; }
	if ( m_SVIB ) { m_SVIB->unuse(); m_SVIB = 0; }
	if ( m_Normal ) { delete[] m_Normal; m_Normal = 0; }
	if ( m_Edge ) { delete[] m_Edge; m_Edge = 0; }
	if ( m_Adjecency ) { delete[] m_Adjecency; m_Adjecency = 0; }
}

};

