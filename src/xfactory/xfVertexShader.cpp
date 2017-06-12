#include "common/all.h"
#include "system/ovrlsystem.h"
#include "xfactory/xfVertexShader.h"
#include "iosystem/fileiodev.h"

namespace openvrl {


/******************************************************************************
 * CxfVertexShaderList class
 *****************************************************************************/
CxfVertexShaderList::CxfVertexShaderList(CxFactory* xf)
	:CxFactoryListTemplate<CxfVertexShader, CxfVertexShaderList>(xf)
{
}

CxfVertexShaderList::~CxfVertexShaderList()
{
}

CxfVertexShader* CxfVertexShaderList::create(DWORD handler, const CString& name)
{
	char str[9];
	CxfVertexShader * tmp;
	if ( OVRL_ISSTREMPTY(name.c_str()) )
	{
		sprintf(str, "%08x", handler);
		tmp = create(str);
	}
	else
		tmp = create(name);
	tmp->create(handler);
	return tmp;
}

int CxfVertexShaderList::load_library(const CString& path, const CString& pattern, DWORD flags)
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

int CxfVertexShaderList::load_library(CTPLLib* tpl, const CString& pattern, DWORD flags)
{
	return 1;
}

int CxfVertexShaderList::save_library(const CString& path)
{
	return 1;
}
int CxfVertexShaderList::save_library(CTPLLib* tpl)
{
	return 1;
}



/******************************************************************************
 * CxfVertexShader class
 *****************************************************************************/
CxfVertexShader::CxfVertexShader(CxfVertexShaderList* xfl)
	: CxFactoryTemplate<CxfVertexShaderList, CxfVertexShader>(xfl),
	m_hVS(0), m_handler(0)
{
}

CxfVertexShader::~CxfVertexShader()
{
}



int CxfVertexShader::lock()
{
	return 0;
}

int CxfVertexShader::unlock()
{
	return 0;
}

int CxfVertexShader::create(DWORD handler)
{
	if ( m_hVS ) return 1;
	m_hVS = xList()->xFactory()->System()->Pipeline()->VSPool()->create(handler);
	m_handler = m_hVS->dwFormat;
	return 0;
}

int CxfVertexShader::free()
{
	return 0;
}

void CxfVertexShader::release()
{
	delete this;
}

}