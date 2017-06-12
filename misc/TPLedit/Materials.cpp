// Materials.cpp : implementation file
//

#include "stdafx.h"
#include "TPLedit.h"
#include "Materials.h"
#include "NewMaterial.h"
#include "NewLight.h"
#include "NewCamera.h"
#include "NewRAW.h"
#include "NewTEX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaterials dialog
BEGIN_MESSAGE_MAP(CMaterials, CDialog)
	//{{AFX_MSG_MAP(CMaterials)
	ON_BN_CLICKED(IDC_BUTTON1, OnNew)
	ON_LBN_DBLCLK(IDC_MATERIALS, OnDblclkMaterials)
	ON_BN_CLICKED(IDC_BUTTON2, OnDelete)
	ON_CBN_SELCHANGE(IDC_WHAT, OnSelchangeWhat)
	//}}AFX_MSG_MAP
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MATERIALS, OnLvnItemchangedMaterials)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, OnHdnItemdblclickMaterials)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickMaterials)
	ON_NOTIFY(NM_DBLCLK, IDC_MATERIALS, OnNMDblclkMaterials)
END_MESSAGE_MAP()

//	ON_NOTIFY(NM_DBLCLK, IDC_MATERIALS, OnDblclkMaterials)

CMaterials::CMaterials(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterials::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaterials)
	//}}AFX_DATA_INIT
}


void CMaterials::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterials)
	DDX_Control(pDX, IDC_MATERIALS, m_Materials);
	DDX_Control(pDX, IDC_WHAT, m_What);
	//}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CMaterials message handlers
#define NUM_COLUMNS 5
static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("Name"), _T("Version"), _T("Signature"), _T("Type"), _T("Size")
};
static int _gnColumnFmt[NUM_COLUMNS] =
{
	LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT
};

static int _gnColumnWidth[NUM_COLUMNS] =
{
	250, 150, 50, 50, 50
};

