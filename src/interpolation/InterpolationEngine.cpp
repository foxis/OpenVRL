#include "interp/InterpolationEngine.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInterpolationEngine::CInterpolationEngine()
{

}

CInterpolationEngine::~CInterpolationEngine()
{

}

int CInterpolationEngine::Run()
{
	onStart();
	while ( !isFinished() )	Interpolate();
	onStop();
	return 0;
}

}