#include "common/all.h"
#include "system/ovrlsystem.h"
#include "xfactory/xflight.h"
#include "iosystem/fileiodev.h"
#include "common/pattern.h"

namespace openvrl {

/******************************************************************************
 * CxfLightList class
 *****************************************************************************/
CxfLightList::CxfLightList(CxFactory* xf)
	:CxFactoryListTemplate<CxfLight, CxfLightList>(xf)
{
}

CxfLightList::~CxfLightList()
{
}

CxfLight* CxfLightList::create(const CString&	_name,
		LIGHT_TYPE	_type,
		const C3DPoint&	_position, const C3DVector& _direction,
		DRGB_t	_ambient,	DRGB_t	_diffuse,
		DRGB_t	_specular,	
		real	_cutoff,	real	_falloff,
		real	_theta,	real	_phi,
		real	*_attenuation, ulong num)
{
	CxfLight *tmp = create(_name);
	tmp->create(_name, _type, _position, _direction, _ambient, _diffuse, _specular, 
		_cutoff, _falloff, _theta, _phi,
		_attenuation, num);
	return tmp;
}

CxfLight* CxfLightList::create(const TPL_LIGHT& m)
{
	CxfLight *tmp = create(m.name);
	tmp->create(m);
	return tmp;
}

int CxfLightList::load_library(const CString& path, const CString& pattern, DWORD flags)
{
	CFileIOD f(0);
	CTPLLib	tpl(&f, "Test TPL file", 1, 1);
//	CLog log("load_library", "material.log");
	int rc;

	if ( tpl.open(path.c_str(), IOD_RDWR) )
	{
			MessageBox(0, "couldnt open template...", "error", MB_OK);
//			log<<"couldnt open template..."<<"\n";
	}

	rc = load_library(&tpl, pattern, flags);

	tpl.close();
	return rc;
}

int CxfLightList::load_library(CTPLLib* tpl, const CString& pattern, DWORD flags)
{
	ulong i;
	for ( i=0;i<tpl->lights();i++ )
	if ( CPattern(pattern) == tpl->light(i)->name ) 
		create(*tpl->light(i));
	
	return 0;
}

int CxfLightList::save_library(const CString& path)
{
	return 1;
}
int CxfLightList::save_library(CTPLLib* tpl)
{
	return 1;
}


/******************************************************************************
 * CxfLight class
 *****************************************************************************/
CxfLight::CxfLight(CxfLightList* xfl)
	: CxFactoryTemplate<CxfLightList,CxfLight>(xfl)
{
	OVRL_memset(maps, 0, sizeof(maps));
	m_hLight = 0;
	m_locked_Light = 0;
}

CxfLight::~CxfLight()
{
}

int CxfLight::create()
{
	return 1;
}

int CxfLight::create(const TPL_LIGHT& m)
{
	name() = m.name;
	ambient.r =  m.ambient.red;	ambient.g =  m.ambient.green;	ambient.b =  m.ambient.blue;	ambient.a =  m.ambient.alpha;	
	diffuse.r = m.diffuse.red;	diffuse.g = m.diffuse.green;	diffuse.b = m.diffuse.blue;	diffuse.a = m.diffuse.alpha;	
	specular.r = m.specular.red;	specular.g = m.specular.green;	specular.b = m.specular.blue;	specular.a = m.specular.alpha;	
	cut_off=m.cut_off;
	fall_off=m.fall_off;
	phi=m.phi;
	theta=m.theta;
	type = (LIGHT_TYPE)m.style;
	memcpy(attenuation, m.attenuation, sizeof(attenuation));
	return 0;
}

int CxfLight::create(const CString&	_name,
		LIGHT_TYPE	_type,
		const C3DPoint&	_position, const C3DVector& _direction,
		DRGB_t	_ambient,	DRGB_t	_diffuse,
		DRGB_t	_specular,	
		real	_cutoff,	real	_falloff,
		real	_theta,	real	_phi,
		real	*_attenuation, ulong num)
{
	name() = _name;
	position = _position;
	direction = _direction;
	ambient =  _ambient;	
	diffuse = _diffuse;	
	specular = _specular;	
	cut_off=_cutoff;
	fall_off=_falloff;
	phi=_phi;
	theta=_theta;
	type = _type;
	if ( attenuation && num<=sizeof(attenuation) )
		memcpy(attenuation, _attenuation, num);	
	return 0;
}

CxfTexture* CxfLight::set_map(LIGHTMAP_TYPE map, CxfTexture* tx)
{
	const ulong i = (ulong)map;
	CxfTexture* tmp;

	if ( i>=OVRL_LIGHT_MAX_MAPS ) return 0;
	tmp = maps[i];
	maps[i] = tx;
	if ( tmp ) tmp->unuse();
	if ( tx ) tx->use();
	return tmp;
}

CxfTexture* CxfLight::unset_map(LIGHTMAP_TYPE map)
{
	const ulong i = (ulong)map;
	CxfTexture* tmp;

	if ( i>=OVRL_LIGHT_MAX_MAPS ) return 0;
	tmp = maps[i];
	maps[i] = 0;
	if ( tmp ) tmp->unuse();
	return tmp;
}

int CxfLight::lock()
{
	return 0;
}

int CxfLight::unlock()
{
	return 0;
}

int CxfLight::free()
{
	ulong i;
	for ( i=0;i<OVRL_LIGHT_MAX_MAPS;i++ ) unset_map((LIGHTMAP_TYPE)i);
	return 0;
}
void CxfLight::release()
{
	delete this;
}

}