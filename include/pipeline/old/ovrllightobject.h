/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/old/ovrllightobject.h,v $
 * $Implementation: ~/src/pipeline/mesh.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:21 $
 * $Description: mesh $
 *
 * $Log: ovrllightobject.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:21  foxis
 * sources import
 *
 * Revision 0.1  20020812  22:02:00 FoxiE
 * y
 *
 */

#if !defined(_ovrl_OVRLLIGHTOBJECT_H)
#define _ovrl_OVRLLIGHTOBJECT_H

#include <vector>
#include <list>

#include "common/all.h"
#include "pipeline/ovrlmesh.h"
#include "pipeline/ovrlpipeline.h"
#include "tpllib/tpl.hpp"

namespace openvrl {

class OVRLIBAPI CPipeline;

class OVRLIBAPI CplLightObject : public CMesh
{
protected:
	CxfLight*	m_light;
	C3DPoint		m_Position;
	C3DVector		m_Direction;

public:
	const CxfLight* Light() const { return m_light; }
	CxfLight*& Light() { return m_light; }

	C3DVector getDirection() const { return m_Direction; }
	C3DVector& getDirection() { return m_Direction; }
	C3DPoint getPosition() const { return m_Position; }
	C3DPoint& getPosition() { return m_Position; }

	//
	virtual int Initialize();
	virtual int Update();
	virtual int SetStates();
	virtual int SetStreams();
	virtual int RenderSubset(ulong i, const CplCameraObject* campos);
	virtual int Render(const CplCameraObject* campos, bool set_states=true);
	virtual int Cleanup();
	virtual int Apply(ulong num);

	//
	int Create(CxfLight* light);
	int Load(const CString& path);

	//
	CplLightObject(CPipeline* vbp=CPipeline::s_THIS);
	virtual ~CplLightObject();

	virtual void PrintStateToStr(CString& out, ulong tabs=0);

	virtual ulong what() const { return ORW_LIGHT_OBJECT; }
	virtual CHAR* get_name() const { return "OpenVRL plLightObject class"; }
};

};

#endif // !defined(_ovrl_OVRLLIGHTOBJECT_H)
