/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xftemplate.h,v $
 * $Implementation: /src/xfactroy/xftemplate.cc $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:08 $
 * $Description: xFactory Template class $
 *
 * $Log: xftemplate.h,v $
 * Revision 1.3  2005/07/14 12:14:08  foxis
 * no message
 *
 * Revision 1.2  2005/03/04 13:21:16  foxis
 * no message
 *
 * Revision 1.1.1.1  2005/02/02 15:39:24  foxis
 * sources import
 *
 * Revision 0.2  20020815  15:05:00 FoxiE
 *  Kaikurie pataisymai
 *
 * Revision 0.1  20020117  20:30:00 FoxiE
 *  :)
 *
 */



#if !defined(__ovrl_XFTEMPLATE_HPP)
#define __ovrl_XFTEMPLATE_HPP

#include <vector>
#include <list>
#include "common/all.h"
#include "common/string.h"
#include "tpllib/tpl.hpp"

namespace openvrl {

class OVRLIBAPI CxFactory;

template <class TA, class Tthis>
class OVRLIBAPI CxFactoryListTemplate 
{
	CxFactoryListTemplate() {}
	CxFactoryListTemplate(const CxFactoryListTemplate& xf) {}

protected:
	CxFactory*	m_xFactory;
	std::list<TA*>* m_list;

public:
	CxFactory* xFactory() const { return m_xFactory; }
	CxFactory* get_xFactory() const { return m_xFactory; }

	virtual TA* create(const CString& name);
	int release(TA* m);
	TA* add(const CString& name, TA* m);
	TA* remove(const CString& name);
	TA* remove(TA*);
	TA* find(const CString& name);

	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY)=0;
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY)=0;
	virtual int save_library(const CString& path) = 0;
	virtual int save_library(CTPLLib* tpl) = 0;

	//
	CxFactoryListTemplate(CxFactory* xf);
	virtual ~CxFactoryListTemplate();
};

/**
 *  CxFactoryTemplate class
 */
template <class TA, class Tthis>
class OVRLIBAPI CxFactoryTemplate 
{
	CxFactoryTemplate() {};
	CxFactoryTemplate(const CxFactoryTemplate<TA, Tthis>&) {}

protected:
	TA			*m_xList;
	CString	m_name;
	bool		m_do_free;
	ulong	m_ref_count;
//	CTPLLib		*m_tpl;

public:
	TA* xList() const { return m_xList; }
	TA*& xList() { return m_xList; }
	TA* get_xList() const { return m_xList; }
	TA*& get_xList() { return m_xList; }

	CString name() const { return m_name; }
	CString& name() { return m_name; }

	int use();	// increase ref_count
	int unuse();	// decrease ref_count
	ulong ref_count() const { return m_ref_count; }

	virtual int free()=0;
	virtual void release()=0;

//	virtual int read();
//	virtual int read(CTPLLib&);
//	virtual int write();
//	virtual int write(CTPLLib&);
//	virtual int set_tpl(CTPLLib*);
//	virtual CTPLLib* tpl() { return m_tpl; }
//	virtual int get_tpl() { return m_tpl; }
//	virtual const CTPLLib* tpl() const { return m_tpl; }

	//
	CxFactoryTemplate(TA* xfl); 
	virtual ~CxFactoryTemplate(); 
};

#include "xfactory/xftemplate.inl"

};

#endif /* !defined(__ovrl_XFTEMPLATE_HPP) */
