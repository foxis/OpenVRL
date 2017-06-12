#if !defined(AFX_EDITMATRIX_H__E6D7C482_B389_11D6_8083_9B7564B02709__INCLUDED_)
#define AFX_EDITMATRIX_H__E6D7C482_B389_11D6_8083_9B7564B02709__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditMatrix.h : header file
//

#include "openvrl.h"

/////////////////////////////////////////////////////////////////////////////
// CEditMatrix dialog

class CEditMatrix : public CDialog
{
// Construction
public:
	void fromUI();
	void toUI();
	openvrl::TPL_4x4matrix_t matrix;

	CEditMatrix(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditMatrix)
	enum { IDD = IDD_DIALOG2 };
	CEdit	m_9;
	CEdit	m_8;
	CEdit	m_7;
	CEdit	m_6;
	CEdit	m_5;
	CEdit	m_4;
	CEdit	m_3;
	CEdit	m_2;
	CEdit	m_16;
	CEdit	m_15;
	CEdit	m_14;
	CEdit	m_13;
	CEdit	m_12;
	CEdit	m_11;
	CEdit	m_10;
	CEdit	m_1;
	CComboBox	m_Set;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditMatrix)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditMatrix)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITMATRIX_H__E6D7C482_B389_11D6_8083_9B7564B02709__INCLUDED_)
