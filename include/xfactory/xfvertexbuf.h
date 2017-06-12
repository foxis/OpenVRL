/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xfvertexbuf.h,v $
 * $Implementation: /src/xfactory/xfvertexbuf.cc $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:08 $
 * $Description: Vertex Buffer class $
 *
 * $Log: xfvertexbuf.h,v $
 * Revision 1.2  2005/07/14 12:14:08  foxis
 * no message
 *
 * Revision 1.1.1.1  2005/02/02 15:39:24  foxis
 * sources import
 *
 * Revision 0.1  20020117  20:30:00 FoxiE
 *  :)
 *
 */



#if !defined(__ovrl_XFVERTEXBUF_HPP)
#define __ovrl_XFVERTEXBUF_HPP

#include "common/all.h"
#include "pipeline/vbpool.h"
#include "xfactory/xftemplate.h"
#include "xfactory/xfactory.h"
#include "xfactory/xfVertexShader.h"

namespace openvrl {

class OVRLIBAPI CxFactory;
class OVRLIBAPI CxfVertexBuffer;

/**
 * CxfVertexBufferList class
 */
class OVRLIBAPI CxfVertexBufferList : public CxFactoryListTemplate<CxfVertexBuffer, CxfVertexBufferList>
{
public:
	virtual CxfVertexBuffer* create(const CString& name)
	{
		CxfVertexBuffer* tmp = find(name);
		return (tmp)?(tmp):(CxFactoryListTemplate<CxfVertexBuffer, CxfVertexBufferList>::create(name));
	}
	virtual CxfVertexBuffer* create(ulong length, WORD format, DWORD usage, const CString& name="", const BYTE* buf=0);

	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int save_library(const CString& path);
	virtual int save_library(CTPLLib* tpl);


	/** 
	 *
	 */
	CxfVertexBufferList(CxFactory* xf);
	virtual ~CxfVertexBufferList();
};

/**
 * CxfVertexBuffer class
 */
class OVRLIBAPI CxfVertexBuffer : public CxFactoryTemplate<CxfVertexBufferList, CxfVertexBuffer>
{
protected: 
	DWORD	 m_VB_usage;
	WORD	 m_local_VB_format;
	WORD	 m_VB_format;
	ulong	 m_local_VB_length;
	ulong	 m_VB_length;
	BYTE	*m_local_VB;
	BYTE	*m_locked_VB;
	HVB	 m_hVB;
	CxfVertexShader*	m_VertexShader;

	ulong	m_lock_count;

public:
	// Calculates number of bytes given vertex type occupies in memory
	virtual ulong calculate_vertex_size(WORD format) const;
	// Copies one vertex with flags sflg into a vertex with flags dflg
	virtual ulong copy_vertex(const BYTE* src, WORD sfmt, BYTE* dst, WORD dfmt) const;

	ulong vertex_size() const { return calculate_vertex_size(m_VB_format); }

	/**
	 * 
	 */
	DWORD usage() const { return m_VB_usage; }
	ulong length() const { return m_VB_length; }
	WORD format() const { return m_VB_format; }
	const BYTE* pVB() const { return m_locked_VB; }
	BYTE* pVB() { return m_locked_VB; }
	HVB hVB() const { return m_hVB; }
	HVB& hVB() { return m_hVB; }

	CxfVertexShader* get_VertexShader() const { return m_VertexShader; }
	CxfVertexShader* set_VertexShader(CxfVertexShader* vs) 
	{ 
		CxfVertexShader* tmp = m_VertexShader;
		m_VertexShader = vs;
		return tmp; 
	}
	

	/** 
	 *
	 */
	WORD local_format() const { return m_local_VB_format; }
	const BYTE* local_pVB() const { return m_local_VB; }
	BYTE* local_pVB() { return m_local_VB; }

	virtual ulong copy_VB_to_local();
	virtual ulong copy_local_to_VB();
	//const BYTE* src, ulong length, WORD fmt
	virtual ulong copy_to_local(const BYTE* src, ulong length, WORD fmt);
	//BYTE* dst, ulong length, WORD fmt
	virtual ulong copy_from_local(BYTE* dst, ulong length, WORD fmt);
	//const BYTE* src, ulong length, WORD fmt
	virtual ulong copy_to_VB(const BYTE* src, ulong length, WORD fmt);
	//BYTE* dst, ulong length, WORD fmt
	virtual ulong copy_from_VB(BYTE* dst, ulong length, WORD fmt);
	virtual int set_local_format(WORD fmt);
	virtual int set_VB_format(WORD fmt);

	/**
	 * 
	 */
	//ulong length, WORD format, DWORD usage, const BYTE* buf=0
	virtual int create(ulong length, WORD format, DWORD usage, const BYTE* buf=0);
	//ulong offset=0, ulong size=0
	virtual int lock(ulong offset=0, ulong size=0);
	virtual int unlock();
	virtual int free(DWORD usage);
	virtual int free()	{ return free(0); }
	virtual void release();

	bool locked() const { return m_locked_VB!=0; }
	bool created() const { return m_hVB!=0 || m_local_VB; }
	bool local_created() const { return m_local_VB!=0; }

	/**
	 *
	 */
	CxfVertexBuffer(CxfVertexBufferList* xfl);
	virtual ~CxfVertexBuffer();
};

};

#endif /* !defined(__ovrl_XFVERTEXBUF_HPP) */
