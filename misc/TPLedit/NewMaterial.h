#if !defined(AFX_NEWMATERIAL_H__461D7504_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
#define AFX_NEWMATERIAL_H__461D7504_B1DE_11D6_8083_CE13E10F361E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewMaterial.h : header file
//

#include "openvrl.h"

/////////////////////////////////////////////////////////////////////////////
// CNewMaterial dialog

class CNewMaterial : public CDialog
{
// Construction
public:
	void fromUI();
	void toUI();
	openvrl::TPL_MAT m_material;
	bool	init;

	CNewMaterial(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewMaterial)
	enum { IDD = IDD_NEWMATERIAL };
	CEdit	m_Version;
	CEdit	m_StrengthM;
	CEdit	m_Strength;
	CEdit	m_StaticFrictionM;
	CEdit	m_StaticFriction;
	CEdit	m_SpecularR;
	CEdit	m_SpecularG;
	CEdit	m_SpecularB;
	CEdit	m_SpecularA;
	CEdit	m_Specular;
	CEdit	m_SlidingFrictionM;
	CEdit	m_SlidingFriction;
	CEdit	m_ShinessM;
	CEdit	m_Shiness;
	CEdit	m_SelfIllumination;
	CEdit	m_RefractionR;
	CEdit	m_RefractionA;
	CEdit	m_RefractionG;
	CEdit	m_RefractionB;
	CEdit	m_Refraction;
	CEdit	m_OpacityM;
	CEdit	m_Opacity;
	CEdit	m_Illumination;
	CEdit	m_Name;
	CEdit	m_FilterR;
	CEdit	m_Filter;
	CEdit	m_FilterG;
	CEdit	m_FilterB;
	CEdit	m_FilterA;
	CEdit	m_DiffuseR;
	CEdit	m_DiffuseG;
	CEdit	m_DiffuseB;
	CEdit	m_DiffuseA;
	CEdit	m_Diffuse;
	CEdit	m_BounceM;
	CEdit	m_Bounce;
	CEdit	m_AmbientR;
	CEdit	m_AmbientG;
	CEdit	m_AmbientA;
	CEdit	m_Ambient;
	CEdit	m_AmbientB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewMaterial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewMaterial)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWMATERIAL_H__461D7504_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
