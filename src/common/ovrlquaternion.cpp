#include <math.h>
#include "common/quaternion.h"
#include "common/math.h"

namespace openvrl {

const quaternion_t                QUATZERO = {0,0,0,0};
const quaternion_t                QUATUNITX = {1,0,0,0};
const quaternion_t                QUATUNITY = {0,1,0,0};
const quaternion_t                QUATUNITZ = {0,0,1,0};
const quaternion_t                QUATUNITXYZ = {1,1,1,0};
const quaternion_t                QUATNEGUNITX = {-1,0,0,0};
const quaternion_t                QUATNEGUNITY = {0,-1,0,0};
const quaternion_t                QUATNEGUNITZ = {0,0,-1,0};
const quaternion_t                QUATNEGUNIT = {-1,-1,-1,-1};
const quaternion_t                QUATZEROUNITQ = {0,0,0,1};
const quaternion_t                QUATUNITXUNITQ = {1,0,0,1};
const quaternion_t                QUATUNITYUNITQ = {0,1,0,1};
const quaternion_t                QUATUNITZUNITQ = {0,0,1,1};
const quaternion_t                QUATUNITXYZQ = {1,1,1,1};
const quaternion_t                QUATNEGUNITXUNITQ = {-1,0,0,1};
const quaternion_t                QUATNEGUNITYUNITQ = {0,-1,0,1};
const quaternion_t                QUATNEGUNITZUNITQ = {0,0,-1, 1};

void OVRLIBAPI quaternion_set(quaternion_t *q, real x, real y, real z, real r)
{
        real s;
        if ( q==0 ) return;
        q->q = cos(r/2.0);
        s = sin(r/2.0) / sqrt(x*x+y*y+z*z);
        q->x = x * s;
        q->y = y * s;
        q->z = z * s;
        return ;
}

quaternion_t OVRLIBAPI quaternion_cross_product(const quaternion_t& a, const quaternion_t& b)
{
        quaternion_t tmp;
        vector3d_t  va;
        vector3d_t  vb;
        vector3d_t  vc;

        va.x = a.x;
        va.y = a.y;
        va.z = a.z;
        vb.x = b.x;
        vb.y = b.y;
        vb.z = b.z;
        vc = cross_product(va, vb);

        tmp.x = vc.x;
        tmp.y = vc.y;
        tmp.z = vc.z;
        tmp.q = (a.q + b.q) / 2.0;      /* ??? */

        return tmp;
}

//real OVRLIBAPI quaternion_dot_product(const quaternion_t&, const quaternion_t&);
quaternion_t OVRLIBAPI mul_quaternion(const quaternion_t& q, real k)
{
        quaternion_t tmp;

        tmp.x = q.x*k;
        tmp.y = q.y*k;
        tmp.z = q.z*k;
        tmp.q = q.q*k;

        return tmp;
}

quaternion_t OVRLIBAPI div_quaternion(const quaternion_t& q, real k)
{
        quaternion_t tmp;

        tmp.x = q.x/k;
        tmp.y = q.y/k;
        tmp.z = q.z/k;
        tmp.q = q.q/k;

        return tmp;
}

quaternion_t OVRLIBAPI mul_quaternions(const quaternion_t& a, const quaternion_t& b)
{
        quaternion_t tmp;

        tmp.x = a.q*b.x + a.x*b.q + a.y*b.z - a.z*b.y;
        tmp.y = a.q*b.y - a.x*b.z + a.y*b.q + a.z*b.x;
        tmp.z = a.q*b.z + a.x*b.y - a.y*b.x + a.z*b.q;
        tmp.q = a.q*b.q - a.x*b.x - a.y*b.y - a.z*b.z;

        return tmp;
}

quaternion_t OVRLIBAPI add_quaternions(const quaternion_t& a, const quaternion_t& b)
{
        quaternion_t tmp;

        tmp.x = a.x*b.x;
        tmp.y = a.y*b.y;
        tmp.z = a.z*b.z;
        tmp.q = a.q*b.q;

        return tmp;
}

quaternion_t OVRLIBAPI sub_quaternions(const quaternion_t& a, const quaternion_t& b)
{
        quaternion_t tmp;

        tmp.x = a.x-b.x;
        tmp.y = a.y-b.y;
        tmp.z = a.z-b.z;
        tmp.q = a.q-b.q;

        return tmp;
}

quaternion_t OVRLIBAPI neg_quaternion(const quaternion_t& q)
{
        quaternion_t tmp;

        tmp.x = -q.x;
        tmp.y = -q.y;
        tmp.z = -q.z;
        tmp.q = -q.q;

        return tmp;
}

}