// NewRAW.cpp : implementation file
//

#include "stdafx.h"
#include "TPLedit.h"
#include "NewRAW.h"
#include "EditVI.h"
#include "SubsetManager.h"
#include ".\newraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewRAW dialog


CNewRAW::CNewRAW(CWnd* pParent /*=NULL*/)
	: CDialog(CNewRAW::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewRAW)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	init = true;
}


void CNewRAW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewRAW)
	DDX_Control(pDX, IDC_SUBSETS, m_Subsets);
	DDX_Control(pDX, IDC_COMZ, m_COMZ);
	DDX_Control(pDX, IDC_COMX, m_COMX);
	DDX_Control(pDX, IDC_COMY, m_COMY);
	DDX_Control(pDX, IDC_VERTEXSIZE, m_VSize);
	DDX_Control(pDX, IDC_VERTEXLIST, m_VList);
	DDX_Control(pDX, IDC_VERTEXFLAGS, m_VFlags);
	DDX_Control(pDX, IDC_VERTECES, m_Verteces);
	DDX_Control(pDX, IDC_VERSION, m_Version);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_INDEXSIZE, m_ISize);
	DDX_Control(pDX, IDC_INDEXLIST, m_IList);
	DDX_Control(pDX, IDC_INDEXFLAGS, m_IFlags);
	DDX_Control(pDX, IDC_INDECES, m_Indeces);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewRAW, CDialog)
	//{{AFX_MSG_MAP(CNewRAW)
	ON_BN_CLICKED(IDC_BUTTON3, OnImportMesh)
	ON_BN_CLICKED(IDC_BUTTON2, OnImportIndeces)
	ON_BN_CLICKED(IDC_BUTTON1, OnImportVerteces)
	ON_BN_CLICKED(IDC_BUTTON4, OnVResize)
	ON_BN_CLICKED(IDC_BUTTON6, OnIResize)
	ON_LBN_DBLCLK(IDC_VERTEXLIST, OnDblclkVertexlist)
	ON_LBN_DBLCLK(IDC_INDEXLIST, OnDblclkIndexlist)
	ON_BN_CLICKED(IDC_BUTTON7, OnAddVertex)
	ON_BN_CLICKED(IDC_BUTTON8, OnInsertVertex)
	ON_BN_CLICKED(IDC_BUTTON10, OnDeleteVertex)
	ON_BN_CLICKED(IDC_BUTTON11, OnAddFace)
	ON_BN_CLICKED(IDC_BUTTON9, OnInsertFace)
	ON_BN_CLICKED(IDC_BUTTON12, OnDeleteFace)
	ON_BN_CLICKED(IDC_BUTTON14, OnSubsets)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON15, OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, OnBnClickedButton16)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewRAW message handlers

inline openvrl::TPL_BYTE hex2byte(char hex)
{
	if ( hex>='0'&&hex<='9' ) return (openvrl::TPL_BYTE)(hex-'0');
	else
		switch ( hex )
	{
		case 'A': return 10;
		case 'B': return 11;
		case 'C': return 12;
		case 'D': return 13;
		case 'E': return 14;
		case 'F': return 15;
		case 'a': return 10;
		case 'b': return 11;
		case 'c': return 12;
		case 'd': return 13;
		case 'e': return 14;
		case 'f': return 15;
		default:return 0;
	}
}

void hex2raw(openvrl::TPL_BYTE* d, const char* hex)
{
	const openvrl::ulong cb = strlen(hex)&0xFFFFFFFE;
	openvrl::ulong i;
	for ( i=0;i<cb; )
	{
		d[i>>1] = hex2byte(hex[i])*16 + hex2byte(hex[1]);
		i+=2;
	}
}

void raw2hex(char* d, openvrl::TPL_BYTE* raw, openvrl::ulong cb)
{
	char str[3]="";
	openvrl::ulong i;
	*d = 0;
	for ( i=0;i<cb;i++ )
	{
		sprintf(str, "%02X", raw[i]);
		strcat(d, str);
	}
}


