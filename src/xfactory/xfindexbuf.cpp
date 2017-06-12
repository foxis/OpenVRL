#include "common/all.h"
#include "system/ovrlsystem.h"
#include "xfactory/xfindexbuf.h"
#include "iosystem/fileiodev.h"

namespace openvrl {

/***************************************************************************** 
 * CxfIndexBufferList class
 *****************************************************************************/

CxfIndexBufferList::CxfIndexBufferList(CxFactory* xf)
	:CxFactoryListTemplate<CxfIndexBuffer,CxfIndexBufferList>(xf)
{
}

CxfIndexBufferList::~CxfIndexBufferList()
{
	printf("CxfIndexBufferList: dtor\n");
}


CxfIndexBuffer* CxfIndexBufferList::create(ulong length, WORD format, DWORD usage, const CString& name, const BYTE* buf)
{
	static ulong cnt=0;
	char str[32]="";
	CxfIndexBuffer* tmp;
	if ( OVRL_ISSTREMPTY(name.c_str()) )
	{
		sprintf(str, "%08x%08x%08x", length, format, cnt++);	// generate "random" name
		tmp = create(str);
	}
	else
		tmp = create(name);
	tmp->create(length, format, usage, buf);
	return tmp;
}


int CxfIndexBufferList::load_library(const CString& path, const CString& pattern, DWORD flags)
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

int CxfIndexBufferList::load_library(CTPLLib* tpl, const CString& pattern, DWORD flags)
{
	ulong i;
	for ( i=0;i<tpl->rawmeshes();i++ )
	{
		create(tpl->rawmesh(i)->faces, tpl->rawmesh(i)->IB_flags, 0, tpl->rawmesh(i)->name, tpl->rawmesh(i)->IB);
	}
	return 0;	
}

int CxfIndexBufferList::save_library(const CString& path)
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

	rc = save_library(&tpl);
	tpl.modified = true;
	tpl.close();
	return rc;
}
int CxfIndexBufferList::save_library(CTPLLib* tpl)
{
	return 1;
}

/***************************************************************************** 
 * CxfIndexBuffer class
 *****************************************************************************/

/**
 *
 */
CxfIndexBuffer::CxfIndexBuffer(CxfIndexBufferList* xfl) 
	: CxFactoryTemplate<CxfIndexBufferList, CxfIndexBuffer>(xfl),
	m_IB_usage(0),	m_local_IB_format(0),	m_IB_format(0),
	m_local_IB_length(0),	m_IB_length(0),	m_local_IB(0),
	m_locked_IB(0),	m_hIB(0)
{
}

CxfIndexBuffer::~CxfIndexBuffer()
{
	printf("CxfIndexBuffer: dtor '%s'\n", name().c_str());
}


/** 
 * Calculates number of bytes given index type accupies in memory
 */
ulong CxfIndexBuffer::calculate_index_size(WORD fmt) const
{
    if ( fmt&OVRL_IB_16 ) return 2;
    if ( fmt&OVRL_IB_32 ) return 4;
	return 0;
}


ulong CxfIndexBuffer::copy_IB_to_local()
{
	if ( m_IB_length==0 || m_local_IB==0 || m_locked_IB==0 ) return 0;
	return copy_to_local(m_locked_IB, m_IB_length, m_IB_format);
}

ulong CxfIndexBuffer::copy_local_to_IB()
{
	if ( m_IB_length==0 || m_local_IB==0 || m_locked_IB==0 ) return 0;
	return copy_from_local(m_locked_IB, m_IB_length, m_IB_format);
}

ulong CxfIndexBuffer::copy_to_local(const BYTE* sIB, ulong length, WORD fmt)
{
	ulong dicb, sicb;
	BYTE *dIB;
	if ( m_IB_length==0 || m_local_IB==0 || sIB==0 || !(m_IB_usage&OVRL_IB_CONTAINS_LOCAL) ) return 0;

	dIB = m_local_IB;
	dicb = calculate_index_size(m_local_IB_format);
	sicb = calculate_index_size(fmt);

	if ( dicb==sicb ) memcpy(m_local_IB, sIB, dicb*length);
	else
	{
		// @todo tingiu implementint
	}

	return dicb*length;
}

ulong CxfIndexBuffer::copy_from_local(BYTE* dIB, ulong length, WORD fmt)
{
	ulong dicb, sicb;
	BYTE *sIB;
	if ( m_IB_length==0 || m_local_IB==0 || dIB==0 || !(m_IB_usage&OVRL_IB_CONTAINS_LOCAL) ) return 0;

	sIB = m_local_IB;
	sicb = calculate_index_size(m_local_IB_format);
	dicb = calculate_index_size(fmt);

	if ( dicb==sicb ) memcpy(dIB, m_local_IB, dicb*length);
	else
	{
		// @todo tingiu implementint
	}

	return dicb*length;
}

