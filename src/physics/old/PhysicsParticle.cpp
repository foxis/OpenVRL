#include "stdafx.h"

#include "physics/PhysicsEngine.h"
#include "physics/PhysicsParticle.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPhysicsParticle::CPhysicsParticle()
{

}

CPhysicsParticle::~CPhysicsParticle()
{

}

int	CPhysicsParticle::initialize()
{
	mass() = 1.0;	// mass = 1Kg
	charge() = 0.0; // in C
	BSphere().x() = BSphere().y() = BSphere().z() = 0.0;
	BSphere().r() = 1.0;
	m_centre_geometry = m_centre_mass = C3DVector::ZERO();
	sliding_friction() = 0.01;
	rolling_friction() = 0.004;
	bounce_coeficient() = 0.0;
	precalculate();
	return 0;
}
int CPhysicsParticle::precalculate()
{
	m_1mass = 1.0/mass();
	m_MoI = (mass()/12.0) * BSphere().r()*BSphere().r();
	m_1MoI = 1.0/_MomentOfInertia();
	return 0;
}

int CPhysicsParticle::release()
{
	stop_forces(0, m_forces.size());
	return 0;
}

int CPhysicsParticle::on_collide(const CPhysicsParticle& Particle, const CPhysicsCDReport& cr)
{
	return 0;
}

int CPhysicsParticle::on_check_collide(const CPhysicsParticle& Particle, double IC, CPhysicsCDReport& cr)
{
	double u[3];
	bool inter;
	C4x4Matrix m;
	C3DSphere sph(BSphere());
	C3DSphere sph1(Particle.BSphere());
	C3DVector c1(sph.centre());
	C3DVector c2(sph1.centre());

	// translate first object
	m.set(calculate_matrix());
	c1.mul(m);	
	sph.centre() = c1;

	// translate second object
	m.set(Particle.calculate_matrix());
	c2.mul(m);	
	sph1.centre() = c2;

	// check for collision
	inter = sph.intersect_sweep_sphere(
		configuration().CM_velocity(1), configuration().CM_acceleration(),
		sph1, Particle.configuration().CM_velocity(1), Particle.configuration().CM_acceleration(),
		u[0], u[1]);

	// add collisions
	const bool u0 = u[0]>=-constants::EPSILON && u[0]<IC+constants::EPSILON;
	const bool u1 = u[1]>=-constants::EPSILON && u[1]<IC+constants::EPSILON;
	if ( inter && (u0 || u1) ) 
	{
		u[2] = -1;
		if ( u0 && u1 )
		{
			if ( u[1]>=u[0] )	u[2]=u[0];	else 	u[2]=u[1];
		} 
		else
		{
			if ( u0 )	u[2]=u[0];	else if ( u1 )	u[2]=u[1];
		}

		if ( u[2]>=0)
		{
			CPhysicsCDReport::CollisionPoint cp;
			C3DVector AB = CPhysicsEngine::MC(c2,Particle.configuration().CM_velocity(), Particle.configuration().CM_acceleration(), u[2]) -
				CPhysicsEngine::MC(c1,configuration().CM_velocity(), configuration().CM_acceleration(), u[2]);
			AB.normalize();
			cp.origin() = AB*sph.r();
			cp.origin1() = AB*(-sph1.r());
			cp.normal() = AB;
			cp.time() = u[2];
			cr.AddCollision(0, &cp, 1);
		}
//		if ( u[0]==u[1] )
//			return -1;	// penetrating
//		else
			return 1;	// just glanced
	}

	return 0;	// clear
}

