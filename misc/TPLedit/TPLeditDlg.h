// TPLeditDlg.h : header file
//

#if !defined(AFX_TPLEDITDLG_H__E968A5C9_B15E_11D6_8083_E64533B81295__INCLUDED_)
#define AFX_TPLEDITDLG_H__E968A5C9_B15E_11D6_8083_E64533B81295__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "openvrl.h"
//#include <iosystem/fileiodev.hpp>


/////////////////////////////////////////////////////////////////////////////
// CTPLeditDlg dialog

class CTPLeditDlg : public CDialog
{
// Construction
public:
	void UpdateTPL();
	void UpdateDump();
	CTPLeditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTPLeditDlg)
	enum { IDD = IDD_TPLEDIT_DIALOG };
	CEdit	m_Type;
	CEdit	m_UID;
	CEdit	m_Time;
	CEdit	m_OriginalSize;
	CEdit	m_HeaderSize;
	CEdit	m_HeaderOffs;
	CEdit	m_GID;
	CEdit	m_CRC;
	CEdit	m_CompressionSize;
	CEdit	m_Compression;
	CEdit	m_Comments;
	CEdit	m_Description;
	CEdit	m_Signature;
	CEdit	m_Version;
	CComboBox	m_Path;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPLeditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	openvrl::CTPLLib* m_tpl;

	// Generated message map functions
	//{{AFX_MSG(CTPLeditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreate();
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnMaterials();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TPLEDITDLG_H__E968A5C9_B15E_11D6_8083_E64533B81295__INCLUDED_)
