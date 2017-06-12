#include "stdafx.h"

#include "physics/PhysicsIntegrator.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPhysicsIntegrator::CPhysicsIntegrator()
{
	m_first_started_time = m_last_frame_time = get_tick();
	m_frame_time	= 0;
	m_last_frame_delta = 1;
}

CPhysicsIntegrator::~CPhysicsIntegrator()
{
}

}