// PanelListDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "ElectronicSaw.h"
#include "PanelListDlg.h"
#include "afxdialogex.h"

#include "../../FileReadWrite/ExcelReadWrite/Excel/CApplication.h"
#include "../../FileReadWrite/ExcelReadWrite/Excel/CRange.h"
#include "../../FileReadWrite/ExcelReadWrite/Excel/CWorkbook.h"
#include "../../FileReadWrite/ExcelReadWrite/Excel/CWorkbooks.h"
#include "../../FileReadWrite/ExcelReadWrite/Excel/CWorksheet.h"
#include "../../FileReadWrite/ExcelReadWrite/Excel/CWorksheets.h"
#include "../../FileReadWrite/ExcelReadWrite/ExcelReadWrite.h"

#include "..\Misc\Misc.h"
// CPanelListDlg 对话框

IMPLEMENT_DYNAMIC(CPanelListDlg, CDialog)

//************************************
// Method:    CPanelListDlg
// FullName:  CPanelListDlg::CPanelListDlg
// Access:    public 
// Returns:   
// Qualifier: : CDialog(IDD, pParent)
// Parameter: CWnd * pParent
//************************************
CPanelListDlg::CPanelListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPanelListDlg::IDD, pParent)
{
	LPCTSTR s = "123";
	vector<ComponentInputItem> v;
	int a = add(s, v);


}

CPanelListDlg::~CPanelListDlg()
{
}

void CPanelListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PANEL, m_lcPanelList);
}


BEGIN_MESSAGE_MAP(CPanelListDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPanelListDlg 消息处理程序


BOOL CPanelListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_lcPanelList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lcPanelList.InsertColumn(0, "条码", 0, 160);
	m_lcPanelList.InsertColumn(1, "柜体名称", 0, 160);
	m_lcPanelList.InsertColumn(2, "板件名称", 0, 160);
	m_lcPanelList.InsertColumn(3, "成品长", 0, 160);
	m_lcPanelList.InsertColumn(4, "成品宽", 0, 160);
	m_lcPanelList.InsertColumn(5, "板件厚", 0, 160);
	m_lcPanelList.InsertColumn(6, "材质", 0, 160);
	m_lcPanelList.InsertColumn(7, "纹理", 0, 160);
	m_lcPanelList.InsertColumn(8, "需切数量", 0, 160);
	m_lcPanelList.InsertColumn(9, "异形数据", 0, 160);
	m_lcPanelList.InsertColumn(10, "正面孔", 0, 160);
	m_lcPanelList.InsertColumn(11, "反面孔", 0, 160);
	m_lcPanelList.InsertColumn(12, "正面槽", 0, 160);
	m_lcPanelList.InsertColumn(13, "反面槽", 0, 160);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPanelListDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CRect rcClient;
	GetClientRect(rcClient);
	dc.FillSolidRect(rcClient, RGB(255, 100, 255));
}


void CPanelListDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_lcPanelList.GetSafeHwnd())
	{
		m_lcPanelList.MoveWindow(0, 0, cx, cy);
	}
}

void CPanelListDlg::SetPanelInfo(vector<ComponentInputItem>& vComponentInputItem)
{
	m_lcPanelList.DeleteAllItems();

	int nItem = 0;
	for(int i = 0; i < vComponentInputItem.size(); i++)
	{
		m_lcPanelList.InsertItem(nItem, vComponentInputItem[i].m_strBarcode);
		m_lcPanelList.SetItemText(nItem, 1, vComponentInputItem[i].m_strCabinetName);
		m_lcPanelList.SetItemText(nItem, 2, vComponentInputItem[i].m_strPanelName);
		m_lcPanelList.SetItemText(nItem, 3, GetFloatString(vComponentInputItem[i].m_fLength, 0));
		m_lcPanelList.SetItemText(nItem, 4, GetFloatString(vComponentInputItem[i].m_fWidth, 0));
		m_lcPanelList.SetItemText(nItem, 5, GetFloatString(vComponentInputItem[i].m_fThickness, 0));
		m_lcPanelList.SetItemText(nItem, 6, vComponentInputItem[i].m_strMaterial);
		m_lcPanelList.SetItemText(nItem, 7, vComponentInputItem[i].m_strTexture);
		m_lcPanelList.SetItemText(nItem, 8, GetFloatString(vComponentInputItem[i].m_nCount, 0));
		m_lcPanelList.SetItemText(nItem, 9, vComponentInputItem[i].m_strAbnormalInfo);
		m_lcPanelList.SetItemText(nItem, 10, vComponentInputItem[i].m_strFrontHoleInfo	);
		m_lcPanelList.SetItemText(nItem, 11, vComponentInputItem[i].m_strBackHoleInfo	);
		m_lcPanelList.SetItemText(nItem, 12, vComponentInputItem[i].m_strFrontSlotInfo	);
		m_lcPanelList.SetItemText(nItem, 13, vComponentInputItem[i].m_strBackSlotInfo	);

		nItem++;
	}
}