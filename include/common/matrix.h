/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/matrix.h,v $
 * $Implementation: ~/src/ $
 * $Revision: 1.4 $
 * $Author: foxis $
 * $Date: 2005/03/01 18:21:15 $
 * $Description:  $
 *
 * $Log: matrix.h,v $
 * Revision 1.4  2005/03/01 18:21:15  foxis
 * Pipeline: shadows now working more or less. need to handle special cases.
 * C4x4Matrix: added inverse method + others
 *
 * Revision 1.3  2005/02/23 12:30:56  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.2  2005/02/02 20:04:15  foxis
 * Basic ODE support - seems to work ok
 * basic CBody - seems to work
 * basic system overall - seems to work :)
 *
 * minor bugfixes, and changes in body managment code
 *
 * Revision 1.1.1.1  2005/02/02 15:39:12  foxis
 * sources import
 *
 * Revision 0.3  20010411  :: FoxiE
 *
 */

#if !defined(AFX_COMMATRX_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_)
#define AFX_COMMATRX_H__48B351E2_A216_11D6_8083_D66192D7171A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include <stdio.h>

#include "common/types.h"
#include "common/exception.h"

namespace openvrl {

//
// 2D Matrix class OVRLIBAPI
//
class OVRLIBAPI C2DMatrix
{
	ulong m_width;
	ulong m_height;
	real *m_data;

	C2DMatrix();
public:
	C2DMatrix(ulong w, ulong h)
	{ 
		m_data = 0;
		resize(w,h);
	}
	C2DMatrix(ulong w, ulong h, const real *values)
	{ 
		m_data = 0;
		resize(w,h);
		set(values, size());
	}
	C2DMatrix(const C2DMatrix& matrix)
	{ 
		m_data = 0;
		resize(matrix.width(),matrix.height());
		set(matrix.data(), size());
	}
	~C2DMatrix()
	{ 
		OVRL_DELETE(m_data);
	}

	bool resize(ulong w, ulong h)
	{
		OVRL_DELETE(m_data);
		m_height = h;
		m_width = w;
		OVRL_NEW_EX(m_data, real,size());
		return m_data==0;
	}

	void set(ulong x, ulong y, real value)
	{
		if ( x<width() && y<height() ) data()[x + width()*y] = value;
	}
	real get(ulong x, ulong y)
	{
		if ( x<width() && y<height() ) 
			return data()[x + width()*y];
		else
			return 0;
	}
	void set(const real* values, ulong n)
	{
		OVRL_memcpy(data(), values, sizeof(data()[0])*n);
	}
	void get(real* values, ulong n)
	{
		OVRL_memcpy(values, data(), sizeof(data()[0])*n);
	}
	void set(ulong x, ulong y, ulong w, ulong h, const real* values);
	void get(ulong x, ulong y, ulong w, ulong h, real* values) const;

	//
	//
	C2DMatrix& operator=(const C2DMatrix& m)
	{
		set(m.data(), m.size());
		return *this;
	}

	/////
	//
	ulong width() const { return m_width; }
	ulong height() const { return m_height; }
	ulong size() const { return m_width*m_height; }
	real* data() const { return m_data; }
	real* data() { return m_data; }

	real determinant() const { return 0; }
};

//
// 3D Matrix class OVRLIBAPI
//
class OVRLIBAPI C3DMatrix
{
	ulong m_width;
	ulong m_height;
	ulong m_depth;
	real *m_data;

	C3DMatrix();
public:
	C3DMatrix(ulong w, ulong h, ulong d)
	{ 
		m_data = 0;
		resize(w,h,d);
	}
	C3DMatrix(ulong w, ulong h, ulong d, const real* values)
	{ 
		m_data = 0;
		resize(w,h,d);
		set(values, size());
	}
	C3DMatrix(const C3DMatrix& matrix)
	{ 
		m_data = 0;
		resize(matrix.width(),matrix.height(),matrix.depth());
		set(matrix.data(), matrix.size());
	}
	~C3DMatrix()
	{ 
		OVRL_DELETE(m_data);
	}

