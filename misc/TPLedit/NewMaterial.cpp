// NewMaterial.cpp : implementation file
//

#include "stdafx.h"
#include "TPLedit.h"
#include "NewMaterial.h"
#include ".\newmaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewMaterial dialog


CNewMaterial::CNewMaterial(CWnd* pParent /*=NULL*/)
	: CDialog(CNewMaterial::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewMaterial)
	//}}AFX_DATA_INIT
	init = true;
}


void CNewMaterial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewMaterial)
	DDX_Control(pDX, IDC_VERSION, m_Version);
	DDX_Control(pDX, IDC_STRENGTHM, m_StrengthM);
	DDX_Control(pDX, IDC_STRENGTH, m_Strength);
	DDX_Control(pDX, IDC_STATICFRICTIONM, m_StaticFrictionM);
	DDX_Control(pDX, IDC_STATICFRICTION, m_StaticFriction);
	DDX_Control(pDX, IDC_SPECULARR, m_SpecularR);
	DDX_Control(pDX, IDC_SPECULARG, m_SpecularG);
	DDX_Control(pDX, IDC_SPECULARB, m_SpecularB);
	DDX_Control(pDX, IDC_SPECULARA, m_SpecularA);
	DDX_Control(pDX, IDC_SPECULAR, m_Specular);
	DDX_Control(pDX, IDC_SLIDINGFRICTIONM, m_SlidingFrictionM);
	DDX_Control(pDX, IDC_SLIDINGFRICTION, m_SlidingFriction);
	DDX_Control(pDX, IDC_SHINESSM, m_ShinessM);
	DDX_Control(pDX, IDC_SHINESS, m_Shiness);
	DDX_Control(pDX, IDC_SELFILLUMINATION, m_SelfIllumination);
	DDX_Control(pDX, IDC_REFRACTIONR, m_RefractionR);
	DDX_Control(pDX, IDC_REFRACTIONA, m_RefractionA);
	DDX_Control(pDX, IDC_REFRACTIONG, m_RefractionG);
	DDX_Control(pDX, IDC_REFRACTIONB, m_RefractionB);
	DDX_Control(pDX, IDC_REFRACTION, m_Refraction);
	DDX_Control(pDX, IDC_OPACITYM, m_OpacityM);
	DDX_Control(pDX, IDC_OPACITY, m_Opacity);
	DDX_Control(pDX, IDC_ILLUMINATIONM, m_Illumination);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_FILTERR, m_FilterR);
	DDX_Control(pDX, IDC_FILTER, m_Filter);
	DDX_Control(pDX, IDC_FILTERG, m_FilterG);
	DDX_Control(pDX, IDC_FILTERB, m_FilterB);
	DDX_Control(pDX, IDC_FILTERA, m_FilterA);
	DDX_Control(pDX, IDC_DIFFUSER, m_DiffuseR);
	DDX_Control(pDX, IDC_DIFFUSEG, m_DiffuseG);
	DDX_Control(pDX, IDC_DIFFUSEB, m_DiffuseB);
	DDX_Control(pDX, IDC_DIFFUSEA, m_DiffuseA);
	DDX_Control(pDX, IDC_DIFFUSE, m_Diffuse);
	DDX_Control(pDX, IDC_BOUNCEM, m_BounceM);
	DDX_Control(pDX, IDC_BOUNCE, m_Bounce);
	DDX_Control(pDX, IDC_AMBIENTR, m_AmbientR);
	DDX_Control(pDX, IDC_AMBIENTG, m_AmbientG);
	DDX_Control(pDX, IDC_AMBIENTA, m_AmbientA);
	DDX_Control(pDX, IDC_AMBIENT, m_Ambient);
	DDX_Control(pDX, IDC_AMBIENDB, m_AmbientB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewMaterial, CDialog)
	//{{AFX_MSG_MAP(CNewMaterial)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewMaterial message handlers

