
// ElectricSaw.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ElectricSaw.h"
#include "ElectricSawDlg.h"

#include "../../include/DataManager/BaseDataType/CSingleton/CSingleon.h"
#include "../../include/TinyXml/tinyxml.h"
#include "../../include/FileReadWrite/HgmReadWrite/HGTools.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CElectricSawApp

BEGIN_MESSAGE_MAP(CElectricSawApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CElectricSawApp 构造

CElectricSawApp::CElectricSawApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CElectricSawApp 对象

CElectricSawApp theApp;


// CElectricSawApp 初始化

BOOL CElectricSawApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	Gdiplus::GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL); 

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CElectricSawDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。



	// 程序启动前加载配置文件
	CSingleon* pSingleton = CSingleon::GetSingleton();

	// 加载刀库文件
	//从hgx文件目录生成xml文件目录
//	CString knifeType_hgm = HGTools::getRelativePath("kdata\\knifetype.hgm");
// 	CString knifeType_xml = HGTools::getXmlPathFromHgxPath(knifeType_hgm);
// 
// 	HGTools::decryptFile(knifeType_hgm,knifeType_xml);
// 	pSingleton->m_pKnifetypeDoc->LoadFile(knifeType_xml);
// 	HGTools::deleteFile(knifeType_xml);






	return FALSE;
}



int CElectricSawApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	GdiplusShutdown(m_pGdiToken);
	return CWinApp::ExitInstance();
}