void CNewRAW::toUI(int w)
{
	char str[512], tmp[128];
	openvrl::ulong i;
	long j;

	sprintf(str, "0x%08x", m_rawmesh.version);
	m_Version.SetWindowText(str);
	m_Name.SetWindowText(m_rawmesh.name);

	sprintf(str, "%lu", m_rawmesh.verteces);
	m_Verteces.SetWindowText(str);
	sprintf(str, "%lu", m_rawmesh.vertex_size);
	m_VSize.SetWindowText(str);
	sprintf(str, "%04x", m_rawmesh.VB_flags);
	m_VFlags.SetWindowText(str);

	sprintf(str, "%lu", m_rawmesh.faces);
	m_Indeces.SetWindowText(str);
	sprintf(str, "%lu", m_rawmesh.face_size);
	m_ISize.SetWindowText(str);
	sprintf(str, "%04x", m_rawmesh.IB_flags);
	m_IFlags.SetWindowText(str);

	sprintf(str, "%f", m_rawmesh.center_mass.x);
	m_COMX.SetWindowText(str);
	sprintf(str, "%f", m_rawmesh.center_mass.y);
	m_COMY.SetWindowText(str);
	sprintf(str, "%f", m_rawmesh.center_mass.z);
	m_COMZ.SetWindowText(str);

	sprintf(str, "%lu", subsets.size());
	m_Subsets.SetWindowText(str);

	if ( w&U_VERTECES )
	{
		m_VList.ResetContent();
		m_VList.SetRedraw(FALSE);
		for ( i=0;i<m_rawmesh.verteces;i++ )
		{
			j = m_rawmesh.vertex_size;
			str[0] = 0;
			while ( j>0 )
			{
				sprintf(tmp, "%.08f ", *(float*)(VB+(i+1)*m_rawmesh.vertex_size-j));
				strcat(str, tmp);
				j-=sizeof(float);	// show floats
			}
	//		raw2hex(str+strlen(str), VB+i*m_rawmesh.vertex_size,m_rawmesh.vertex_size);
			m_VList.AddString(str);
		}
		m_VList.SetRedraw(TRUE);
		m_VList.Invalidate(TRUE);
	}
	if ( w&U_INDECES )
	{
		m_IList.ResetContent();
		m_IList.SetRedraw(FALSE);
		for ( i=0;i<m_rawmesh.faces;i++ )
		{
			str[0] = 0;
			j = m_rawmesh.face_size;
			if ( m_rawmesh.IB_flags&OVRL_IB_16 )
			{
				while ( j>0 )
				{
					sprintf(tmp, "%4u ", *(openvrl::ushort*)(IB+(i+1)*m_rawmesh.face_size-j));
					strcat(str, tmp);
					j-=sizeof(openvrl::ushort);	// show floats
				}
			}
			else
			{
				while ( j>0 )
				{
					sprintf(tmp, "%8ul ", *(openvrl::ulong*)(IB+(i+1)*m_rawmesh.face_size-j));
					strcat(str, tmp);
					j-=sizeof(openvrl::ulong);	// show floats
				}
			}
	//		raw2hex(str+strlen(str), IB+i*m_rawmesh.face_size,m_rawmesh.face_size);
			m_IList.AddString(str);
		}

		m_IList.SetRedraw(TRUE);
		m_IList.Invalidate(TRUE);
	}
}

void CNewRAW::fromUI()
{
	CString str;
	openvrl::ulong l;
	m_Name.GetWindowText(m_rawmesh.name, TPL_MAX_NAME_LEN);
	m_COMX.GetWindowText(str);
	m_rawmesh.center_mass.x = atof(str);
	m_COMY.GetWindowText(str);
	m_rawmesh.center_mass.y = atof(str);
	m_COMZ.GetWindowText(str);
	m_rawmesh.center_mass.z = atof(str);
	m_VFlags.GetWindowText(str);
	sscanf(str, "%x", &l);
	m_rawmesh.VB_flags = l;
	m_IFlags.GetWindowText(str);
	sscanf(str, "%x", &l);
	m_rawmesh.IB_flags = l;
}

BOOL CNewRAW::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( init )
	{
		memset(&m_rawmesh, 0, sizeof(m_rawmesh));
		m_rawmesh.version = TPL_RAW_VERSION;
		strcpy(m_rawmesh.signature, TPL_RAW_SIG);
		VB = 0; IB = 0;
	}
	toUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewRAW::OnOK() 
{
	fromUI();
	CDialog::OnOK();
}

struct vertex
{
	openvrl::short_real x, y, z;
};

struct uvvertex
{
	openvrl::short_real u, v;
};

int read_geo(const char* str, vertex**vb, openvrl::TPL_BYTE**ib, openvrl::ulong* vbcb, openvrl::ulong* ibcb);
int read_verteces(const char* str, vertex**vb, openvrl::ulong* vbcb);
int read_indices(const char* str, openvrl::ushort**ib, openvrl::ulong* ibcb);
int read_uv(const char* str, vertex**tb, openvrl::ulong* tbcb);

