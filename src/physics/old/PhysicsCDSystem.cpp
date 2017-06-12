#include "stdafx.h"

#include "physics/PhysicsCDSystem.h"

namespace openvrl {

#define TI(i,j) (cb*j+i)


//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
static int sqrt_priorities(const void* a, const void* b)
{
	return ((const CPhysicsParticle*)a)->priority() - ((const CPhysicsParticle*)b)->priority();
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPhysicsCDSystem::CPhysicsCDSystem()
{
	m_size = 0;
	m_states = 0;
	m_reports = 0;
}

CPhysicsCDSystem::~CPhysicsCDSystem()
{
	if ( m_states ) delete[] m_states;
	if ( m_reports ) delete[] m_reports;
}

bool CPhysicsCDSystem::BeginPhysics()
{
//	m_objects.sort(sqrt_priorities);
	return false;
}

bool CPhysicsCDSystem::EndPhysics()
{
	return false;
}

int CPhysicsCDSystem::AddParticle(CPhysicsParticle* part)
{
	OVRL_ASSERT(part);
	m_objects.insert(m_objects.end(), part);
	resize_containers(m_objects.size(), false);
	return 0;
}

int CPhysicsCDSystem::RemoveParticle(CPhysicsParticle* part)
{
	std::vector<CPhysicsParticle*>::iterator i(m_objects.begin());
	OVRL_ASSERT(part);
	while ( i!=m_objects.end() && *i != part )	i++;
	if ( *i == part )
		m_objects.erase(i);
	else
		return 1;
	return 0;
}


int CPhysicsCDSystem::solve_collisions(const CPhysicsIntegrator& I)
{
	const ulong cb = m_objects.size();
	ulong i;
	ulong collisions;
	ulong counter=0;
	CPhysicsCDReport::Report *report;
	std::vector<CPhysicsParticle*>::iterator	Ii, Ib(m_objects.begin());

	// find collisions
	if ( find_collisions(I)<=0 ) return 0;

	// resolve collisions
	// @todo think of a better algorithm, now i'm lazy to do it
	do {
		for ( collisions=0,i=0,Ii=Ib; Ii<m_objects.end(); i++,Ii++ )
			if ( (report = m_reports[i].report())!=0 ) 
			{
				m_states[TI(i,i)].solved();
				while ( report )
					if ( m_states[TI(i,report->id())].is_solved() ) 
					{
						report = report->next();
						continue;
					}
					else
					{
						(*Ii)->resolve_collision(report, *(Ib+report->id()));
						m_states[TI(i,report->id())].solved();
  						m_states[TI(report->id(),report->id())].solved();
						m_states[TI(report->id(),i)].solved();
						report = report->next();
						collisions++;	// collisions resolved at this iteration
					}
			}
		resolve_impulses(I);
	} while ( ++counter<iterations() && find_collisions(I)>0 );
	return counter;
}

int CPhysicsCDSystem::find_collisions(const CPhysicsIntegrator& I)
{
	const ulong cb = m_objects.size();
	ulong i, j, collisions;
	std::vector<CPhysicsParticle*>::iterator Ii, Ij, Ib(m_objects.begin());
	int tmp;

	// clear states and reports
	memset(m_states, 0, sizeof(m_states[0])*cb*cb);
	for ( i=0;i<cb;i++ ) m_reports[i].clear();

	// build new reports
	for ( collisions=0,i=0,Ii=Ib;Ii<m_objects.end();i++,Ii++ )
	{
		m_states[TI(i,i)].checked();
		for ( Ij=Ii+1,j=i+1;Ij<m_objects.end();j++,Ij++ )
		{
			m_states[TI(i,j)].checked();
			m_states[TI(j,i)].checked();
			if ( (tmp=(*Ii)->on_check_collide(**Ij, I.IntegrationCoeficient(), m_reports[i]))!=0 )
			{
				m_reports[i].set_last_id(j);
				(*Ii)->on_collide(**Ij, m_reports[i]);
//				m_reports[j].copy_last(i,j, m_reports[i]);
				(*Ij)->on_collide(**Ii, m_reports[j]);

				collisions++;
				m_states[TI(i,j)].collided();
				m_states[TI(j,i)].collided();
			}
		}
	}
	return collisions; // return penetrating collisions
}

int CPhysicsCDSystem::resolve_impulses(const CPhysicsIntegrator& I)
{
	ulong i = 0;
	const ulong cb = m_objects.size();
	std::vector<CPhysicsParticle*>::iterator Ii(m_objects.begin());
	while ( Ii<m_objects.end() )
	{
		if ( m_states[TI(i,i)].is_solved() ) 
			(*Ii)->resolve_impulses(I);
		Ii++;
		i++;
	}
	return 0;
}

bool CPhysicsCDSystem::resize_containers(ulong n, bool cp)
{
	State		*states;  // nxn array of states
	CPhysicsCDReport		*reports;	// n array of objects
	const ulong cb = m_objects.size();

	if ( m_size>=n ) return false;
	m_size += size_increment();
	if ( cp )
	{
		states = new State[m_size*m_size];
		reports = new CPhysicsCDReport[m_size];
		memcpy(states, m_states, sizeof(states[0])*cb*cb);
		memcpy(reports, m_reports, sizeof(reports[0])*cb);
		if ( m_states ) delete[] m_states;		m_states = states;
		if ( m_reports ) delete[] m_reports;		m_reports = reports;
	}
	else
	{
		if ( m_states ) delete[] m_states;
		if ( m_reports ) delete[] m_reports;
		m_states = new State[m_size*m_size];
		m_reports = new CPhysicsCDReport[m_size];
	}
	
	return false;
}

}