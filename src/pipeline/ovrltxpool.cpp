#include "pipeline/txpool.h"

namespace openvrl {

/**
 *
 */
CplTXPool::CplTXPool(HTX head)
	:CplBasePool< CBasePoolEntry<CplTXPool> >(head)
{
}

CplTXPool::~CplTXPool()
{
}


}