//
//
// @todo handle multiple points of collision
int CPhysicsParticle::resolve_collision(const CPhysicsCDReport::Report* report, CPhysicsParticle* b2)
{
	const double u = report->points()[0].time();
	Configuration& cn1 = configuration();
	Configuration& cn2 = b2->configuration();
	const C3DVector P(report->points()[0].origin());
	const C3DVector P1(report->points()[0].origin1());
	const double l1 = P.length()*constants::m_12pi;
	const double l2 = P1.length()*constants::m_12pi;
	const double L1 = 1/l1;
	const double L2 = 1/l2;
	const C3DVector Vvs1 = CPhysicsEngine::wMV(cn1.CM_spin(),cn1.CM_spin_acceleration(), u) * l1; // linear circular velocities 
	const C3DVector Vvs2 = CPhysicsEngine::wMV(cn2.CM_spin(),cn2.CM_spin_acceleration(), u) * l2; // ---//---
	const double bc = 1 - ( b2->bounce_coeficient()+bounce_coeficient() )*0.5; // @todo: ?
	const double sf = 1 - ( b2->sliding_friction()*sliding_friction() ) *0.5;  // @todo: ?
	const double M = mass() + b2->mass();
	const double I = _MomentOfInertia() + b2->_MomentOfInertia();

	C3DVector v1, v2;
	C3DVector N, N1, N2;
	C3DVector Nv1, Nv2, Vv1, Vv2;
	C3DVector Ns1, Ns2, Vs1, Vs2;

	// normals
	N = report->points()[0].normal();	// plane normal
	N1 = P*L1;							// normal for the collision points
	N2 = P1*L2;

	// velocities
	v1 = CPhysicsEngine::MV(cn1.CM_velocity(),cn1.CM_acceleration(), u) + Vvs1.cross(N1);
	v2 = CPhysicsEngine::MV(cn2.CM_velocity(),cn2.CM_acceleration(), u) + Vvs2.cross(N2);

	Nv1 = N* N.dot(v1);
	Nv2 = N* N.dot(v2);
	Vv1 = (v1-Nv1)*sf;
	Vv2 = (v2-Nv2)*sf;

	// impulse
	const long double one = 1/M;
	const C3DVector V = (Nv1*mass() + Nv2*b2->mass())*one;

	v1 = (V - Nv1*bc);
	v2 = (V - Nv2*bc);
	Nv1 = N1* N1.dot(v1);
	Nv2 = N2* N2.dot(v2);

	// calculate impulse for linear component
	cn1.CM_impulse() +=  Vv1; // Nv1 +
	cn2.CM_impulse() +=  Vv2; // Nv2 +
	cn1.CM_im_pos() += CPhysicsEngine::MS(cn1.CM_velocity(),cn1.CM_acceleration(), u);
	cn2.CM_im_pos() += CPhysicsEngine::MS(cn2.CM_velocity(),cn2.CM_acceleration(), u);

	// calculate impulse for spin component
	
	cn1.CM_impulse_thorgue() += ( C3DVector(v1-Nv1).cross(N1) )*L1;
	cn2.CM_impulse_thorgue() += ( C3DVector(v2-Nv2).cross(N2) )*L2;
	cn1.CM_im_spn() += CPhysicsEngine::wMS(cn1.CM_spin(),cn1.CM_spin_acceleration(), u);
	cn2.CM_im_spn() += CPhysicsEngine::wMS(cn2.CM_spin(),cn2.CM_spin_acceleration(), u);

	return 0;
}



int CPhysicsParticle::resolve_impulses(const CPhysicsIntegrator& i)
{
	Configuration& config = configuration();
	config.CM_velocity() = config.CM_impulse() +config.CM_im_pos();
	config.CM_spin() = config.CM_impulse_thorgue() +config.CM_im_spn();

	config.CM_impulse() = config.CM_impulse_thorgue() = 
		config.CM_im_pos() = config.CM_im_spn() = 
		config.CM_acceleration() = config.CM_spin_acceleration() = 
		C3DVector::ZERO();

	config.CM_position(1) = config.CM_position() + config.CM_velocity()*i.IntegrationCoeficient();
	config.CM_orientation(1) = config.CM_orientation() + config.CM_spin()*i.IntegrationCoeficient();
	config.CM_velocity(1) = config.CM_velocity() + config.CM_acceleration();
	config.CM_spin(1) = config.CM_spin() + config.CM_spin_acceleration();

	return 0;
}


//
// calculates CM_force and CM_thorgue from a list of forces applied
//
int CPhysicsParticle::solve_forces()
{
	ulong i;
	Configuration& config = configuration();
	C3DVector force(0,0,0);
	C3DVector thorgue(0,0,0);

	for ( i=0;i<forces().size();i++ )
		if ( forces()[i].active() ) {
			force += forces()[i].force();
			thorgue += forces()[i].thorgue();
		}

	config.CM_force() = force;
	config.CM_thorgue() = thorgue;

	config.CM_acceleration() = config.CM_force()*m_1mass;
	config.CM_spin_acceleration() = config.CM_thorgue()*m_1MoI;
	return 0;
}

int CPhysicsParticle::solve_integrate(const CPhysicsIntegrator& i)
{
	Configuration& config = configuration();
	config.CM_position(1) = config.CM_position() + config.CM_velocity()*i.IntegrationCoeficient();
	config.CM_orientation(1) = config.CM_orientation() + config.CM_spin()*i.IntegrationCoeficient();
	config.CM_velocity(1) = config.CM_velocity() + config.CM_acceleration()*i.IntegrationCoeficient();
	config.CM_spin(1) = config.CM_spin() + config.CM_spin_acceleration()*i.IntegrationCoeficient();
	return 0;
}
int CPhysicsParticle::solve_velocities()
{
	return 0;
}

inline double MAKE_INSIDE_PI(double a)
{
	if ( a>constants::m_2pi || a<-constants::m_2pi )
		return a - constants::m_2pi*(int)(a*constants::m_12pi);
	else
		return a;
}

