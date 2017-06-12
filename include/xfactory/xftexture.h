/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/xfactory/xftexture.h,v $
 * $Implementation: /src/xfactory/xftexture.cc $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/07/14 12:14:08 $
 * $Description: texture class $
 *
 * $Log: xftexture.h,v $
 * Revision 1.3  2005/07/14 12:14:08  foxis
 * no message
 *
 * Revision 1.2  2005/03/04 13:21:16  foxis
 * no message
 *
 * Revision 1.1.1.1  2005/02/02 15:39:24  foxis
 * sources import
 *
 * Revision 0.1  20020814  20:30:00 FoxiE
 *  :)
 *
 */



#if !defined(__ovrl_XFTEXTURE_HPP)
#define __ovrl_XFTEXTURE_HPP

#include "common/all.h"
#include "pipeline/txpool.h"
#include "xfactory/xftemplate.h"
#include "xfactory/xfactory.h"

namespace openvrl {

class OVRLIBAPI CxFactory;
class OVRLIBAPI CxfTexture;

/**
 * CxfTextureList class
 */
class OVRLIBAPI CxfTextureList : public CxFactoryListTemplate<CxfTexture, CxfTextureList>
{
public:
	virtual CxfTexture* create(const CString& name)
	{
		CxfTexture* tmp = find(name);
		return (tmp)?(tmp):(CxFactoryListTemplate<CxfTexture, CxfTextureList>::create(name));
	}
	virtual CxfTexture* create(ulong Width, ulong Height, ulong Levels, DWORD Usage, DWORD Format, const CString& name="");
	virtual CxfTexture* load(const CString& name);


	virtual int load_library(const CString& path, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int load_library(CTPLLib* tpl, const CString& pattern="*", DWORD flags=USAGE_WRITEONLY);
	virtual int save_library(const CString& path);
	virtual int save_library(CTPLLib* tpl);

	/** 
	 *
	 */
	CxfTextureList(CxFactory* xf);
	virtual ~CxfTextureList();
};

/**
 * CxfTexture class
 */
class OVRLIBAPI CxfTexture : public CxFactoryTemplate<CxfTextureList, CxfTexture>
{
protected: 
	DWORD	m_TX_usage;
	WORD	m_TX_format;
	ulong	m_TX_levels;
	BYTE	*m_locked_TX;
	ulong	m_locked_TX_pitch;
	HTX	m_hTX;

	ulong	m_lock_count;

public:
	DWORD usage() const { return m_TX_usage; }
	ulong levels() const { return m_TX_levels; }
	WORD format() const { return m_TX_format; }
	const BYTE* pTX() const { return m_locked_TX; }
	BYTE* pTX() { return m_locked_TX; }
	ulong TX_pitch() const { return m_locked_TX_pitch; }
	HTX hTX() const { return m_hTX; }
	HTX& hTX() { return m_hTX; }


	/**
	 * 
	 */
	virtual int create(ulong Width, ulong Height, ulong Levels, DWORD Usage, DWORD Format);
	virtual int load(const CString& name);

	virtual int lock(ulong level=0);
	virtual int lock_rect(ulong level, const C2DRect& rect);
	virtual int unlock(ulong level=0);
	virtual int free(DWORD usage);
	virtual int free()	{ return free(0); }
	virtual void release();

	bool locked() const { return m_locked_TX!=0; }
	bool created() const { return m_hTX!=0; }

	/**
	 *
	 */
	CxfTexture(CxfTextureList* xfl);
	virtual ~CxfTexture();
};

};

#endif /* !defined(__ovrl_XF_HPP) */
