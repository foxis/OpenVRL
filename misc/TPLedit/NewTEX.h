#pragma once

#include "openvrl.h"

// CNewTEX dialog

class CNewTEX : public CDialog
{
	DECLARE_DYNAMIC(CNewTEX)

public:
	void fromUI();
	void toUI();
	openvrl::CTPLLib::tex m_tex;
	bool	init;

	CNewTEX(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewTEX();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString m_Version;
	CString m_Name;
	CString m_texFName;
};
