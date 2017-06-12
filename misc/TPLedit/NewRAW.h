#if !defined(AFX_NEWRAW_H__461D750D_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
#define AFX_NEWRAW_H__461D750D_B1DE_11D6_8083_CE13E10F361E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewRAW.h : header file
//

#include "openvrl.h"

/////////////////////////////////////////////////////////////////////////////
// CNewRAW dialog

class CNewRAW : public CDialog
{
// Construction
enum { U_NONE=0, U_VERTECES=0x1, U_INDECES=0x2, U_ALL=0x3 };

public:
	void fromUI();
	void toUI(int w=U_ALL);
	openvrl::tpl_rawmesh_struct m_rawmesh;
	bool init;
	openvrl::TPL_BYTE* VB;
	openvrl::TPL_BYTE* IB;
	std::vector<openvrl::TPL_MESHSUBSET> subsets;
	
	CNewRAW(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CNewRAW)
	enum { IDD = IDD_NEWRAW };
	CEdit	m_Subsets;
	CEdit	m_COMZ;
	CEdit	m_COMX;
	CEdit	m_COMY;
	CEdit	m_VSize;
	CListBox	m_VList;
	CEdit	m_VFlags;
	CEdit	m_Verteces;
	CEdit	m_Version;
	CEdit	m_Name;
	CEdit	m_ISize;
	CListBox	m_IList;
	CEdit	m_IFlags;
	CEdit	m_Indeces;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewRAW)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewRAW)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnImportMesh();
	afx_msg void OnImportIndeces();
	afx_msg void OnImportVerteces();
	afx_msg void OnVResize();
	afx_msg void OnIResize();
	afx_msg void OnDblclkVertexlist();
	afx_msg void OnDblclkIndexlist();
	afx_msg void OnAddVertex();
	afx_msg void OnInsertVertex();
	afx_msg void OnDeleteVertex();
	afx_msg void OnAddFace();
	afx_msg void OnInsertFace();
	afx_msg void OnDeleteFace();
	afx_msg void OnSubsets();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWRAW_H__461D750D_B1DE_11D6_8083_CE13E10F361E__INCLUDED_)
