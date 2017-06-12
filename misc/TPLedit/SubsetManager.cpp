// SubsetManager.cpp : implementation file
//

#include "stdafx.h"
#include "TPLedit.h"
#include "SubsetManager.h"
#include "EditMatrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define NUM_COLUMNS 7
static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("Version"), _T("Type"), _T("VB"), _T("IB"), _T("Verteces"), _T("Indeces"), _T("Material")
};
static int _gnColumnFmt[NUM_COLUMNS] =
{
	LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT
};

static int _gnColumnWidth[NUM_COLUMNS] =
{
	80, 80, 80, 80, 80, 80, 120
};

/////////////////////////////////////////////////////////////////////////////
// CSubsetManager dialog


CSubsetManager::CSubsetManager(CWnd* pParent /*=NULL*/)
	: CDialog(CSubsetManager::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubsetManager)
	//}}AFX_DATA_INIT
	start_vertex = start_index = 0;
}


void CSubsetManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubsetManager)
	DDX_Control(pDX, NUMVERTEX, m_NumVertex);
	DDX_Control(pDX, IDC_VBINDEX, m_VBIndex);
	DDX_Control(pDX, IDC_NUMINDEX, m_NumIndex);
	DDX_Control(pDX, IDC_MATERIAL, m_Material);
	DDX_Control(pDX, IDC_IBINDEX, m_IBIndex);
	DDX_Control(pDX, IDC_TYPE, m_Type);
	DDX_Control(pDX, IDC_MAXVERTEX, m_MaxVertex);
	DDX_Control(pDX, IDC_MAXINDEX, m_MaxIndex);
	DDX_Control(pDX, IDC_LIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubsetManager, CDialog)
	//{{AFX_MSG_MAP(CSubsetManager)
	ON_BN_CLICKED(IDC_BUTTON1, OnNew)
	ON_BN_CLICKED(IDC_BUTTON2, OnDelete)
	ON_BN_CLICKED(IDC_BUTTON3, OnBrowse)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_EN_CHANGE(IDC_IBINDEX, OnChangeIbindex)
	ON_EN_CHANGE(IDC_MATERIAL, OnChangeMaterial)
	ON_EN_CHANGE(IDC_NUMINDEX, OnChangeNumindex)
	ON_EN_CHANGE(IDC_VBINDEX, OnChangeVbindex)
	ON_EN_CHANGE(NUMVERTEX, OnChangeNUMVERTEX)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	ON_BN_CLICKED(IDC_BUTTON4, OnEditMatrix)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubsetManager message handlers

void CSubsetManager::OnNew() 
{
	openvrl::TPL_MESHSUBSET s;
	memset(&s, 0, sizeof(s));
	s.version = TPL_MESHSUBSET_VERSION;
	s.IB_index = start_index;
	s.VB_index = start_vertex;
	s.IB_size = indeces-start_index;
	s.VB_size = verteces-start_vertex;
	s.transform[0]=s.transform[5]=s.transform[10]=s.transform[15]=1.0f;
	subsets->insert(subsets->end(), s);
	Update(-1);
}

void CSubsetManager::OnDelete() 
{
	const openvrl::ulong i = m_List.GetSelectionMark();
	if ( i<0 )	 return;

	subsets->erase(subsets->begin()+i);
	m_List.DeleteItem(i);
}

void CSubsetManager::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	
}

#define C_TYPE 0
#define C_VBINDEX 1
#define C_IBINDEX 2
#define C_VBSIZE 3
#define C_IBSIZE 4
#define C_MATERIAL 5

void CSubsetManager::toUI()
{
	const openvrl::ulong i = m_List.GetSelectionMark();
	char str[128];
	if ( i<0||i>=subsets->size() ) return;

	if ( changing[C_TYPE]==false )  
		m_Type.SetCurSel((*subsets)[i].type);
	
	if ( changing[C_VBINDEX]==false )  
	{
		sprintf(str, "%lu", (*subsets)[i].VB_index);
		m_VBIndex.SetWindowText(str);
	}
	
	if ( changing[C_IBINDEX]==false )  
	{
		sprintf(str, "%lu", (*subsets)[i].IB_index);
		m_IBIndex.SetWindowText(str);
	}
	
	if ( changing[C_VBSIZE]==false )  
	{
		sprintf(str, "%lu", (*subsets)[i].VB_size);
		m_NumVertex.SetWindowText(str);
	}
	
	if ( changing[C_IBSIZE]==false )  
	{
		sprintf(str, "%lu", (*subsets)[i].IB_size);
		m_NumIndex.SetWindowText(str);
	}
	
	if ( changing[C_MATERIAL]==false )  
		m_Material.SetWindowText((*subsets)[i].material);
}

