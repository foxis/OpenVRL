#include "pipeline/ibpool.h"

namespace openvrl {

/**
 *
 */
CplIBPool::CplIBPool(HIB head)
	:CplBasePool< CBasePoolEntry<CplIBPool> >(head)
{
}

CplIBPool::~CplIBPool()
{
}


}