#include "common/all.h"
#include "system/ovrlsystem.h"
#include "xfactory/xftexture.h"
#include "iosystem/fileiodev.h"
#include "tools/imageprocessing.h"

namespace openvrl {

/***************************************************************************** 
 * CxfTextureList class
 *****************************************************************************/

CxfTextureList::CxfTextureList(CxFactory* xf)
	:CxFactoryListTemplate<CxfTexture, CxfTextureList>(xf)
{
}


CxfTextureList::~CxfTextureList()
{
}

CxfTexture* CxfTextureList::create(ulong Width, ulong Height, ulong Levels, DWORD Usage, DWORD Format, const CString& name)
{
	static ulong txs=0;
	char str[9];
	CxfTexture* tmp;
	if ( OVRL_ISSTREMPTY(name.c_str()) )
	{
		sprintf(str, "%08x", txs++);
		tmp = create(str);
	}
	else
		tmp = create(name);
	tmp->create(Width, Height, Levels, Usage, Format);
	return tmp;
}

CxfTexture* CxfTextureList::load(const CString& name)
{
	CxfTexture* tmp = find(name);
	if ( tmp )
	{
		return tmp;
	}
	else
	{
		tmp = create(name);
		tmp->load(name);
		return tmp;
	}
}


int CxfTextureList::load_library(const CString& path, const CString& pattern, DWORD flags)
{
	CFileIOD f(0);
	CTPLLib	tpl(&f, "Test TPL file", 1, 1);
//	CLog log("load_library", "material.log");
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

int CxfTextureList::load_library(CTPLLib* tpl, const CString& pattern, DWORD flags)
{
	ulong i,j;
	for ( i=0;i<tpl->textures();i++ )
	{
		CTPLLib::tex t;
		tpl->texture_read(&t, i);
		CxfTexture* tex;
		char *fn = tpl->get_fname();
		char *p = strrchr(fn, '\\');
		if ( p!='\0' && *p=='\\' ) *(p+1) = '\0';
		char path[512];

		strncpy(path, fn, 512);
		strncat(path, (char*)t.data, 512);

		switch ( t.head.styles&0x0F )
		{
		case TPL_TEX_PATH:
		{
			CImageProcessing::img img;
			CImageProcessing IP;
			int r = img.LoadFromFile(path, "BMP");

			OVRL_ASSERT(r==0);

			switch ( img.BytesPerPixel() )
			{
			case 4:
				tex = create(img.Width(), img.Height(), 1, OVRL_TX_DYNAMIC, FMT_A8R8G8B8, t.head.name);
				tex->lock();
				OVRL_memcpy(tex->pTX(), img.Data(), img.Width()*img.Height());
				tex->unlock();
				break;
			case 3:
				tex = create(img.Width(), img.Height(), 1, OVRL_TX_DYNAMIC, FMT_X8R8G8B8, t.head.name);
				if ( tex )
				{
					tex->lock();
					OVRL_ASSERT(tex->pTX());
					BYTE* s, *d;
					s = (BYTE*)img.Data();
					d = (BYTE*)tex->pTX();
					for ( j=0;j<img.Width()*img.Height();j++ )
					{
						*(d++) = *(s++);
						*(d++) = *(s++);
						*(d++) = *(s++);
						*(d++) = 0;
					}
					tex->unlock();
				}
				break;
			case 1:
			case 2:
			default:
				OVRL_ASSERT_EX(false, NOTIMPLEMENTED, "Not implemented texture format!");
			}
			break;
		}

		case TPL_TEX_SRF:
		case TPL_TEX_RAW:
		case TPL_TEX_TEX:
		default:
			OVRL_ASSERT_EX(false, NOTIMPLEMENTED, "texture format not implemented!");
		}
	}
	return 0;
}

int CxfTextureList::save_library(const CString& path)
{
	return 1;
}
int CxfTextureList::save_library(CTPLLib* tpl)
{
	return 1;
}

/***************************************************************************** 
 * CxfTexture class
 *****************************************************************************/

/**
 *
 */
CxfTexture::CxfTexture(CxfTextureList* xfl) 
	: CxFactoryTemplate<CxfTextureList, CxfTexture>(xfl),
	m_TX_usage(0),	m_TX_format(0),
	m_TX_levels(0),	m_locked_TX(0),	m_hTX(0)
{
}


CxfTexture::~CxfTexture()
{
}

int CxfTexture::create(ulong Width, ulong Height, ulong Levels, DWORD Usage, DWORD Format)
{
	if ( (Usage&OVRL_TX_LOCAL_ONLY)!=OVRL_TX_LOCAL_ONLY ) 
	{
		if ( m_hTX || m_locked_TX ) return 1;
		m_hTX = xList()->xFactory()->System()->Pipeline()->TXPool()->create(Width, Height, Levels, Usage, Format);
		m_TX_format =  (WORD)Format;
	}


	m_TX_usage = Usage;
	m_TX_levels = Levels;
	return 0;
}

int CxfTexture::load(const CString& nm)
{
	if ( m_hTX || m_locked_TX ) return 1;
	m_hTX = xList()->xFactory()->System()->Pipeline()->TXPool()->load(nm.c_str());
	name() = nm;
	m_TX_usage = 0;
	m_TX_levels = 0;
	return 0;
}

int CxfTexture::lock(ulong level)
{
	if ( locked() || m_hTX==0 ) return 1;
	m_locked_TX = m_hTX->pool->lock(m_hTX, level, &m_locked_TX_pitch);
	return 0; 
}
int CxfTexture::lock_rect(ulong level, const C2DRect& rect)
{
	if ( locked() || m_hTX==0 ) return 1;
	m_locked_TX = m_hTX->pool->lock_rect(m_hTX, level, (ulong)rect.left(), 
		(ulong)rect.top(), (ulong)rect.right(), (ulong)rect.bottom(), &m_locked_TX_pitch);
	return 0; 
}

int CxfTexture::unlock(ulong level)
{
	if ( !locked() || m_hTX==0 ) return 1;
	m_hTX->pool->unlock(m_hTX, level);
	m_locked_TX = 0;
	return 0; 
}

int CxfTexture::free(DWORD usage)
{
	if ( !(usage&(OVRL_TX_LOCAL_ONLY|~OVRL_TX_CONTAINS_LOCAL)) ) {
		if ( locked() ) unlock();
		m_hTX->pool->release(m_hTX, usage);
		m_TX_format = 0;
		m_hTX = 0;
	}

	m_TX_usage = 0;
	m_TX_levels = 0;
	return 0;
}

void CxfTexture::release()
{
	delete this;
}

}