void CSubsetManager::Update(long j)
{
	if ( j<0 )
	{
		m_List.DeleteAllItems();
		for ( openvrl::ulong i=0;i<subsets->size();i++ )
			AddSubset(i);
	}
	else
		SetSubset(j);
	toUI();
}

BOOL CSubsetManager::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char str[128];
	LV_COLUMN lvc;
	openvrl::ulong i;

	memset(changing, 0, sizeof(changing));

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	for(i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		m_List.InsertColumn(i,&lvc);
	}

	sprintf(str, "%lu", verteces);
	m_MaxVertex.SetWindowText(str);
	sprintf(str, "%lu", indeces);
	m_MaxIndex.SetWindowText(str);

	m_List.SetRedraw(FALSE);
	m_List.DeleteAllItems();
	for ( i=0;i<subsets->size();i++ )
		AddSubset(i);
	m_List.SetRedraw(TRUE);
	m_List.Invalidate(TRUE);
	toUI();/**/

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubsetManager::AddSubset(long i)
{
	m_List.InsertItem(m_List.GetItemCount(), "NULL");
	SetSubset(i);
}

void CSubsetManager::SetSubset(long i)
{
	char str[128];
	if ( i<0||i>=subsets->size() ) return;
	sprintf(str, "%08x", (*subsets)[i].version);
	m_List.SetItemText(i, 0, str);
	sprintf(str, "%08x", (*subsets)[i].type);
	m_List.SetItemText(i, 1, str);
	sprintf(str, "%lu", (*subsets)[i].VB_index);
	m_List.SetItemText(i, 2, str);
	sprintf(str, "%lu", (*subsets)[i].IB_index);
	m_List.SetItemText(i, 3, str);
	sprintf(str, "%lu", (*subsets)[i].VB_size);
	m_List.SetItemText(i, 4, str);
	sprintf(str, "%lu", (*subsets)[i].IB_size);
	m_List.SetItemText(i, 5, str);
	m_List.SetItemText(i, 6, (*subsets)[i].material);/**/
}

void CSubsetManager::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	toUI();
	
	*pResult = 0;
}

void CSubsetManager::OnChangeIbindex() 
{
	const long i = m_List.GetSelectionMark();
	CString s;
	if ( i<0||i>=subsets->size() ) return;
	if ( changing[C_IBINDEX] ) return;
	changing[C_IBINDEX]=true;
	m_IBIndex.GetWindowText(s);
	(*subsets)[i].IB_index = atol(s);
	SetSubset(i);
	changing[C_IBINDEX]=false;/**/
}

void CSubsetManager::OnChangeMaterial() 
{
	const long i = m_List.GetSelectionMark();
	CString s;
	if ( i<0||i>=subsets->size() ) return;
	if ( changing[C_IBINDEX] ) return;
	changing[C_MATERIAL]=true;
	m_Material.GetWindowText(s);
	strncpy((*subsets)[i].material, s, TPL_MAX_NAME_LEN);
	SetSubset(i);
	changing[C_MATERIAL]=false; /**/
}

void CSubsetManager::OnChangeNumindex() 
{
	const long i = m_List.GetSelectionMark();
	CString s;
	if ( i<0||i>=subsets->size() ) return;
	if ( changing[C_IBSIZE] ) return;
	changing[C_IBSIZE]=true;
	m_NumIndex.GetWindowText(s);
	(*subsets)[i].IB_size = atol(s);
	SetSubset(i);
	changing[C_IBSIZE]=false; /**/
}

void CSubsetManager::OnChangeVbindex() 
{
	const long i = m_List.GetSelectionMark();
	CString s;
	if ( i<0||i>=subsets->size() ) return;
	if ( changing[C_VBINDEX] ) return;
	changing[C_VBINDEX]=true;
	m_VBIndex.GetWindowText(s);
	(*subsets)[i].VB_index = atol(s);
	SetSubset(i);
	changing[C_VBINDEX]=false;/**/
}

void CSubsetManager::OnChangeNUMVERTEX() 
{
	const long i = m_List.GetSelectionMark();
	CString s;
	if ( i<0||i>=subsets->size() ) return;
	if ( changing[C_VBSIZE] ) return;
	changing[C_VBSIZE]=true;
	m_NumVertex.GetWindowText(s);
	(*subsets)[i].VB_size = atol(s);
	SetSubset(i);
	changing[C_VBSIZE]=false; /**/
}

void CSubsetManager::OnSelchangeType() 
{
	// TODO: Add your control notification handler code here
	
}

void CSubsetManager::OnEditMatrix() 
{
	const long i = m_List.GetSelectionMark();
	if ( i<0||i>=subsets->size() ) return;
	CEditMatrix em;
	memcpy(em.matrix, (*subsets)[i].transform, sizeof(em.matrix));
	if ( em.DoModal()==IDOK )  	
		memcpy((*subsets)[i].transform, em.matrix, sizeof((*subsets)[i].transform));
}
