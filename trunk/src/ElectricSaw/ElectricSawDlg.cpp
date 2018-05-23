
// ElectricSawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElectricSaw.h"
#include "ElectricSawDlg.h"
#include "afxdialogex.h"

#include "Dlg/PanelListDlg.h"
#include "Dlg/ResultDlg.h"

#include "DataProcess/DataProcess.h"

// 外部DataManager.dll的头文件
#include "../../include/DataManager/BaseDataType/CSingleton/CSingleon.h"
#include "../../include/DataManager/BaseDataType/CSolution/CSolution.h"
#include "../../include/DataManager/BaseDataType/CommonData/CommonData.h"


// 外部FileReadWrite.dll的头文件
#include "../../include/FileReadWrite/ExcelReadWrite/ExcelReadWrite.h"
#include "../../include/FileReadWrite/HgmReadWrite/HgmReadWrite.h"
#include "../../include/FileReadWrite/HgyReadWrite/HgyReadWrite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CElectricSawDlg 对话框




CElectricSawDlg::CElectricSawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CElectricSawDlg::IDD, pParent)
	, m_pPanelListDlg(NULL)
	, m_pResultDlg(NULL)
	, m_eCurViewType(VIEW_PANEL_LIST)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_valFirstSectionOPTimes = 1;						// 初始化 第一阶段优化次数
	m_valPanelLength = 2440.0f;
	m_valPanelWidth = 1220.0f;
	m_valKerfWidth = 6.0f;	m_valThirdSectionOPTimes = 0;
	m_valSecondSectionOPTimes = 0;
	m_valThirdSectionAcceptableUtilization = 0.90f;
}

void CElectricSawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIRST_SECTION_OP_TIMES, m_valFirstSectionOPTimes);
	DDV_MinMaxInt(pDX, m_valFirstSectionOPTimes, 1, 1000000);
	DDX_Control(pDX, IDC_COMBO_FIRST_SECTION_OP_METHOD, m_cbxFirstSectionOPMethod);
	DDX_Text(pDX, IDC_EDIT_PANEL_LENGTH, m_valPanelLength);
	DDV_MinMaxFloat(pDX, m_valPanelLength, 1, 10000);
	DDX_Text(pDX, IDC_EDIT_PANEL_WIDTH, m_valPanelWidth);
	DDV_MinMaxFloat(pDX, m_valPanelWidth, 1, 10000);
	DDX_Text(pDX, IDC_EDIT_KERF_WIDTH, m_valKerfWidth);
	DDV_MinMaxFloat(pDX, m_valKerfWidth, 0.1f, 100.0f);
	DDX_Text(pDX, IDC_EDIT_THIRD_SECTION_OP_TIMES, m_valThirdSectionOPTimes);
	DDV_MinMaxInt(pDX, m_valThirdSectionOPTimes, 0, 100000);
	DDX_Text(pDX, IDC_EDIT_SECOND_SECTION_OP_TIMES, m_valSecondSectionOPTimes);
	DDV_MinMaxInt(pDX, m_valSecondSectionOPTimes, 0, 100000);
	DDX_Text(pDX, IDC_EDIT_THIRD_SECTION_ACCEPTABLE_UTILIZATION, m_valThirdSectionAcceptableUtilization);
	DDV_MinMaxFloat(pDX, m_valThirdSectionAcceptableUtilization, 0.1f, 1.0f);
}

BEGIN_MESSAGE_MAP(CElectricSawDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CElectricSawDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CElectricSawDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_PANEL_LIST, &CElectricSawDlg::OnBnClickedButtonPanelList)
	ON_BN_CLICKED(IDC_BUTTON_RESULT, &CElectricSawDlg::OnBnClickedButtonResult)
	ON_BN_CLICKED(IDC_BUTTON_OPTIMIZE, &CElectricSawDlg::OnBnClickedButtonOptimize)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CElectricSawDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_NC, &CElectricSawDlg::OnBnClickedButtonOutputNc)
END_MESSAGE_MAP()


// CElectricSawDlg 消息处理程序

BOOL CElectricSawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码
	SwitchView(VIEW_PANEL_LIST);


	m_cbxFirstSectionOPMethod.InsertString(0, "改进最低轮廓线算法");
	m_cbxFirstSectionOPMethod.InsertString(1, "改进贪心算法");
	m_cbxFirstSectionOPMethod.InsertString(2, "组合算法");

	m_cbxFirstSectionOPMethod.SetCurSel(1);





	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CElectricSawDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CElectricSawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CElectricSawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CElectricSawDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	int i = 1;

	int j = 0;

	j = 1;

	CSingleon* p = CSingleon::GetSingleton();


	int a = 0;

	CDialogEx::OnOK();
}



void CElectricSawDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	
	// 先清除上一次的数据
	CSingleon* pSingleton = CSingleon::GetSingleton();
	pSingleton->ClearAllData();
	m_vComponentInputItem.clear();


	CString m_strPanelInfoFile;
	CString filter = "xls 文件(*.xls)|*.xls|hgm 文件(*.hgm)|*.hgm|xml 文件(*.xml)|*.xml|所有文件 (*.*)|*.*||";

	CFileDialog fileDlg (true, _T("xls"), _T("*.xls"), OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, filter, NULL);
	if ( fileDlg.DoModal() == IDOK)
	{
		m_strPanelInfoFile = fileDlg.GetPathName();

		int Which = m_strPanelInfoFile.ReverseFind('.');  
		CString strExtName = m_strPanelInfoFile.Right(m_strPanelInfoFile.GetLength() - Which - 1);  
		strExtName.MakeLower();

		if (strExtName == "xls" || strExtName == "xlsx" )
		{
			if(ExcelReadWrite::ReadPanelInfo(m_strPanelInfoFile, m_vComponentInputItem) == true)
			{
				m_pPanelListDlg->SetPanelInfo(m_vComponentInputItem);
			}


			// 计算小板
			int nCpnNum = 0;
			for(vector<ComponentInputItem>::iterator it = m_vComponentInputItem.begin(); it != m_vComponentInputItem.end(); )
			{
				ComponentInputItem& item = *it;
				if (item.m_nCount > 0)
				{
					nCpnNum += item.m_nCount;
					it++;
				}
				else
				{
					it = m_vComponentInputItem.erase(it);
				}
			}

			CString str;
			str.Format("%d", nCpnNum);
			str += "块小板";
			AfxMessageBox(str);
				
		}
		else if (strExtName == "hgm")
		{
			if(HgmReadWrite::ReadPanelInfo(m_strPanelInfoFile, m_vComponentInputItem) == true)
			{
				m_pPanelListDlg->SetPanelInfo(m_vComponentInputItem);
			}

			// 计算小板
			int nCpnNum = 0;
			for(vector<ComponentInputItem>::iterator it = m_vComponentInputItem.begin(); it != m_vComponentInputItem.end(); )
			{
				ComponentInputItem& item = *it;
				if (item.m_nCount > 0)
				{
					nCpnNum += item.m_nCount;
					it++;
				}
				else
				{
					it = m_vComponentInputItem.erase(it);
				}
			}

			CString str;
			str.Format("%d", nCpnNum);
			str += "块小板";
			AfxMessageBox(str);

		}
		else if (strExtName == "xml")
		{
			if(HgyReadWrite::ReadHgy(m_strPanelInfoFile) != true)
			{
				AfxMessageBox("hgy 文件出错!");
			}
			else
			{
				m_vComponentInputItem = pSingleton->m_vBackupComponentInputItem;
			}

			SwitchView(VIEW_RESULT);
			m_pResultDlg->RefreshOptimizeResult();
		}
	}

	// 备份输入板件组
	pSingleton->SetBackupComponentInputItem(m_vComponentInputItem);

}


void CElectricSawDlg::OnBnClickedButtonPanelList()
{
	// TODO: 在此添加控件通知处理程序代码
	SwitchView(VIEW_PANEL_LIST);
}


void CElectricSawDlg::OnBnClickedButtonResult()
{
	// TODO: 在此添加控件通知处理程序代码
	SwitchView(VIEW_RESULT);
}

void CElectricSawDlg::SwitchView(ViewType eViewType)
{
	//if(eViewType == m_eCurViewType)
	//	return;

	switch(eViewType)
	{
	case VIEW_PANEL_LIST:
		if(m_pPanelListDlg == NULL || m_pPanelListDlg->GetSafeHwnd() == NULL)
		{
			delete m_pPanelListDlg;
			m_pPanelListDlg = new CPanelListDlg(this);
			m_pPanelListDlg->Create(CPanelListDlg::IDD, this);
			
		}
		if(m_pResultDlg != NULL && m_pResultDlg->GetSafeHwnd())
			m_pResultDlg->ShowWindow(SW_HIDE);
		//m_pResultDlg->SetWindowPos(NULL,10, 500, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		m_pPanelListDlg->MoveWindow(/*0, 300, 500, 500*/GetViewRect());
		m_pPanelListDlg->ShowWindow(SW_SHOW);
		m_eCurViewType = VIEW_PANEL_LIST;
		break;

	case VIEW_RESULT:
		if(m_pResultDlg == NULL || m_pResultDlg->GetSafeHwnd() == NULL)
		{
			delete m_pResultDlg;
			m_pResultDlg = new CResultDlg(this);
			m_pResultDlg->Create(CResultDlg::IDD, this);
			
		}
		if(m_pPanelListDlg != NULL && m_pPanelListDlg->GetSafeHwnd())
			m_pPanelListDlg->ShowWindow(SW_HIDE);
		m_pResultDlg->ShowWindow(SW_SHOW);
		m_pResultDlg->MoveWindow(/*0, 300, 500, 500*/GetViewRect());
		m_eCurViewType = VIEW_RESULT;
		break;
	}
}

CRect CElectricSawDlg::GetViewRect()
{
	CRect rcRet;
	CRect rcClient;
	GetClientRect(rcClient);
	rcRet.CopyRect(rcClient);
	rcRet.InflateRect(0, -150, 0, 0);
	return rcRet;
}

void CElectricSawDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_pPanelListDlg != NULL && m_pPanelListDlg->GetSafeHwnd())
		m_pPanelListDlg->MoveWindow(GetViewRect());
	if(m_pResultDlg != NULL && m_pResultDlg->GetSafeHwnd())
		m_pResultDlg->MoveWindow(GetViewRect());
}

void CElectricSawDlg::OnBnClickedButtonOptimize()
{
	// 获取界面数据
	UpdateData(TRUE);

	// 切换视图，新建窗口
	SwitchView(VIEW_RESULT);

	vector<ComponentList> vComponentList;
	ComponentList componentList;
	CSingleon* pSingleton = CSingleon::GetSingleton();

	//pSingleton->ClearAllData();

	pSingleton->m_BaseInfo.m_SawKerfWidth = m_valKerfWidth;
	pSingleton->m_BaseInfo.m_PanelLength = m_valPanelLength;
	pSingleton->m_BaseInfo.m_PanelWidth = m_valPanelWidth;

	pSingleton->m_BaseInfo.m_FirstSectionOPTimes = m_valFirstSectionOPTimes;
	pSingleton->m_BaseInfo.m_FirstSectionOPMethod = m_cbxFirstSectionOPMethod.GetCurSel();
	pSingleton->m_BaseInfo.m_SecondSectionOPTimes = m_valSecondSectionOPTimes;
	pSingleton->m_BaseInfo.m_ThirdSectionOPTimes = m_valThirdSectionOPTimes;
	pSingleton->m_BaseInfo.m_ThirdSectionOAccptableUtilization = m_valThirdSectionAcceptableUtilization;


	// 排样原点
	int Org = LayoutOrg_LeftBottom;


	// 第一段优化
	for(int i_first_op_times = 0; i_first_op_times < m_valFirstSectionOPTimes; i_first_op_times++)
	{
		// 清空所有数据
		//pSingleton->ClearAllData();
		pSingleton->ClearCurrentSolution();
		pSingleton->m_vComponentGroup.clear();


		// 重新赋值
		ConvertInputInfoToComponentList(m_vComponentInputItem, componentList);
		SplitComponentList(componentList, pSingleton->m_vComponentGroup);

		// 优化
		if (pSingleton->m_BaseInfo.m_FirstSectionOPMethod == 0)			// 最低轮廓线
		{
			pSingleton->Layout(0, CutDir_Random, Org);
		}
		else if ( pSingleton->m_BaseInfo.m_FirstSectionOPMethod == 1)	// 贪心
		{
			pSingleton->Layout(1, CutDir_Random, Org);
		}
		else
		{
			// 组合 贪心+最低轮廓线
			int flag = m_valFirstSectionOPTimes/2;

			if (i_first_op_times > flag) // 随机
			{
				pSingleton->Layout(0, CutDir_Random, Org);
			}
			else
			{
				pSingleton->Layout(1, CutDir_Random, Org);
			}
		}
		
		pSingleton->BackupBestSolution();

	}

	// 第二段优化
	for (int i_second_op_times = 0; i_second_op_times < m_valSecondSectionOPTimes; i_second_op_times++)
	{
		for(int i_sln = 0; i_sln < pSingleton->GetBackupSolutionNum(); i_sln++)
		{
			CSolution* pSln = pSingleton->m_BackupSolutionList.at(i_sln);

			pSln->ReOptimizeEveryPanel(Org);
		}
	}

	


	// 针对优化率不高的板件重新排样
	for (int i_third_op_times = 0; i_third_op_times < m_valThirdSectionOPTimes; i_third_op_times++)
	{
		for(int i_sln = 0; i_sln < pSingleton->GetBackupSolutionNum(); i_sln++)
		{
			CSolution* pSln = pSingleton->m_BackupSolutionList.at(i_sln);

			pSingleton->ReOptimizeSln(pSln, Org);
		}
	}

	// 更新解决方案ID和板件ID
	pSingleton->UpdateSlnNum();



	CString str;

	str.Format("%d", pSingleton->GetBackupSolutionPanelNum());
	str += "块大板,";
	str = "目前最优:" + str;

	::MessageBox(NULL, str, "", MB_OK);
	
	m_pResultDlg->RefreshOptimizeResult();
}


// 保存优化结果文件
void CElectricSawDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString m_strFilePath;
	//CString filter = "hgy 文件(*.hgy)|*.hgy|所有文件 (*.*)|*.*||";
	CString filter = "xml 文件(*.xml)|*.xml|所有文件 (*.*)|*.*||";

	CFileDialog fileDlg (FALSE, _T("xml"), _T("HG001.xml"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);
	if ( fileDlg.DoModal() == IDOK)
	{
		m_strFilePath = fileDlg.GetPathName();
		HgyReadWrite::WriteHgy(m_strFilePath);
	}

}


void CElectricSawDlg::OnBnClickedButtonOutputNc()
{
	// TODO: 在此添加控件通知处理程序代码

}
