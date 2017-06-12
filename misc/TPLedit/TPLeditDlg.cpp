// TPLeditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TPLedit.h"
#include "TPLeditDlg.h"
#include "Materials.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CRichEditCtrl	m_Description;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_RICHEDIT1, m_Description);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPLeditDlg dialog

CTPLeditDlg::CTPLeditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTPLeditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTPLeditDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTPLeditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPLeditDlg)
	DDX_Control(pDX, IDC_TYPE, m_Type);
	DDX_Control(pDX, IDC_UID, m_UID);
	DDX_Control(pDX, IDC_TIME, m_Time);
	DDX_Control(pDX, IDC_ORIGINALSIZE, m_OriginalSize);
	DDX_Control(pDX, IDC_HEADERSIZE, m_HeaderSize);
	DDX_Control(pDX, IDC_HEADEROFFS, m_HeaderOffs);
	DDX_Control(pDX, IDC_GUID, m_GID);
	DDX_Control(pDX, IDC_CRC, m_CRC);
	DDX_Control(pDX, IDC_COMPRESSIZE, m_CompressionSize);
	DDX_Control(pDX, IDC_COMPRESSION, m_Compression);
	DDX_Control(pDX, IDC_COMMENTS, m_Comments);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_SIGNATURE, m_Signature);
	DDX_Control(pDX, IDC_VERSION, m_Version);
	DDX_Control(pDX, IDC_PATH, m_Path);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTPLeditDlg, CDialog)
	//{{AFX_MSG_MAP(CTPLeditDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON9, OnCreate)
	ON_BN_CLICKED(IDC_BUTTON2, OnOpen)
	ON_BN_CLICKED(IDC_BUTTON3, OnClose)
	ON_BN_CLICKED(IDC_BUTTON4, OnMaterials)
	ON_BN_CLICKED(IDC_BUTTON1, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPLeditDlg message handlers

BOOL CTPLeditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_tpl = new openvrl::CTPLLib(new openvrl::CFileIOD(0), "Not loaded", 1, 1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTPLeditDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTPLeditDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTPLeditDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char buf[2048];
	
	openvrl::dllOpenVRL_Description(buf, 2048);
	strcat(buf, "\n\n\n");
	openvrl::CTPLLib::dllTPLLib_Description(buf+strlen(buf), 2048-strlen(buf));
	m_Description.SetWindowText(buf);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTPLeditDlg::OnCreate() 
{
	char str[512];
	int id;
	m_Path.GetWindowText(str, 512);
	if ( m_tpl->opened() )
	{
		id = MessageBox("Opened Template Library, Do you want to save it?", "Warning", MB_YESNO);
		if ( id==IDYES )
		{
			m_tpl->modified = true;
			m_tpl->close();
		}
		else if ( id==IDNO )
		{
			m_tpl->modified = false;
			m_tpl->close();
		} else
			return ;
	}
	if ( m_tpl->create(str, 0, IOD_RDWR) )
		MessageBox("Could not create template library", 0, MB_OK);
	else
	{
		UpdateDump();
		OnMaterials();
	}
}

void CTPLeditDlg::OnOpen() 
{
	char str[512];
	int id;
	m_Path.GetWindowText(str, 512);
	if ( m_tpl->opened() )
	{
		id = MessageBox("Opened Template Library, Do you want to save it?", "Warning", MB_YESNOCANCEL);
		if ( id==IDYES )
		{
			m_tpl->modified = true;
			m_tpl->close();
		}
		else if ( id==IDNO )
		{
			m_tpl->modified = false;
			m_tpl->close();
		} else
			return ;
	}

	m_Path.AddString(str);
	if ( m_tpl->open(str, IOD_RDWR) )
		MessageBox("Could not open template library", 0, MB_OK);
	else
	{
		UpdateDump();
		OnMaterials();
	}
}

void CTPLeditDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	UpdateTPL();
	m_tpl->modified = true;
	m_tpl->close();
//	delete m_tpl;
//	m_tpl = 0;
	UpdateDump();
}

void CTPLeditDlg::UpdateDump()
{
	char str[512];
	if ( m_tpl /*&& m_tpl->is_opened()*/ )
	{
		sprintf(str, "0x%08x", m_tpl->header_version());
		m_Version.SetWindowText(str);
		sprintf(str, "0x%08x", m_tpl->header_type());
		m_Type.SetWindowText(str);
		m_Signature.SetWindowText(m_tpl->header_signature());
		m_Description.SetWindowText(m_tpl->header_name());
		m_Comments.SetWindowText(m_tpl->header_comment());
		sprintf(str, "0x%08x", m_tpl->header_compression());
		m_Compression.SetWindowText(str);
		sprintf(str, "0x%08x", m_tpl->header_offset());
		m_HeaderOffs.SetWindowText(str);
		sprintf(str, "0x%08x", 256);
		m_HeaderSize.SetWindowText(str);
		sprintf(str, "0x%08x", m_tpl->header_compressed_size());
		m_CompressionSize.SetWindowText(str);
		sprintf(str, "0x%08x", m_tpl->header_original_size());
		m_OriginalSize.SetWindowText(str);
		sprintf(str, "0x%04x", m_tpl->header_UID());
		m_UID.SetWindowText(str);
		sprintf(str, "0x%04x", m_tpl->header_GID());
		m_GID.SetWindowText(str);
	}
	else
	{
	}
}

void CTPLeditDlg::UpdateTPL()
{
	char str[512];
	if ( m_tpl /*&& m_tpl->is_opened()*/ )
	{
		m_Version.GetWindowText(str, 512);
//		m_Signature.GetWindowText(m_tpl->header_signature(), 4); m_tpl->header_signature()[3]=0;
		m_Description.GetWindowText(m_tpl->header_name(), TPL_MAX_NAME_LEN);
		//m_Comments.GetWindowText(m_tpl->header_comment());
	}
	else
	{
	}
}

void CTPLeditDlg::OnMaterials() 
{
	CMaterials mat;
	mat.m_tpl = m_tpl;
	mat.DoModal();
}

void CTPLeditDlg::OnBrowse() 
{
	CFileDialog	fd(TRUE);
	char path[512] = ".\\";
	CString	str;
	fd.m_ofn.lpstrInitialDir = path;
	if ( fd.DoModal()==IDOK )
	{
		str = fd.GetPathName();
		m_Path.SetWindowText(str);
		OnOpen();
	}
}