void CNewRAW::OnImportMesh() 
{
	char str[16]=".\\";
	CFileDialog f(TRUE);
	f.m_ofn.lpstrInitialDir = str;
	fromUI();
	if ( f.DoModal() == IDOK )
	{
		if ( VB ) delete[] VB;
		if ( IB ) delete[] IB;
		read_geo(f.GetPathName(), (vertex**)&VB, (openvrl::TPL_BYTE**)&IB, &m_rawmesh.verteces, &m_rawmesh.faces);
		m_rawmesh.vertex_size = sizeof(vertex);
		m_rawmesh.VB_flags = OVRL_VB_XYZ;
		if ( m_rawmesh.verteces<=0xffff )
		{
			m_rawmesh.face_size = sizeof(openvrl::ushort)*3;
			m_rawmesh.IB_flags = OVRL_IB_16;
		}
		else
		{
			m_rawmesh.face_size = sizeof(openvrl::ulong)*3;
			m_rawmesh.IB_flags = OVRL_IB_32;
		}
		toUI();
	}
}

void CNewRAW::OnImportIndeces() 
{
	char str[16]=".\\";
	CFileDialog f(TRUE);
	f.m_ofn.lpstrInitialDir = str;
	fromUI();
	if ( f.DoModal() == IDOK )
	{
		delete[] VB;
		read_indices(f.GetPathName(), (openvrl::ushort**)&IB, &m_rawmesh.faces);
		m_rawmesh.face_size = sizeof(openvrl::ushort)*3;
		m_rawmesh.IB_flags = OVRL_IB_16;
		toUI();
	}	
}

void CNewRAW::OnImportVerteces() 
{
	char str[16]=".\\";
	CFileDialog f(TRUE);
	f.m_ofn.lpstrInitialDir = str;
	fromUI();
	if ( f.DoModal() == IDOK )
	{
		delete[] VB;
		if (read_verteces(f.GetPathName(), (vertex**)&VB, &m_rawmesh.verteces)) return;
		m_rawmesh.vertex_size = sizeof(vertex);
		m_rawmesh.VB_flags = OVRL_VB_XYZ;
		toUI();
	}	
}

void CNewRAW::OnVResize() 
{
	CString str;
	m_VSize.GetWindowText(str);
	fromUI();
	const openvrl::ulong ncb = atoi(str);
	const openvrl::ulong ocb = m_rawmesh.vertex_size;
	openvrl::ulong i;
	openvrl::TPL_BYTE *nVB;
	if ( VB )
	{
		if ( ncb>>2==0 ) return;
		nVB = new openvrl::TPL_BYTE[ncb*m_rawmesh.verteces];
		memset(nVB, 0, ncb*m_rawmesh.verteces);
		if ( ncb>m_rawmesh.vertex_size )
		{
			for ( i=0;i<m_rawmesh.verteces;i++ )
				memcpy(nVB+i*ncb, VB+i*ocb, ocb);
		}
		else
		{
			for ( i=0;i<m_rawmesh.verteces;i++ )
				memcpy(nVB+i*ncb, VB+i*ocb, ncb);
		}
		delete[] VB;
		VB = nVB;
		m_rawmesh.vertex_size = ncb;
	}
	else
	{
		m_rawmesh.vertex_size = ncb;
	}
	toUI();
}

void CNewRAW::OnIResize() 
{
	CString str;
	m_ISize.GetWindowText(str);
	fromUI();
	const openvrl::ulong ncb = atoi(str);
	const openvrl::ulong ocb = m_rawmesh.face_size;
	openvrl::ulong i;
	openvrl::TPL_BYTE *nIB;
	if ( IB )
	{
		if ( ncb>>2==0 ) return;
		nIB = new openvrl::TPL_BYTE[ncb*m_rawmesh.faces];
		memset(nIB, 0, ncb*m_rawmesh.faces);
		if ( ncb>m_rawmesh.face_size )
		{
			for ( i=0;i<m_rawmesh.faces;i++ )
				memcpy(nIB+i*ncb, IB+i*ocb, ocb);
		}
		else
		{
			for ( i=0;i<m_rawmesh.faces;i++ )
				memcpy(nIB+i*ncb, IB+i*ocb, ncb);
		}
		delete[] IB;
		IB = nIB;
		m_rawmesh.face_size = ncb;
	}
	else
	{
		m_rawmesh.face_size = ncb;
	}
	toUI();
}

