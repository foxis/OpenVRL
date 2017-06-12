#include "system/ovrlsystem.h"
#include "world/body.h"
#include "pipeline/shadowvolume.h"

namespace openvrl {

CBody::CBody()
	:CBasicEntity()
{
	m_TransformMatrix.set_identity();
	m_WorldTransformMatrix.set_identity();
	m_Mesh = 0;
	m_TypeBits = OVRL_BT_MOVEABLE | OVRL_BT_PHYSICSABLE | OVRL_BT_CANAFFECTOTHERS;
}

CBody::~CBody()
{
}

C4x4Matrix& CBody::GetTransformMatrix()
{
	return m_TransformMatrix;
}
C4x4Matrix& CBody::GetWorldTransformMatrix()
{
	return m_WorldTransformMatrix;
}

void CBody::Release()
{
	if ( m_Mesh ) { m_Mesh->unuse(); m_Mesh =0; }
	CBasicEntity::Release();
}

void CBody::Attach(CxfMesh* mesh, bool shadowcaster)
{
	OVRL_ASSERT(m_Mesh==0);
	OVRL_ASSERT(mesh);
	if ( m_Mesh )	m_Mesh->unuse();	// this should never happen in debug
	m_Mesh = mesh;
	if ( !m_Mesh ) return;
	m_Mesh->use();
	if ( shadowcaster && m_Mesh->ref_count()==1 )
		for ( ulong i=0;i<m_Mesh->Subsets().size();i++ )
			m_Mesh->getSubset(i).shadowVolume() = new CShadowVolume(GetPipeline());
	m_Mesh->Initialize();
}

void CBody::Attach(const CString& path, int what, bool shadowcaster)
{
	OVRL_ASSERT(m_Mesh==0);
	OVRL_ASSERT_EX(what==0, NOTIMPLEMENTED, "CBody only supports mesh templates");

	m_Mesh = GetPipeline()->meshes->find(path);
	OVRL_ASSERT_EX(m_Mesh, GENERAL, "Could not find specified mesh");
	if ( m_Mesh ) // in debug mode assertion should happen. this is for release
	{
		m_Mesh->use();
		if ( shadowcaster && m_Mesh->ref_count()==1 )
			for ( ulong i=0;i<m_Mesh->Subsets().size();i++ )
				m_Mesh->getSubset(i).shadowVolume() = new CShadowVolume(GetPipeline());
		m_Mesh->Initialize();
	}
}

void CBody::UpdatePhysics(real time_step)
{
	C3DVector v;
	C4x4Matrix m;
//	C4x4Matrix t;

	v = GetPosition();
	m = GetOrientationMatrix();

	m_WorldTransformMatrix = m;
	m_WorldTransformMatrix.mul(C4x4Matrix::translate(v.x(),v.y(),v.z()));
}

void CBody::PrecalculateWorldMatrix()
{
	m_PrecalculatedMatrix.set(m_TransformMatrix);
	m_PrecalculatedMatrix.mul(m_WorldTransformMatrix);
}

};