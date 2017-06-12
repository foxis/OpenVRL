// EditMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "TPLedit.h"
#include "EditMatrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditMatrix dialog


CEditMatrix::CEditMatrix(CWnd* pParent /*=NULL*/)
	: CDialog(CEditMatrix::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditMatrix)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEditMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditMatrix)
	DDX_Control(pDX, IDC_EDIT9, m_9);
	DDX_Control(pDX, IDC_EDIT8, m_8);
	DDX_Control(pDX, IDC_EDIT7, m_7);
	DDX_Control(pDX, IDC_EDIT6, m_6);
	DDX_Control(pDX, IDC_EDIT5, m_5);
	DDX_Control(pDX, IDC_EDIT4, m_4);
	DDX_Control(pDX, IDC_EDIT3, m_3);
	DDX_Control(pDX, IDC_EDIT2, m_2);
	DDX_Control(pDX, IDC_EDIT16, m_16);
	DDX_Control(pDX, IDC_EDIT15, m_15);
	DDX_Control(pDX, IDC_EDIT14, m_14);
	DDX_Control(pDX, IDC_EDIT13, m_13);
	DDX_Control(pDX, IDC_EDIT12, m_12);
	DDX_Control(pDX, IDC_EDIT11, m_11);
	DDX_Control(pDX, IDC_EDIT10, m_10);
	DDX_Control(pDX, IDC_EDIT1, m_1);
	DDX_Control(pDX, IDC_AUTOSET, m_Set);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditMatrix, CDialog)
	//{{AFX_MSG_MAP(CEditMatrix)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditMatrix message handlers

void CEditMatrix::OnOK() 
{
	fromUI();
	
	CDialog::OnOK();
}

BOOL CEditMatrix::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	toUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditMatrix::toUI()
{
	char str[1028];
	sprintf(str, "%f", matrix[0]);
	m_1.SetWindowText(str);
	sprintf(str, "%f", matrix[1]);
	m_2.SetWindowText(str);
	sprintf(str, "%f", matrix[2]);
	m_3.SetWindowText(str);
	sprintf(str, "%f", matrix[3]);
	m_4.SetWindowText(str);
	sprintf(str, "%f", matrix[4]);
	m_5.SetWindowText(str);
	sprintf(str, "%f", matrix[5]);
	m_6.SetWindowText(str);
	sprintf(str, "%f", matrix[6]);
	m_7.SetWindowText(str);
	sprintf(str, "%f", matrix[7]);
	m_8.SetWindowText(str);
	sprintf(str, "%f", matrix[8]);
	m_9.SetWindowText(str);
	sprintf(str, "%f", matrix[9]);
	m_10.SetWindowText(str);
	sprintf(str, "%f", matrix[10]);
	m_11.SetWindowText(str);
	sprintf(str, "%f", matrix[11]);
	m_12.SetWindowText(str);
	sprintf(str, "%f", matrix[12]);
	m_13.SetWindowText(str);
	sprintf(str, "%f", matrix[13]);
	m_14.SetWindowText(str);
	sprintf(str, "%f", matrix[14]);
	m_15.SetWindowText(str);
	sprintf(str, "%f", matrix[15]);
	m_16.SetWindowText(str);
}

void CEditMatrix::fromUI()
{
	CString str;
	m_1.GetWindowText(str);
	matrix[0] = atof(str);
	m_2.GetWindowText(str);
	matrix[1] = atof(str);
	m_3.GetWindowText(str);
	matrix[2] = atof(str);
	m_4.GetWindowText(str);
	matrix[3] = atof(str);
	m_5.GetWindowText(str);
	matrix[4] = atof(str);
	m_6.GetWindowText(str);
	matrix[5] = atof(str);
	m_7.GetWindowText(str);
	matrix[6] = atof(str);
	m_8.GetWindowText(str);
	matrix[7] = atof(str);
	m_9.GetWindowText(str);
	matrix[8] = atof(str);
	m_10.GetWindowText(str);
	matrix[9] = atof(str);
	m_11.GetWindowText(str);
	matrix[10] = atof(str);
	m_12.GetWindowText(str);
	matrix[11] = atof(str);
	m_13.GetWindowText(str);
	matrix[12] = atof(str);
	m_14.GetWindowText(str);
	matrix[13] = atof(str);
	m_15.GetWindowText(str);
	matrix[14] = atof(str);
	m_16.GetWindowText(str);
	matrix[15] = atof(str);
}
