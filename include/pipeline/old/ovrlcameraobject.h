/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/old/ovrlcameraobject.h,v $
 * $Implementation: ~/src/pipeline/camera.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:21 $
 * $Description: camera $
 *
 * $Log: ovrlcameraobject.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:21  foxis
 * sources import
 *
 * Revision 0.1  20020812  22:02:00 FoxiE
 * y
 *
 */

#if !defined(_ovrl_OVRLCAMERAOBJECT_HPP)
#define _ovrl_OVRLCAMERAOBJECT_HPP

#include <vector>
#include <list>

#include "common/all.h"
#include "pipeline/ovrlpipeline.h"
#include "tpllib/tpl.hpp"

namespace openvrl {

class OVRLIBAPI CPipeline;

class OVRLIBAPI CplCameraObject : public IObject
{
protected:
	CPipeline*	m_Pipeline;
	CxfCamera*	m_camera;
	C4x4Matrix	m_View;
	C4x4Matrix	m_Projection;

public:
	virtual C4x4Matrix matrix() const { return m_View; }
	virtual C4x4Matrix& matrix() { return m_View; }

	virtual C4x4Matrix getModelTransform() const { return matrix(); }
	virtual C4x4Matrix& getModelTransform()	{ return matrix(); }

	virtual C4x4Matrix getView() const { return m_View; }
	virtual C4x4Matrix& getView()	{ return m_View; }

	virtual C4x4Matrix getProjection() const { return m_Projection; }
	virtual C4x4Matrix& getProjection()	{ return m_Projection; }

	const CxfCamera* Camera() const { return m_camera; }
	CxfCamera* Camera() { return m_camera; }

	//
	int Create(CxfCamera* camera);
	int Load(const CString& path);

	//
	virtual int Initialize();
	virtual int Update();
	virtual int Cleanup();
	virtual int Apply();

	//
	CplCameraObject(CPipeline* vbp=CPipeline::s_THIS);
	virtual ~CplCameraObject();

	virtual void PrintStateToStr(CString& out, ulong tabs=0);

	virtual ulong what() const { return ORW_CAMERA_OBJECT; }
	virtual CHAR* get_name() const { return "OpenVRL plCameraObject class"; }
};

};

#endif // !defined(_ovrl_OVRLMESH_H)
