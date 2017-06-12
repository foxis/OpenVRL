/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xfmaterial.h,v $
 * $Implementation: /src/xfactory/xfmaterial.cc $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:07 $
 * $Description: Material class $
 *
 * $Log: xfmaterial.h,v $
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



#if !defined(__XFMATERIAL_HPP)
#define __XFMATERIAL_HPP

#include "common/all.h"
//#include "system/ovrlsystem.h"
#include "xfactory/xftemplate.h"
#include "xfactory/xfactory.h"
#include "xfactory/xftexture.h"
#include "tpllib/tpl.hpp"

namespace openvrl {

#define OVRL_MATERIAL_MAX_MAPS           TPL_MATERIAL_MAX_MAPS

class OVRLIBAPI CxFactory;
class OVRLIBAPI CxfMaterial;

/**
 * CxfMaterialList class
 */
class OVRLIBAPI CxfMaterialList : public CxFactoryListTemplate<CxfMaterial, CxfMaterialList>
{
public:
	virtual CxfMaterial* create(const CString& name)
	{
		CxfMaterial* tmp = find(name);
		return (tmp)?(tmp):(CxFactoryListTemplate<CxfMaterial, CxfMaterialList>::create(name));
	}
	virtual CxfMaterial* create(const CString&	_name,
		DRGB_t	_ambient,	DRGB_t	_diffuse,
		DRGB_t	_specular,	DRGB_t	_filter,
		DRGB_t	_refraction,	real	_shiness,
		real	_strength,	real	_self_illumination,
		real	_opacity,	real	_bounce_coeficient,
		real	_static_friction,	real	_sliding_friction/*,
		const HANDLER& _maps*/);
	virtual CxfMaterial* create(const TPL_MAT& m);


	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int save_library(const CString& path);
	virtual int save_library(CTPLLib* tpl);

	/** 
	 *
	 */
	CxfMaterialList(CxFactory* xf);
	virtual ~CxfMaterialList();
};

/**
 * CxfMaterial class
 */
class OVRLIBAPI CxfMaterial : public CxFactoryTemplate<CxfMaterialList, CxfMaterial>
{
protected:
	HANDLER	 m_hMaterial;
	BYTE		*m_locked_Material;
	ulong		m_lock_count;

public:
	DRGB_t	ambient;
	DRGB_t	diffuse;
	DRGB_t	specular;
	DRGB_t	filter;
	DRGB_t	refraction;
	real	shiness;
	real	strength;
	real	self_illumination;
	real	opacity;
	real	bounce_coeficient;
	real	static_friction;
	real	sliding_friction;
	CxfTexture*	maps[OVRL_MATERIAL_MAX_MAPS];


	/**
	 *
	 */
	CxfTexture* set_map(MATERIALMAP_TYPE map, CxfTexture* tx);
	CxfTexture* unset_map(MATERIALMAP_TYPE map);
	virtual int lock();
	virtual int unlock();
	virtual int create();
	virtual int free();
	virtual void release();

	bool locked() const { return m_locked_Material!=0; }
	bool created() const { return m_hMaterial!=0; }
	bool local_created() const { return true; }

	int create(const TPL_MAT& m);
	int create(const CString&	_name,
		DRGB_t	_ambient,	DRGB_t	_diffuse,
		DRGB_t	_specular,	DRGB_t	_filter,
		DRGB_t	_refraction,	real	_shiness,
		real	_strength,	real	_self_illumination,
		real	_opacity,	real	_bounce_coeficient,
		real	_static_friction,	real	_sliding_friction);


	//
	CxfMaterial(CxfMaterialList* xfl);
	virtual ~CxfMaterial();
};

};

#endif /* !defined(__XFMATERIAL_HPP) */
