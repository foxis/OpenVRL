// NewCamera.cpp : implementation file
//

#include "stdafx.h"
#include "TPLedit.h"
#include "NewCamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewCamera dialog


CNewCamera::CNewCamera(CWnd* pParent /*=NULL*/)
	: CDialog(CNewCamera::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewCamera)
	//}}AFX_DATA_INIT
}


void CNewCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewCamera)
	DDX_Control(pDX, IDC_BLACKPOINT, m_BlackPoint);
	DDX_Control(pDX, IDC_BRIGHTNESS, m_Brightness);
	DDX_Control(pDX, IDC_WHITEPOINT, m_WhitePoint);
	DDX_Control(pDX, IDC_GAMMA, m_Gamma);
	DDX_Control(pDX, IDC_CONTRAST, m_Contrast);
	DDX_Control(pDX, IDC_VERSION, m_Version);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_LENSRX, m_LensRX);
	DDX_Control(pDX, IDC_LENSRY, m_LensRY);
	DDX_Control(pDX, IDC_FOCUS, m_Focus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewCamera, CDialog)
	//{{AFX_MSG_MAP(CNewCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCamera message handlers

void CNewCamera::OnOK() 
{
	fromUI();	
	
	CDialog::OnOK();
}

BOOL CNewCamera::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( init )
	{
		memset(&m_camera, 0, sizeof(m_camera));
		m_camera.version = TPL_CAMERA_VERSION;
		strcpy(m_camera.signature, TPL_CAMERA_SIG);
	}
	toUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewCamera::toUI()
{
	char str[512];
	sprintf(str, "0x%08x", m_camera.version);
	m_Version.SetWindowText(str);
	m_Name.SetWindowText(m_camera.name);

	sprintf(str, "%2.8f", m_camera.focus);
	m_Focus.SetWindowText(str);
	sprintf(str, "%2.8f", m_camera.dx);
	m_LensRX.SetWindowText(str);
	sprintf(str, "%2.8f", m_camera.dy);
	m_LensRY.SetWindowText(str);

	sprintf(str, "%3.1f", (m_camera.blackpoint/255.0)*100);
	m_BlackPoint.SetWindowText(str);
	sprintf(str, "%3.1f", (m_camera.whitepoint/255.0)*100);
	m_WhitePoint.SetWindowText(str);
	sprintf(str, "%i", (signed int)m_camera.brightness);
	m_Brightness.SetWindowText(str);
	sprintf(str, "%i", (signed int)m_camera.contrast);
	m_Contrast.SetWindowText(str);
	sprintf(str, "%f", m_camera.gamma);
	m_Gamma.SetWindowText(str);
}

void CNewCamera::fromUI()
{
	char str[512];
	m_Name.GetWindowText(m_camera.name, TPL_MAX_NAME_LEN);

	m_Focus.GetWindowText(str, 512);
	m_camera.focus = atof(str);
	m_LensRX.GetWindowText(str, 512);
	m_camera.dx = atof(str);
	m_LensRY.GetWindowText(str, 512);
	m_camera.dy = atof(str);

	m_BlackPoint.GetWindowText(str, 512);
	m_camera.blackpoint = (atof(str)/100.0)*255;
	m_WhitePoint.GetWindowText(str, 512);
	m_camera.whitepoint = (atof(str)/100.0)*255;
	m_Brightness.GetWindowText(str, 512);
	m_camera.brightness = (unsigned char)atoi(str);
	m_Contrast.GetWindowText(str, 512);
	m_camera.contrast = (unsigned char)atoi(str);
	m_Gamma.GetWindowText(str, 512);
	m_camera.gamma = atof(str);
}
