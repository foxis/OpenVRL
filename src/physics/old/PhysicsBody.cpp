#include "stdafx.h"

#include "physics/PhysicsBody.h"
#include "physics/PhysicsEngine.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPhysicsBody::CPhysicsBody()
{

}

CPhysicsBody::~CPhysicsBody()
{

}

int	CPhysicsBody::initialize()
{
	BSphere() = C3DSphere(0,0,0,1);
	return CPhysicsParticle::initialize();
}
int CPhysicsBody::precalculate()
{
	return CPhysicsParticle::precalculate();
}

int CPhysicsBody::release()
{
	return CPhysicsParticle::release();
}

int CPhysicsBody::on_collide(const CPhysicsParticle& body, const CPhysicsCDReport& cr)
{
	return CPhysicsParticle::on_collide(body, cr);
}

int CPhysicsBody::on_check_collide(const CPhysicsParticle& body, double IC, CPhysicsCDReport& cr)
{
	return CPhysicsParticle::on_check_collide(body, IC, cr);	// clear
}

//
//
// @todo handle multiple points of collision
int CPhysicsBody::resolve_collision(const CPhysicsCDReport::Report* report, CPhysicsParticle* b2)
{
	return CPhysicsParticle::resolve_collision(report, b2);
}

int CPhysicsBody::resolve_impulses(const CPhysicsIntegrator& i)
{
	return CPhysicsParticle::resolve_impulses(i);
}


//		C3DVector vv(configuration().CM_velocity(1));
//		vv.normalize();
//		const double dp = vv.dot(configuration().CM_acceleration());
//		const double dq = configuration().CM_velocity().dot(vv);
//		const double D = dq*dq + 2*dp*u[2];
//
//		if ( dp==0 )
//		{
//			u[2] = u[2] / dq;
//		} 
//		else if ( D>constants::EPSILON )
//		{
//			const double sD = sqrt(D);
//			u[0] = -(dq+sD)/dp;
//			u[1] = -(dq-sD)/dp;
//			const bool tu0 = u[0]>=-constants::EPSILON && u[0]<IC;
//			const bool tu1 = u[1]>=-constants::EPSILON && u[1]<IC;
//			u[2] = -1;
//			if ( tu0 && tu1 )
//			{
//				if ( u[1]>=u[0] )	u[2]=u[0];	else 	u[2]=u[1];
//			} 
//			else
//			{
//				if ( tu0 )	u[2]=u[0];	else if ( tu1 )	u[2]=u[1];
//			}
//		}
//		else
//			u[2] = -1;

//
// calculates CM_force and CM_thorgue from a list of forces applied
//
int CPhysicsBody::solve_forces()
{
	return CPhysicsParticle::solve_forces();
}

int CPhysicsBody::solve_integrate(const CPhysicsIntegrator& i)
{
	return CPhysicsParticle::solve_integrate(i);
}
int CPhysicsBody::solve_velocities()
{
	return CPhysicsParticle::solve_velocities();
}

int CPhysicsBody::solve_update()
{
	return CPhysicsParticle::solve_update();
}

void CPhysicsBody::PrintStateToStr(CString& out, ulong tabs)
{
	CPhysicsParticle::PrintStateToStr(out, tabs);
}

}