#include "common/all.h"
#include "system/ovrlsystem.h"
#include "xfactory/xfvertexbuf.h"
#include "iosystem/fileiodev.h"
#include "system/ovrllog.h"

namespace openvrl {

/***************************************************************************** 
 * CxfVertexBufferList class
 *****************************************************************************/

CxfVertexBufferList::CxfVertexBufferList(CxFactory* xf)
	:CxFactoryListTemplate<CxfVertexBuffer, CxfVertexBufferList>(xf)
{
}

CxfVertexBufferList::~CxfVertexBufferList()
{
}

CxfVertexBuffer* CxfVertexBufferList::create(ulong length, WORD format, DWORD usage, const CString& name, const BYTE* buf)
{
	static ulong cnt=0;
	char str[32]="";
	CxfVertexBuffer* tmp;

//	printf("CxfVertexBufferList: create: %i %x %x, '%s'\n", length, (int) format, (int) usage, name.c_str());
//	printf("CxfVertexBufferList: %p %p\n", name, name.c_str());

	if ( OVRL_ISSTREMPTY(name.c_str()) )
	{
//	printf("CxfVertexBufferList: create: str %p, %i\n", str, cnt);
		sprintf(str, "%08x%08x%08x", (int)length, (int)format, (int)cnt++);	// generate "random" name
//	printf("CxfVertexBufferList: create: str '%s'\n", str);
		tmp = create(str);
	}
	else
	{
//	printf("CxfVertexBufferList: create otherwise\n");
		tmp = create(name);
	}

//	printf("CxfVertexBufferList: create: '%s' %p\n", str, tmp);

	tmp->create(length, format, usage, buf);
//	printf("CxfVertexBufferList: create done\n", str, tmp);
	return tmp;
}


int CxfVertexBufferList::load_library(const CString& path, const CString& pattern, DWORD flags)
{
	CFileIOD f(0);
	CTPLLib	tpl(&f, "Test TPL file", 1, 1);
//	CLog log("load_library", "material.log");
	int rc;

	if ( tpl.open(path.c_str(), IOD_RDWR) )
	{
			ovrl_warning("xfVertexBufferList: Couldn't open template...");
//			log<<"couldnt open template..."<<"\n";
	}

	rc = load_library(&tpl, pattern, flags);

	tpl.close();
	return rc;
}

int CxfVertexBufferList::load_library(CTPLLib* tpl, const CString& pattern, DWORD flags)
{
	ulong i;
	CxfVertexBuffer* vb;

	for ( i=0;i<tpl->rawmeshes();i++ ) if ( pattern==tpl->rawmesh(i)->name && find(tpl->rawmesh(i)->name)!=0 ) {
		vb = create(tpl->rawmesh(i)->verteces, tpl->rawmesh(i)->VB_flags|OVRL_VB_NORMAL, flags, tpl->rawmesh(i)->name, tpl->rawmesh(i)->VB);
		OVRL_ASSERT_EX(vb, GENERAL, "Failed to create vertex buffer");
	}
	
	return 0;
}

int CxfVertexBufferList::save_library(const CString& path)
{
	return 1;
}
int CxfVertexBufferList::save_library(CTPLLib* tpl)
{
	return 1;
}

/***************************************************************************** 
 * CxfVertexBuffer class
 *****************************************************************************/
CxfVertexBuffer::CxfVertexBuffer(CxfVertexBufferList* xfl) 
	: CxFactoryTemplate<CxfVertexBufferList, CxfVertexBuffer>(xfl),
	m_VB_usage(0),	m_local_VB_format(0),	m_VB_format(0),
	m_local_VB_length(0),	m_VB_length(0),	m_local_VB(0),
	m_locked_VB(0),	m_hVB(0)
{
}

CxfVertexBuffer::~CxfVertexBuffer()
{
}


/** 
 * Calculates number of bytes given vertex type accupies in memory
 */
ulong CxfVertexBuffer::calculate_vertex_size(WORD fmt) const
{
	WORD cb=0;
    if ( fmt&OVRL_VB_XYZ ) cb+= 3*sizeof(float);
    if ( fmt&OVRL_VB_RHW ) cb+= sizeof(float);
    if ( fmt&OVRL_VB_B1 ) cb+= sizeof(float);
    if ( fmt&OVRL_VB_B2 ) cb+= sizeof(float);
    if ( fmt&OVRL_VB_B3 ) cb+= sizeof(float);
    if ( fmt&OVRL_VB_B4 ) cb+= sizeof(float);
    if ( fmt&OVRL_VB_NORMAL ) cb+= 3*sizeof(float);
    if ( fmt&OVRL_VB_PSIZE ) cb+= sizeof(float);
    if ( fmt&OVRL_VB_DIFFUSE ) cb+= 4;
    if ( fmt&OVRL_VB_SPECULAR ) cb+= 4;
    if ( fmt&OVRL_VB_TX1 ) cb+= 2*sizeof(float);
    if ( fmt&OVRL_VB_TX2 ) cb+= 2*sizeof(float);
    if ( fmt&OVRL_VB_TX3 ) cb+= 2*sizeof(float);
    if ( fmt&OVRL_VB_TX4 ) cb+= 2*sizeof(float);
    if ( fmt&OVRL_VB_MASS ) cb+= sizeof(float);
    if ( fmt&OVRL_VB_BONE_ID ) cb+= sizeof(DWORD);

	return cb;
}

/**
 * Copies one vertex with fmt sfmt into a vertex with fmt dfmt
 */
ulong CxfVertexBuffer::copy_vertex(const BYTE* src, WORD sfmt, BYTE* dst, WORD dfmt) const
{
	BYTE* dst1 = dst;
    if ( dfmt&OVRL_VB_XYZ ) { if ( sfmt&OVRL_VB_XYZ ) memcpy(dst, src, 3*sizeof(float)); else memset(dst, 0, 3*sizeof(float)); dst+=3*sizeof(float); }
    if ( sfmt&OVRL_VB_XYZ ) src+= 3*sizeof(float);
    if ( dfmt&OVRL_VB_RHW ) { if ( sfmt&OVRL_VB_RHW ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sfmt&OVRL_VB_RHW ) src+= sizeof(float);
    if ( dfmt&OVRL_VB_B1 ) { if ( sfmt&OVRL_VB_B1 ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sfmt&OVRL_VB_B1 ) src+= sizeof(float);
    if ( dfmt&OVRL_VB_B2 ) { if ( sfmt&OVRL_VB_B2 ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sfmt&OVRL_VB_B2 ) src+= sizeof(float);
    if ( dfmt&OVRL_VB_B3 ) { if ( sfmt&OVRL_VB_B3 ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sfmt&OVRL_VB_B3 ) src+= sizeof(float);
    if ( dfmt&OVRL_VB_B4 ) { if ( sfmt&OVRL_VB_B4 ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sfmt&OVRL_VB_B4 ) src+= sizeof(float);
    if ( dfmt&OVRL_VB_NORMAL ) { if ( sfmt&OVRL_VB_NORMAL ) memcpy(dst, src, 3*sizeof(float)); else memset(dst, 0, 3*sizeof(float)); dst+=3*sizeof(float); }
    if ( sfmt&OVRL_VB_NORMAL ) src+= 3*sizeof(float);
    if ( dfmt&OVRL_VB_PSIZE ) { if ( sfmt&OVRL_VB_PSIZE ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sfmt&OVRL_VB_PSIZE ) src+= sizeof(float);
    if ( dfmt&OVRL_VB_DIFFUSE ) { if ( sfmt&OVRL_VB_DIFFUSE ) memcpy(dst, src, 4*sizeof(BYTE)); else memset(dst, 0, 4*sizeof(BYTE)); dst+=4*sizeof(BYTE); }
    if ( sfmt&OVRL_VB_DIFFUSE ) src+= 4*sizeof(BYTE);
    if ( dfmt&OVRL_VB_SPECULAR ) { if ( sfmt&OVRL_VB_SPECULAR ) memcpy(dst, src, 4*sizeof(BYTE)); else memset(dst, 0, 4*sizeof(BYTE)); dst+=4*sizeof(BYTE); }
    if ( sfmt&OVRL_VB_SPECULAR ) src+= 4*sizeof(BYTE);
    if ( dfmt&OVRL_VB_TX1 ) { if ( sfmt&OVRL_VB_TX1 ) memcpy(dst, src, 2*sizeof(float)); else memset(dst, 0, 2*sizeof(float)); dst+=2*sizeof(float); }
    if ( sfmt&OVRL_VB_TX1 ) src+= 2*sizeof(float);
    if ( dfmt&OVRL_VB_TX2 ) { if ( sfmt&OVRL_VB_TX2 ) memcpy(dst, src, 2*sizeof(float)); else memset(dst, 0, 2*sizeof(float)); dst+=2*sizeof(float); }
    if ( sfmt&OVRL_VB_TX2 ) src+= 2*sizeof(float);
    if ( dfmt&OVRL_VB_TX3 ) { if ( sfmt&OVRL_VB_TX3 ) memcpy(dst, src, 2*sizeof(float)); else memset(dst, 0, 2*sizeof(float)); dst+=2*sizeof(float); }
    if ( sfmt&OVRL_VB_TX3 ) src+= 2*sizeof(float);
    if ( dfmt&OVRL_VB_TX4 ) { if ( sfmt&OVRL_VB_TX4 ) memcpy(dst, src, 2*sizeof(float)); else memset(dst, 0, 2*sizeof(float)); dst+=2*sizeof(float); }
    if ( sfmt&OVRL_VB_TX4 ) src+= 2*sizeof(float);
    if ( dfmt&OVRL_VB_MASS ) { if ( sfmt&OVRL_VB_MASS ) memcpy(dst, src, sizeof(float)); else memset(dst, 0, sizeof(float)); dst+=sizeof(float); }
    if ( sfmt&OVRL_VB_MASS ) src+= sizeof(float);
    if ( dfmt&OVRL_VB_BONE_ID ) { if ( sfmt&OVRL_VB_BONE_ID ) memcpy(dst, src, sizeof(DWORD)); else memset(dst, 0, sizeof(DWORD)); dst+=sizeof(DWORD); }
    if ( sfmt&OVRL_VB_BONE_ID ) src+= sizeof(DWORD);

	return (ulong)(dst-dst1);
}


ulong CxfVertexBuffer::copy_VB_to_local()
{
	if ( m_VB_length==0 || m_local_VB==0 || m_locked_VB==0 ) return 0;
	return copy_to_local(m_locked_VB, m_VB_length, m_VB_format);
}

ulong CxfVertexBuffer::copy_local_to_VB()
{
	if ( m_VB_length==0 || m_local_VB==0 || m_locked_VB==0 ) return 0;
	return copy_from_local(m_locked_VB, m_VB_length, m_VB_format);
}

ulong CxfVertexBuffer::copy_to_local(const BYTE* sVB, ulong length, WORD fmt)
{
	ulong cb, dcb, wcb, dvcb, svcb;
	BYTE *dVB;
	if ( m_VB_length==0 || m_local_VB==0 || sVB==0 || !(m_VB_usage&OVRL_VB_CONTAINS_LOCAL) ) return 0;

	dVB = m_local_VB;
	dvcb = calculate_vertex_size(m_local_VB_format);
	svcb = calculate_vertex_size(fmt);
	dcb = (length<=m_VB_length)?(length*dvcb):(m_VB_length*dvcb);
	wcb = 0;
	cb = 0;
	while ( (cb+wcb)<=dcb ) 
	{
		wcb = copy_vertex(sVB, fmt, dVB, m_local_VB_format);
		sVB += svcb;
		dVB += dvcb;
		cb += wcb;
	}

	return cb;
}

ulong CxfVertexBuffer::copy_from_local(BYTE* dVB, ulong length, WORD fmt)
{
	ulong cb, dcb, wcb, dvcb, svcb;
	BYTE *sVB;
	if ( m_VB_length==0 || m_local_VB==0 || dVB==0 || !(m_VB_usage&OVRL_VB_CONTAINS_LOCAL) ) return 0;

	sVB = m_local_VB;
	svcb = calculate_vertex_size(m_local_VB_format);
	dvcb = calculate_vertex_size(fmt);
	dcb = (length<=m_VB_length)?(length*dvcb):(m_VB_length*svcb);
	wcb = 0;
	cb = 0;
	while ( (cb+wcb)<=dcb ) 
	{
		wcb = copy_vertex(sVB, m_local_VB_format, dVB, fmt);
		sVB += svcb;
		dVB += dvcb;
		cb += wcb;
	}

	return cb;
}

ulong CxfVertexBuffer::copy_to_VB(const BYTE* sVB, ulong length, WORD fmt)
{
	ulong cb, dcb, wcb, dvcb, svcb;
	BYTE *dVB;
	if ( m_VB_length==0 || m_locked_VB==0 || sVB==0 ) return 0;

	dVB = m_locked_VB;
	dvcb = calculate_vertex_size(m_VB_format);
	svcb = calculate_vertex_size(fmt);
	dcb = (length<=m_VB_length)?(length*dvcb):(m_VB_length*svcb);
	wcb = 0;
	cb = 0;
	while ( (cb+wcb)<=dcb ) 
	{
		wcb = copy_vertex(sVB, m_VB_format, dVB, fmt);
		sVB += svcb;
		dVB += dvcb;
		cb += wcb;
	}

	return cb;
}

ulong CxfVertexBuffer::copy_from_VB(BYTE* dVB, ulong length, WORD fmt)
{
	ulong cb, dcb, wcb, dvcb, svcb;
	BYTE *sVB;
	if ( m_VB_length==0 || m_locked_VB==0 || dVB==0 ) return 0;

	sVB = m_locked_VB;
	svcb = calculate_vertex_size(m_VB_format);
	dvcb = calculate_vertex_size(fmt);
	dcb = (length<=m_VB_length)?(length*dvcb):(m_VB_length*svcb);
	wcb = 0;
	cb = 0;
	while ( (cb+wcb)<=dcb ) 
	{
		wcb = copy_vertex(sVB, m_VB_format, dVB, fmt);
		sVB += svcb;
		dVB += dvcb;
		cb += wcb;
	}

	return cb;
}

int CxfVertexBuffer::set_local_format(WORD fmt)
{
	BYTE* lVB, *ltmp;
	WORD ftmp;
	if ( m_VB_length==0 || m_local_VB==0 || !(m_VB_usage&OVRL_VB_CONTAINS_LOCAL) ) return 1;

	lVB = new BYTE[m_VB_length*calculate_vertex_size(fmt)];
	if ( lVB==0 ) return 1;
	ltmp = m_local_VB;
	m_local_VB = lVB;
	ftmp = m_local_VB_format;
	m_local_VB_format = fmt;
	if ( copy_to_local(ltmp, m_VB_length, ftmp)==0 ) { delete[] ltmp; return 1; }
	delete[] ltmp;
	return 0;
}

int CxfVertexBuffer::set_VB_format(WORD fmt)
{
	return 0;
}


/**
 * 
 */
int CxfVertexBuffer::create(ulong length, WORD format, DWORD usage, const BYTE* buf)
{
	const ulong cb = length*calculate_vertex_size(format);

	if ( (usage&OVRL_VB_LOCAL_ONLY)!=OVRL_VB_LOCAL_ONLY ) 
	{
//	printf("CxfVertexBuffer: create  (usage&OVRL_VB_LOCAL_ONLY)!=OVRL_VB_LOCAL_ONLY\n");
		if ( m_hVB || m_locked_VB ) return 1;
		m_hVB = xList()->xFactory()->System()->Pipeline()->VBPool()->create(length, format, usage, buf);
//	printf("CxfVertexBuffer: create  (usage&OVRL_VB_LOCAL_ONLY)!=OVRL_VB_LOCAL_ONLY done\n");
		OVRL_ASSERT(m_hVB);
		m_VB_format =  format;
	}

	if ( usage&OVRL_VB_CONTAINS_LOCAL ) {
		if ( m_local_VB || m_local_VB_format ) return 1;
//	printf("CxfVertexBuffer: create  usage&OVRL_VB_CONTAINS_LOCAL  %i\n", cb);
		m_local_VB = new BYTE[cb];
//	printf("CxfVertexBuffer: create  usage&OVRL_VB_CONTAINS_LOCAL %p\n", m_local_VB);
		OVRL_ASSERT(m_local_VB);
		if ( buf==0 )  
			memset(m_local_VB, 0, cb);
		else
			memcpy(m_local_VB, buf, cb);
		m_local_VB_format = format;
	}

	// create default vertex shader
//	printf("CxfVertexBuffer: create vs\n");
	m_VertexShader = xList()->xFactory()->vertex_shaders->create(format);
	OVRL_ASSERT(m_VertexShader);
//	printf("CxfVertexBuffer: create vs done\n");

	m_VB_usage = usage;
	m_VB_length = length;
	return 0;
}

int CxfVertexBuffer::lock(ulong offset, ulong size)
{
	if ( locked() || m_hVB==0 ) return 1;
	m_locked_VB = m_hVB->pool->lock(m_hVB, offset, size);
	return 0; 
}

int CxfVertexBuffer::unlock()
{
	if ( !locked() || m_hVB==0 ) return 1;
	m_hVB->pool->unlock(m_hVB);
	m_locked_VB = 0;
	return 0; 
}


int CxfVertexBuffer::free(DWORD usage)
{
	if ( !(usage&(OVRL_VB_LOCAL_ONLY|~OVRL_VB_CONTAINS_LOCAL)) ) {
		if ( locked() ) unlock();
		m_hVB->pool->release(m_hVB, usage);
		m_VB_format = 0;
		m_hVB = 0;
	}
	if ( usage&OVRL_VB_CONTAINS_LOCAL ) {
		if ( m_local_VB ) delete[] m_local_VB;
		m_local_VB_format = 0;
	}

	if ( m_local_VB==0 && m_hVB==0 ) {
		m_VB_usage = 0;
		m_VB_length = 0;
	}
	return 0;
}

void CxfVertexBuffer::release()
{
	delete this;
}

}