void CNewRAW::OnSubsets() 
{
	CSubsetManager	sm;
	fromUI();
	sm.subsets = &subsets;
	sm.verteces = m_rawmesh.verteces;
	sm.indeces = m_rawmesh.faces*3;
	if ( sm.DoModal()==IDOK )
	{
		toUI(U_NONE);
	}
}

typedef struct DWORD_poly_struct
{
  openvrl::DWORD index;
  openvrl::DWORD ned;
} DWORD_poly_t ;

/**
 *  some pieces of code borrowed from SCITECH MESA MGL library and ported
 *  to my code... eghrrr...
 */
int read_geo(const char* str, vertex**vb, openvrl::TPL_BYTE**ib, openvrl::ulong* vbcb, openvrl::ulong* ibcb)
{
	openvrl::ulong verteces, polys, edges;
	openvrl::ulong ned;
	openvrl::ulong *edgedata;
	openvrl::ulong tmp;
	openvrl::ulong *e;
	openvrl::DWORD tris;
	openvrl::DWORD i, nedges;
	openvrl::DWORD j, i1;
	DWORD_poly_t *polyverts;
	openvrl::short_real fx, fy, fz;
	FILE* fp;

	fp = fopen(str, "rt");

	if ( fscanf(fp, "%lu %lu %lu", &verteces, &polys, &edges) != 3 ) {
		openvrl::ovrl_warning("Could not read geometry header!");
	       return 1;
	}

	edgedata = new openvrl::ulong [edges*2];
	polyverts = new DWORD_poly_t[polys*2];
	*vb = new vertex[verteces+1];
	TPL_ASSERT(edgedata);
	TPL_ASSERT(polyverts);
	TPL_ASSERT(*vb);

	for ( i=0;i<verteces;i++ ) {
	    if ( fscanf(fp, "%f %f %f", &fx, &fy, &fz) != 3 ) {
		     openvrl::ovrl_warning("Could not read verteces!");
		     return 1;
	    }
	    (*vb)[i].x = fx;
	    (*vb)[i].y = fy;
	    (*vb)[i].z = fz;
	}

	for ( tris=0,nedges=0,i=0,j=0;i<polys;i++ )  {
	    fscanf(fp, "%lu", &ned);

	    polyverts[i].index = j;
	    polyverts[i].ned = ned;

	    for ( i1=0;i1<ned;i1++,j++ ) {
		  if ( j>=edges ) {
		       openvrl::ovrl_warning("Edges != read Edges !!!");
		       return 1;
		  }
		  if ( fscanf(fp, "%lu", &tmp)!=1 ) {
		     openvrl::ovrl_warning("Could not read polygon edges!");
		     return 1;
		  }
		  edgedata[j] = tmp-1;
	    }
	}
	nedges = j;

	if ( nedges!=edges ) {
	     openvrl::ovrl_warning("Edges != read Edges !!!");
	     return 1;
	}

	e = edgedata;
	for ( tris=0,i=0;i<polys;i++ ) {
	      if ( polyverts[i].ned<3 ) continue;
	      for ( i1=1;i1<polyverts[i].ned-1;i1++ ) {
			tris++;
		  }
	}
	if ( verteces<=0xFFFF )
		*ib = (openvrl::TPL_BYTE*)new openvrl::ushort[(tris+1)*3];
	else
		*ib = (openvrl::TPL_BYTE*)new openvrl::ulong[(tris+1)*3];
	TPL_ASSERT(*ib);
	*vbcb = verteces;
	*ibcb = tris;

	if ( verteces<=0xFFFF )
		for ( tris=0,i=0;i<polys;i++ ) {
			if ( polyverts[i].ned<3 ) continue;
			for ( i1=1;i1<polyverts[i].ned-1;i1++ ) {
				(*(openvrl::ushort**)ib)[tris++] = edgedata[polyverts[i].index];
				(*(openvrl::ushort**)ib)[tris++] = edgedata[polyverts[i].index+i1];
				(*(openvrl::ushort**)ib)[tris++] = edgedata[polyverts[i].index+i1+1];
			}
		}
	else
		for ( tris=0,i=0;i<polys;i++ ) {
			if ( polyverts[i].ned<3 ) continue;
			for ( i1=1;i1<polyverts[i].ned-1;i1++ ) {
				(*(openvrl::ulong**)ib)[tris++] = edgedata[polyverts[i].index];
				(*(openvrl::ulong**)ib)[tris++] = edgedata[polyverts[i].index+i1];
				(*(openvrl::ulong**)ib)[tris++] = edgedata[polyverts[i].index+i1+1];
			}
		}

	fclose(fp);

	return 0;
}

