#include "common/3dbvl.h"

namespace openvrl {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int C3DBoundingVolume::create(const C3DPoint* p, ulong n, BoundingVolume_enum type)
{
	switch ( type )
	{
	case VOLUME_AABB: return create_AABB(p, n);
	case VOLUME_OBB: return create_OBB(p, n);
	case VOLUME_BS: return create_BS(p, n);
	default: return 0;
	}
}

//////////
//
//
int C3DBoundingVolume::create_OBB(const C3DPoint* p, ulong n)
{
	return 0;
}

//////////
//
//
int C3DBoundingVolume::create_AABB(const C3DPoint* p, ulong n)
{
	return 0;
}

//////////
//
//
int C3DBoundingVolume::create_BS(const C3DPoint* p, ulong n)
{
	return 0;
}


////////////////////////////////////////////
//
////////////////////////////////////////////
CAABBTree::CAABBTree()
{
}
CAABBTree::~CAABBTree()
{
}

int CAABBTree::build()
{
	return 0;
}

} // namespace