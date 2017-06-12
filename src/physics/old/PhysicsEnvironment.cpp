#include "stdafx.h"

#include "physics/PhysicsEnvironment.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPhysicsEnvironment::CPhysicsEnvironment()
{
	density = 1;
	temperature = 293.3;	// 20 degress C
	pressure = 1.01e5;		// 101 kPa
	electrostatic_density = 1;
	magnetic_density=1;
	electric_permeance=1;
	magnetic_permeance=1;
	friction = 0;
}

CPhysicsEnvironment::~CPhysicsEnvironment()
{

}

}