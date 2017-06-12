// NewLight.cpp : implementation file
//

#include "stdafx.h"
#include "TPLedit.h"
#include "NewLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewLight dialog


CNewLight::CNewLight(CWnd* pParent /*=NULL*/)
	: CDialog(CNewLight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewLight)
	//}}AFX_DATA_INIT
}


void CNewLight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewLight)
	DDX_Control(pDX, IDC_TYPE, m_Type);
	DDX_Control(pDX, IDC_VERSION, m_Version);
	DDX_Control(pDX, IDC_THETA, m_Theta);
	DDX_Control(pDX, IDC_SPECULARR, m_SpecularR);
	DDX_Control(pDX, IDC_SPECULARG, m_SpecularG);
	DDX_Control(pDX, IDC_SPECULARB, m_SpecularB);
	DDX_Control(pDX, IDC_SPECULARA, m_SpecularA);
	DDX_Control(pDX, IDC_PHI, m_Phi);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_FALLOFF, m_Falloff);
	DDX_Control(pDX, IDC_DIFFUSER, m_DiffuseR);
	DDX_Control(pDX, IDC_DIFFUSEG, m_DiffuseG);
	DDX_Control(pDX, IDC_DIFFUSEB, m_DiffuseB);
	DDX_Control(pDX, IDC_DIFFUSEA, m_DiffuseA);
	DDX_Control(pDX, IDC_CUTOFF, m_Cutoff);
	DDX_Control(pDX, IDC_ATTENUATION3, m_Attenuation3);
	DDX_Control(pDX, IDC_ATTENUATION2, m_Attenuation2);
	DDX_Control(pDX, IDC_ATTENUATION1, m_Attenuation1);
	DDX_Control(pDX, IDC_ATTENUATION0, m_Attenuation0);
	DDX_Control(pDX, IDC_AMBIENTR, m_AmbientR);
	DDX_Control(pDX, IDC_AMBIENTG, m_AmbientG);
	DDX_Control(pDX, IDC_AMBIENTA, m_AmbientA);
	DDX_Control(pDX, IDC_AMBIENDB, m_AmbientB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewLight, CDialog)
	//{{AFX_MSG_MAP(CNewLight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewLight message handlers

void CNewLight::toUI()
{
	char str[512];
	sprintf(str, "0x%08x", m_light.version);
	m_Version.SetWindowText(str);
	m_Name.SetWindowText(m_light.name);
	m_Type.SetCurSel(m_light.style-1);
	sprintf(str, "%2.8f", m_light.ambient.red);
	m_AmbientR.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.ambient.green);
	m_AmbientG.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.ambient.blue);
	m_AmbientB.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.ambient.alpha);
	m_AmbientA.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.diffuse.red);
	m_DiffuseR.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.diffuse.green);
	m_DiffuseG.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.diffuse.blue);
	m_DiffuseB.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.diffuse.alpha);
	m_DiffuseA.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.specular.red);
	m_SpecularR.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.specular.green);
	m_SpecularG.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.specular.blue);
	m_SpecularB.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.specular.alpha);
	m_SpecularA.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.cut_off);
	m_Cutoff.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.fall_off);
	m_Falloff.SetWindowText(str);

	sprintf(str, "%2.8f", m_light.theta);
	m_Theta.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.phi);
	m_Phi.SetWindowText(str);

	sprintf(str, "%2.8f", m_light.attenuation[0]);
	m_Attenuation0.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.attenuation[1]);
	m_Attenuation1.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.attenuation[2]);
	m_Attenuation2.SetWindowText(str);
	sprintf(str, "%2.8f", m_light.attenuation[3]);
	m_Attenuation3.SetWindowText(str);
}

void CNewLight::fromUI()
{
	char str[512];
	m_Name.GetWindowText(m_light.name, TPL_MAX_NAME_LEN);

	m_light.style = m_Type.GetCurSel()+1;
	m_AmbientR.GetWindowText(str, 512);
	m_light.ambient.red = atof(str);
	m_AmbientG.GetWindowText(str, 512);
	m_light.ambient.green = atof(str);
	m_AmbientB.GetWindowText(str, 512);
	m_light.ambient.blue = atof(str);
	m_AmbientA.GetWindowText(str, 512);
	m_light.ambient.alpha = atof(str);
	m_DiffuseR.GetWindowText(str, 512);
	m_light.diffuse.red = atof(str);
	m_DiffuseG.GetWindowText(str, 512);
	m_light.diffuse.green = atof(str);
	m_DiffuseB.GetWindowText(str, 512);
	m_light.diffuse.blue = atof(str);
	m_DiffuseA.GetWindowText(str, 512);
	m_light.diffuse.alpha = atof(str);
	m_SpecularR.GetWindowText(str, 512);
	m_light.specular.red = atof(str);
	m_SpecularG.GetWindowText(str, 512);
	m_light.specular.green = atof(str);
	m_SpecularB.GetWindowText(str, 512);
	m_light.specular.blue = atof(str);
	m_SpecularA.GetWindowText(str, 512);
	m_light.specular.alpha = atof(str);

	m_Cutoff.GetWindowText(str, 512);
	m_light.fall_off = atof(str);
	m_Falloff.GetWindowText(str, 512);
	m_light.cut_off = atof(str);
	m_Theta.GetWindowText(str, 512);
	m_light.theta = atof(str);
	m_Phi.GetWindowText(str, 512);
	m_light.phi = atof(str);

	m_Attenuation0.GetWindowText(str, 512);
	m_light.attenuation[0] = atof(str);
	m_Attenuation1.GetWindowText(str, 512);
	m_light.attenuation[1] = atof(str);
	m_Attenuation2.GetWindowText(str, 512);
	m_light.attenuation[2] = atof(str);
	m_Attenuation3.GetWindowText(str, 512);
	m_light.attenuation[3] = atof(str);
}

void CNewLight::OnOK() 
{
	fromUI();	
	CDialog::OnOK();
}

BOOL CNewLight::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( init )
	{
		memset(&m_light, 0, sizeof(m_light));
		m_light.version = TPL_LIGHT_VERSION;
		strcpy(m_light.signature, TPL_LIGHT_SIG);
	}
	m_Type.AddString("Ambient Light");
	m_Type.AddString("Directional Light");
	m_Type.AddString("Point Light");
	m_Type.AddString("Spot Light");
	m_Type.AddString("Projectional Light");
 	toUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
