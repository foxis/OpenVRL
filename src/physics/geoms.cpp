#include "physics/geoms.h"


namespace openvrl
{

///////////////////////////////////////////////////////////////////////////////
// Basic ODE geometry wrapper
//
CBasicODEGeom::CBasicODEGeom()
{
	m_Geom = 0;
	m_Body = 0;
	m_Parent = 0;
}

CBasicODEGeom::~CBasicODEGeom()
{
	Release();
}

void CBasicODEGeom::SetGeom(dGeomID g)
{
	OVRL_ASSERT(m_Geom==0);
	OVRL_ASSERT(g);
	m_Geom = g;
}

//
// IBasicGeom
//
void CBasicODEGeom::Create(IBasicBody* b)
{
	OVRL_ASSERT(m_Geom==0);
	Create();
	Attach(b);
}

void CBasicODEGeom::Prepare()
{
//	if ( m_Body && m_Geom )
//	{
//		OVRL_ASSERT(m_Body->GetPhysicsEngine());
		// @todo ICollisionSpace
		//  if body is not assigned to any of spaces
		//  then add to the default space
		//
		// clients should add geoms themselves on PreparePhysics
		//
//		dSpaceAdd(m_Body->GetPhysicsEngine()->GetSpace(), m_Geom);
//	}
}

void CBasicODEGeom::Release()
{
	if ( m_Parent )
	{
		// donno if this is safe..
		// if some spaces/geoms are not released during CWorldSector::Release
		// then there will be an attempt to do this in CPhysicsEngine::Release
		// that's where it'll crash probably... because std:list isn't capable of
		// iterating and removing/inserting of items at the same time...
		//m_Parent->Remove(this);	

		dSpaceRemove(m_Parent->GetSpace(), GetGeom());
		m_Parent = 0;
	}

	if ( m_Geom )
	{
		Attach(0);
		dGeomDestroy(m_Geom);
		m_Geom = 0;
	}
}

void CBasicODEGeom::onInsert(IBasicSpace* s)
{
	OVRL_ASSERT(s);
	OVRL_ASSERT(m_Parent==0);
	m_Parent = s;
	dSpaceAdd(s->GetSpace(), GetGeom());
}

void CBasicODEGeom::onRemove(IBasicSpace* s)
{
	OVRL_ASSERT(s);
	OVRL_ASSERT(m_Parent==s);
	m_Parent = 0;
	dSpaceRemove(s->GetSpace(), GetGeom());
}

void CBasicODEGeom::Update()
{
//	if ( m_Body )
//	{
//		C3DVector pos;
//		C4x4Matrix orient;
//
//		pos = m_Body->GetPosition();
//		orient = m_Body->GetOrientationMatrix();
//
//		SetPosition(pos);
//		SetOrientationMatrix(orient);
//	}
}

void CBasicODEGeom::Attach(IBasicBody* b)
{
	OVRL_ASSERT(m_Body==0 || b==0);
	OVRL_ASSERT(m_Geom);
	m_Body = b;
	if ( m_Body ) 
	{
		dGeomSetBody(m_Geom, m_Body->GetBody());
		dGeomSetData(m_Geom, m_Body);
	}
	else
	{
		dGeomSetBody(m_Geom, 0);
		dGeomSetData(m_Geom, 0);
	}
}

bool CBasicODEGeom::IsPlaceable() const
{
	return true;	// @todo implement
}

void CBasicODEGeom::Enable(bool en)
{
	OVRL_ASSERT(m_Geom);
	if ( en )
		dGeomEnable(m_Geom);
	else
		dGeomDisable(m_Geom);
}

bool CBasicODEGeom::IsEnabled() const
{
	OVRL_ASSERT(m_Geom);
	return dGeomIsEnabled(m_Geom)==1;
}

C3DVector CBasicODEGeom::GetPosition() const
{
	OVRL_ASSERT(m_Geom);
	const dReal *dv;
	dv = dGeomGetPosition(m_Geom);
	return C3DVector(dv[0], dv[1], dv[2]);
}

C3DVector CBasicODEGeom::GetOrientation() const
{
	OVRL_ASSERT(m_Geom);
	const dReal *dv;
	C4x4Matrix m;
	C3DVector v(1,0,0);
	dv = dGeomGetRotation(m_Geom);
	m.set(dv[0], dv[4], dv[8], 0, dv[1],dv[5],dv[9], 0, dv[2],dv[6],dv[10], 0, 0,0,0,1);
//	m.set(dv[0], dv[1], dv[2], 0, dv[4],dv[5],dv[6], 0, dv[8],dv[9],dv[10], 0, 0,0,0,1);
	v.mul(m);
	return v;
}

C4x4Matrix CBasicODEGeom::GetOrientationMatrix() const
{
	OVRL_ASSERT(m_Geom);
	const dReal *dv;
	C4x4Matrix m;
	dv = dGeomGetRotation(m_Geom);
	m.set(dv[0], dv[4], dv[8], 0, dv[1],dv[5],dv[9], 0, dv[2],dv[6],dv[10], 0, 0,0,0,1);
//	m.set(dv[0], dv[1], dv[2], 0, dv[4],dv[5],dv[6], 0, dv[8],dv[9],dv[10], 0, 0,0,0,1);
	return m;
}

const void* CBasicODEGeom::GetUserData() const
{
	OVRL_ASSERT(m_Geom);
	return dGeomGetData(m_Geom);
}

C3DBoundingVolume CBasicODEGeom::GetBoudingVolume() const
{
	OVRL_ASSERT(m_Geom);
	return C3DBoundingVolume();
}


void CBasicODEGeom::SetPosition(const C3DVector& dv)
{
	OVRL_ASSERT(m_Geom);
	dGeomSetPosition(m_Geom, dv.x(), dv.y(), dv.z());
}

void CBasicODEGeom::SetOrientation(const C3DVector& dv)
{
	OVRL_ASSERT(m_Geom);
	C4x4Matrix m;
	dMatrix3 dm;
	m.set_rotate(dv.x(), dv.y(), dv.z());
	OVRL_memset(&dm, 0, sizeof(dm));
	dm[0] = m.data()[0];
	dm[1] = m.data()[4];
	dm[2] = m.data()[8];
	dm[4] = m.data()[1];
	dm[5] = m.data()[5];
	dm[6] = m.data()[9];
	dm[8] = m.data()[2];
	dm[9] = m.data()[6];
	dm[10] = m.data()[10];
	dGeomSetRotation(m_Geom, dm);
}

void CBasicODEGeom::SetOrientationMatrix(const C4x4Matrix& m)
{
	OVRL_ASSERT(m_Geom);
	dMatrix3 dm;
	OVRL_memset(&dm, 0, sizeof(dm));
	dm[0] = m.data()[0];
	dm[1] = m.data()[4];
	dm[2] = m.data()[8];
	dm[4] = m.data()[1];
	dm[5] = m.data()[5];
	dm[6] = m.data()[9];
	dm[8] = m.data()[2];
	dm[9] = m.data()[6];
	dm[10] = m.data()[10];
	dGeomSetRotation(m_Geom, dm);
}

void CBasicODEGeom::SetUserData(void* data)
{
	OVRL_ASSERT(m_Geom);
	dGeomSetData(m_Geom, data);
}

ulong CBasicODEGeom::GetCategoryBits() const
{
	OVRL_ASSERT(m_Geom);
	return dGeomGetCategoryBits(m_Geom);
}

ulong CBasicODEGeom::GetCollideBits() const
{
	OVRL_ASSERT(m_Geom);
	return dGeomGetCollideBits(m_Geom);
}

void CBasicODEGeom::SetCategoryBits(ulong ul)
{
	OVRL_ASSERT(m_Geom);
	dGeomSetCategoryBits(m_Geom, ul);
}

void CBasicODEGeom::SetCollideBits(ulong ul)
{
	OVRL_ASSERT(m_Geom);
	dGeomSetCollideBits(m_Geom, ul);
}

///////////////////////////////////////////////////////////////////////////////
// Basic ODE geom space wrapper
//
CBasicODESpace::CBasicODESpace()
{
	m_Space = 0;
	m_Body = 0;
	m_Parent = 0;
	m_Geoms = new std::list<IBasicGeom*>;
}

CBasicODESpace::~CBasicODESpace()
{
	Release();
	delete m_Geoms;
}

void CBasicODESpace::SetGeom(dGeomID g)
{
	OVRL_ASSERT(m_Space==0);
	OVRL_ASSERT(g);
	OVRL_ASSERT(dGeomIsSpace(g));
	m_Space = (dSpaceID)g;
}

void CBasicODESpace::SetSpace(dSpaceID s)
{
	OVRL_ASSERT(m_Space==0);
	OVRL_ASSERT(s);
	m_Space = s;
}

void CBasicODESpace::Clear()
{
	std::list<IBasicGeom*>::iterator I;

	I = m_Geoms->begin();
	while ( I!=m_Geoms->end() )
	{
		if ( *I )
		{
			(*I)->onRemove(this);
			dSpaceRemove(m_Space, (*I)->GetGeom());
		}
		I++;
	}
	m_Geoms->clear();
}

//
// IBasicSpace
//
void CBasicODESpace::Add(IBasicGeom* g)
{
	OVRL_ASSERT(m_Space);
	OVRL_ASSERT(g);

	g->onInsert(this);
	m_Geoms->insert(m_Geoms->end(), g);
}

void CBasicODESpace::Remove(IBasicGeom* g)
{
	OVRL_ASSERT(m_Space);
	OVRL_ASSERT(g);

	g->onRemove(this);
	m_Geoms->remove(g);
}

//
// IBasicGeom
//
void CBasicODESpace::Create(IBasicBody* b)
{
	OVRL_ASSERT(m_Space==0);
	Create();
	Attach(b);
}

void CBasicODESpace::Prepare()
{
	std::list<IBasicGeom*>::iterator I;

	I = m_Geoms->begin();
	while ( I!=m_Geoms->end() )
	{
		if ( *I )
			(*I)->Prepare();
		I++;
	}
}

void CBasicODESpace::onInsert(IBasicSpace* s)
{
	OVRL_ASSERT(s);
	OVRL_ASSERT(m_Parent==0);
	m_Parent = s;
	dSpaceAdd(s->GetSpace(), GetGeom());
}

void CBasicODESpace::onRemove(IBasicSpace* s)
{
	OVRL_ASSERT(s);
	OVRL_ASSERT(m_Parent==s);
	m_Parent = 0;
	dSpaceRemove(s->GetSpace(), GetGeom());
}

void CBasicODESpace::Release()
{
	std::list<IBasicGeom*>::iterator I;

	I = m_Geoms->begin();

	while ( I!=m_Geoms->end() )
	{
		if ( *I )
			(*I)->Release();
		delete *I;
		I++;
	}
	m_Geoms->clear();

	if ( m_Parent )
	{
		// donno if this is safe..
		// if some spaces/geoms are not released during CWorldSector::Release
		// then there will be an attempt to do this in CPhysicsEngine::Release
		// that's where it'll crash probably... because std:list isn't capable of
		// iterating and removing/inserting of items at the same time...
//		m_Parent->Remove(this);	
		dSpaceRemove(m_Parent->GetSpace(), GetGeom());
		m_Parent = 0;
	}

	if ( m_Space )
	{
		Attach(0);
		dSpaceDestroy(m_Space);
		m_Space = 0;
	}
}

void CBasicODESpace::Update()
{
		std::list<IBasicGeom*>::iterator I;

		I = m_Geoms->begin();

		while ( I!=m_Geoms->end() )
		{
			if ( *I )
				(*I)->Update();
			I++;
		}
}

void CBasicODESpace::Attach(IBasicBody* b)
{
	std::list<IBasicGeom*>::iterator I;
	OVRL_ASSERT(m_Body==0 || b==0);
	OVRL_ASSERT(m_Space);

	m_Body = b;

	if ( m_Body ) 
	{
		dGeomSetData((dGeomID)m_Space, m_Body);
	}
	else
	{
		dGeomSetData((dGeomID)m_Space, 0);
	}

//	I = m_Geoms->begin();

//	while ( I!=m_Geoms->end() )
//	{
//		if ( *I )
//			(*I)->Attach(b);
//		I++;
//	}
}

bool CBasicODESpace::IsPlaceable() const
{
	return false;	
}

void CBasicODESpace::Enable(bool en)
{
	OVRL_ASSERT(m_Space);
	if ( en )
		dGeomEnable((dGeomID)m_Space);
	else
		dGeomDisable((dGeomID)m_Space);
}

bool CBasicODESpace::IsEnabled() const
{
	OVRL_ASSERT(m_Space);
	return dGeomIsEnabled((dGeomID)m_Space)==1;
}

C3DVector CBasicODESpace::GetPosition() const
{
	OVRL_ASSERT(false);
	return C3DVector::ZERO();
}

C3DVector CBasicODESpace::GetOrientation() const
{
	OVRL_ASSERT(false);
	return C3DVector::ZERO();
}

C4x4Matrix CBasicODESpace::GetOrientationMatrix() const
{
	OVRL_ASSERT(false);
	return C4x4Matrix::identity();
}

const void* CBasicODESpace::GetUserData() const
{
	OVRL_ASSERT(m_Space);
	return dGeomGetData((dGeomID)m_Space);
}

C3DBoundingVolume CBasicODESpace::GetBoudingVolume() const
{
	OVRL_ASSERT(false);
	return C3DBoundingVolume();
}


void CBasicODESpace::SetPosition(const C3DVector& dv)
{
	OVRL_ASSERT(false);
}

void CBasicODESpace::SetOrientation(const C3DVector& dv)
{
	OVRL_ASSERT(false);
}

void CBasicODESpace::SetOrientationMatrix(const C4x4Matrix& m)
{
	OVRL_ASSERT(false);
}

void CBasicODESpace::SetUserData(void* data)
{
	OVRL_ASSERT(false);
}

ulong CBasicODESpace::GetCategoryBits() const
{
	OVRL_ASSERT(m_Space);
	return dGeomGetCategoryBits((dGeomID)m_Space);
}

ulong CBasicODESpace::GetCollideBits() const
{
	OVRL_ASSERT(m_Space);
	return dGeomGetCollideBits((dGeomID)m_Space);
}

void CBasicODESpace::SetCategoryBits(ulong ul)
{
	OVRL_ASSERT(m_Space);
	dGeomSetCategoryBits((dGeomID)m_Space, ul);
}

void CBasicODESpace::SetCollideBits(ulong ul)
{
	OVRL_ASSERT(m_Space);
	dGeomSetCollideBits((dGeomID)m_Space, ul);
}


///////////////////////////////////////////////////////////////////////////////
// Simple Space
//

CSimpleSpace::CSimpleSpace()
	:CBasicODESpace()
{
}

CSimpleSpace::~CSimpleSpace()
{
}

void CSimpleSpace::Create()
{
	SetSpace(dSimpleSpaceCreate(0));
}

void CSimpleSpace::Update()
{
	CBasicODESpace::Update();
}

///////////////////////////////////////////////////////////////////////////////
// Hash Space
//

CHashSpace::CHashSpace()
	:CBasicODESpace()
{
}

CHashSpace::~CHashSpace()
{
}

void CHashSpace::Create()
{
	SetSpace(dHashSpaceCreate(0));
}

void CHashSpace::Update()
{
	CBasicODESpace::Update();
}

///////////////////////////////////////////////////////////////////////////////
// Quad Tree Space
//

//CQTSpace::CQTSpace()
//	:CBasicODESpace()
//{
//}
//
//CQTSpace::~CQTSpace()
//{
//}
//
//void CQTSpace::Create()
//{
//	SetSpace(dQuadTreeSpaceCreate(0));
//}
//
//void CQTSpace::Update()
//{
//	CBasicODESpace::Update();
//}

///////////////////////////////////////////////////////////////////////////////
// Encapsulates a geom so that geom can be moved independantly of the body
//
CEncapsulatedGeom::CEncapsulatedGeom()
:CBasicODEGeom()
{
	m_Encapsulated = 0;
}

CEncapsulatedGeom::~CEncapsulatedGeom()
{
}

void CEncapsulatedGeom::Create()
{
	SetGeom(dCreateGeomTransform(0));
}

void CEncapsulatedGeom::Release()
{
	if ( m_Encapsulated ) m_Encapsulated->Release();
	CBasicODEGeom::Release();
}

void CEncapsulatedGeom::Attach(IBasicBody*b)
{
	OVRL_ASSERT(m_Encapsulated);
	CBasicODEGeom::Attach(b);
}

void CEncapsulatedGeom::Set(IBasicGeom* b)
{
	OVRL_ASSERT(m_Encapsulated==0 || b==0);
	if ( b )
	{
		OVRL_ASSERT(b->GetParent()==0);
		OVRL_ASSERT(b->GetBody()==0);
		dGeomTransformSetGeom(GetGeom(), b->GetGeom());
	}
	else
		dGeomTransformSetGeom(GetGeom(), 0);
	m_Encapsulated = b;
}

///////////////////////////////////////////////////////////////////////////////
// Sphere geometry
//
CSphereGeom::CSphereGeom()
	:CBasicODEGeom()
{
}

CSphereGeom::~CSphereGeom()
{
}

void CSphereGeom::Create()
{
	SetGeom(dCreateSphere(0,1));
}

real CSphereGeom::GetRadius() const
{
	OVRL_ASSERT(GetGeom());
	return dGeomSphereGetRadius(GetGeom());
}

void CSphereGeom::SetRadius(real r)
{
	OVRL_ASSERT(GetGeom());
	dGeomSphereSetRadius(GetGeom(), r);
}

real CSphereGeom::GetDepth(const C3DVector&v) const
{
	OVRL_ASSERT(GetGeom());
	return dGeomSpherePointDepth(GetGeom(), v.x(), v.y(), v.z());
}

void CSphereGeom::Update()
{
	CBasicODEGeom::Update();
}

///////////////////////////////////////////////////////////////////////////////
//  Box geometry
//
CBoxGeom::CBoxGeom()
{
}

CBoxGeom::~CBoxGeom()
{
}

void CBoxGeom::Create()
{
	SetGeom(dCreateBox(0,1,1,1));
}


C3DVector CBoxGeom::GetLengths() const
{
	OVRL_ASSERT(GetGeom());
	dVector3 dv;
	dGeomBoxGetLengths(GetGeom(), dv);
	return C3DVector(dv[0], dv[1], dv[2]);
}

void CBoxGeom::SetLengths(const C3DVector&v)
{
	OVRL_ASSERT(GetGeom());
	dGeomBoxSetLengths(GetGeom(), v.x(), v.y(), v.z());
}

real CBoxGeom::GetDepth(const C3DVector&v) const
{
	OVRL_ASSERT(GetGeom());
	return dGeomSpherePointDepth(GetGeom(), v.x(), v.y(), v.z());
}

void CBoxGeom::Update()
{
	CBasicODEGeom::Update();
}

///////////////////////////////////////////////////////////////////////////////
//  Capped Cylinder geometry
//
CCappedCylinderGeom::CCappedCylinderGeom()
{
}

CCappedCylinderGeom::~CCappedCylinderGeom()
{
}

void CCappedCylinderGeom::Create()
{
	SetGeom(dCreateCCylinder(0,1,1));
}

real CCappedCylinderGeom::GetLength() const
{
	OVRL_ASSERT(GetGeom());
	dReal r, l;
	dGeomCCylinderGetParams(GetGeom(), &r, &l);
	return (real)l;
}

real CCappedCylinderGeom::GetCapRadius() const
{
	OVRL_ASSERT(GetGeom());
	dReal r, l;
	dGeomCCylinderGetParams(GetGeom(), &r, &l);
	return (real)r;
}

void CCappedCylinderGeom::SetLength(real l)
{
	OVRL_ASSERT(GetGeom());
	dReal dr, dl;
	dGeomCCylinderGetParams(GetGeom(), &dr, &dl);
	dl = l;
	dGeomCCylinderSetParams(GetGeom(), dr, dl);
}

void CCappedCylinderGeom::SetCapRadius(real r)
{
	OVRL_ASSERT(GetGeom());
	dReal dr, dl;
	dGeomCCylinderGetParams(GetGeom(), &dr, &dl);
	dr = r;
	dGeomCCylinderSetParams(GetGeom(), dr, dl);
}


real CCappedCylinderGeom::GetDepth(const C3DVector&v) const
{
	OVRL_ASSERT(GetGeom());
	return dGeomCCylinderPointDepth(GetGeom(), v.x(), v.y(), v.z());
}

void CCappedCylinderGeom::Update()
{
	CBasicODEGeom::Update();
}

///////////////////////////////////////////////////////////////////////////////
//  Cylinder geometry
//
CCylinderGeom::CCylinderGeom()
{
}

CCylinderGeom::~CCylinderGeom()
{
}

void CCylinderGeom::Create()
{
	SetGeom(dCreateCylinder(0,1,1));
}

real CCylinderGeom::GetLength() const
{
	OVRL_ASSERT(GetGeom());
	dReal r, l;
	dGeomCylinderGetParams(GetGeom(), &r, &l);
	return (real)l;
}

real CCylinderGeom::GetRadius() const
{
	OVRL_ASSERT(GetGeom());
	dReal r, l;
	dGeomCylinderGetParams(GetGeom(), &r, &l);
	return (real)r;
}

void CCylinderGeom::SetLength(real l)
{
	OVRL_ASSERT(GetGeom());
	dReal dr, dl;
	dGeomCylinderGetParams(GetGeom(), &dr, &dl);
	dl = l;
	dGeomCylinderSetParams(GetGeom(), dr, dl);
}

void CCylinderGeom::SetRadius(real r)
{
	OVRL_ASSERT(GetGeom());
	dReal dr, dl;
	dGeomCylinderGetParams(GetGeom(), &dr, &dl);
	dr = r;
	dGeomCylinderSetParams(GetGeom(), dr, dl);
}


real CCylinderGeom::GetDepth(const C3DVector&v) const
{
	OVRL_ASSERT(GetGeom());
	OVRL_ASSERT_EX(false, NOTIMPLEMENTED, "Cylinder Point Depth not implemented");
//	return dGeomCylinderPointDepth(GetGeom(), v.x(), v.y(), v.z());
	return 0;
}

void CCylinderGeom::Update()
{
	CBasicODEGeom::Update();
}

///////////////////////////////////////////////////////////////////////////////
//  Plane geometry
//
CPlaneGeom::CPlaneGeom()
{
}

CPlaneGeom::~CPlaneGeom()
{
}

void CPlaneGeom::Create()
{
	SetGeom(dCreatePlane(0,0,0,1,0));
}

void CPlaneGeom::SetParams(const C3DVector&n, real d)
{
	OVRL_ASSERT(GetGeom());
	dGeomPlaneSetParams(GetGeom(), n.x(),n.y(),n.z(),d);
}

real CPlaneGeom::GetDepth(const C3DVector& v)
{
	OVRL_ASSERT(GetGeom());
	return dGeomPlanePointDepth(GetGeom(), v.x(), v.y(), v.z());
}

void CPlaneGeom::Attach(IBasicBody* b)
{
	OVRL_ASSERT(m_Body==0 || b==0);
	OVRL_ASSERT(m_Geom);
	m_Body = b;
	if ( m_Body ) 
	{
//		dGeomSetBody(m_Geom, m_Body->GetBody());
		dGeomSetData(m_Geom, m_Body);
	}
	else
	{
//		dGeomSetBody(m_Geom, 0);
		dGeomSetData(m_Geom, 0);
	}
}

void CPlaneGeom::Update()
{
	CBasicODEGeom::Update();
}

///////////////////////////////////////////////////////////////////////////////
//  Triangle Mesh geometry
//
CTriangleMeshGeom::CTriangleMeshGeom()
{
	OVRL_ASSERT_EX(false,NOTIMPLEMENTED, "TriangleMesh wrapper is currently not implemented!");
}

CTriangleMeshGeom::~CTriangleMeshGeom()
{
}

void CTriangleMeshGeom::Create()
{
//	SetGeom(dCreateTriMesh(0,1,1));
}

void CTriangleMeshGeom::Update()
{
	CBasicODEGeom::Update();
//	const double *DoubleArrayPtr = Bodies[BodyIndex].TransformationMatrix->GetArray();
//	dGeomTriMeshDataSet( TriMeshData, TRIMESH_LAST_TRANSFORMATION, (void *) DoubleArrayPtr );
}

}
