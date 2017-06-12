#include "system/ovrlsystem.h"
#include "world/camera.h"

namespace openvrl {

CCamera::CCamera()
	:CBasicEntity()
{
	m_Camera = 0;
	m_TypeBits = OVRL_BT_MOVEABLE | OVRL_BT_PHYSICSABLE;
	m_RenderTarget = 0;
}

CCamera::~CCamera()
{
	Release();
}


void CCamera::Release()
{
	if ( m_Camera ) { m_Camera->unuse(); m_Camera =0; }
	if ( m_RenderTarget ) { m_RenderTarget->Release(); m_RenderTarget =0; }
	CBasicEntity::Release();
}

void CCamera::SetRenderTarget(IRenderTarget* rt)
{
	OVRL_ASSERT(rt);
	OVRL_ASSERT(m_RenderTarget==0);
	m_RenderTarget = rt;
}

void CCamera::SetLookAt(const C3DVector& p, const C3DVector& target, real roll)
{
	SetPosition(p);
	C3DVector zAxis = target - p;
	C3DVector yAxis=C3DVector::ZERO(), xAxis;
	C4x4Matrix m,r;

	zAxis.normalize();
	if ( !zAxis.x() || !zAxis.z() )
		yAxis = C3DVector(-zAxis.y(),0.0,0.0);
	else
		yAxis.y() = 1.0;
	
	xAxis = yAxis.cross(zAxis);
	xAxis.normalize();

	yAxis = xAxis.cross(zAxis);
	yAxis.normalize();
	yAxis.neg();

	m.set_rotate(0.0,0.0,roll);
		
	r.set(
		xAxis.x(),xAxis.y(),xAxis.z(),0.0,
		yAxis.x(),yAxis.y(),yAxis.z(),0.0,
		zAxis.x(),zAxis.y(),zAxis.z(),0.0,
		0.0,0.0,0.0,1.0);
	m.mul(r);

	SetOrientationMatrix(m);
}


//
// IBasicWorldEntity
//
void CCamera::Prepare()
{
	CBasicEntity::Prepare();

	//Projection Matrix
//pOut
//[in, out] Pointer to the D3DXMATRIX structure that is the result of the operation. 
//fovY
//[in] Field of view, in the y direction, in radians. 
//Aspect
//[in] Aspect ratio, defined as view space height divided by width.
//zn
//[in] Z-value of the near view-plane. 
//zf
//[in] Z-value of th
//w       0       0               0
//0       h       0               0
//0       0       zf/(zf-zn)      1
//0       0       -zn*zf/(zf-zn)  0
//where:
//h is the view space height. It is calculated from 
//h = cot(fovY/2);
//
//w is the view space width. It is calculated from
//w = h / Aspect.

}

int CCamera::Update(real time_step)
{
	real 
		Y = m_Camera->dy/m_Camera->focus,//(constants::m_pi*2/180.0)*m_Camera->focus, 
		X = m_Camera->dx/m_Camera->focus,//(constants::m_pi*2/180.0)*m_Camera->focus, 
		h = 1/Y,
		w = 1/X,
		aspect = 1;

	//real 
	//	fovY = constants::m_pi*4, 
	//	fovY = constants::m_pi*4, 
	//	h = 1/tan(fovY/2.0),
	//	w = 1/tan(fovX/2.0),
	//	aspect = 1;

	real 
		zf = 1000.0,
		zn = 1;

	m_Projection.set(
		w,0,0,0,
		0,h,0,0,
		0,0,zf/(zf-zn),1,
		0,0,-zn*zf/(zf-zn),0
		);

	return CBasicEntity::Update(time_step);

	//ViewMatrix
//pOut
//[in, out] Pointer to the D3DXMATRIX structure that is the result of the operation. 
//pEye
//[in] Pointer to the D3DXVECTOR3 structure that defines the eye point. This value is used in translation. 
//pAt
//[in] Pointer to the D3DXVECTOR3 structure that defines the camera look-at target. 
//pUp
//[in] Pointer to the D3DXVECTOR3 structure that defines the current world's up, usually [0, 1, 0].
//zaxis = normal(At - Eye)
//xaxis = normal(cross(Up, zaxis))
//yaxis = cross(zaxis, xaxis)
//
// xaxis.x           yaxis.x           zaxis.x          0
// xaxis.y           yaxis.y           zaxis.y          0
// xaxis.z           yaxis.z           zaxis.z          0
//-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1
	//Projection Matrix
//pOut
//[in, out] Pointer to the D3DXMATRIX structure that is the result of the operation. 
//fovY
//[in] Field of view, in the y direction, in radians. 
//Aspect
//[in] Aspect ratio, defined as view space height divided by width.
//zn
//[in] Z-value of the near view-plane. 
//zf
//[in] Z-value of th
//w       0       0               0
//0       h       0               0
//0       0       zf/(zf-zn)      1
//0       0       -zn*zf/(zf-zn)  0
//where:
//h is the view space height. It is calculated from 
//h = cot(fovY/2);
//
//w is the view space width. It is calculated from
//w = h / Aspect.
}

//
// IBasicBody
//
void CCamera::UpdatePhysics(real time_step)
{
	C4x4Matrix t;
	C4x4Matrix o;
	C3DVector v;

	CBasicEntity::Update(time_step);

	v = GetPosition();
//	printf("camera update: v: {%08g,%08g,%08g}\n", v.x(), v.y(), v.z());
	t.set(C4x4Matrix::translate(v.x(),v.y(),v.z()));
	o = GetOrientationMatrix();
//	printf("camera update: o: {%08g,%08g,%08g,%08g,%08g,%08g,%08g,%08g,%08g}\n", 
//		o.data()[0],o.data()[1],o.data()[2],
//		o.data()[4],o.data()[5],o.data()[6],
//		o.data()[8],o.data()[9],o.data()[10]);
	o.transpose_rotate();
	t.neg_translate();
	t.mul(o);

	m_View = t;
}

//
// IBasicMesh
//
void CCamera::Attach(CxfCamera* camera)
{
	OVRL_ASSERT(m_Camera==0);
	OVRL_ASSERT(camera);
	if ( m_Camera )	m_Camera->unuse();	// this should never happen in debug
	m_Camera = camera;
	if ( !m_Camera ) return;
	m_Camera->use();
//	m_Camera->Initialize();
}

void CCamera::Attach(const CString& path, int what) 
{
	OVRL_ASSERT_EX(what==1, NOTIMPLEMENTED, "CCamera only supports camera templates");
	OVRL_ASSERT(m_Camera==0);
	
	printf("CCamera: attach attempt '%s'\n", path.c_str());
	m_Camera = GetPipeline()->cameras->find(path);
	printf("CCamera: search result %p\n", m_Camera);
	OVRL_ASSERT_EX(m_Camera, GENERAL, "Could not find specified camera");
	if ( m_Camera ) // in debug mode assertion should happen. this is for release
		m_Camera->use();
}


}
