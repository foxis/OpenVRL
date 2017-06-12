#if !defined(AFX_NEWLIGHT_H__461D750B_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
#define AFX_NEWLIGHT_H__461D750B_B1DE_11D6_8083_CE13E10F361E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewLight.h : header file
//

#include "openvrl.h"

/////////////////////////////////////////////////////////////////////////////
// CNewLight dialog

class CNewLight : public CDialog
{
// Construction
public:
	openvrl::tpl_light_struct m_light;
	bool init;

	void fromUI();
	void toUI();
	CNewLight(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewLight)
	enum { IDD = IDD_NEWLIGHT };
	CComboBox	m_Type;
	CEdit	m_Version;
	CEdit	m_Theta;
	CEdit	m_SpecularR;
	CEdit	m_SpecularG;
	CEdit	m_SpecularB;
	CEdit	m_SpecularA;
	CEdit	m_Phi;
	CEdit	m_Name;
	CEdit	m_Falloff;
	CEdit	m_DiffuseR;
	CEdit	m_DiffuseG;
	CEdit	m_DiffuseB;
	CEdit	m_DiffuseA;
	CEdit	m_Cutoff;
	CEdit	m_Attenuation3;
	CEdit	m_Attenuation2;
	CEdit	m_Attenuation1;
	CEdit	m_Attenuation0;
	CEdit	m_AmbientR;
	CEdit	m_AmbientG;
	CEdit	m_AmbientA;
	CEdit	m_AmbientB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewLight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewLight)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWLIGHT_H__461D750B_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
