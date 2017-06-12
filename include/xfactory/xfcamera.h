/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xfcamera.h,v $
 * $Implementation: /src/xfactory/xfCamera.cc $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:07 $
 * $Description: Camera class $
 *
 * $Log: xfcamera.h,v $
 * Revision 1.2  2005/07/14 12:14:07  foxis
 * no message
 *
 * Revision 1.1.1.1  2005/02/02 15:39:23  foxis
 * sources import
 *
 * Revision 0.1  20020117  20:30:00 FoxiE
 *  :)
 *
 */



#if !defined(__ovrl_XFCAMERA_HPP)
#define __ovrl_XFCAMERA_HPP

#include "common/all.h"
//#include "system/ovrlsystem.h"
#include "xfactory/xftemplate.h"
#include "xfactory/xfactory.h"
//#include "xfactory/xfsurface.h"
#include "tpllib/tpl.hpp"

namespace openvrl {


class OVRLIBAPI CxFactory;
class OVRLIBAPI CxfCamera;

/**
 * CxfCameraList class
 */
class OVRLIBAPI CxfCameraList : public CxFactoryListTemplate<CxfCamera, CxfCameraList>
{
public:
	virtual CxfCamera* create(const CString& name)
	{
		CxfCamera* tmp = find(name);
		return (tmp)?(tmp):(CxFactoryListTemplate<CxfCamera, CxfCameraList>::create(name));
	}
	virtual CxfCamera* create(const TPL_CAMERA& m);
	virtual CxfCamera* create(const CString&	_name,
		C3DPoint _pos, C3DPoint _target, C3DVector _up,
		real _focus, real dx, real dy,
		real _gamma, BYTE _brightness, BYTE _contrast,
		BYTE _white, BYTE _black);
	virtual CxfCamera* create(const CString&	_name,
		C3DPoint _pos, C3DPoint _target, C3DVector _up,
		real _focus, real lens)
	{
		return create(_name, _pos, _target, _up, _focus, lens,lens, 1.0f, 0,0,255,0);
	}



	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int save_library(const CString& path);
	virtual int save_library(CTPLLib* tpl);

	/** 
	 *
	 */
	CxfCameraList(CxFactory* xf);
	virtual ~CxfCameraList();
};

/**
 * CxfCamera class
 */
class OVRLIBAPI CxfCamera : public CxFactoryTemplate<CxfCameraList, CxfCamera>
{
protected:
	HANDLER	 m_hCamera;
	BYTE		*m_locked_Camera;
	ulong		m_lock_count;

public:
	C3DPoint		position;
	C3DPoint		target;
	C3DVector		world_up;
	real		focus;              /* Effective camera focus [mm] */
	real		dx;                 /* Width of camera lens [mm] */
	real		dy;                 /* Height of camera lens [mm] */
	real		gamma;
	BYTE		brightness;
	BYTE		contrast;
	BYTE		whitepoint;
	BYTE		blackpoint;

//	CxfViewport*	viewport;
//	CxfSurface*		target_surface;
//	CxfSurface*		target_stencil;

	/**
	 *
	 */
	virtual int lock();
	virtual int unlock();
	virtual int create();
	virtual int free();
	virtual void release();

	bool locked() const { return m_locked_Camera!=0; }
	bool created() const { return m_hCamera!=0; }
	bool local_created() const { return true; }

	virtual int create(const TPL_CAMERA& m);
	virtual int create(const CString&	_name,
		C3DPoint _pos, C3DPoint _target, C3DVector _up,
		real _focus, real dx, real dy,
		real _gamma, BYTE _brightness, BYTE _contrast,
		BYTE _white, BYTE _black);
	virtual int create(const CString&	_name,
		C3DPoint _pos, C3DPoint _target, C3DVector _up,
		real _focus, real lens)
	{
		return create(_name, _pos, _target, _up, _focus, lens,lens, 1.0f, 0,0,255,0);
	}


	//
	CxfCamera(CxfCameraList* xfl);
	virtual ~CxfCamera();
};

};

#endif /* !defined(__ovrl_XFCAMERA_HPP) */
