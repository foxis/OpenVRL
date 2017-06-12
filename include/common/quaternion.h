/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/quaternion.h,v $
 * $Implementation: ~/src/math/quatern.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:12 $
 * $Description: quaternion math $
 *
 * $Log: quaternion.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:12  foxis
 * sources import
 *
 * Revision 0.1  20010913  14:01:17 FoxiE
 * y
 *
 */



#if !defined(__ovrl_OVRLQUATERNION_HPP)
#define __ovrl_OVRLQUATERNION_HPP

#include "common/types.h"
#include "common/constants.h"
#include "common/exception.h"

namespace openvrl {

/**
 *
 */
struct OVRLIBAPI quaternion_struct
{
        real x,y,z,q;
};
typedef struct quaternion_struct         quaternion_t;


#if defined(__cplusplus)
extern "C" {
#endif /* ifdef __cplusplus */

extern OVRLIBAPI const quaternion_t                QUATZERO;
extern OVRLIBAPI const quaternion_t                QUATUNITX;
extern OVRLIBAPI const quaternion_t                QUATUNITY;
extern OVRLIBAPI const quaternion_t                QUATUNITZ;
extern OVRLIBAPI const quaternion_t                QUATUNITXYZ;
extern OVRLIBAPI const quaternion_t                QUATNEGUNITX;
extern OVRLIBAPI const quaternion_t                QUATNEGUNITY;
extern OVRLIBAPI const quaternion_t                QUATNEGUNITZ;
extern OVRLIBAPI const quaternion_t                QUATNEGUNIT;
extern OVRLIBAPI const quaternion_t                QUATZEROUNITQ;
extern OVRLIBAPI const quaternion_t                QUATUNITXUNITQ;
extern OVRLIBAPI const quaternion_t                QUATUNITYUNITQ;
extern OVRLIBAPI const quaternion_t                QUATUNITZUNITQ;
extern OVRLIBAPI const quaternion_t                QUATUNITXYZQ;
extern OVRLIBAPI const quaternion_t                QUATNEGUNITXUNITQ;
extern OVRLIBAPI const quaternion_t                QUATNEGUNITYUNITQ;
extern OVRLIBAPI const quaternion_t                QUATNEGUNITZUNITQ;


void OVRLIBAPI quaternion_set(quaternion_t *q, real x, real y, real z, real r);
quaternion_t OVRLIBAPI quaternion_cross_product(const quaternion_t&, const quaternion_t&);
quaternion_t OVRLIBAPI mul_quaternion(const quaternion_t&, real);
quaternion_t OVRLIBAPI div_quaternion(const quaternion_t&, real);
quaternion_t OVRLIBAPI mul_quaternions(const quaternion_t&, const quaternion_t&);
quaternion_t OVRLIBAPI add_quaternions(const quaternion_t&, const quaternion_t&);
quaternion_t OVRLIBAPI sub_quaternions(const quaternion_t&, const quaternion_t&);
quaternion_t OVRLIBAPI neg_quaternion(const quaternion_t&);

#if defined(__cplusplus)
inline real quaternion_dot_product(const quaternion_t& a, const quaternion_t& b) 
{
	return a.x*b.x + a.y*b.y + a.z*b.z + a.q*b.q;
}
#else
#error @todo: C style inlines
#endif /* ifdef __cplusplus */

#if defined(__cplusplus)
};
#endif /* ifdef __cplusplus */

#if defined(__cplusplus)


#endif // if defined(__cplusplus)

};

#endif // if !defined(__ovrl_OVRLQUATERNION_HPP)