	bool resize(ulong w, ulong h, ulong d)
	{
		OVRL_DELETE(m_data);
		m_height = h;
		m_width = w;
		m_depth = d;
		OVRL_NEW_EX(m_data,real,size());
		return m_data==0;
	}

	void set(ulong x, ulong y, ulong z, real value)
	{
		if ( x<width() && y<height() && z<depth() ) 
			data()[x + width()*y + size2d()*z] = value;
	}
	real get(ulong x, ulong y, ulong z) const
	{
		if ( x<width() && y<height() ) 
			return data()[x + width()*y + size2d()*z];
		else
			return 0;
	}
	void set(const real* values, ulong n)
	{
		OVRL_memcpy(data(), values, sizeof(data()[0])*n);
	}
	void set(ulong depth, const real* values, ulong n)
	{
//		set(size2d()*depth, values, n);
	}
	void set(ulong depth, const C2DMatrix& matrix)
	{
		set(depth, matrix.data(), size2d());
	}
	void get(real* values, ulong n) const
	{
		OVRL_memcpy(values, data(), sizeof(data()[0])*n);
	}
	void get(ulong depth, const real* values, ulong n) const
	{
//		get(size2d()*depth, values, n);
	}
	void get(ulong depth, C2DMatrix& matrix) const
	{
		get(depth, matrix.data(), size2d());
	}
	C2DMatrix get(ulong depth) const
	{
		C2DMatrix matrix(width(), height());
		get(depth, matrix);
		return matrix;
	}
	void set(ulong x, ulong y, ulong z, ulong w, ulong h, ulong d, const real* values);
	void get(ulong x, ulong y, ulong z, ulong w, ulong h, ulong d, real* values) const;

	//
	//
	C3DMatrix& operator=(const C3DMatrix& m)
	{
		set(m.data(), m.size());
		return *this;
	}

	////
	//
	ulong width() const { return m_width; }
	ulong height() const { return m_height; }
	ulong depth() const { return m_depth; }
	ulong size() const { return m_width*m_height*m_depth; }
	ulong size2d() const { return m_width*m_height; }
	real* data() const { return m_data; }
	real* data() { return m_data; }

	real determinant() const { return 0; }
};

//
// 4x4 Matrix class OVRLIBAPI
//
class OVRLIBAPI C4x4Matrix
{
	real m_data[16];

public:
	C4x4Matrix()
	{
	}
	C4x4Matrix(const real* values)
	{
		set(values);
	}
	C4x4Matrix(real a1, real a2, real a3, real a4, 
		real a5, real a6, real a7, real a8, 
		real a9, real a10, real a11, real a12, 
		real a13, real a14, real a15, real a16)
	{
		set(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16);
	}
	C4x4Matrix(const C4x4Matrix& matrix)
	{
		set(matrix);
	}
	~C4x4Matrix() 
	{ }

	void clear()
	{
		OVRL_memset(data(), 0, sizeof(real)*size());
	}
	void set(const real* values, ulong n=16)
	{
		OVRL_memcpy(data(), values, sizeof(real)*n);
	}
	void set(real a1, real a2, real a3, real a4, 
		real a5, real a6, real a7, real a8, 
		real a9, real a10, real a11, real a12, 
		real a13, real a14, real a15, real a16)
	{
		data()[0] = a1;	data()[1] = a2;	data()[2] = a3;	data()[3] = a4;
		data()[4] = a5;	data()[5] = a6;	data()[6] = a7;	data()[7] = a8;
		data()[8] = a9;	data()[9] = a10;data()[10] = a11;data()[11] = a12;
		data()[12] = a13;data()[13] = a14;data()[14] = a15;data()[15] = a16;
	}
	void set(const C4x4Matrix& matrix)
	{
		set(matrix.data());
	}

