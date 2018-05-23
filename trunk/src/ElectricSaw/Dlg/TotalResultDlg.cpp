// TotalResultDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "../ElectricSaw.h"
#include "TotalResultDlg.h"
#include "afxdialogex.h"
#include "../Misc/Misc.h"

#include "../../../include/DataManager/BaseDataType/CommonData/CommonData.h"
#include "../../../include/DataManager/BaseDataType/CSingleton/CSingleon.h"
#include "../../../include/DataManager/BaseDataType/CSolution/CSolution.h"
#include "../../../include/DataManager/BaseDataType/Component/Component.h"
#include "../../../include/DataManager/BaseDataType/Panel/Panel.h"


// CTotalResultDlg 对话框

IMPLEMENT_DYNAMIC(CTotalResultDlg, CDialog)

CTotalResultDlg::CTotalResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTotalResultDlg::IDD, pParent)
{

}

CTotalResultDlg::~CTotalResultDlg()
{
}

void CTotalResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TOTAL_SULUTION_PANEL, m_lcTotalSolutionPanel);
}


BEGIN_MESSAGE_MAP(CTotalResultDlg, CDialog)
	ON_WM_PAINT()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TOTAL_SULUTION_PANEL, &CTotalResultDlg::OnLvnItemchangedListTotalSolutionPanel)
END_MESSAGE_MAP()


// CTotalResultDlg 消息处理程序
BOOL CTotalResultDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_lcTotalSolutionPanel.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lcTotalSolutionPanel.InsertColumn(0, "材质", 0, 100);
	m_lcTotalSolutionPanel.InsertColumn(1, "优化率", 0, 80);
	m_lcTotalSolutionPanel.InsertColumn(2, "厚度", 0, 50);
	m_lcTotalSolutionPanel.InsertColumn(3, "尺寸", 0, 100);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTotalResultDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CRect rcClient;
	GetClientRect(rcClient);
	//dc.FillSolidRect(rcClient, RGB(255, 0, 0));
}

void CTotalResultDlg::RefreshOptimizeResult()
{
	RefreshTotalSolutionPanel();
	m_lcTotalSolutionPanel.EnsureVisible(0, FALSE);
	m_lcTotalSolutionPanel.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
}

void CTotalResultDlg::RefreshTotalSolutionPanel()
{
	m_lcTotalSolutionPanel.DeleteAllItems();

	int nItem = 0;

#if 0
	for(int i = 0; i < CSingleon::GetSingleton()->m_CurrentSolutionList.size(); i++)
	{
		CSolution* pSolution = CSingleon::GetSingleton()->m_CurrentSolutionList[i];
		for(int j = 0; j < CSingleon::GetSingleton()->m_CurrentSolutionList[i]->m_PanelList.size(); j++)
		{
			Panel& thePanel = *(CSingleon::GetSingleton()->m_CurrentSolutionList[i]->m_PanelList[j]);

			CString strSize;
			strSize.Format("%s*%s", GetFloatString(thePanel.m_RealLength, 0), GetFloatString(thePanel.m_RealWidth, 0));
			PanelViewingParam* pParam = new PanelViewingParam;
			pParam->m_pSolution = CSingleon::GetSingleton()->m_CurrentSolutionList[i];
			pParam->m_pPanel = CSingleon::GetSingleton()->m_CurrentSolutionList[i]->m_PanelList[j];

			m_lcTotalSolutionPanel.InsertItem(nItem, pSolution->m_strMaterial);			
			m_lcTotalSolutionPanel.SetItemText(nItem, 1, GetFloatString(thePanel.m_Thickness, 0));	
			m_lcTotalSolutionPanel.SetItemText(nItem, 2, strSize);	
			m_lcTotalSolutionPanel.SetItemText(nItem, 3, "111");	
			m_lcTotalSolutionPanel.SetItemData(nItem, (DWORD_PTR)pParam);
			nItem++;
		}
	}

#else

	for(int i = 0; i < CSingleon::GetSingleton()->m_BackupSolutionList.size(); i++)
	{
		CSolution* pSolution = CSingleon::GetSingleton()->m_BackupSolutionList[i];
		for(int j = 0; j < CSingleon::GetSingleton()->m_BackupSolutionList[i]->m_PanelList.size(); j++)
		{
			Panel& thePanel = *(CSingleon::GetSingleton()->m_BackupSolutionList[i]->m_PanelList[j]);

			CString strSize;
			strSize.Format("%s*%s", GetFloatString(thePanel.m_RealLength, 0), GetFloatString(thePanel.m_RealWidth, 0));
			PanelViewingParam* pParam = new PanelViewingParam;
			pParam->m_pSolution = CSingleon::GetSingleton()->m_BackupSolutionList[i];
			pParam->m_pPanel = CSingleon::GetSingleton()->m_BackupSolutionList[i]->m_PanelList[j];

			CString strUtilization;
			strUtilization.Format("%f", thePanel.GetUtilization());


			m_lcTotalSolutionPanel.InsertItem(nItem, pSolution->m_strMaterial);	
			m_lcTotalSolutionPanel.SetItemText(nItem, 1, strUtilization);			
			m_lcTotalSolutionPanel.SetItemText(nItem, 2, GetFloatString(thePanel.m_Thickness, 0));	
			m_lcTotalSolutionPanel.SetItemText(nItem, 3, strSize);	
			m_lcTotalSolutionPanel.SetItemData(nItem, (DWORD_PTR)pParam);
			nItem++;
		}
	}

#endif




}

void CTotalResultDlg::OnLvnItemchangedListTotalSolutionPanel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(pNMLV->uNewState & LVIS_SELECTED)
	{
		PanelViewingParam* pParam = (PanelViewingParam*)m_lcTotalSolutionPanel.GetItemData(pNMLV->iItem);
		::PostMessage(GetParent()->GetSafeHwnd(), WM_REFRESH_PANEL_VIEW, (WPARAM)pParam, 0);
	}
	//m_lcPanelFace.GetFirstSelectedItemPosition()
	*pResult = 0;
}