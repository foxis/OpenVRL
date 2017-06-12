/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xflight.h,v $
 * $Implementation: /src/xfactory/xflight.cc $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:07 $
 * $Description: Light class $
 *
 * $Log: xflight.h,v $
 * Revision 1.2  2005/07/14 12:14:07  foxis
 * no message
 *
 * Revision 1.1.1.1  2005/02/02 15:39:24  foxis
 * sources import
 *
 * Revision 0.1  20020117  20:30:00 FoxiE
 *  :)
 *
 */



#if !defined(__ovrl_XFLIGHT_HPP)
#define __ovrl_XFLIGHT_HPP

#include "common/all.h"
//#include "system/ovrlsystem.h"
#include "xfactory/xftemplate.h"
#include "xfactory/xfactory.h"
#include "xfactory/xftexture.h"
#include "tpllib/tpl.hpp"

namespace openvrl {


#define OVRL_LIGHT_MAX_MAPS           TPL_LIGHT_MAX_MAPS
#define OVRL_LIGHT_MAX_ATTENUATIONS           TPL_LIGHT_MAX_ATTENUATIONS

class OVRLIBAPI CxFactory;
class OVRLIBAPI CxfLight;

/**
 * CxfLightList class
 */
class OVRLIBAPI CxfLightList : public CxFactoryListTemplate<CxfLight, CxfLightList>
{
public:
	virtual CxfLight* create(const CString& name)
	{
		CxfLight* tmp = find(name);
		return (tmp)?(tmp):(CxFactoryListTemplate<CxfLight, CxfLightList>::create(name));
	}
	virtual CxfLight* create(const TPL_LIGHT& l);
	virtual CxfLight* create(const CString&	_name,
		LIGHT_TYPE	_type,
		const C3DPoint&	_position, const C3DVector& direction,
		DRGB_t	_ambient,	DRGB_t	_diffuse,
		DRGB_t	_specular,	
		real	_cutoff,	real	_falloff,
		real	_theta,	real	_phi,
		real	*_attenuation, ulong num=TPL_LIGHT_MAX_ATTENUATIONS);

	CxfLight* create_ambient(const CString& _name,DRGB_t _color)
	{
		return create(_name, LIGHT_AMBIENT, C3DPoint(0,0,0), C3DVector(0,0,0), _color, _color, _color,
		0,0,0,0,0,0);
	}
	CxfLight* create_point(const CString& _name,
		const C3DPoint&	_pos, 
		DRGB_t _amb, DRGB_t _diff,
		DRGB_t _spec, real _cutoff, real _falloff)
	{
		return create(_name, LIGHT_POINT, _pos, C3DVector(0,0,0), _amb, _diff, _spec,
		_cutoff,_falloff,0,0,0,0);
	}
	CxfLight* create_directional(const CString& _name,
		const C3DPoint&	_pos, const C3DVector& _dir,
		DRGB_t _amb, DRGB_t _diff,
		DRGB_t _spec, real _cutoff, real _falloff)
	{
		return create(_name, LIGHT_DIRECTIONAL, _pos, _dir, _amb, _diff, _spec,
		_cutoff,_falloff,0,0,0,0);
	}
	CxfLight* create_spot(const CString& _name,
		const C3DPoint&	_pos, const C3DVector& _dir,
		DRGB_t _amb, DRGB_t _diff,
		DRGB_t _spec, real _cutoff, real _falloff,
		real _phi, real _theta)
	{
		return create(_name, LIGHT_SPOT, _pos, _dir, _amb, _diff, _spec,
		_cutoff,_falloff,_phi,_theta,0,0);
	}



	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int save_library(const CString& path);
	virtual int save_library(CTPLLib* tpl);

	/** 
	 *
	 */
	CxfLightList(CxFactory* xf);
	virtual ~CxfLightList();
};

/**
 * CxfLight class
 */
class OVRLIBAPI CxfLight : public CxFactoryTemplate<CxfLightList, CxfLight>
{
protected:
	HANDLER	 m_hLight;
	BYTE		*m_locked_Light;
	ulong		m_lock_count;

public:
	LIGHT_TYPE 	type;
	C3DPoint	position;
	C3DVector	direction;
	DRGB_t 	ambient;
	DRGB_t	diffuse;
	DRGB_t	specular;

	real	cut_off;
	real	fall_off;
	real	theta;         /* spot light angles  */
	real	phi;           /*  */

	real	attenuation[OVRL_LIGHT_MAX_ATTENUATIONS];
	CxfTexture*	maps[OVRL_LIGHT_MAX_MAPS];


	/**
	 *
	 */
	virtual CxfTexture* set_map(LIGHTMAP_TYPE map, CxfTexture* tx);
	virtual CxfTexture* unset_map(LIGHTMAP_TYPE map);
	virtual int lock();
	virtual int unlock();
	virtual int create();
	virtual int free();
	virtual void release();

	bool locked() const { return m_locked_Light!=0; }
	bool created() const { return m_hLight!=0; }
	bool local_created() const { return true; }

	virtual int create(const TPL_LIGHT& l);
	virtual int create(const CString&	_name,
		LIGHT_TYPE	_type,
		const C3DPoint&	_pos, const C3DVector& _dir,
		DRGB_t	_ambient,	DRGB_t	_diffuse,
		DRGB_t	_specular,	
		real	_cutoff,	real	_falloff,
		real	_theta,	real	_phi,
		real	*_attenuation, ulong num=OVRL_LIGHT_MAX_ATTENUATIONS);

	int create_ambient(const CString& _name,DRGB_t _color)
	{
		return create(_name, LIGHT_AMBIENT, C3DPoint(0,0,0), C3DVector(0,0,0), _color, _color, _color,
		0,0,0,0,0,0);
	}
	int create_point(const CString& _name,
		const C3DPoint&	_pos, 
		DRGB_t _amb, DRGB_t _diff,
		DRGB_t _spec, real _cutoff, real _falloff)
	{
		return create(_name, LIGHT_POINT, _pos, C3DVector(0,0,0), _amb, _diff, _spec,
		_cutoff,_falloff,0,0,0,0);
	}
	int create_directional(const CString& _name,
		const C3DPoint&	_pos, const C3DVector& _dir,
		DRGB_t _amb, DRGB_t _diff,
		DRGB_t _spec, real _cutoff, real _falloff)
	{
		return create(_name, LIGHT_DIRECTIONAL, _pos, _dir, _amb, _diff, _spec,
		_cutoff,_falloff,0,0,0,0);
	}
	int create_spot(const CString& _name,
		const C3DPoint&	_pos, const C3DVector& _dir,
		DRGB_t _amb, DRGB_t _diff,
		DRGB_t _spec, real _cutoff, real _falloff,
		real _phi, real _theta)
	{
		return create(_name, LIGHT_SPOT, _pos, _dir, _amb, _diff, _spec,
		_cutoff,_falloff,_phi,_theta,0,0);
	}

	//
	CxfLight(CxfLightList* xfl);
	virtual ~CxfLight();
};

};

#endif /* !defined(__ovrl_XFLIGHT_HPP) */
