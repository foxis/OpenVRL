#include "pipeline/vspool.h"

namespace openvrl {

/**
 *
 */
CplVSPool::CplVSPool(HVS head)
	:CplBasePool< CBasePoolEntry<CplVSPool> >(head)
{
}

CplVSPool::~CplVSPool()
{
}

}