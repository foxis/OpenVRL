#if !defined(AFX_EDITVI_H__ABA7B201_B2BF_11D6_8083_C6DE0900081E__INCLUDED_)
#define AFX_EDITVI_H__ABA7B201_B2BF_11D6_8083_C6DE0900081E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditVI.h : header file
//

#include "openvrl.h"

/////////////////////////////////////////////////////////////////////////////
// CEditVI dialog

class CEditVI : public CDialog
{
// Construction
public:
	void Update(openvrl::ulong i);
	CEditVI(CWnd* pParent = NULL);   // standard constructor
	openvrl::TPL_BYTE* data;
	openvrl::TPL_ulong size;
	bool	vertex;
	bool	bits16;
	bool onchange[2];

// Dialog Data
	//{{AFX_DATA(CEditVI)
	enum { IDD = IDD_EDITVI };
	CListBox	m_List;
	CEdit	m_Hex;
	CEdit	m_Float;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditVI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditVI)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList();
	afx_msg void OnBfloat();
	afx_msg void OnBhex();
	afx_msg void OnChangeFloat();
	afx_msg void OnChangeHex();
	afx_msg void OnUpdateFloat();
	afx_msg void OnUpdateHex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITVI_H__ABA7B201_B2BF_11D6_8083_C6DE0900081E__INCLUDED_)