int CPhysicsParticle::solve_update()
{
	configuration().configuration_next();
	// just to avoid getting out of range
	C3DVector tmp(configuration().CM_orientation());
	C3DVector tmp1(configuration().CM_spin());
	tmp.x() = MAKE_INSIDE_PI(tmp.x());
	tmp.y() = MAKE_INSIDE_PI(tmp.y());
	tmp.z() = MAKE_INSIDE_PI(tmp.z());
	tmp1.x() = MAKE_INSIDE_PI(tmp1.x());
	tmp1.y() = MAKE_INSIDE_PI(tmp1.y());
	tmp1.z() = MAKE_INSIDE_PI(tmp1.z());
	configuration().CM_orientation() = tmp;
	configuration().CM_spin() = tmp1;
	return 0;
}

//////////
ulong CPhysicsParticle::add_force(const CPhysicsForce& force)
{
	return forces().add(force);
}
ulong CPhysicsParticle::add_forces(const CPhysicsForce* force, ulong n)
{
	ulong i,j;
	for ( i=0,j=0;i<n;i++ )
	{
		if ( i==0 )
			j = forces().add(force[i]);
		else
			forces().add(force[i]);
	}
	return j;
}
void CPhysicsParticle::set_force(const CPhysicsForce& force, ulong i)
{
	if ( i>=forces().size() ) return;
	forces()[i] = force;
}
void CPhysicsParticle::set_forces(const CPhysicsForce* force, ulong i, ulong n)
{
	ulong j;
	if ( i>=forces().size() ) return ;
	if ( i+n>=forces().size() ) 
		n = forces().size();
	else
		n = n+i;
	for ( j=0;i<n;i++,j++ )
		forces()[i] = force[j];
}
void CPhysicsParticle::stop_force(ulong i)
{
	if ( i>=forces().size() ) return ;
	forces()[i].active() = 0;
	forces().remove(i);
}
void CPhysicsParticle::stop_forces(ulong i, ulong n)
{
	ulong j;
	if ( i>=forces().size() ) return ;
	if ( i+n>=forces().size() ) 
		n = forces().size();
	else
		n = n+i;
	for ( j=0;i<n;i++,j++ )
		forces()[i].active()=0;
	forces().remove(i,n);
}


C4x4Matrix CPhysicsParticle::calculate_matrix(long i) const
{ 
	return configuration().CM_matrix(i);
}

/////////////
// CPhysicsParticle::Configuration
////////////
CPhysicsParticle::Configuration::Configuration(ulong configs)
{
	m_configurations = new configuration_struct[configs];
	m_num_configurations = configs;
	m_configuration = m_configuration_last = 0;
	clear_all();
}
CPhysicsParticle::Configuration::~Configuration()
{
	delete[] m_configurations;
}

//
void CPhysicsParticle::Configuration::copy_from_to(ulong dest, ulong src)
{
	memcpy(m_configurations+dest, m_configurations+src, sizeof(m_configurations[dest]));
}
void CPhysicsParticle::Configuration::copy_to(ulong i)
{
	copy_from_to(i, m_configuration);
}
void CPhysicsParticle::Configuration::copy_from(ulong i)
{
	copy_from_to(m_configuration, i);
}
void CPhysicsParticle::Configuration::copy_from_last()
{
	copy_from_to(m_configuration, m_configuration_last);
}
void CPhysicsParticle::Configuration::clear(ulong i)
{
	memset(m_configurations+i, 0, sizeof(m_configurations[i])); 
}
void CPhysicsParticle::Configuration::clear_current() 
{ 
	clear(m_configuration); 
}
void CPhysicsParticle::Configuration::clear_all()
{
	memset(m_configurations, 0, sizeof(m_configurations[0])*m_num_configurations);
}

C4x4Matrix CPhysicsParticle::Configuration::CM_matrix(long i) const
{
	const C3DVector spin(CM_orientation(i)+CM_im_pos(i));
	const C3DVector pos(CM_position(i)+CM_im_spn(i));
	return C4x4Matrix::rotate(spin.x(),spin.y(),spin.z()) * 
		C4x4Matrix::translate(pos.x(),pos.y(),pos.z());
}

C4x4Matrix CPhysicsParticle::Configuration::CM_matrix_at(ulong i) const
{
	const C3DVector spin(CM_orientation_at(i));
	const C3DVector pos(CM_position_at(i));
	return C4x4Matrix::rotate(spin.x(),spin.y(),spin.z()) * 
		C4x4Matrix::translate(pos.x(),pos.y(),pos.z());
}

void CPhysicsParticle::Configuration::set_configuration(ulong c)
{ 
	m_configuration_last = m_configuration;
	m_configuration = c;
}
ulong CPhysicsParticle::Configuration::configuration_next()
{
	m_configuration_last = m_configuration;
	return m_configuration = OADD(1);
}
ulong CPhysicsParticle::Configuration::configuration_last()
{
	m_configuration_last = m_configuration;
	return m_configuration = OADD(1);
}

void CPhysicsParticle::PrintStateToStr(CString& out, ulong tabs)
{
	//IObject::PrintStateToStr(out, tabs);
}

}