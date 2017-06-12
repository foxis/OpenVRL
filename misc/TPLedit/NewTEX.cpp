// NewTEX.cpp : implementation file
//

#include "stdafx.h"
#include "TPLEdit.h"
#include "NewTEX.h"
#include ".\newtex.h"


// CNewTEX dialog

IMPLEMENT_DYNAMIC(CNewTEX, CDialog)
CNewTEX::CNewTEX(CWnd* pParent /*=NULL*/)
	: CDialog(CNewTEX::IDD, pParent)
	, m_Version(_T(""))
	, m_Name(_T(""))
	, m_texFName(_T(""))
{
	init = true;
}

CNewTEX::~CNewTEX()
{
}

void CNewTEX::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VERSION, m_Version);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT1, m_texFName);
}


BEGIN_MESSAGE_MAP(CNewTEX, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()



void CNewTEX::fromUI()
{
	UpdateData(true);
	strncpy(m_tex.head.name, m_Name, TPL_MAX_NAME_LEN);
	if ( m_tex.data ) delete[] m_tex.data;
	m_tex.data = new char[strlen(m_texFName)+1];
	m_tex.head.data_size = strlen(m_texFName)+1;
	strcpy((char*)m_tex.data, m_texFName);
	m_tex.head.styles = TPL_TEX_PATH;
}

void CNewTEX::toUI()
{
	m_Version.Format("0x%08X", m_tex.head.version);
	m_Name.Format("%s", m_tex.head.name);
	if ( m_tex.head.styles==TPL_TEX_PATH )
	{
		m_texFName.Format("%s", (char*)m_tex.data);
	}
	else
	{
		// not supported
	}
	UpdateData(false);
}


// CNewTEX message handlers

void CNewTEX::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}

BOOL CNewTEX::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	if ( init )
	{
		memset(&m_tex.head, 0, sizeof(m_tex.head));
		m_tex.head.version = TPL_MAT_VERSION;
		strcpy(m_tex.head.signature, TPL_TEX_SIG);
	}
	toUI();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CNewTEX::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	fromUI();
	OnOK();
}
