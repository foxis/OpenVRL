/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xfindexbuf.h,v $
 * $Implementation: /src/xfactory/xfindexbuf.cc $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:07 $
 * $Description: Index Buffer class $
 *
 * $Log: xfindexbuf.h,v $
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



#if !defined(__ovrl_XFINDEXBUF_HPP)
#define __ovrl_XFINDEXBUF_HPP

#include "common/all.h"
#include "pipeline/ibpool.h"
#include "xfactory/xftemplate.h"
#include "xfactory/xfactory.h"

namespace openvrl {

class OVRLIBAPI CxFactory;
class OVRLIBAPI CxfIndexBuffer;

/**
 * CxfIndexBufferList class
 */
class OVRLIBAPI CxfIndexBufferList : public CxFactoryListTemplate<CxfIndexBuffer, CxfIndexBufferList>
{
public:
	virtual CxfIndexBuffer* create(const CString& name)
	{
		CxfIndexBuffer* tmp = find(name);
		return (tmp)?(tmp):(CxFactoryListTemplate<CxfIndexBuffer, CxfIndexBufferList>::create(name));
	}
	virtual CxfIndexBuffer* create(ulong length, WORD format, DWORD usage, const CString& name="", const BYTE* buf=0);

	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int save_library(const CString& path);
	virtual int save_library(CTPLLib* tpl);

	/** 
	 *
	 */
	CxfIndexBufferList(CxFactory* xf);
	virtual ~CxfIndexBufferList();
};

/**
 * CxfIndexBuffer class
 */
class OVRLIBAPI CxfIndexBuffer : public CxFactoryTemplate<CxfIndexBufferList, CxfIndexBuffer>
{
protected: 
	DWORD	 m_IB_usage;
	WORD	 m_local_IB_format;
	WORD	 m_IB_format;
	ulong	 m_local_IB_length;
	ulong	 m_IB_length;
	BYTE	*m_local_IB;
	BYTE	*m_locked_IB;
	HIB	 m_hIB;

	ulong	m_lock_count;

public:
	// Calculates number of bytes given index type occupies in memory
	virtual ulong calculate_index_size(WORD format) const;
	ulong index_size() const { return calculate_index_size(m_IB_format); }

	/**
	 * 
	 */
	DWORD usage() const { return m_IB_usage; }
	ulong length() const { return m_IB_length; }
	WORD format() const { return m_IB_format; }
	const BYTE* pIB() const { return m_locked_IB; }
	BYTE* pIB() { return m_locked_IB; }
	HIB hIB() const { return m_hIB; }
	HIB& hIB() { return m_hIB; }

	/** 
	 *
	 */
	WORD local_format() const { return m_local_IB_format; }
	const BYTE* local_pIB() const { return m_local_IB; }
	BYTE* local_pIB() { return m_local_IB; }

	virtual ulong copy_IB_to_local();
	virtual ulong copy_local_to_IB();
	//const BYTE* src, ulong length, WORD fmt
	virtual ulong copy_to_local(const BYTE* src, ulong length, WORD fmt);
	//BYTE* dst, ulong length, WORD fmt
	virtual ulong copy_from_local(BYTE* dst, ulong length, WORD fmt);
	//const BYTE* src, ulong length, WORD fmt
	virtual ulong copy_to_IB(const BYTE* src, ulong length, WORD fmt);
	//BYTE* dst, ulong length, WORD fmt
	virtual ulong copy_from_IB(BYTE* dst, ulong length, WORD fmt);
	virtual int set_local_format(WORD fmt);
	virtual int set_IB_format(WORD fmt);

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

	bool locked() const { return m_locked_IB!=0; }
	bool created() const { return m_hIB!=0 || m_local_IB; }
	bool local_created() const { return m_local_IB!=0; }

	/**
	 *
	 */
	CxfIndexBuffer(CxfIndexBufferList* xfl);
	virtual ~CxfIndexBuffer();
};

};

#endif /* !defined(__ovrl_XFINDEXBUF_HPP) */