BOOL CNewMaterial::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( init )
	{
		memset(&m_material, 0, sizeof(m_material));
		m_material.version = TPL_MAT_VERSION;
		strcpy(m_material.signature, TPL_MAT_SIG);
	}
	toUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewMaterial::toUI()
{
	char str[512];
	sprintf(str, "0x%08x", m_material.version);
	m_Version.SetWindowText(str);
	m_Name.SetWindowText(m_material.name);
	sprintf(str, "%2.8f", m_material.ambient.red);
	m_AmbientR.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.ambient.green);
	m_AmbientG.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.ambient.blue);
	m_AmbientB.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.ambient.alpha);
	m_AmbientA.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.diffuse.red);
	m_DiffuseR.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.diffuse.green);
	m_DiffuseG.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.diffuse.blue);
	m_DiffuseB.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.diffuse.alpha);
	m_DiffuseA.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.specular.red);
	m_SpecularR.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.specular.green);
	m_SpecularG.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.specular.blue);
	m_SpecularB.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.specular.alpha);
	m_SpecularA.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.filter.red);
	m_FilterR.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.filter.green);
	m_FilterG.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.filter.blue);
	m_FilterB.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.filter.alpha);
	m_FilterA.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.refraction.red);
	m_RefractionR.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.refraction.green);
	m_RefractionG.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.refraction.blue);
	m_RefractionB.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.refraction.alpha);
	m_RefractionA.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.strength);
	m_Strength.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.shiness);
	m_Shiness.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.self_illumination);
	m_SelfIllumination.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.opacity);
	m_Opacity.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.static_friction);
	m_StaticFriction.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.sliding_friction);
	m_SlidingFriction.SetWindowText(str);
	sprintf(str, "%2.8f", m_material.bounce_coeficient);
	m_Bounce.SetWindowText(str);
}

void CNewMaterial::fromUI()
{
	char str[512];
	m_Name.GetWindowText(m_material.name, TPL_MAX_NAME_LEN);

	m_AmbientR.GetWindowText(str, 512);
	m_material.ambient.red = atof(str);
	m_AmbientG.GetWindowText(str, 512);
	m_material.ambient.green = atof(str);
	m_AmbientB.GetWindowText(str, 512);
	m_material.ambient.blue = atof(str);
	m_AmbientA.GetWindowText(str, 512);
	m_material.ambient.alpha = atof(str);
	m_DiffuseR.GetWindowText(str, 512);
	m_material.diffuse.red = atof(str);
	m_DiffuseG.GetWindowText(str, 512);
	m_material.diffuse.green = atof(str);
	m_DiffuseB.GetWindowText(str, 512);
	m_material.diffuse.blue = atof(str);
	m_DiffuseA.GetWindowText(str, 512);
	m_material.diffuse.alpha = atof(str);
	m_SpecularR.GetWindowText(str, 512);
	m_material.specular.red = atof(str);
	m_SpecularG.GetWindowText(str, 512);
	m_material.specular.green = atof(str);
	m_SpecularB.GetWindowText(str, 512);
	m_material.specular.blue = atof(str);
	m_SpecularA.GetWindowText(str, 512);
	m_material.specular.alpha = atof(str);
	m_FilterR.GetWindowText(str, 512);
	m_material.filter.red = atof(str);
	m_FilterG.GetWindowText(str, 512);
	m_material.filter.green = atof(str);
	m_FilterB.GetWindowText(str, 512);
	m_material.filter.blue = atof(str);
	m_FilterA.GetWindowText(str, 512);
	m_material.filter.alpha = atof(str);
	m_RefractionR.GetWindowText(str, 512);
	m_material.refraction.red = atof(str);
	m_RefractionG.GetWindowText(str, 512);
	m_material.refraction.green = atof(str);
	m_RefractionB.GetWindowText(str, 512);
	m_material.refraction.blue = atof(str);
	m_RefractionA.GetWindowText(str, 512);
	m_material.refraction.alpha = atof(str);
	m_Strength.GetWindowText(str, 512);
	m_material.strength = atof(str);
	m_Shiness.GetWindowText(str, 512);
	m_material.shiness = atof(str);
	m_SelfIllumination.GetWindowText(str, 512);
	m_material.self_illumination = atof(str);
	m_Opacity.GetWindowText(str, 512);
	m_material.opacity = atof(str);
	m_StaticFriction.GetWindowText(str, 512);
	m_material.static_friction = atof(str);
	m_SlidingFriction.GetWindowText(str, 512);
	m_material.sliding_friction = atof(str);
	m_Bounce.GetWindowText(str, 512);
	m_material.bounce_coeficient = atof(str);
//	m_Ambient.GetWindowText(str, 512);
//	m_material.
}

void CNewMaterial::OnOK() 
{
	// TODO: Add extra validation here
	fromUI();
	CDialog::OnOK();
}

void CNewMaterial::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
