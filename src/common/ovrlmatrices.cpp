#include "common/matrices.h"
#include "common/math.h"

namespace openvrl {

const matrix4x4_t MATUNIT =    {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
const matrix3x3_t MATUNIT3X3 = {1,0,0,0,1,0,0,0,1};

/* Initializes the 4x4 matrix */
void OVRLIBAPI
matrix_set(matrix4x4_t* DST,
        real a0, real a1, real a2, real a3,
        real a4, real a5, real a6, real a7,
        real a8, real a9, real aA, real aB,
        real aC, real aD, real aE, real aF
)
{
        if ( DST==0 ) return;

        DST->data16[0]= a0;
        DST->data16[1]= a1;
        DST->data16[2]= a2;
        DST->data16[3]= a3;
        DST->data16[4]= a4;
        DST->data16[5]= a5;
        DST->data16[6]= a6;
        DST->data16[7]= a7;
        DST->data16[8]= a8;
        DST->data16[9]= a9;
        DST->data16[10]= aA;
        DST->data16[11]= aB;
        DST->data16[12]= aC;
        DST->data16[13]= aD;
        DST->data16[14]= aE;
        DST->data16[15]= aF;
}

/* identity matrix */
void OVRLIBAPI
matrix_set_identity(matrix4x4_t* A)
{
        matrix_set(A, 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
}

/* rotation matrix */
void OVRLIBAPI
matrix_set_rotate(matrix4x4_t* A, const vector3d_t& a)
{
        matrix4x4_t mr;
        real c1, c2, c3, s1, s2, s3;

        if ( A==0 ) return;
        c1 = cos(a.x);  c2 = cos(a.y);  c3 = cos(a.z);
        s1 = sin(a.x);  s2 = sin(a.y);  s3 = sin(a.z);
        matrix_set(A, 1, 0, 0, 0, 0,c1,-s1, 0, 0,s1,c1, 0, 0, 0, 0, 1);
        matrix_set(&mr, c2, 0,-s2, 0, 0, 1, 0, 0, s2, 0,c2, 0, 0, 0, 0, 1);
        *A = matrix_mul(*A, mr);
        matrix_set(&mr, c3,s3, 0, 0, -s3,c3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
        *A = matrix_mul(*A, mr);
}

/* rotation matrix from quaternion */
void OVRLIBAPI
matrix_set_from_quaternion(matrix4x4_t* A, const quaternion_t& q)
{
//(1-2*(y*y+z*z),  2*(x*y+r*z),  2*(x*z-r*y));}
//(  2*(x*y-r*z),1-2*(x*x+z*z),  2*(y*z+r*x));}
//(  2*(x*z+r*y),  2*(y*z-r*x),1-2*(x*x+y*y));}
        A->data4x4[0][0] = 1-2*(q.y*q.y + q.z*q.z);
        A->data4x4[1][0] = 2*(q.x*q.y - q.q*q.z);
        A->data4x4[2][0] = 2*(q.x*q.z + q.q*q.y);
        A->data4x4[3][0] = 0;
        A->data4x4[0][1] = 2*(q.x*q.y + q.q*q.z);
        A->data4x4[1][1] = 1-2*(q.x*q.x + q.z*q.z);
        A->data4x4[2][1] = 2*(q.y*q.z - q.q*q.x);
        A->data4x4[3][1] = 0;
        A->data4x4[0][2] = 2*(q.x*q.z - q.q*q.y);
        A->data4x4[1][2] = 2*(q.y*q.z + q.q*q.x);
        A->data4x4[2][2] = 1-2*(q.x*q.x + q.y*q.y);
        A->data4x4[3][2] = 0;
        A->data4x4[0][3] = 0;
        A->data4x4[1][3] = 0;
        A->data4x4[2][3] = 0;
        A->data4x4[3][3] = 1;
}

/* translation matrix */
void OVRLIBAPI
matrix_set_translate(matrix4x4_t* A, const vector3d_t& v)
{
        matrix_set(A, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, v.x,v.y,v.z, 1);
}

/* scale matrix */
void OVRLIBAPI
matrix_set_scale(matrix4x4_t* A, const vector3d_t& v)
{
        matrix_set(A, v.x,  0, 0, 0, 0,v.y, 0, 0, 0, 0,v.z, 0, 0, 0, 0, 1);
}

/* identity matrix */
matrix4x4_t OVRLIBAPI
matrix_identity(void)
{
        matrix4x4_t a;
        matrix_set(&a, 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
        return a;
}

/* rotation matrix */
matrix4x4_t OVRLIBAPI
matrix_rotate(const vector3d_t& a)
{
        matrix4x4_t mr;
        matrix4x4_t A;
        real c1, c2, c3, s1, s2, s3;

        c1 = cos(a.x);  c2 = cos(a.y);  c3 = cos(a.z);
        s1 = sin(a.x);  s2 = sin(a.y);  s3 = sin(a.z);
        matrix_set(&A, 1, 0, 0, 0, 0,c1,-s1, 0, 0,s1,c1, 0, 0, 0, 0, 1);
        matrix_set(&mr, c2, 0,-s2, 0, 0, 1, 0, 0, s2, 0,c2, 0, 0, 0, 0, 1);
        A = matrix_mul(A, mr);
        matrix_set(&mr, c3,s3, 0, 0, -s3,c3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
        A = matrix_mul(A, mr);
        return A;
}

/* rotation matrix from quaternion */
matrix4x4_t OVRLIBAPI
matrix_from_quaternion(const quaternion_t& q)
{
        matrix4x4_t A;

        A.data4x4[0][0] = 1-2*(q.y*q.y + q.z*q.z);
        A.data4x4[1][0] = 2*(q.x*q.y + q.q*q.z);
        A.data4x4[2][0] = 2*(q.x*q.z - q.q*q.y);
        A.data4x4[3][0] = 0;
        A.data4x4[0][1] = 2*(q.x*q.y - q.q*q.z);
        A.data4x4[1][1] = 1-2*(q.x*q.x - q.z*q.z);
        A.data4x4[2][1] = 2*(q.y*q.z + q.q*q.x);
        A.data4x4[3][1] = 0;
        A.data4x4[0][2] = 2*(q.x*q.z + q.q*q.y);
        A.data4x4[1][2] = 2*(q.y*q.z - q.q*q.x);
        A.data4x4[2][2] = 1-2*(q.x*q.x - q.y*q.y);
        A.data4x4[3][2] = 0;
        A.data4x4[0][3] = 0;
        A.data4x4[1][3] = 0;
        A.data4x4[2][3] = 0;
        A.data4x4[3][3] = 1;

        return A;
}

/* translation matrix */
matrix4x4_t OVRLIBAPI
matrix_translate(const vector3d_t& v)
{
        matrix4x4_t A;
        matrix_set(&A, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, v.x,v.y,v.z, 1);
        return A;
}

/* scale matrix */
matrix4x4_t OVRLIBAPI
matrix_scale(const vector3d_t& v)
{
        matrix4x4_t A;
        matrix_set(&A, v.x,  0, 0, 0, 0,v.y, 0, 0, 0, 0,v.z, 0, 0, 0, 0, 1);
        return A;
}

/* Copies one matrix to another(DST<-source) */
void OVRLIBAPI
matrix_copy(matrix4x4_t* DST, const matrix4x4_t& A)
{
        if ( DST==0 ) return;
        memcpy(DST, &A, sizeof(matrix4x4_t));
}

/* Adds one matrix to another and puts it to the first matrix */
matrix4x4_t OVRLIBAPI
matrix_add(const matrix4x4_t& A, const matrix4x4_t& B)
{
        matrix4x4_t DST;
        DST.data16[0] = A.data16[0] + B.data16[0];
        DST.data16[1] = A.data16[1] + B.data16[1];
        DST.data16[2] = A.data16[2] + B.data16[2];
        DST.data16[3] = A.data16[3] + B.data16[3];
        DST.data16[4] = A.data16[4] + B.data16[4];
        DST.data16[5] = A.data16[5] + B.data16[5];
        DST.data16[6] = A.data16[6] + B.data16[6];
        DST.data16[7] = A.data16[7] + B.data16[7];
        DST.data16[8] = A.data16[8] + B.data16[8];
        DST.data16[9] = A.data16[9] + B.data16[9];
        DST.data16[10] = A.data16[10] + B.data16[10];
        DST.data16[11] = A.data16[11] + B.data16[11];
        DST.data16[12] = A.data16[12] + B.data16[12];
        DST.data16[13] = A.data16[13] + B.data16[13];
        DST.data16[14] = A.data16[14] + B.data16[14];
        DST.data16[15] = A.data16[15] + B.data16[15];

        return DST;
}

/* Adds one matrix to another and puts it to the first matrix */
void OVRLIBAPI
matrix_add_to(matrix4x4_t* DST, const matrix4x4_t& A, const matrix4x4_t& B)
{
        if ( DST==0 ) return;
        DST->data16[0] = A.data16[0] + B.data16[0];
        DST->data16[1] = A.data16[1] + B.data16[1];
        DST->data16[2] = A.data16[2] + B.data16[2];
        DST->data16[3] = A.data16[3] + B.data16[3];
        DST->data16[4] = A.data16[4] + B.data16[4];
        DST->data16[5] = A.data16[5] + B.data16[5];
        DST->data16[6] = A.data16[6] + B.data16[6];
        DST->data16[7] = A.data16[7] + B.data16[7];
        DST->data16[8] = A.data16[8] + B.data16[8];
        DST->data16[9] = A.data16[9] + B.data16[9];
        DST->data16[10] = A.data16[10] + B.data16[10];
        DST->data16[11] = A.data16[11] + B.data16[11];
        DST->data16[12] = A.data16[12] + B.data16[12];
        DST->data16[13] = A.data16[13] + B.data16[13];
        DST->data16[14] = A.data16[14] + B.data16[14];
        DST->data16[15] = A.data16[15] + B.data16[15];
}

/* Substracts first matrix from second and puts the result to the first one. */
matrix4x4_t OVRLIBAPI
matrix_sub(const matrix4x4_t& A, const matrix4x4_t& B)
{
        matrix4x4_t DST;
        DST.data16[0] = A.data16[0] - B.data16[0];
        DST.data16[1] = A.data16[1] - B.data16[1];
        DST.data16[2] = A.data16[2] - B.data16[2];
        DST.data16[3] = A.data16[3] - B.data16[3];
        DST.data16[4] = A.data16[4] - B.data16[4];
        DST.data16[5] = A.data16[5] - B.data16[5];
        DST.data16[6] = A.data16[6] - B.data16[6];
        DST.data16[7] = A.data16[7] - B.data16[7];
        DST.data16[8] = A.data16[8] - B.data16[8];
        DST.data16[9] = A.data16[9] - B.data16[9];
        DST.data16[10] = A.data16[10] - B.data16[10];
        DST.data16[11] = A.data16[11] - B.data16[11];
        DST.data16[12] = A.data16[12] - B.data16[12];
        DST.data16[13] = A.data16[13] - B.data16[13];
        DST.data16[14] = A.data16[14] - B.data16[14];
        DST.data16[15] = A.data16[15] - B.data16[15];

        return DST;
}

/* Substracts first matrix from second and puts the result to the first one. */
void OVRLIBAPI
matrix_sub_to(matrix4x4_t* DST, const matrix4x4_t& A, const matrix4x4_t& B)
{
        if ( DST==0 ) return;
        DST->data16[0] = A.data16[0] - B.data16[0];
        DST->data16[1] = A.data16[1] - B.data16[1];
        DST->data16[2] = A.data16[2] - B.data16[2];
        DST->data16[3] = A.data16[3] - B.data16[3];
        DST->data16[4] = A.data16[4] - B.data16[4];
        DST->data16[5] = A.data16[5] - B.data16[5];
        DST->data16[6] = A.data16[6] - B.data16[6];
        DST->data16[7] = A.data16[7] - B.data16[7];
        DST->data16[8] = A.data16[8] - B.data16[8];
        DST->data16[9] = A.data16[9] - B.data16[9];
        DST->data16[10] = A.data16[10] - B.data16[10];
        DST->data16[11] = A.data16[11] - B.data16[11];
        DST->data16[12] = A.data16[12] - B.data16[12];
        DST->data16[13] = A.data16[13] - B.data16[13];
        DST->data16[14] = A.data16[14] - B.data16[14];
        DST->data16[15] = A.data16[15] - B.data16[15];
}

/* Multiplys a matrix by some real */
matrix4x4_t OVRLIBAPI
matrix_mul_by(const matrix4x4_t& A, real K)
{
        matrix4x4_t DST;
        DST.data16[0] = A.data16[0] * K;
        DST.data16[1] = A.data16[1] * K;
        DST.data16[2] = A.data16[2] * K;
        DST.data16[3] = A.data16[3] * K;
        DST.data16[4] = A.data16[4] * K;
        DST.data16[5] = A.data16[5] * K;
        DST.data16[6] = A.data16[6] * K;
        DST.data16[7] = A.data16[7] * K;
        DST.data16[8] = A.data16[8] * K;
        DST.data16[9] = A.data16[9] * K;
        DST.data16[10] = A.data16[10] * K;
        DST.data16[11] = A.data16[11] * K;
        DST.data16[12] = A.data16[12] * K;
        DST.data16[13] = A.data16[13] * K;
        DST.data16[14] = A.data16[14] * K;
        DST.data16[15] = A.data16[15] * K;

        return DST;
}

/* Does the same, but puts the result into 'source' */
void OVRLIBAPI
matrix_mul_by(matrix4x4_t* DST, const matrix4x4_t& A, real K)
{
        if ( DST==0 ) return;
        DST->data16[0] = A.data16[0] * K;
        DST->data16[1] = A.data16[1] * K;
        DST->data16[2] = A.data16[2] * K;
        DST->data16[3] = A.data16[3] * K;
        DST->data16[4] = A.data16[4] * K;
        DST->data16[5] = A.data16[5] * K;
        DST->data16[6] = A.data16[6] * K;
        DST->data16[7] = A.data16[7] * K;
        DST->data16[8] = A.data16[8] * K;
        DST->data16[9] = A.data16[9] * K;
        DST->data16[10] = A.data16[10] * K;
        DST->data16[11] = A.data16[11] * K;
        DST->data16[12] = A.data16[12] * K;
        DST->data16[13] = A.data16[13] * K;
        DST->data16[14] = A.data16[14] * K;
        DST->data16[15] = A.data16[15] * K;
}

/* Divides a matrix by some real */
matrix4x4_t OVRLIBAPI
matrix_div_by(const matrix4x4_t& A, real k)
{
        matrix4x4_t DST;
        real K;
        if ( k<constants::EPSILON ) return A;
        K = 1/k;
        DST.data16[0] = A.data16[0] * K;
        DST.data16[1] = A.data16[1] * K;
        DST.data16[2] = A.data16[2] * K;
        DST.data16[3] = A.data16[3] * K;
        DST.data16[4] = A.data16[4] * K;
        DST.data16[5] = A.data16[5] * K;
        DST.data16[6] = A.data16[6] * K;
        DST.data16[7] = A.data16[7] * K;
        DST.data16[8] = A.data16[8] * K;
        DST.data16[9] = A.data16[9] * K;
        DST.data16[10] = A.data16[10] * K;
        DST.data16[11] = A.data16[11] * K;
        DST.data16[12] = A.data16[12] * K;
        DST.data16[13] = A.data16[13] * K;
        DST.data16[14] = A.data16[14] * K;
        DST.data16[15] = A.data16[15] * K;

        return DST;
}

/* Does the same, but puts the result into 'DST' */
void OVRLIBAPI
matrix_div_by_to(matrix4x4_t* DST, const matrix4x4_t& A, real k)
{
        real K;

        if ( DST==0 ) return;
        if ( k<constants::EPSILON ) return;
        K = 1/k;
        DST->data16[0] = A.data16[0] * K;
        DST->data16[1] = A.data16[1] * K;
        DST->data16[2] = A.data16[2] * K;
        DST->data16[3] = A.data16[3] * K;
        DST->data16[4] = A.data16[4] * K;
        DST->data16[5] = A.data16[5] * K;
        DST->data16[6] = A.data16[6] * K;
        DST->data16[7] = A.data16[7] * K;
        DST->data16[8] = A.data16[8] * K;
        DST->data16[9] = A.data16[9] * K;
        DST->data16[10] = A.data16[10] * K;
        DST->data16[11] = A.data16[11] * K;
        DST->data16[12] = A.data16[12] * K;
        DST->data16[13] = A.data16[13] * K;
        DST->data16[14] = A.data16[14] * K;
        DST->data16[15] = A.data16[15] * K;
}

/* Multiplys one matrix by another(concatenates'em) */
matrix4x4_t OVRLIBAPI
matrix_mul(const matrix4x4_t& A, const matrix4x4_t& B)
{
  real tmp[4];
  matrix4x4_t DST;

#define MMUL(A,B,i) A[0]*B.data4x4[0][i]+A[1]*B.data4x4[1][i]+ \
                    A[2]*B.data4x4[2][i]+A[3]*B.data4x4[3][i]

    tmp[0] = A.data4x4[0][0];
    tmp[1] = A.data4x4[0][1];
    tmp[2] = A.data4x4[0][2];
    tmp[3] = A.data4x4[0][3];
    DST.data4x4[0][0]=MMUL(tmp,B,0);
    DST.data4x4[0][1]=MMUL(tmp,B,1);
    DST.data4x4[0][2]=MMUL(tmp,B,2);
    DST.data4x4[0][3]=MMUL(tmp,B,3);

    tmp[0] = A.data4x4[1][0];
    tmp[1] = A.data4x4[1][1];
    tmp[2] = A.data4x4[1][2];
    tmp[3] = A.data4x4[1][3];
    DST.data4x4[1][0]=MMUL(tmp,B,0);
    DST.data4x4[1][1]=MMUL(tmp,B,1);
    DST.data4x4[1][2]=MMUL(tmp,B,2);
    DST.data4x4[1][3]=MMUL(tmp,B,3);

    tmp[0] = A.data4x4[2][0];
    tmp[1] = A.data4x4[2][1];
    tmp[2] = A.data4x4[2][2];
    tmp[3] = A.data4x4[2][3];
    DST.data4x4[2][0]=MMUL(tmp,B,0);
    DST.data4x4[2][1]=MMUL(tmp,B,1);
    DST.data4x4[2][2]=MMUL(tmp,B,2);
    DST.data4x4[2][3]=MMUL(tmp,B,3);

    tmp[0] = A.data4x4[3][0];
    tmp[1] = A.data4x4[3][1];
    tmp[2] = A.data4x4[3][2];
    tmp[3] = A.data4x4[3][3];
    DST.data4x4[3][0]=MMUL(tmp,B,0);
    DST.data4x4[3][1]=MMUL(tmp,B,1);
    DST.data4x4[3][2]=MMUL(tmp,B,2);
    DST.data4x4[3][3]=MMUL(tmp,B,3);

#undef MMUL

  return DST;
}

/* The same, but puts the result into 'source' */
void OVRLIBAPI
matrix_mul_to(matrix4x4_t* DST, const matrix4x4_t& A, const matrix4x4_t& B)
{
  real tmp[4];

    if ( DST==0 ) return;
#define MMUL(A,B,i) A[0]*B.data4x4[0][i]+A[1]*B.data4x4[1][i]+ \
                    A[2]*B.data4x4[2][i]+A[3]*B.data4x4[3][i]

    tmp[0] = A.data4x4[0][0];
    tmp[1] = A.data4x4[0][1];
    tmp[2] = A.data4x4[0][2];
    tmp[3] = A.data4x4[0][3];
    DST->data4x4[0][0]=MMUL(tmp,B,0);
    DST->data4x4[0][1]=MMUL(tmp,B,1);
    DST->data4x4[0][2]=MMUL(tmp,B,2);
    DST->data4x4[0][3]=MMUL(tmp,B,3);

    tmp[0] = A.data4x4[1][0];
    tmp[1] = A.data4x4[1][1];
    tmp[2] = A.data4x4[1][2];
    tmp[3] = A.data4x4[1][3];
    DST->data4x4[1][0]=MMUL(tmp,B,0);
    DST->data4x4[1][1]=MMUL(tmp,B,1);
    DST->data4x4[1][2]=MMUL(tmp,B,2);
    DST->data4x4[1][3]=MMUL(tmp,B,3);

    tmp[0] = A.data4x4[2][0];
    tmp[1] = A.data4x4[2][1];
    tmp[2] = A.data4x4[2][2];
    tmp[3] = A.data4x4[2][3];
    DST->data4x4[2][0]=MMUL(tmp,B,0);
    DST->data4x4[2][1]=MMUL(tmp,B,1);
    DST->data4x4[2][2]=MMUL(tmp,B,2);
    DST->data4x4[2][3]=MMUL(tmp,B,3);

    tmp[0] = A.data4x4[3][0];
    tmp[1] = A.data4x4[3][1];
    tmp[2] = A.data4x4[3][2];
    tmp[3] = A.data4x4[3][3];
    DST->data4x4[3][0]=MMUL(tmp,B,0);
    DST->data4x4[3][1]=MMUL(tmp,B,1);
    DST->data4x4[3][2]=MMUL(tmp,B,2);
    DST->data4x4[3][3]=MMUL(tmp,B,3);

#undef MMUL
}


/* Multiplys a matrix by a vector */
vector3d_t OVRLIBAPI
matrix_mul_vector(const matrix4x4_t& M, const vector3d_t& V)
{
  vector3d_t tmp;

#define MMUL(m,i) M.data16[0+i]*V.x+M.data16[4+i]*V.y+ \
                  M.data16[8+i]*V.z+M.data16[12+i]
  tmp.x = MMUL(M,0);
  tmp.y = MMUL(M,1);
  tmp.z = MMUL(M,2);
#undef MMUL
  return tmp;
}


/* Finds out the determinant of a matrix */
real OVRLIBAPI
matrix_determinant(const matrix4x4_t& matrix)
{
        matrix4x4_t  A, P;
        int j, n;
        real result;

        n = 4;
        matrix_copy(&A, matrix);
        matrix_set_identity(&P);

        /*
        * case for singular matrix
        */

        /*
        * normal case: |A| = |L||U||P|
        * |L| = 1,
        * |U| = multiplication of the diagonal
        * |P| = +-1
        */
        result = 1.0;
        for ( j=0; j<n; j++) {
//              result *= A[(int)P[j][0]][j];
        }

        return result;
}

/* Inverts a matrix */
matrix4x4_t OVRLIBAPI
matrix_invert(const matrix4x4_t& A)
{
  return A;
}

/* inserts a matrix on a matrix stack */
int OVRLIBAPI matrix_push3x3(matrix_stack_t* ms, const matrix3x3_t& A, MATRIX_WHAT_t w)
{
        matrix_stack_node_t* tmp;

        if ( ms==0 ) return 1;
        tmp = new matrix_stack_node_t;
        memset(tmp, 0, sizeof(*tmp));
        tmp->next = ms->first;
        if ( ms->first ) tmp->next->prev = tmp;
        ms->first = tmp;
        tmp->what = w;
        tmp->matrix3x3 = A;
        ms->elements++;
        return 0;
}

int OVRLIBAPI matrix_push4x4(matrix_stack_t* ms, const matrix4x4_t& A, MATRIX_WHAT_t w)
{
        matrix_stack_node_t* tmp;

        if ( ms==0 ) return 1;
        tmp = new matrix_stack_node_t;
        memset(tmp, 0, sizeof(*tmp));
        tmp->next = ms->first;
        if ( ms->first ) tmp->next->prev = tmp;
        ms->first = tmp;
        tmp->what = w;
        tmp->matrix4x4 = A;
        ms->elements++;
        return 0;
}

/* removes a matrix from a matrix stack */
MATRIX_WHAT_t OVRLIBAPI matrix_pop3x3(matrix_stack_t* ms, matrix3x3_t* A)
{
        matrix_stack_node_t* tmp;
        MATRIX_WHAT_t wt;

        if ( ms==0 ) return MATRIX_INVALID;
        tmp = ms->first;
        if ( tmp==0 ) return MATRIX_INVALID;
        ms->first = tmp->next;
        if ( tmp->next ) tmp->next->prev = 0;
        wt = tmp->what;
        *A = tmp->matrix3x3;
        delete tmp;
        ms->elements--;
        return wt;
}

//OLD $   /* removes a matrix from a matrix stack */
//OLD $   MATRIX_WHAT_t OVRLIBAPI matrix_pop3x3(matrix_stack_t* ms, matrix3x3_t* A)
//OLD $   {
//OLD $           matrix_stack_node_t* tmp, *last =0;
//OLD $           MATRIX_WHAT_t wt;
//OLD $
//OLD $           if ( ms==0 ) return MATRIX_INVALID;
//OLD $           tmp = ms->first;
//OLD $           if ( tmp==0 ) return MATRIX_INVALID;
//OLD $           while ( tmp->next!=0 ) {
//OLD $                 last = tmp;
//OLD $                 tmp = tmp->next;
//OLD $           }
//OLD $           if ( last ) {
//OLD $                 last->next = 0;
//OLD $                 wt = tmp->what;
//OLD $                 *A = tmp->matrix3x3;
//OLD $                 delete tmp;
//OLD $                 ms->elements--;
//OLD $                 return wt;
//OLD $           } else {
//OLD $                 ms->first = 0;
//OLD $                 wt = tmp->what;
//OLD $                 *A = tmp->matrix3x3;
//OLD $                 delete tmp;
//OLD $                 ms->elements--;
//OLD $                 return wt;
//OLD $           }
//OLD $   }

/* removes a matrix from a matrix stack */
MATRIX_WHAT_t OVRLIBAPI matrix_pop4x4(matrix_stack_t* ms, matrix4x4_t* A)
{
        matrix_stack_node_t* tmp;
        MATRIX_WHAT_t wt;

        if ( ms==0 ) return MATRIX_INVALID;
        tmp = ms->first;
        if ( tmp==0 ) return MATRIX_INVALID;
        ms->first = tmp->next;
        if ( tmp->next ) tmp->next->prev = 0;
        wt = tmp->what;
        *A = tmp->matrix4x4;
        delete tmp;
        ms->elements--;
        return wt;
}

//OLD $   MATRIX_WHAT_t OVRLIBAPI matrix_pop4x4(matrix_stack_t* ms, matrix4x4_t* A)
//OLD $   {
//OLD $           matrix_stack_node_t* tmp, *last =0;
//OLD $           MATRIX_WHAT_t wt;
//OLD $
//OLD $           if ( ms==0 ) return MATRIX_INVALID;
//OLD $           tmp = ms->first;
//OLD $           if ( tmp==0 ) return MATRIX_INVALID;
//OLD $           while ( tmp->next!=0 ) {
//OLD $                 last = tmp;
//OLD $                 tmp = tmp->next;
//OLD $           }
//OLD $           if ( last ) {
//OLD $                 last->next = 0;
//OLD $                 wt = tmp->what;
//OLD $                 *A = tmp->matrix4x4;
//OLD $                 delete tmp;
//OLD $                 ms->elements--;
//OLD $                 return wt;
//OLD $           } else {
//OLD $                 ms->first = 0;
//OLD $                 wt = tmp->what;
//OLD $                 *A = tmp->matrix4x4;
//OLD $                 delete tmp;
//OLD $                 ms->elements--;
//OLD $                 return wt;
//OLD $           }
//OLD $   }

/* copy matrix stack */
static void put_on_top(matrix_stack_t* ms, const matrix_stack_node_t& mn)
{
        matrix_stack_node_t *tmp, *tmp1;

        tmp = ms->first;
        if ( tmp==0 ) {
             tmp = new matrix_stack_node_t;
             memset(tmp, 0, sizeof(*tmp));
             *tmp = mn;
             ms->first = tmp;
             return;
        }
        while ( tmp->next!=0 ) tmp = tmp->next;
        tmp1 = new matrix_stack_node_t;
        *tmp1 = mn;
        tmp->next = tmp1;
        tmp1->prev = tmp;
        ms->elements++;
}

int OVRLIBAPI matrix_copy_stack(matrix_stack_t* ms, const matrix_stack_t* ms1)
{
        matrix_stack_node_t* tmp;

        if ( ms==0 ) return 1;
        tmp = ms1->first;
        if ( tmp==0 ) return 0;
        while ( tmp->next!=0 ) {
              put_on_top(ms, *tmp);
              tmp = tmp->next;
        }
        return 0;
}

/** very tweaky way to do it, `cause I'm using linked lists for storing
    stack nodes to the stack... but here i add ability to retrieve a
    pointer, but i CAN't return actual pointer to matrix_stack_node_t
    struct... so i calculate index from the very top where the tail is...
    that means i actually calculate how many items there are in the stack...

    modifying stack in that way is far too slow way.... maybe next time i'll
    do it through pointers... that would be a better way...

    >>>>>>>>>>>>>>>>>>    did it right way... through pointers
*/
MATRIXSP_t OVRLIBAPI matrix_get_stack_pointer(matrix_stack_t* ms)
{
        if ( ms==0 ) return 0;
        return (MATRIXSP_t)ms->first;
}

/* pushes a matrix on a matrix stack, doesn't modify stack pointer */
int OVRLIBAPI matrix_push3x3_to(matrix_stack_t* ms, const matrix3x3_t& m, MATRIX_WHAT_t w, MATRIXSP_t sp)
{
        if ( ms==0 ) return 1;
        if ( sp==0 ) return 1;
        ((matrix_stack_node_t*)sp)->what = w;
        ((matrix_stack_node_t*)sp)->matrix3x3 = m;
        return 0;
}

int OVRLIBAPI matrix_push4x4_to(matrix_stack_t* ms, const matrix4x4_t& m, MATRIX_WHAT_t w, MATRIXSP_t sp)
{
        if ( ms==0 ) return 1;
        if ( sp==0 ) return 1;
        ((matrix_stack_node_t*)sp)->what = w;
        ((matrix_stack_node_t*)sp)->matrix4x4 = m;
        return 0;
}

/* pops a matrix from a matrix stack, doesn't modify stack pointer */
MATRIX_WHAT_t OVRLIBAPI matrix_pop3x3_from(matrix_stack_t* ms, matrix3x3_t* m, MATRIXSP_t sp)
{
        if ( ms==0 ) return MATRIX_INVALID;
        if ( sp==0 ) return MATRIX_INVALID;
        *m = ((matrix_stack_node_t*)sp)->matrix3x3;
        return ((matrix_stack_node_t*)sp)->what;
}

MATRIX_WHAT_t OVRLIBAPI matrix_pop4x4_from(matrix_stack_t* ms, matrix4x4_t* m, MATRIXSP_t sp)
{
        if ( ms==0 ) return MATRIX_INVALID;
        if ( sp==0 ) return MATRIX_INVALID;
        *m = ((matrix_stack_node_t*)sp)->matrix4x4;
        return ((matrix_stack_node_t*)sp)->what;
}


matrix_stack_t* OVRLIBAPI matrix_dublicate_stack(const matrix_stack_t* ms1)
{
        matrix_stack_t* ms;
        matrix_stack_node_t *tmp;

        if ( ms1==0 ) return 0;
        tmp = ms1->first;
        ms = new matrix_stack_t;
        if ( ms==0 ) return 0;
        memset(ms, 0, sizeof(ms));
        if ( tmp==0 ) return ms;
        while ( tmp->next!=0 ) {
              put_on_top(ms, *tmp);
              tmp = tmp->next;
        }
        return ms;
}

}