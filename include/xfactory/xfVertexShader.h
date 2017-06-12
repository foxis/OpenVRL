/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xfVertexShader.h,v $
 * $Implementation: /src/xfactory/xfvertexshader.cc $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:07 $
 * $Description: Vertex shader class $
 *
 * $Log: xfVertexShader.h,v $
 * Revision 1.2  2005/07/14 12:14:07  foxis
 * no message
 *
 * Revision 1.1.1.1  2005/02/02 15:39:24  foxis
 * sources import
 *
 * Revision 0.1  20020815  20:30:00 FoxiE
 *  :)
 *
 */


#if !defined(__ovrl_XFVERTEXSHADER_HPP)
#define __ovrl_XFVERTEXSHADER_HPP


#include "common/all.h"
#include "pipeline/vspool.h"
#include "xfactory/xftemplate.h"
#include "xfactory/xfactory.h"

namespace openvrl {

class OVRLIBAPI CxFactory;
class OVRLIBAPI CxfVertexShader;

/**
 * CxfVertexShaderList class
 */
class OVRLIBAPI CxfVertexShaderList : public CxFactoryListTemplate<CxfVertexShader, CxfVertexShaderList>
{
public:
	virtual CxfVertexShader* create(const CString& name)
	{
		CxfVertexShader* tmp = find(name);
		return (tmp)?(tmp):(CxFactoryListTemplate<CxfVertexShader, CxfVertexShaderList>::create(name));
	}
	virtual CxfVertexShader* create(DWORD handler, const CString& name="");

	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int save_library(const CString& path);
	virtual int save_library(CTPLLib* tpl);

	/** 
	 *
	 */
	CxfVertexShaderList(CxFactory* xf);
	virtual ~CxfVertexShaderList();
};

/**
 * CxfVertexShader class
 */
class OVRLIBAPI CxfVertexShader : public CxFactoryTemplate<CxfVertexShaderList, CxfVertexShader>
{
protected:
	HVS	 m_hVS;
	DWORD		m_handler;

public:
	HVS hVS() const { return m_hVS; }
	HVS& hVS() { return m_hVS; }

	DWORD handler() const { return m_handler; }
	DWORD& handler() { return m_handler; }

	/**
	 *
	 */
	virtual int lock();
	virtual int unlock();
	virtual int create(DWORD handler);
	virtual int free();
	virtual void release();

	bool locked() const { return 0; }
	bool created() const { return 0; }
	bool local_created() const { return true; }


	/**
	 *
	 */
	CxfVertexShader(CxfVertexShaderList* xfl);
	virtual ~CxfVertexShader();
};

};

#endif // !defined(__ovrl_XFVERTEXSHADER_HPP)
