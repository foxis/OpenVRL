/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/pipeline/old/ovrlrenderobject.h,v $
 * $Implementation: ~/src/pipeline/renderobject.cc $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:21 $
 * $Description: renderable object abstract class $
 *
 * $Log: ovrlrenderobject.h,v $
 * Revision 1.1.1.1  2005/02/02 15:39:21  foxis
 * sources import
 *
 * Revision 0.1  20020813  22:02:00 FoxiE
 * y
 *
 */

#if !defined(__ovrl_OVRLRENDEROBJECT_HPP)
#define __ovrl_OVRLRENDEROBJECT_HPP

#include "common/ovrlobj.h"
#include "pipeline/ovrlpipeline.h"
#include "pipeline/ovrlcameraobject.h"

namespace openvrl {

class OVRLIBAPI CPipeline;

//
// class
//
class OVRLIBAPI CplRenderableObject : public IObject
{
protected:
	CPipeline*			m_Pipeline;
	C4x4Matrix				m_matrix;

public:
	CplRenderableObject(CPipeline* vbp=CPipeline::s_THIS) 
		:m_Pipeline(vbp) 
	{ }
	virtual ~CplRenderableObject() 
	{ }

	CPipeline*& Pipeline() { return m_Pipeline; }
	const CPipeline* Pipeline() const { return m_Pipeline; }

	C4x4Matrix matrix() const { return m_matrix; }
	C4x4Matrix& matrix() { return m_matrix; }

	virtual C4x4Matrix getWorldTransform() const = 0;
	virtual C4x4Matrix& getWorldTransform() = 0;

	virtual C4x4Matrix getModelTransform() const = 0;
	virtual C4x4Matrix& getModelTransform() = 0;

	// inserts to the rendering pipeline
	bool	activate()
	{
		return !!m_Pipeline->AddObject(this);
	}
	// removes from rendering pipeline
	bool	deactivate()
	{
		return !!m_Pipeline->RemoveObject(this);
	}

	//
	virtual int Initialize() = 0;
	virtual int Update() = 0;
	virtual int SetStates() = 0;
	virtual int SetStreams() = 0;
	virtual int RenderSubset(ulong i, const CplCameraObject* cam) = 0;
	virtual int Render(const CplCameraObject* cam, bool set_states=true) = 0;
	virtual int Cleanup() = 0;

	virtual ulong subsets() const = 0;

	virtual void PrintStateToStr(CString& out, ulong tabs=0)
	{
		CString t;
		t.feed_tabs(tabs);
		out << t << "// CplRenderableObject\n";
		out << t << "matrix = " << m_matrix <<";\n";
//		IObject::PrintStateToStr(out, tabs+1);
	}

	//
	virtual ulong what() const {	return ORW_RENDERABLE_OBJECT;	}
	virtual CHAR* get_name() const { return "OpenVRL Renderable Object class"; }
};

};

#endif // !defined(__ovrl_OVRLRENDEROBJECT_HPP)