ulong CxfIndexBuffer::copy_to_IB(const BYTE* sIB, ulong length, WORD fmt)
{
	ulong dicb, sicb;
	if ( m_IB_length==0 || m_locked_IB==0 || sIB==0 ) return 0;

	sIB = m_locked_IB;
	sicb = calculate_index_size(m_IB_format);
	dicb = calculate_index_size(fmt);

	if ( dicb==sicb ) memcpy(m_locked_IB, sIB, dicb*length);
	else
	{
		// @todo tingiu implementint
	}

	return dicb*length;
}

ulong CxfIndexBuffer::copy_from_IB(BYTE* dIB, ulong length, WORD fmt)
{
	ulong dicb, sicb;
	BYTE *sIB;
	if ( m_IB_length==0 || m_locked_IB==0 || dIB==0 ) return 0;

	sIB = m_locked_IB;
	sicb = calculate_index_size(m_IB_format);
	dicb = calculate_index_size(fmt);
	if ( dicb==sicb ) memcpy(dIB, m_locked_IB, dicb*length);
	else
	{
		// @todo tingiu implementint
	}


	return dicb*length;
}

int CxfIndexBuffer::set_local_format(WORD fmt)
{
	BYTE* lIB, *ltmp;
	WORD ftmp;
	if ( m_IB_length==0 || m_local_IB==0 || !(m_IB_usage&OVRL_IB_CONTAINS_LOCAL) ) return 1;

	lIB = new BYTE[m_IB_length*calculate_index_size(fmt)];
	if ( lIB==0 ) return 1;
	ltmp = m_local_IB;
	m_local_IB = lIB;
	ftmp = m_local_IB_format;
	m_local_IB_format = fmt;
	if ( copy_to_local(ltmp, m_IB_length, ftmp)==0 ) { delete[] ltmp; return 1; }
	delete[] ltmp;
	return 0;
}

int CxfIndexBuffer::set_IB_format(WORD fmt)
{
	return 0;
}


/**
 * 
 */
int CxfIndexBuffer::create(ulong length, WORD format, DWORD usage, const BYTE* buf)
{
	const ulong cb = length*calculate_index_size(format);
	if ( (usage&OVRL_IB_LOCAL_ONLY)!=OVRL_IB_LOCAL_ONLY ) {
		if ( m_hIB || m_locked_IB ) return 1;
		m_hIB = xList()->xFactory()->System()->Pipeline()->IBPool()->create(length, format, usage, buf);
		m_IB_format =  format;
	}
	if ( usage&OVRL_IB_CONTAINS_LOCAL ) {
		if ( m_local_IB || m_local_IB_format ) return 1;
		m_local_IB = new BYTE[cb];
		if ( m_local_IB==0 ) return 1;
		if ( buf==0 )  
			memset(m_local_IB, 0, cb);
		else
			memcpy(m_local_IB, buf, cb);
		m_local_IB_format = format;
	}

	m_IB_usage = usage;
	m_IB_length = length;
	return 0;
}

int CxfIndexBuffer::lock(ulong offset, ulong size)
{
	if ( locked() || m_hIB==0 ) return 1;
	m_locked_IB = m_hIB->pool->lock(m_hIB, offset, size);
	return 0; 
}

int CxfIndexBuffer::unlock()
{
	if ( !locked() || m_hIB==0 ) return 1;
	m_hIB->pool->unlock(m_hIB);
	m_locked_IB = 0;
	return 0; 
}

int CxfIndexBuffer::free(DWORD usage)
{
	printf("CxfIndexBuffer free\n");
	if ( !(usage&(OVRL_IB_LOCAL_ONLY|~OVRL_IB_CONTAINS_LOCAL)) ) {
		if ( locked() ) unlock();
		m_hIB->pool->release(m_hIB, usage);
		m_IB_format = 0;
		m_hIB = 0;
	}
	if ( usage&OVRL_IB_CONTAINS_LOCAL ) {
		if ( m_local_IB ) delete[] m_local_IB;
		m_local_IB_format = 0;
	}

	if ( m_local_IB==0 && m_hIB==0 ) {
		m_IB_usage = 0;
		m_IB_length = 0;
	}
	printf("CxfIndexBuffer free done\n");
	return 0;
}

void CxfIndexBuffer::release()
{
	delete this;
}

}