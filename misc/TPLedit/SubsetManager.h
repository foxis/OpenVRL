#if !defined(AFX_SUBSETMANAGER_H__E6D7C481_B389_11D6_8083_9B7564B02709__INCLUDED_)
#define AFX_SUBSETMANAGER_H__E6D7C481_B389_11D6_8083_9B7564B02709__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubsetManager.h : header file
//

#include "openvrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSubsetManager dialog

class CSubsetManager : public CDialog
{
// Construction
public:
	void SetSubset(long i);
	void AddSubset(long i);
	std::vector<openvrl::TPL_MESHSUBSET>* subsets;
	openvrl::ulong verteces;
	openvrl::ulong indeces;
	openvrl::ulong start_vertex, start_index;
	bool changing[8];

	void Update(long j);
	void toUI();
	CSubsetManager(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubsetManager)
	enum { IDD = IDD_SUBSETMANAGER };
	CEdit	m_NumVertex;
	CEdit	m_VBIndex;
	CEdit	m_NumIndex;
	CEdit	m_Material;
	CEdit	m_IBIndex;
	CComboBox	m_Type;
	CEdit	m_MaxVertex;
	CEdit	m_MaxIndex;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubsetManager)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubsetManager)
	afx_msg void OnNew();
	afx_msg void OnDelete();
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeIbindex();
	afx_msg void OnChangeMaterial();
	afx_msg void OnChangeNumindex();
	afx_msg void OnChangeVbindex();
	afx_msg void OnChangeNUMVERTEX();
	afx_msg void OnSelchangeType();
	afx_msg void OnEditMatrix();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBSETMANAGER_H__E6D7C481_B389_11D6_8083_9B7564B02709__INCLUDED_)
