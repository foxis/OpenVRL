#include "system/ovrlsystem.h"
#include "world/light.h"

namespace openvrl {

CLight::CLight()
	:CBasicEntity()
{
	m_Light = 0;
	m_TypeBits = OVRL_BT_MOVEABLE | OVRL_BT_PHYSICSABLE;
	m_TransformMatrix.set_identity();
	m_WorldTransformMatrix.set_identity();
}

CLight::~CLight()
{
	Release();
}


void CLight::Release()
{
	if ( m_Light ) { m_Light->unuse(); m_Light =0; }
	CBasicEntity::Release();
}

//
// IBasicWorldEntity
//
void CLight::Prepare()
{
	CBasicEntity::Prepare();
}

int CLight::Update(real time_step)
{
	return CBasicEntity::Update(time_step);
}

//
// IBasicBody
//
void CLight::UpdatePhysics(real time_step)
{
	CBasicEntity::Update(time_step);
}

//
// IBasicLight
//
void CLight::Attach(CxfLight* light)
{
	OVRL_ASSERT(m_Light==0);
	OVRL_ASSERT(light);
	if ( m_Light )	m_Light->unuse();	// this should never happen in debug
	m_Light = light;
	if ( !m_Light ) return;
	m_Light->use();
}

void CLight::Attach(const CString& path, int what)
{
	OVRL_ASSERT_EX(what==3, NOTIMPLEMENTED, "CLight only supports light templates");
	OVRL_ASSERT(m_Light==0);

	m_Light = GetPipeline()->lights->find(path);
	OVRL_ASSERT_EX(m_Light, GENERAL, "Could not find specified light");
	if ( m_Light ) // in debug mode assertion should happen. this is for release
	{
		m_Light->use();
	}
}


}
