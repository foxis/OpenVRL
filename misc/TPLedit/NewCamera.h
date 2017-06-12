#if !defined(AFX_NEWCAMERA_H__461D750C_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
#define AFX_NEWCAMERA_H__461D750C_B1DE_11D6_8083_CE13E10F361E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewCamera.h : header file
//

#include "openvrl.h"

/////////////////////////////////////////////////////////////////////////////
// CNewCamera dialog

class CNewCamera : public CDialog
{
// Construction
public:
	openvrl::tpl_camera_struct m_camera;
	bool init;

	void fromUI();
	void toUI();
	CNewCamera(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewCamera)
	enum { IDD = IDD_NEWCAMERA };
	CEdit	m_BlackPoint;
	CEdit	m_Brightness;
	CEdit	m_WhitePoint;
	CEdit	m_Gamma;
	CEdit	m_Contrast;
	CEdit	m_Version;
	CEdit	m_Name;
	CEdit	m_LensRX;
	CEdit	m_LensRY;
	CEdit	m_Focus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCamera)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewCamera)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCAMERA_H__461D750C_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
