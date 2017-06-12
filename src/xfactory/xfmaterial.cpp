#include "common/all.h"
#include "system/ovrlsystem.h"
#include "xfactory/xfmaterial.h"
#include "iosystem/fileiodev.h"
#include "common/pattern.h"

namespace openvrl {

/******************************************************************************
 * CxfMaterialList class
 *****************************************************************************/
CxfMaterialList::CxfMaterialList(CxFactory* xf)
	:CxFactoryListTemplate<CxfMaterial, CxfMaterialList>(xf)
{
}

CxfMaterialList::~CxfMaterialList()
{
}

CxfMaterial* CxfMaterialList::create(const CString&	_name,
		DRGB_t	_ambient,	DRGB_t	_diffuse,
		DRGB_t	_specular,	DRGB_t	_filter,
		DRGB_t	_refraction,	real	_shiness,
		real	_strength,	real	_self_illumination,
		real	_opacity,	real	_bounce_coeficient,
		real	_static_friction,	real	_sliding_friction/*,
		const OVRL_HANDLER& _maps*/)
{
	CxfMaterial *tmp = create(_name);
	tmp->create(_name, _ambient, _diffuse, _specular, _filter, _refraction,
		_shiness, _strength, _self_illumination, _opacity, _bounce_coeficient,
		_static_friction, _sliding_friction);
	return tmp;
}

CxfMaterial* CxfMaterialList::create(const TPL_MAT& m)
{
	CxfMaterial *tmp = create(m.name);
	tmp->create(m);
	return tmp;
}

int CxfMaterialList::load_library(const CString& path, const CString& pattern, DWORD flags)
{
	CFileIOD f(0);
	CTPLLib	tpl(&f, "Test TPL file", 1, 1);
//	CLog log("load_library", "material.log");

	if ( tpl.open(path.c_str(), IOD_RDWR) )
	{
			MessageBox(0, "couldnt open template...", "error", MB_OK);
//			log<<"couldnt open template..."<<"\n";
	}

	load_library(&tpl, pattern, flags);
	
	tpl.close();
	return 0;
}

int CxfMaterialList::load_library(CTPLLib* tpl, const CString& pattern, DWORD flags)
{
	ulong i;
	for ( i=0;i<tpl->materials();i++ )
	if ( CPattern(pattern) == tpl->material(i)->name ) 
		create(*tpl->material(i));
	
	return 0;
}

int CxfMaterialList::save_library(const CString& path)
{
	return 1;
}
int CxfMaterialList::save_library(CTPLLib* tpl)
{
	return 1;
}


/******************************************************************************
 * CxfMaterial class
 *****************************************************************************/
CxfMaterial::CxfMaterial(CxfMaterialList* xfl)
	: CxFactoryTemplate<CxfMaterialList,CxfMaterial>(xfl)
{
	OVRL_memset(maps, 0, sizeof(maps));
	m_hMaterial = 0;
	m_locked_Material = 0;
}

CxfMaterial::~CxfMaterial()
{
}

int CxfMaterial::create()
{
	return 1;
}

int CxfMaterial::create(const TPL_MAT& m)
{
	name() = m.name;
	ambient.r =  m.ambient.red;	ambient.g =  m.ambient.green;	ambient.b =  m.ambient.blue;	ambient.a =  m.ambient.alpha;	
	diffuse.r = m.diffuse.red;	diffuse.g = m.diffuse.green;	diffuse.b = m.diffuse.blue;	diffuse.a = m.diffuse.alpha;	
	specular.r = m.specular.red;	specular.g = m.specular.green;	specular.b = m.specular.blue;	specular.a = m.specular.alpha;	
	filter.r = m.filter.red;		filter.g = m.filter.green;	filter.b = m.filter.blue;	filter.a = m.filter.alpha;
	refraction.r = m.refraction.red;	refraction.g = m.refraction.green;	refraction.b = m.refraction.blue;	refraction.a = m.refraction.alpha;
	shiness=m.shiness;
	strength=m.strength;
	self_illumination=m.self_illumination;
	opacity=m.opacity;
	bounce_coeficient=m.bounce_coeficient;
	static_friction=m.static_friction;
	sliding_friction=m.sliding_friction;
	return 1;
}

int CxfMaterial::create(const CString&	_name,
		DRGB_t	_ambient,
		DRGB_t	_diffuse,
		DRGB_t	_specular,
		DRGB_t	_filter,
		DRGB_t	_refraction,
		real	_shiness,
		real	_strength,
		real	_self_illumination,
		real	_opacity,
		real	_bounce_coeficient,
		real	_static_friction,
		real	_sliding_friction)
{
	name()=_name;
	ambient=_ambient;
	diffuse=_diffuse;
	specular=_specular;
	filter=_filter;
	refraction=_refraction;
	shiness=_shiness;
	strength=_strength;
	self_illumination=_self_illumination;
	opacity=_opacity;
	bounce_coeficient=_bounce_coeficient;
	static_friction=_static_friction;
	sliding_friction=_sliding_friction;
	return 0;
}

CxfTexture* CxfMaterial::set_map(MATERIALMAP_TYPE map, CxfTexture* tx)
{
	const ulong i = (ulong)map - 1;
	CxfTexture* tmp;

	if ( i>=OVRL_MATERIAL_MAX_MAPS ) return 0;
	tmp = maps[i];
	maps[i] = tx;
	if ( tmp ) tmp->unuse();
	if ( tx ) tx->use();
	return tmp;
}

CxfTexture* CxfMaterial::unset_map(MATERIALMAP_TYPE map)
{
	const ulong i = (ulong)map;
	CxfTexture* tmp;

	if ( i>=OVRL_MATERIAL_MAX_MAPS ) return 0;
	tmp = maps[i];
	maps[i] = 0;
	if ( tmp ) tmp->unuse();
	return tmp;
}

int CxfMaterial::lock()
{
	return 0;
}

int CxfMaterial::unlock()
{
	return 0;
}

int CxfMaterial::free()
{
	ulong i;
	for ( i=0;i<OVRL_MATERIAL_MAX_MAPS;i++ ) unset_map((MATERIALMAP_TYPE)i);
	return 0;
}
void CxfMaterial::release()
{
	delete this;
}

}