int read_verteces(const char* str, vertex**vb, openvrl::ulong* vbcb)
{
	openvrl::ulong verteces;
	openvrl::DWORD i;
	openvrl::short_real fx, fy, fz;
	FILE* fp;

	fp = fopen(str, "rt");

	if ( fscanf(fp, "%lu\n", &verteces) != 3 ) {
		openvrl::ovrl_warning("Could not read geometry header!");
	       return 1;
	}

	*vb = new vertex[verteces+1];
	TPL_ASSERT(*vb);

	for ( i=0;i<verteces;i++ ) {
	    if ( fscanf(fp, "%f %f %f", &fx, &fy, &fz) != 3 ) {
		     openvrl::ovrl_warning("Could not read verteces!");
		     return 1;
	    }
	    (*vb)[i].x = fx;
	    (*vb)[i].y = fy;
	    (*vb)[i].z = fz;
	}
	fclose(fp);
	*vbcb = verteces;

	return 0;
}

int read_indices(const char* str, openvrl::ushort**ib, openvrl::ulong* ibcb)
{
	openvrl::ulong indices;
	openvrl::DWORD i;
	int a, b, c;
	FILE* fp;

	fp = fopen(str, "rt");

	if ( fscanf(fp, "%lu\n", &indices) != 3 ) {
		openvrl::ovrl_warning("Could not read geometry header!");
	       return 1;
	}

	*ib = new openvrl::ushort[indices+1];
	TPL_ASSERT(*ib);

	for ( i=0;i<indices; ) {
	    if ( fscanf(fp, "%i %i %i\n", &a, &b, &c) != 3 ) {
		     openvrl::ovrl_warning("Could not read verteces!");
		     return 1;
	    }
		(*ib)[i++] = (openvrl::ushort)a;
	    (*ib)[i++] = (openvrl::ushort)b;
	    (*ib)[i++] = (openvrl::ushort)c;
	}
	fclose(fp);
	*ibcb = indices;

	return 0;
}

int read_uv(const char* str, uvvertex**tb, openvrl::ulong* tbcb)
{
	openvrl::ulong verteces;
	openvrl::DWORD i;
	openvrl::short_real fu, fv;
	FILE* fp;

	fp = fopen(str, "rt");

	if ( fscanf(fp, "%lu\n", &verteces) != 1 ) {
		openvrl::ovrl_warning("Could not read geometry header!");
	       return 1;
	}

	*tb = new uvvertex[verteces+1];
	TPL_ASSERT(*tb);

	for ( i=0;i<verteces;i++ ) {
	    if ( fscanf(fp, "%f %f", &fu, &fv) != 2 ) {
		     openvrl::ovrl_warning("Could not read verteces!");
		     return 1;
	    }
	    (*tb)[i].u = fu;
	    (*tb)[i].v = fv;
	}
	fclose(fp);
	*tbcb = verteces;

	return 0;
}


void CNewRAW::OnDblclkVertexlist() 
{
	CEditVI vi;
	const openvrl::ulong i = m_VList.GetCurSel();
	vi.vertex = true;
	vi.size = m_rawmesh.vertex_size;
	vi.data = new openvrl::TPL_BYTE[vi.size];
	memcpy(vi.data, VB + m_rawmesh.vertex_size*i, vi.size);
	if ( vi.DoModal()==IDOK )
	{
		memcpy(VB+m_rawmesh.vertex_size*i, vi.data, vi.size);
		toUI();
		m_VList.SetCurSel(i);
	}
	delete[] vi.data;
}

void CNewRAW::OnDblclkIndexlist() 
{
	CEditVI vi;
	const openvrl::ulong i = m_IList.GetCurSel();
	vi.vertex = false;
	vi.bits16 = !!(m_rawmesh.IB_flags&OVRL_IB_16);
	vi.size = m_rawmesh.face_size;
	vi.data = new openvrl::TPL_BYTE[vi.size];
	memcpy(vi.data, IB+vi.size*i, vi.size);
	if ( vi.DoModal()==IDOK )
	{
		memcpy(IB+vi.size*i, vi.data, vi.size);
		toUI();
		m_IList.SetCurSel(i);
	}
	delete[] vi.data;
}

