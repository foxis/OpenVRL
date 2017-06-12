// EditVI.cpp : implementation file
//

#include "stdafx.h"
#include "TPLedit.h"
#include "EditVI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditVI dialog


CEditVI::CEditVI(CWnd* pParent /*=NULL*/)
	: CDialog(CEditVI::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditVI)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEditVI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditVI)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_HEX, m_Hex);
	DDX_Control(pDX, IDC_FLOAT, m_Float);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditVI, CDialog)
	//{{AFX_MSG_MAP(CEditVI)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_BFLOAT, OnBfloat)
	ON_BN_CLICKED(IDC_BHEX, OnBhex)
	ON_EN_CHANGE(IDC_FLOAT, OnChangeFloat)
	ON_EN_CHANGE(IDC_HEX, OnChangeHex)
	ON_EN_UPDATE(IDC_FLOAT, OnUpdateFloat)
	ON_EN_UPDATE(IDC_HEX, OnUpdateHex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditVI message handlers

void CEditVI::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CEditVI::OnInitDialog() 
{
	CDialog::OnInitDialog();
	onchange[0]=onchange[1] = false;
	if ( vertex )
	{
		SetWindowText(_T("Edit Vertex data..."));
	}
	else
	{
		SetWindowText(_T("Edit Index data..."));
		if ( bits16 )
			SetDlgItemText(IDC_BFLOAT, _T("<<USHORT"));
		else
			SetDlgItemText(IDC_BFLOAT, _T("<<ULONG"));
	}
	Update(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditVI::Update(openvrl::ulong j)
{
	openvrl::ulong i=0;
	char str[128];

	m_List.SetRedraw(FALSE);
	m_List.ResetContent();
	if ( vertex )
	{
		while ( i<size )
		{
			sprintf(str, "%.12f", *((float*)(data+i)));
			m_List.AddString(str);
			i+=sizeof(float);
		}
	}
	else
	{
		if ( bits16 )	while ( i<size )
		{
			sprintf(str, "%u", (openvrl::ulong)*((openvrl::ushort*)(data+i)));
			m_List.AddString(str);
			i+=sizeof(openvrl::ushort);
		}
		else	while ( i<size )
		{
			sprintf(str, "%lu", *((openvrl::ulong*)(data+i)));
			m_List.AddString(str);
			i+=sizeof(openvrl::ulong);
		}

	}
	m_List.SetRedraw(TRUE);
	m_List.Invalidate(TRUE);
	m_List.SetCurSel(j);
	OnSelchangeList();
}

void CEditVI::OnSelchangeList() 
{
	const long i = m_List.GetCurSel();
	if ( i<0 ) return;
	const float  f = ((float*)data)[i];
	const openvrl::ulong  l = ((openvrl::ulong*)data)[i];
	const openvrl::ushort  ul = ((openvrl::ushort*)data)[i];

	char str[128];

	if ( vertex )
	{
		if ( !onchange[1] ) {
			sprintf(str, "%08lx", l);
			m_Hex.SetWindowText(str);
		}
		if ( !onchange[0] ) {
			sprintf(str, "%.12f", f);
			m_Float.SetWindowText(str);
		}
	}
	else
	{
		if ( bits16 )
		{
			if ( !onchange[1] ) {
				sprintf(str, "%04x", ul);
				m_Hex.SetWindowText(str);
			}
			if ( !onchange[0] ) {
				sprintf(str, "%u", ul);
				m_Float.SetWindowText(str);
			}
		}
		else
		{
			if ( !onchange[1] ) {
				sprintf(str, "%08lx", l);
				m_Hex.SetWindowText(str);
			}
			if ( !onchange[0] ) {
				sprintf(str, "%lu", l);
				m_Float.SetWindowText(str);
			}
		}
	}
}

void CEditVI::OnBfloat() 
{
	const long i = m_List.GetCurSel();
	if ( i<0 ) return;
	CString str;
	m_Float.GetWindowText(str);

	if ( vertex )
	{
		((openvrl::short_real*)data)[i] = (openvrl::short_real)atof(str);
	} else
	{
		if ( bits16 )
		{
			((openvrl::ushort*)data)[i] = atoi(str);
		}
		else
		{
			((openvrl::ulong*)data)[i] = atol(str);
		}
	}
	Update(i);
}

void CEditVI::OnBhex() 
{
	const long i = m_List.GetCurSel();
	if ( i<0 ) return;
	CString str;
	m_Hex.GetWindowText(str);
	openvrl::ulong n;

	if ( vertex )
	{
		sscanf(str, "%8lx", &n);
		((openvrl::ulong*)data)[i] = n;
	}
	else
	{
		if ( bits16 )
		{
			sscanf(str, "%4lx", &n);
			((openvrl::ushort*)data)[i] = (openvrl::ushort)n;
		}
		else
		{
			sscanf(str, "%8lx", &n);
			((openvrl::ulong*)data)[i] = n;
		}
	}
	Update(i);
}

void CEditVI::OnChangeFloat() 
{
	if ( onchange[0] ) return;
	onchange[0] = true;
	OnBfloat();
	onchange[0] = false;
}

void CEditVI::OnChangeHex() 
{
	if ( onchange[1] ) return;
	onchange[1] = true;
	OnBhex();
	onchange[1] = false;
}

void CEditVI::OnUpdateFloat() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CEditVI::OnUpdateHex() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}