	//
	void set_identity()
	{
		clear();
		data()[0] = data()[5] = data()[10] = data()[15] = 1.0;
	}
	void set_rotate(real x, real y, real z)
	{
		const real c1 = cos(x);  
		const real c2 = cos(y);  
		const real c3 = cos(z);
        const real s1 = sin(x);  
		const real s2 = sin(y);  
		const real s3 = sin(z);
        set(1, 0, 0, 0, 0,c1,-s1, 0, 0,s1,c1, 0, 0, 0, 0, 1);
        mul(C4x4Matrix(c2, 0,-s2, 0, 0, 1, 0, 0, s2, 0,c2, 0, 0, 0, 0, 1));
        mul(C4x4Matrix(c3,s3, 0, 0, -s3,c3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
	}
	void set_translate(real x, real y, real z)
	{
		set(1,0,0,0, 0,1,0,0, 0,0,1,0, x,y,z,1);
	}
	void set_scale(real x, real y, real z)
	{
		set(x,0,0,0, 0,y,0,0, 0,0,z,0, 0,0,0,1);
	}

	static C4x4Matrix identity()
	{
		return C4x4Matrix(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
	}
	static C4x4Matrix zero()
	{
		return C4x4Matrix(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
	}
	static C4x4Matrix rotate(real x, real y, real z) 
	{
		C4x4Matrix m;
		m.set_rotate(x,y,z);
		return m;
	}
	static C4x4Matrix translate(real x, real y, real z) 
	{
		C4x4Matrix m;
		m.set_translate(x,y,z);
		return m;
	}
	static C4x4Matrix scale(real x, real y, real z)
	{
		C4x4Matrix m;
		m.set_scale(x,y,z);
		return m;
	}

	//
	void clear_rotation()
	{
		data()[0] = data()[5] = data()[10] = 1;
		data()[1] = data()[2] = data()[4] = data()[6] = 0;
	}
	void clear_translate()
	{
		data()[12]=data()[13]=data()[14] = 0;
	}

	void normalize()
	{
		real Xx = data()[0], Xy=data()[4],Xz=data()[8];
		real Yx = data()[1],Yy=data()[5],Yz=data()[9];
		real Zx, Zy, Zz;
		real len;
		len = sqrt(Xx*Xx+Xy*Xy+Xz*Xz);
		Xx /= len; Xy /= len; Xz /=len;
		Zx = Xy*Yz - Xz*Yy; // cross product
		Zy = Xz*Yx - Xx*Yz;
		Zz = Xx*Yy - Xy*Yx;
		Yx = Zy*Xz - Zz*Xy;	// cross product
		Yy = Zz*Xx - Zx*Xz;
		Yz = Zx*Xy - Zy*Xx;
		len = sqrt(Yx*Yx+Yy*Yy+Yz*Yz);
		Yx /= len; Yy /= len; Yz /=len;
		len = sqrt(Zx*Zx+Zy*Zy+Zz*Zz);
		Zx /= len; Zy /= len; Zz /=len;
		data()[0] = Xx; data()[1] = Yx; data()[2] = Zx;
		data()[4] = Xy; data()[5] = Yy; data()[6] = Zy;
		data()[8] = Xz; data()[9] = Yz; data()[10] = Zz;
	}

	//
	void add(const C4x4Matrix& m)
	{
		data()[0] += m.data()[0];	data()[8] += m.data()[8];
		data()[1] += m.data()[1];	data()[9] += m.data()[9];
		data()[2] += m.data()[2];	data()[10] += m.data()[10];
		data()[3] += m.data()[3];	data()[11] += m.data()[11];
		data()[4] += m.data()[4];	data()[12] += m.data()[12];
		data()[5] += m.data()[5];	data()[13] += m.data()[13];
		data()[6] += m.data()[6];	data()[14] += m.data()[14];
		data()[7] += m.data()[7];	data()[15] += m.data()[15];
	}
	void sub(const C4x4Matrix& m)
	{
		data()[0] -= m.data()[0];	data()[8] -= m.data()[8];
		data()[1] -= m.data()[1];	data()[9] -= m.data()[9];
		data()[2] -= m.data()[2];	data()[10] -= m.data()[10];
		data()[3] -= m.data()[3];	data()[11] -= m.data()[11];
		data()[4] -= m.data()[4];	data()[12] -= m.data()[12];
		data()[5] -= m.data()[5];	data()[13] -= m.data()[13];
		data()[6] -= m.data()[6];	data()[14] -= m.data()[14];
		data()[7] -= m.data()[7];	data()[15] -= m.data()[15];
	}
	void mulby(real k)
	{
		data()[0] *= k;	data()[4] *= k;	data()[8] *= k;	data()[12] *= k;
		data()[1] *= k;	data()[5] *= k;	data()[9] *= k;	data()[13] *= k;
		data()[2] *= k;	data()[6] *= k;	data()[10] *= k;data()[14] *= k;
		data()[3] *= k;	data()[7] *= k;	data()[11] *= k;data()[15] *= k;
	}
	void mul(const C4x4Matrix& m)
	{
		real tmp[4];
		const	ulong cb = sizeof(tmp[0])*4;
#define M__M4x4MUL__M(A,B,i) (A)[0]*(B)[i]+(A)[1]*(B)[4+i]+(A)[2]*(B)[8+i]+(A)[3]*(B)[12+i]
		memcpy(tmp, data(), cb);
		data()[0]=M__M4x4MUL__M(tmp,m.data(),0);
		data()[1]=M__M4x4MUL__M(tmp,m.data(),1);
		data()[2]=M__M4x4MUL__M(tmp,m.data(),2);
		data()[3]=M__M4x4MUL__M(tmp,m.data(),3);
		memcpy(tmp, data()+4, cb);
		data()[4]=M__M4x4MUL__M(tmp,m.data(),0);
		data()[5]=M__M4x4MUL__M(tmp,m.data(),1);
		data()[6]=M__M4x4MUL__M(tmp,m.data(),2);
		data()[7]=M__M4x4MUL__M(tmp,m.data(),3);
		memcpy(tmp, data()+8, cb);
		data()[8]=M__M4x4MUL__M(tmp,m.data(),0);
		data()[9]=M__M4x4MUL__M(tmp,m.data(),1);
		data()[10]=M__M4x4MUL__M(tmp,m.data(),2);
		data()[11]=M__M4x4MUL__M(tmp,m.data(),3);
		memcpy(tmp, data()+12, cb);
		data()[12]=M__M4x4MUL__M(tmp,m.data(),0);
		data()[13]=M__M4x4MUL__M(tmp,m.data(),1);
		data()[14]=M__M4x4MUL__M(tmp,m.data(),2);
		data()[15]=M__M4x4MUL__M(tmp,m.data(),3);
#undef M__M4x4MUL__M
	}

	C4x4Matrix add(const C4x4Matrix& m1) const
	{
		C4x4Matrix m(*this);
		m.add(m1);
		return m;
	}
	C4x4Matrix sub(const C4x4Matrix& m1) const
	{
		C4x4Matrix m(*this);
		m.sub(m1);
		return m;
	}
	C4x4Matrix mulby(real k) const
	{
		C4x4Matrix m(*this);
		m.mulby(k);
		return m;
	}
	C4x4Matrix mul(const C4x4Matrix& m1) const
	{
		C4x4Matrix m(*this);
		m.mul(m1);
		return m;
	}

	C4x4Matrix& operator=(const C4x4Matrix& m)
	{
		set(m);
		return *this;
	}
	C4x4Matrix operator+(const C4x4Matrix& m1) const
	{
		return add(m1);
	}
	C4x4Matrix operator-(const C4x4Matrix& m1) const
	{
		return sub(m1);
	}
	C4x4Matrix operator*(real k) const
	{
		return mulby(k);
	}
	C4x4Matrix operator*(const C4x4Matrix& m1) const
	{
		return mul(m1);
	}

	C4x4Matrix& operator+=(const C4x4Matrix& m1)
	{
		add(m1);
		return *this;
	}
	C4x4Matrix& operator-=(const C4x4Matrix& m1)
	{
		sub(m1);
		return *this;
	}
	C4x4Matrix& operator*=(real k)
	{
		mulby(k);
		return *this;
	}
	C4x4Matrix& operator*=(const C4x4Matrix& m1)
	{
		mul(m1);
		return *this;
	}

	////
	//
	//
	ulong width() const { return 4; }
	ulong height() const { return 4; }
	ulong size() const { return 16; }
	real* data() const { return (real*)m_data; }
	real* data() { return m_data; }

	real minor(ulong i, ulong j) const
	{
		return 0;
	}

	void submat( const C4x4Matrix& m, ushort i, ushort j)
	{
		short di, dj, si, sj;
		// loop through 3x3 submatrix
		for( di = 0; di < 3; di ++ ) {
			for( dj = 0; dj < 3; dj ++ ) {
			// map 3x3 element (destination) to 4x4 element (source)
			si = di + ( ( di >= i ) ? 1 : 0 );
			sj = dj + ( ( dj >= j ) ? 1 : 0 );
			// copy element
			data()[di*3 + dj] = m.data()[si*4 + sj];
			}
		}
	}

	void inverse(const C4x4Matrix& m)
	{
		C4x4Matrix tmp;
		real mdet = m.determinant( );
		short i, j, sign;

		if ( abs( mdet ) < 1e-32 )
		{
			set_identity();
			return ;
		}

		for ( i = 0; i < 4; i++ )
			for ( j = 0; j < 4; j++ )
			{
				sign = 1 - ( (i +j) % 2 ) * 2;
				tmp.submat( m, i, j );
				data()[i+j*4] = ( tmp.determinant3() * sign ) / mdet;
			}
	}

#define D(i) data()[i]
	void transpose_rotate()
	{
		real tmp;
		tmp = D(4*0+1); D(4*0+1) = D(4*1+0); D(4*1+0) = tmp;
		tmp = D(4*0+2); D(4*0+2) = D(4*2+0); D(4*2+0) = tmp;
		tmp = D(4*1+2); D(4*1+2) = D(4*2+1); D(4*2+1) = tmp;
	}
	void transpose()
	{
		real tmp;
		tmp = D(4*0+1); D(4*0+1) = D(4*1+0); D(4*1+0) = tmp;
		tmp = D(4*0+2); D(4*0+2) = D(4*2+0); D(4*2+0) = tmp;
		tmp = D(4*1+2); D(4*1+2) = D(4*2+1); D(4*2+1) = tmp;

		tmp = D(4*0+3); D(4*0+3) = D(4*3+0); D(4*3+0) = tmp;
		tmp = D(4*1+3); D(4*1+3) = D(4*3+1); D(4*3+1) = tmp;
		tmp = D(4*2+3); D(4*2+3) = D(4*3+2); D(4*3+2) = tmp;
	}
	void neg_translate()
	{
		D(4*3+0) *= -1;
		D(4*3+1) *= -1;
		D(4*3+2) *= -1;
	}
	real determinant() const 
	{ 
		real  det, result = 0, i = 1;
		C4x4Matrix msub3;
		short     n;

		for ( n = 0; n < 4; n++, i *= -1 )
		{
			msub3.submat( *this, 0, n );
			det     = msub3.determinant3( );
			result += data()[n] * det * i;
		}
		return result;
	}

	real determinant3() const 
	{ 
		return D(0) * ( D(4)*D(8) - D(7)*D(5) )
          - D(1) * ( D(3)*D(8) - D(6)*D(5) )
          + D(2) * ( D(3)*D(7) - D(6)*D(5) );
	}

	void dump(char* s) const
	{
		sprintf(s, "%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
			D(0),D(1),D(2),D(3),
			D(4),D(5),D(6),D(7),
			D(8),D(9),D(10),D(11),
			D(12),D(13),D(14),D(15));
	}
#undef D			
};

};

#endif 
