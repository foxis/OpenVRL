#include "stdafx.h"

#include "physics/PhysicsEngine.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPhysicsEngine::CPhysicsEngine()
{
}

CPhysicsEngine::~CPhysicsEngine()
{
}

bool CPhysicsEngine::solve()
{
	std::vector<CPhysicsParticle*>::iterator I(m_objects.begin());

	BeginPhysics();
	solve_forces();
	solve_integrate();
	solve_velocities();
	solve_collisions(*this);
	while ( I!=m_objects.end() ) (*(I++))->solve_update();
	return EndPhysics();
}

bool CPhysicsEngine::BeginPhysics()
{
	CPhysicsIntegrator::BeginFrame();
	return CPhysicsCDSystem::BeginPhysics();
}
bool CPhysicsEngine::EndPhysics()
{
	const bool r=CPhysicsCDSystem::EndPhysics();
	CPhysicsIntegrator::EndFrame();
	return r;
}

int CPhysicsEngine::Update()
{
	std::vector<CPhysicsParticle*>::iterator I(m_objects.begin());
	while ( I!=m_objects.end() ) (*(I++))->Update(*this);
	return solve();
}


void CPhysicsEngine::solve_forces()
{
	const ulong cb = m_objects.size();
	ulong i,j;
	C3DVector force;
	C3DVector V;

	//
	// calculate forces for gravity between objects
	// and electrostatical forces too
	// 
	// @todo: this piece of code is extreemely slow
	//
	// @todo: add field forces
	//
	// @todo: add collision forces
	//
#define TI(i,j) (cb*j+i)
	memset(m_states, 0, sizeof(m_states[0])*cb*cb);
	for ( i=0;i<cb;i++ )
	{
		const C3DPoint pos = m_objects[i]->configuration().CM_position();
		m_states[TI(i,i)].solved();
		for ( j=0;j<cb;j++ ) if ( i!=j ) 
		{
			if ( m_states[TI(j,j)].is_solved() )
			{
				const C3DVector tmp = m_states[TI(j,i)].force().force();
				m_states[TI(i,j)].force() = tmp.neg();
			}
			else 
			{
				V = pos-m_objects[j]->configuration().CM_position();
				V.normalize();
				const real dist = 1/V.sq_length();
				V *= ( -constants::p_G*m_objects[i]->mass()*m_objects[j]->mass() +
						constants::p_K*m_objects[i]->charge()*m_objects[j]->charge() )*dist;
				m_states[TI(i,j)].force() = V;
			}
		}
	}
	for ( i=0;i<cb;i++ ) 
	{
		C3DVector force(0,0,0);
		C3DVector thorgue(0,0,0);
		for ( j=0;j<cb;j++ ) if (  j!=i )
		{
			force += m_states[TI(i,j)].force().force();
			thorgue += m_states[TI(i,j)].force().thorgue();
		}
		m_states[TI(i,i)].force_index() = m_objects[i]->add_force(CPhysicsForce(force,thorgue));
	}

	// calculate forces for objects
	for ( i=0;i<cb;i++ )
	{
		m_objects[i]->solve_forces();
		m_objects[i]->stop_force(m_states[TI(i,i)].force_index());
	}
#undef TI
}

void CPhysicsEngine::solve_velocities()
{
	ulong i;
	for ( i=0;i<m_objects.size();i++ )
		m_objects[i]->solve_velocities();
}

void CPhysicsEngine::solve_integrate()
{
	ulong i;
	for ( i=0;i<m_objects.size();i++ )
		m_objects[i]->solve_integrate(*this);
}

}