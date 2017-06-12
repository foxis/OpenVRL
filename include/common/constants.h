/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/constants.h,v $
 * $Implementation: ~/src/ $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:10 $
 * $Description:  $
 *
 * $Log: constants.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:10  foxis
 * sources import
 *
 * Revision 0.3  20010411  :: FoxiE
 *
 */

#if !defined(AFX_CONSTANTS_H__03D20662_A726_11D6_8083_BA9E9ABD05A2__INCLUDED_)
#define AFX_CONSTANTS_H__03D20662_A726_11D6_8083_BA9E9ABD05A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common/types.h"

namespace openvrl {

namespace constants
{

//
// mathematical constants
//
extern OVRLIBAPI real EPSILON;
	
extern OVRLIBAPI real m_pi;
extern OVRLIBAPI real m_2pi;
extern OVRLIBAPI real m_3pi;
extern OVRLIBAPI real m_4pi;
extern OVRLIBAPI real m_1pi;
extern OVRLIBAPI real m_12pi;
extern OVRLIBAPI real m_13pi;
extern OVRLIBAPI real m_14pi;
extern OVRLIBAPI real m_2pi3;
extern OVRLIBAPI real m_3pi2;
extern OVRLIBAPI real m_3pi4;
extern OVRLIBAPI real m_4pi3;
extern OVRLIBAPI real m_rad;	// how many degrees in 1 radian
extern OVRLIBAPI real m_deg;	// how many radians in 1 degree
extern OVRLIBAPI real m_e;
extern OVRLIBAPI real m_ln10;
extern OVRLIBAPI real m_lge;
extern OVRLIBAPI real m_1ln10;
extern OVRLIBAPI real m_1lge;
extern OVRLIBAPI real m_sqrt2;
extern OVRLIBAPI real m_sqrt3;
extern OVRLIBAPI real m_sqrt5;

//
// Physics constants
//
extern OVRLIBAPI real p_G;// gravity constant
extern OVRLIBAPI real p_c; // the speed of light in vacuum
extern OVRLIBAPI real p_u; // magnetic constant
extern OVRLIBAPI real p_e0; // electrical constant
extern OVRLIBAPI real p_K; // Culon's constant
extern OVRLIBAPI real p_h;  // Planc's constant
extern OVRLIBAPI real p_e; // electon's energy
extern OVRLIBAPI real p_me; // steady electon's mass
extern OVRLIBAPI real p_mp;// steady proton's mass
extern OVRLIBAPI real p_mn;// steady neutron's mass

	};

};

#endif // !defined(AFX_CONSTANTS_H__03D20662_A726_11D6_8083_BA9E9ABD05A2__INCLUDED_)