void CNewRAW::OnAddVertex() 
{
	// TODO: Add your control notification handler code here
	
}

void CNewRAW::OnInsertVertex() 
{
	// TODO: Add your control notification handler code here
	
}

void CNewRAW::OnDeleteVertex() 
{
	// TODO: Add your control notification handler code here
	
}

void CNewRAW::OnAddFace() 
{
	// TODO: Add your control notification handler code here
	
}

void CNewRAW::OnInsertFace() 
{
	// TODO: Add your control notification handler code here
	
}

void CNewRAW::OnDeleteFace() 
{
	// TODO: Add your control notification handler code here
	
}

void CNewRAW::OnBnClickedButton15()
{
	// OnImportUV
	char str[16]=".\\";
	CFileDialog f(TRUE);
	f.m_ofn.lpstrInitialDir = str;
	fromUI();
	uvvertex* tb;
	openvrl::ulong num;

	if ( VB==0 )
		return;

	if ( f.DoModal() == IDOK )
	{
		read_uv(f.GetPathName(), &tb, &num);

		if ( num==m_rawmesh.verteces && num!=0 )
		{
			const openvrl::ulong ncb = m_rawmesh.vertex_size+sizeof(uvvertex);
			const openvrl::ulong ocb = m_rawmesh.vertex_size;
			openvrl::ulong i;
			openvrl::TPL_BYTE *nVB;
			
			if ( ncb>>2==0 ) 
			{
				delete[] tb;
				return;
			}

			nVB = new openvrl::TPL_BYTE[ncb*m_rawmesh.verteces];

			for ( i=0;i<m_rawmesh.verteces;i++ )
			{
				memcpy(nVB+i*ncb, VB+i*ocb, ocb);
				memcpy(nVB+i*ncb+ocb, tb+i, ncb-ocb);
			}

			delete[] VB;
			VB = nVB;
			m_rawmesh.vertex_size = ncb;
			m_rawmesh.VB_flags = OVRL_VB_XYZ | OVRL_VB_TX1;
			toUI();
		}
	}	
	delete[] tb;
}

void CNewRAW::OnBnClickedButton16()
{
	char str[16]=".\\";
	CFileDialog f(TRUE);
	f.m_ofn.lpstrInitialDir = str;
	fromUI();
	if ( f.DoModal() == IDOK )
	{
		vertex* lVB;
		openvrl::TPL_BYTE* lIB;
		openvrl::TPL_DWORD vn, fn;

		if ( !read_geo(f.GetPathName(), (vertex**)&lVB, (openvrl::TPL_BYTE**)&lIB, &vn, &fn) &&vn>0 && fn>0 )
		{
			vertex* tVB;
			openvrl::ushort* tIB;

			CSubsetManager	sm;
			fromUI();
			sm.subsets = &subsets;
			sm.verteces = vn+m_rawmesh.verteces;
			sm.indeces = (fn+m_rawmesh.faces)*3;
			sm.start_vertex = m_rawmesh.verteces;
			sm.start_index = m_rawmesh.faces*3;
			if ( sm.DoModal()!=IDOK )
				return;

			tVB = new vertex[vn+m_rawmesh.verteces];
			tIB = new openvrl::ushort[fn+m_rawmesh.faces];
			OVRL_memcpy(tVB, VB, sizeof(vertex)*m_rawmesh.verteces);
			OVRL_memcpy(tIB, IB, sizeof(openvrl::ushort)*m_rawmesh.verteces);
			OVRL_memcpy(tVB+m_rawmesh.verteces, lVB, sizeof(vertex)*vn);

			for ( openvrl::ulong i=0;i<fn;i++ )
				tIB[i+m_rawmesh.faces] = lIB[i]+m_rawmesh.verteces;

			m_rawmesh.verteces += vn;
			m_rawmesh.faces += fn;
			m_rawmesh.vertex_size = sizeof(vertex);
			m_rawmesh.face_size = sizeof(openvrl::ushort)*3;
			m_rawmesh.IB_flags = OVRL_IB_16;
			m_rawmesh.VB_flags = OVRL_VB_XYZ;

			delete[] VB;
			delete[] IB;
			delete[] lVB;
			delete[] lIB;
			VB = (openvrl::TPL_BYTE*)tVB;
			IB = (openvrl::TPL_BYTE*)tIB;
			toUI();
		}
	}
}
