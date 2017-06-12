/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/matrices.h,v $
 * $Implementation: ~/src/math/matrices.cc $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:59:56 $
 * $Description: Matrices math. Matrix stack manager $
 *
 * $Log: matrices.h,v $
 * Revision 1.2  2005/07/14 12:59:56  foxis
 * demo bugfix
 * sln bugfix
 *
 * Revision 1.1.1.1  2005/02/02 15:39:11  foxis
 * sources import
 *
 * Revision 0.2  20010814  09:10:04 FoxiE
 * Suradau klaida matricu stecko push/pop fun-jose.
 * Dabar nebekabinasi kai steckas beveik tuscias...
 *
 * Revision 0.1  20010814  09:09:04 FoxiE
 * Pradejau rasyti logus :)
 *
 */



#if !defined(__ovrl_OVRLMATRICES_HPP)
#define __ovrl_OVRLMATRICES_HPP

#include "common/constants.h"
#include "common/quaternion.h"
#include "common/exception.h"

namespace openvrl {

/**
 * Description of a matrix stack node type.
 *
 *  MATRIX_INVALID              - invalid matrix   (4x4 matrices)
 *  MATRIX_GENERAL              - general matrix, undetermined
 *  MATRIX_IDENTITY             - identity matrix
 *  MATRIX_ROTATION             - rotation matrix
 *  MATRIX_TRANSLATE            - translate matrix
 *  MATRIX_SCALE                - scale matrix
 *  MATRIX_NO_ROT               - a matrix that does not contain rotation part
 *  MATRIX_ORTHO                - orthogonal matrix [?]
 *  MATRIX_PERSP                - perspective transform matrix
 *  MATRIX_3X3GENERAL           - general matrix, undetermined (3x3 matrices)
 *  MATRIX_3X3IDENTITY          - identity matrix
 *  MATRIX_3X3ROTATION          - rotation matrix
 *  MATRIX_3X3TRANSLATE         - translate matrix
 *  MATRIX_3X3SCALE             - scale matrix
 *  MATRIX_3X3NO_ROT            - a matrix that does not contain rotation part
 *  MATRIX_3X3ORTHO             - orthogonal matrix [?]
 *  MATRIX_3X3PERSP             - perspective transform matrix
 *  MATRIX_TEXTURE_GENERAL      - texture general matrix, undetermined (usually 3x3 matrices)
 *  MATRIX_TEXTURE_IDENTITY     - texture identity matrix
 *  MATRIX_TEXTURE_ROTATION     - texture rotation matrix
 *  MATRIX_TEXTURE_TRANSLATE    - texture translate matrix
 *  MATRIX_TEXTURE_SCALE        - texture scale matrix
 *  MATRIX_TEXTURE_NO_ROT       - texture a matrix that does not contain rotation part
 *  MATRIX_TEXTURE_ORTHO        - texture orthogonal matrix [?]
 */
enum MATRIX_WHAT_enum
{
        MATRIX_INVALID   = -1,
        MATRIX_GENERAL   = 0,
        MATRIX_IDENTITY  = 1,
        MATRIX_ROTATION  = 2,
        MATRIX_TRANSLATE = 3,
        MATRIX_SCALE     = 4,
        MATRIX_NO_ROT    = 5,
        OVRL_MATRIX_ORTHO     = 6,
        OVRL_MATRIX_PERSP     = 7,
        OVRL_MATRIX_3X3GENERAL   = 200,
        OVRL_MATRIX_3X3IDENTITY  = 201,
        OVRL_MATRIX_3X3ROTATION  = 202,
        OVRL_MATRIX_3X3TRANSLATE = 203,
        OVRL_MATRIX_3X3SCALE     = 204,
        OVRL_MATRIX_3X3NO_ROT    = 205,
        OVRL_MATRIX_3X3ORTHO     = 206,
        OVRL_MATRIX_3X3PERSP     = 207,
        OVRL_MATRIX_TEXTURE_GENERAL    = 400,
        OVRL_MATRIX_TEXTURE_IDENTITY   = 401,
        OVRL_MATRIX_TEXTURE_ROTATION   = 402,
        OVRL_MATRIX_TEXTURE_TRANSLATE  = 403,
        OVRL_MATRIX_TEXTURE_SCALE      = 404,
        OVRL_MATRIX_TEXTURE_NO_ROT     = 405,
        OVRL_MATRIX_TEXTURE_ORTHO      = 406,
        OVRL_MATRIX_FORCEDWORD         = 0x7FFFFFFF
};

typedef MATRIX_WHAT_enum MATRIX_WHAT_t;

/**
 *
 */
union OVRLIBAPI matrix3x3_union
{
  real data3x3[3][3];
  real data9[9];
  struct {
         real a1, a2, a3, a4, a5, a6, a7, a8,a9;
  } data;
};

/**
 *
 */
union OVRLIBAPI matrix4x4_union
{
    real data16[16];
    real data4x4[4][4];
    struct {
       real a1, a2, a3, a4,   a5, a6, a7, a8,
              a9, a10,a11,a12,  a13,a14,a15,a16;
    } data;
};

/**
 *
 */
struct OVRLIBAPI matrix_stack_node_struct
{
        MATRIX_WHAT_t what;
        union {
              union matrix4x4_union matrix4x4;
              union matrix3x3_union matrix3x3;
        };

