#include "common/matrix.h"

namespace openvrl {


//
// 2D Matrix
//
C2DMatrix::C2DMatrix()
{
	m_data = 0;
}

void C2DMatrix::set(ulong x, ulong y, ulong w, ulong h, const real* values)
{
}

void C2DMatrix::get(ulong x, ulong y, ulong w, ulong h, real* values) const
{
}

//
// 3D Matrix
//
C3DMatrix::C3DMatrix()
{
	m_data = 0;
}

void C3DMatrix::set(ulong x, ulong y, ulong z, ulong w, ulong h, ulong d, const real* values)
{
}

void C3DMatrix::get(ulong x, ulong y, ulong z, ulong w, ulong h, ulong d, real* values) const
{
}

} // namespace