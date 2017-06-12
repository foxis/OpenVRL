#include "common/all.h"
#include "system/ovrlsystem.h"
#include "xfactory/xfcamera.h"
#include "iosystem/fileiodev.h"
#include "common/pattern.h"

namespace openvrl {

/******************************************************************************
 * CxfCameraList class
 *****************************************************************************/
CxfCameraList::CxfCameraList(CxFactory* xf)
	:CxFactoryListTemplate<CxfCamera, CxfCameraList>(xf)
{
}

CxfCameraList::~CxfCameraList()
{
}

CxfCamera* CxfCameraList::create(const TPL_CAMERA& m)
{
	CxfCamera *tmp = create(m.name);
	tmp->create(m);
	return tmp;
}

CxfCamera* CxfCameraList::create(const CString&	_name,
		C3DPoint _pos, C3DPoint _target, C3DVector _up,
		real _focus, real dx, real dy,
		real _gamma, BYTE _brightness, BYTE _contrast,
		BYTE _white, BYTE _black)
{
	CxfCamera *tmp = create(_name);
	tmp->create(_name, _pos, _target, _up, _focus, dx, dy, _gamma, _brightness, _contrast, _white, _black);
	return tmp;
}

int CxfCameraList::load_library(const CString& path, const CString& pattern, DWORD flags)
{
	CFileIOD f(0);
	CTPLLib	tpl(&f, "Test TPL file", 1, 1);
//	CLog log("load_library", "camera.log");
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

int CxfCameraList::load_library(CTPLLib* tpl, const CString& pattern, DWORD flags)
{
	ulong i;
	for ( i=0;i<tpl->cameras();i++ )
	if ( CPattern(pattern) == tpl->camera(i)->name ) 
		create(*tpl->camera(i));
	
	return 0;
}

int CxfCameraList::save_library(const CString& path)
{
	return 1;
}
int CxfCameraList::save_library(CTPLLib* tpl)
{
	return 1;
}


/******************************************************************************
 * CxfCamera class
 *****************************************************************************/
CxfCamera::CxfCamera(CxfCameraList* xfl)
	: CxFactoryTemplate<CxfCameraList,CxfCamera>(xfl)
{
	m_hCamera = 0;
	m_locked_Camera = 0;
}

CxfCamera::~CxfCamera()
{
}

int CxfCamera::create()
{
	return 1;
}

int CxfCamera::create(const TPL_CAMERA& m)
{
	name() = m.name;
	focus = m.focus;
	dx = m.dx;
	dy = m.dy;
	brightness = m.brightness;
	contrast = m.contrast;
	gamma = m.gamma;
	whitepoint = m.whitepoint;
	blackpoint = m.blackpoint;
	position = C3DPoint(0.0,10.0,-10.0);
	target = C3DPoint(0.0, 0.0, 2.5);
	world_up = C3DVector(0.0,1.0,0.0);
	return 0;
}

int CxfCamera::create(const CString&	_name,
		C3DPoint _pos, C3DPoint _target, C3DVector _up,
		real _focus, real _dx, real _dy,
		real _gamma, BYTE _brightness, BYTE _contrast,
		BYTE _white, BYTE _black)
{
	name() = _name;
	focus = _focus;
	dx = _dx;
	dy = _dy;
	brightness = _brightness;
	contrast = _contrast;
	gamma = _gamma;
	whitepoint = _white;
	blackpoint = _black;
	position = _pos;
	target = _target;
	world_up = _up;
	return 0;
}


int CxfCamera::lock()
{
	return 0;
}

int CxfCamera::unlock()
{
	return 0;
}

int CxfCamera::free()
{
	return 0;
}
void CxfCamera::release()
{
	delete this;
}

}