        struct matrix_stack_node_struct* next;
        struct matrix_stack_node_struct* prev;
};

typedef struct matrix_stack_node_struct* MATRIXSP_t;

/**
 *
 */
struct OVRLIBAPI matrix_stack_struct
{
        ulong  elements;
        struct matrix_stack_node_struct* first;
};

typedef union matrix3x3_union matrix3x3_t;
typedef union matrix4x4_union matrix4x4_t;
typedef struct matrix_stack_node_struct matrix_stack_node_t;
typedef struct matrix_stack_struct matrix_stack_t;

extern OVRLIBAPI const matrix4x4_t MATUNIT;
extern OVRLIBAPI const matrix3x3_t MATUNIT3X3;


#if defined(__cplusplus)
extern "C" {
#endif /* ifdef __cplusplus */

/*************************************************
 *  Matrix math
 */
/* Initializes the 4x4 matrix */
void OVRLIBAPI
matrix_set(matrix4x4_t* dest, real, real, real, real,
        real, real, real, real,
        real, real, real, real,
        real, real, real, real);

void OVRLIBAPI matrix_set_identity(matrix4x4_t* A);
void OVRLIBAPI matrix_set_rotate(matrix4x4_t* A, const vector3d_t& v);
void OVRLIBAPI matrix_set_from_quaternion(matrix4x4_t* A, const quaternion_t& q);
void OVRLIBAPI matrix_set_translate(matrix4x4_t* A, const vector3d_t& v);
void OVRLIBAPI matrix_set_scale(matrix4x4_t* A, const vector3d_t& v);
matrix4x4_t OVRLIBAPI matrix_identity();
matrix4x4_t OVRLIBAPI matrix_rotate(const vector3d_t& v);
matrix4x4_t OVRLIBAPI matrix_from_quaternion(const quaternion_t& q);
matrix4x4_t OVRLIBAPI matrix_translate(const vector3d_t& v);
matrix4x4_t OVRLIBAPI matrix_scale(const vector3d_t& v);
void OVRLIBAPI matrix_copy(matrix4x4_t *dest, const matrix4x4_t& source);
matrix4x4_t OVRLIBAPI matrix_add(const matrix4x4_t& first, const matrix4x4_t& second);
matrix4x4_t OVRLIBAPI matrix_sub(const matrix4x4_t& first, const matrix4x4_t& second);
matrix4x4_t OVRLIBAPI matrix_mul_by(const matrix4x4_t&, real);
matrix4x4_t OVRLIBAPI matrix_div_by(const matrix4x4_t&, real);
matrix4x4_t OVRLIBAPI matrix_mul(const matrix4x4_t&, const matrix4x4_t&);
vector3d_t OVRLIBAPI matrix_mul_vector(const matrix4x4_t&, const vector3d_t&);
real OVRLIBAPI matrix_determinant(const matrix4x4_t&);
matrix4x4_t OVRLIBAPI matrix_invert(const matrix4x4_t&);
void OVRLIBAPI matrix_mul_by_to(matrix4x4_t* result, const matrix4x4_t&, real);
void OVRLIBAPI matrix_div_by_to(matrix4x4_t* result, const matrix4x4_t&, real);
void OVRLIBAPI matrix_mul_to(matrix4x4_t* result, const matrix4x4_t&, const matrix4x4_t&);



/******************************************************************************
 *  Matrix stack manager's functions.
 *  It implements a LIFO type of stack of matrices used to manipulate
 *  objects. it's much a better way to transform objects through matrices
 *  than through several matrices like Rotation, Scale and Translate, like
 *  I did in previous versions.
 *  But it's kindda challenging to manipulate objects, because you have to
 *  track what matrices where pushed and what where pop'ed first...
 */
/** pushes a matrix on a matrix stack */
int OVRLIBAPI matrix_push3x3(matrix_stack_t* ms, const matrix3x3_t& m, MATRIX_WHAT_t w);
int OVRLIBAPI matrix_push4x4(matrix_stack_t* ms, const matrix4x4_t& m, MATRIX_WHAT_t w);

/** pops a matrix from a matrix stack */
MATRIX_WHAT_t OVRLIBAPI matrix_pop3x3(matrix_stack_t* ms, matrix3x3_t* m);
MATRIX_WHAT_t OVRLIBAPI matrix_pop4x4(matrix_stack_t* ms, matrix4x4_t* m);

/** returns a matrix node of the top of the stack */
MATRIXSP_t OVRLIBAPI matrix_get_stack_pointer(matrix_stack_t* ms);

/* pushes a matrix on a matrix stack, doesn't modify stack pointer */
int OVRLIBAPI matrix_push3x3_to(matrix_stack_t* ms, const matrix3x3_t& m, MATRIX_WHAT_t w, MATRIXSP_t sp);
int OVRLIBAPI matrix_push4x4_to(matrix_stack_t* ms, const matrix4x4_t& m, MATRIX_WHAT_t w, MATRIXSP_t sp);

/* pops a matrix from a matrix stack, doesn't modify stack pointer */
MATRIX_WHAT_t OVRLIBAPI matrix_pop3x3_from(matrix_stack_t* ms, matrix3x3_t* m, MATRIXSP_t sp);
MATRIX_WHAT_t OVRLIBAPI matrix_pop4x4_from(matrix_stack_t* ms, matrix4x4_t* m, MATRIXSP_t sp);

/* copy matrix stack */
int OVRLIBAPI matrix_copy_stack(matrix_stack_t* ms, const matrix_stack_t* ms1);
matrix_stack_t* OVRLIBAPI matrix_dublicate_stack(const matrix_stack_t* ms);

#if defined(__cplusplus)
};
#endif /* ifdef __cplusplus */

/**
 *  If we're compiling in C++, and it's obvious it is :-)
 *  Then we can define several overloaded operators,
 *  like "*", "==", "/", etc...
 */
#if defined(__cplusplus)


#endif /* if defined(__cplusplus) */

};

#endif /* defined(__ovrl_OVRLMATRICES_HPP) */