BOOL CMaterials::OnInitDialog() 
{
//	LV_ITEM lvi;
	LV_COLUMN lvc;
//	POSITION pos;
	int i;

	CDialog::OnInitDialog();
	
	m_What.AddString(_T("List Templates: Textures"));
	m_What.AddString(_T("List Templates: Materials"));
	m_What.AddString(_T("List Templates: Lights"));
	m_What.AddString(_T("List Templates: Cameras"));
	m_What.AddString(_T("List Templates: RAW Meshes"));

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	for(i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		m_Materials.InsertColumn(i,&lvc);
	}

//	for ( i=0,pos=m_RegCompList.GetHeadPosition();pos!=0;i++ )
//	{
//		lvi.mask = LVIF_IMAGE;
//		lvi.pszText = buffer;
//		lvi.iItem = i;
//		lvi.iSubItem = 0;
//		lvi.iImage = 0;
//		m_Materials.GetNext(pos)->FillListItem(lvi);
//		list.InsertItem(&lvi);
//	}

	m_What.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMaterials::OnNew() 
{
	const openvrl::ulong what = m_What.GetCurSel();
	openvrl::ulong i;
	CNewMaterial nm;
	CNewLight nl;
	CNewCamera nc;
	CNewRAW nr;
	CNewTEX tx;

	switch ( what )
	{
	case 0:
		if ( tx.DoModal()==IDOK )
		{
			m_tpl->texture_add(tx.m_tex);
			AddString(m_tpl->textures()-1, what);
		}
		break;
	case 1:
		if ( nm.DoModal()==IDOK )
		{
			m_tpl->material_add(nm.m_material);
			AddString(m_tpl->materials()-1, what);
		}
		break;
	case 2:
		if ( nl.DoModal()==IDOK )
		{
			m_tpl->light_add(nl.m_light);
			AddString(m_tpl->lights()-1, what);
		}
		break;
	case 3:
		if ( nc.DoModal()==IDOK )
		{
			m_tpl->camera_add(nc.m_camera);
			AddString(m_tpl->cameras()-1, what);
		}
		break;
	case 4:
		nr.init = true;
		if ( nr.DoModal()==IDOK )
		{
			i = m_tpl->rawmeshes();
			m_tpl->rawmesh_add(nr.m_rawmesh, 0, 0, true); // plain add crashes somehow...
			m_tpl->rawmesh_write_VB0(i, nr.VB, nr.m_rawmesh.verteces*nr.m_rawmesh.vertex_size, nr.m_rawmesh.VB_flags);
			m_tpl->rawmesh_write_IB0(i, nr.IB, nr.m_rawmesh.faces*nr.m_rawmesh.face_size, nr.m_rawmesh.IB_flags);
			m_tpl->rawmesh_set_subsets(i, nr.subsets);
			AddString(m_tpl->rawmeshes()-1, what);
		}
		break;
	}
}

void CMaterials::OnDblclkMaterials() 
{
	const openvrl::ulong what = m_What.GetCurSel();
	const openvrl::ulong i = m_Materials.GetSelectionMark();
	CNewMaterial nm;
	CNewLight nl;
	CNewCamera nc;
	CNewRAW nr;
	CNewTEX tx;
	nm.init = false;
	nl.init = false;
	nc.init = false;
	nr.init = false;
	tx.init = false;

	switch ( what )
	{
	case 0:
		if ( i<0 || i>=m_tpl->textures() ) return;
		m_tpl->texture_read(&tx.m_tex, i);
		if ( tx.DoModal()==IDOK )
		{
			m_tpl->texture_write(tx.m_tex, i);
			SetString(i, what);
		}
		break;
	case 1:
		if ( i<0 || i>=m_tpl->materials() ) return;
		m_tpl->material_read(&nm.m_material, i);
		if ( nm.DoModal()==IDOK )
		{
			m_tpl->material_write(nm.m_material, i);
			SetString(i, what);
		}
		break;
	case 2:
		if ( i<0 || i>=m_tpl->lights() ) return;
		m_tpl->light_read(&nl.m_light, i);
		if ( nl.DoModal()==IDOK )
		{
			m_tpl->light_write(nl.m_light, i);
			SetString(i, what);
		}
		break;
	case 3:
		if ( i<0 || i>=m_tpl->cameras() ) return;
		m_tpl->camera_read(&nc.m_camera, i);
		if ( nc.DoModal()==IDOK )
		{
			m_tpl->camera_write(nc.m_camera, i);
			SetString(i, what);
		}
		break;
	case 4:
		if ( i<0 || i>=m_tpl->rawmeshes() ) return;
		m_tpl->rawmesh_read(&nr.m_rawmesh, i);
		nr.VB = new openvrl::TPL_BYTE[nr.m_rawmesh.verteces*nr.m_rawmesh.vertex_size];
		nr.IB = new openvrl::TPL_BYTE[nr.m_rawmesh.faces*nr.m_rawmesh.face_size];
		m_tpl->rawmesh_read_VB0(i, nr.VB, nr.m_rawmesh.verteces*nr.m_rawmesh.vertex_size);
		m_tpl->rawmesh_read_IB0(i, nr.IB, nr.m_rawmesh.faces*nr.m_rawmesh.face_size);
		m_tpl->rawmesh_get_subsets(i, nr.subsets);
		if ( nr.DoModal()==IDOK )
		{
			m_tpl->rawmesh_write(nr.m_rawmesh, i);
			m_tpl->rawmesh_set_subsets(i, nr.subsets);
			m_tpl->rawmesh(i)->subsets = nr.subsets.size();
			m_tpl->rawmesh_write_VB0(i, nr.VB, nr.m_rawmesh.verteces*nr.m_rawmesh.vertex_size, nr.m_rawmesh.VB_flags);
			m_tpl->rawmesh_write_IB0(i, nr.IB, nr.m_rawmesh.faces*nr.m_rawmesh.face_size, nr.m_rawmesh.IB_flags);
			SetString(i, what);
		}
		delete[] nr.VB;
		delete[] nr.IB;
		break;
	}
}

void CMaterials::OnDelete() 
{
	const openvrl::ulong what = m_What.GetCurSel();
	const openvrl::ulong i = m_Materials.GetSelectionMark();

	switch ( what )
	{
	case 0:
		if ( i<0 || i>=m_tpl->textures() ) break;
		{
			m_tpl->texture_delete(i);
			m_Materials.DeleteItem(i);
		}
		break;
	case 1:
		if ( i<0 || i>=m_tpl->materials() ) break;
		{
			m_tpl->material_delete(i);
			m_Materials.DeleteItem(i);
		}
		break;
	case 2:
		if ( i<0 || i>=m_tpl->lights() ) break;
		{
			m_tpl->light_delete(i);
			m_Materials.DeleteItem(i);
		}
		break;
	case 3:
		if ( i<0 || i>=m_tpl->cameras() ) break;
		{
			m_tpl->camera_delete(i);
			m_Materials.DeleteItem(i);
		}
		break;
	case 4:
		if ( i<0 || i>=m_tpl->rawmeshes() ) break;
		{
			m_tpl->rawmesh_delete(i);
			m_Materials.DeleteItem(i);
		}
		break;
	}
}

void CMaterials::OnSelchangeWhat() 
{
	const openvrl::ulong what = m_What.GetCurSel();
	openvrl::ulong i;
	openvrl::ulong cb;

	m_Materials.DeleteAllItems();
	switch ( what )
	{
	case 0:
		cb =m_tpl->textures();
		break;
	case 1:
		cb = m_tpl->materials();
		break;
	case 2:
		cb = m_tpl->lights();
		break;
	case 3:
		cb = m_tpl->cameras();
		break;
	case 4:
		cb = m_tpl->rawmeshes();
		break;
	}
	
	for ( i=0;i<cb;i++ )
		AddString(i, what);
}

void CMaterials::AddString(openvrl::ulong i, openvrl::ulong what)
{
	switch ( what )
	{
	case 0:
		m_Materials.InsertItem(m_Materials.GetItemCount(), m_tpl->texture(i)->head.name);
		break;
	case 1:
		m_Materials.InsertItem(m_Materials.GetItemCount(), m_tpl->material(i)->name);
		break;
	case 2:
		m_Materials.InsertItem(m_Materials.GetItemCount(), m_tpl->light(i)->name);
		break;
	case 3:
		m_Materials.InsertItem(m_Materials.GetItemCount(), m_tpl->camera(i)->name);
		break;
	case 4:
		m_Materials.InsertItem(m_Materials.GetItemCount(), m_tpl->rawmesh(i)->name);
		break;
	}
	SetString(i, what);
}

void CMaterials::SetString(openvrl::ulong i, openvrl::ulong what)
{
	char str[128];
	switch ( what )
	{
	case 0:
		m_Materials.SetItemText(i,0, m_tpl->texture(i)->head.name);
		sprintf(str, "0x%08x", m_tpl->texture(i)->head.version);
		m_Materials.SetItemText(i, 1, str);
		m_Materials.SetItemText(i, 2, m_tpl->texture(i)->head.signature);
		break;
	case 1:
		m_Materials.SetItemText(i, 0, m_tpl->material(i)->name);
		sprintf(str, "0x%08x", m_tpl->material(i)->version);
		m_Materials.SetItemText(i, 1, str);
		m_Materials.SetItemText(i, 2, m_tpl->material(i)->signature);
		break;
	case 2:
		m_Materials.SetItemText(i, 0, m_tpl->light(i)->name);
		sprintf(str, "0x%08x", m_tpl->light(i)->version);
		m_Materials.SetItemText(i, 1, str);
		m_Materials.SetItemText(i, 2, m_tpl->light(i)->signature);
		break;
	case 3:
		m_Materials.SetItemText(i, 0, m_tpl->camera(i)->name);
		sprintf(str, "0x%08x", m_tpl->camera(i)->version);
		m_Materials.SetItemText(i, 1, str);
		m_Materials.SetItemText(i, 2, m_tpl->camera(i)->signature);
		break;
	case 4:
		m_Materials.SetItemText(i, 0, m_tpl->rawmesh(i)->name);
		sprintf(str, "0x%08x", m_tpl->rawmesh(i)->version);
		m_Materials.SetItemText(i, 1, str);
		m_Materials.SetItemText(i, 2, m_tpl->rawmesh(i)->signature);
		break;
	}
}

void CMaterials::OnLvnItemchangedMaterials(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CMaterials::OnHdnItemdblclickMaterials(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here


	*pResult = 0;
}

void CMaterials::OnHdnItemclickMaterials(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CMaterials::OnNMDblclkMaterials(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	OnDblclkMaterials() ;
	*pResult = 0;
}
