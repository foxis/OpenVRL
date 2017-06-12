#if !defined(AFX_MATERIALS_H__461D7503_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
#define AFX_MATERIALS_H__461D7503_B1DE_11D6_8083_CE13E10F361E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Materials.h : header file
//

#include "openvrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMaterials dialog

class CMaterials : public CDialog
{
// Construction
public:
	void SetString(openvrl::ulong i, openvrl::ulong what);
	void AddString(openvrl::ulong i, openvrl::ulong what);
	openvrl::CTPLLib	*m_tpl;

	CMaterials(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMaterials)
	enum { IDD = IDD_DIALOG1 };
	CListCtrl	m_Materials;
	CComboBox	m_What;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaterials)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaterials)
	virtual BOOL OnInitDialog();
	afx_msg void OnNew();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeWhat();
	afx_msg void OnDblclkMaterials();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedMaterials(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemdblclickMaterials(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickMaterials(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMaterials(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALS_H__461D7503_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
