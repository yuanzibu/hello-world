
// TestBase64Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestBase64.h"
#include "TestBase64Dlg.h"
#include "DES/DES.h"
#include "afxdialogex.h"



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


// CTestBase64Dlg 对话框




CTestBase64Dlg::CTestBase64Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestBase64Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_valSrcFilePath = _T("");
	m_valDstFilePath = _T("");
}

void CTestBase64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_valSrcFilePath);
}

BEGIN_MESSAGE_MAP(CTestBase64Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestBase64Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestBase64Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_FIND_SRC_PATH, &CTestBase64Dlg::OnBnClickedButtonFindSrcPath)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, &CTestBase64Dlg::OnBnClickedButtonEncrypt)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, &CTestBase64Dlg::OnBnClickedButtonDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CTestBase64Dlg::OnBnClickedButtonTest)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CTestBase64Dlg 消息处理程序

BOOL CTestBase64Dlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestBase64Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestBase64Dlg::OnPaint()
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
HCURSOR CTestBase64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


						// HIJKLMNABCDEFGUVWXYZOPQRSTuvwxyzabcdefgopqrsthijklmn789654123#*/

static const char *codes = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  

static const unsigned char map[256] = {  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 253, 255,  
	255, 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 253, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255,  62, 255, 255, 255,  63,  
	52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,  
	255, 254, 255, 255, 255,   0,   1,   2,   3,   4,   5,   6,  
	7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  
	19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255,  
	255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  
	37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  
	49,  50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  
	255, 255, 255, 255 };  

int base64_encode(const unsigned char *in,  unsigned long len,   
		unsigned char *out)  
	{  
		unsigned long i, len2, leven;  
		unsigned char *p;  
		/* valid output size ? */  
		len2 = 4 * ((len + 2) / 3);  
		p = out;  
		leven = 3*(len / 3);  
		for (i = 0; i < leven; i += 3) {  
			*p++ = codes[in[0] >> 2];  
			*p++ = codes[((in[0] & 3) << 4) + (in[1] >> 4)];  
			*p++ = codes[((in[1] & 0xf) << 2) + (in[2] >> 6)];  
			*p++ = codes[in[2] & 0x3f];  
			in += 3;  
		}  
		/* Pad it if necessary...  */  
		if (i < len) {  
			unsigned a = in[0];  
			unsigned b = (i+1 < len) ? in[1] : 0;  
			unsigned c = 0;  

			*p++ = codes[a >> 2];  
			*p++ = codes[((a & 3) << 4) + (b >> 4)];  
			*p++ = (i+1 < len) ? codes[((b & 0xf) << 2) + (c >> 6)] : '=';  
			*p++ = '=';  
		}  

		/* append a NULL byte */  
		*p = '\0';  

		return p - out;  
	}  
static int base64_decode_map[256] = {  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0   - 15  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 16  - 31  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, // 32  - 47  
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, // 48  - 63  
	-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, // 64  - 79  
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, // 80  - 95  
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, // 96  - 111  
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, // 112 - 127  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 128 - 143  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 144 - 159   
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 160 - 175  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 176 - 191  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 192 - 207  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 208 - 223  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 224 - 239  
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 240 - 255  
};  

int base64_decode(const unsigned char *in, unsigned char *out)  
{  
	unsigned long t, x, y, z;  
	unsigned char c;  
	int g = 3;  

	for (x = y = z = t = 0; in[x]!=0;) {  
		c = map[in[x++]];  
		if (c == 255) return -1;  
		if (c == 253) continue;  
		if (c == 254) { c = 0; g--; }  
		t = (t<<6)|c;  
		if (++y == 4) {  
			//          if (z + g > *outlen) { return CRYPT_BUFFER_OVERFLOW; }  
			out[z++] = (unsigned char)((t>>16)&255);  
			if (g > 1) out[z++] = (unsigned char)((t>>8)&255);  
			if (g > 2) out[z++] = (unsigned char)(t&255);  
			y = t = 0;  
		}  
	}  
	//  if (y != 0) {  
	//      return -1;  
	//  }  
	return z;  
}  


/*---------------------------------------*/
//	函数说明：
//		加密文件
//
//
//	参数：
//
//
//
//
//	返回值:
//
//
/*---------------------------------------*/
int encrypt_base64(char* src_path, char* dst_path) 
{
	int src_file_len;
	CFile src_file, dst_file;
	char* pSrcBuf = NULL;
	char* pDstBuf = NULL;

	try
	{
		// 将源文件读到缓冲区
		src_file.Open((LPCTSTR)src_path, CFile::modeRead);
		src_file_len = src_file.GetLength();
		pSrcBuf = new char[src_file_len];
		src_file.Read(pSrcBuf, src_file_len);
		src_file.Close();

		// 将缓冲区的内容用base64加密
		pDstBuf = new char[src_file_len*2];	// 加密会变成，但绝对不会超过2倍
		memset(pDstBuf, 0, src_file_len*2);

		base64_encode((const unsigned char*)pSrcBuf, src_file_len, (unsigned char*)pDstBuf);

		// 写加密文件文件
		DeleteFile((LPCTSTR)dst_path);
		dst_file.Open((LPCTSTR)dst_path, CFile::modeReadWrite | CFile::modeCreate);
		CString str(pDstBuf);
		dst_file.Write(pDstBuf, str.GetLength());
		dst_file.Close();

		// 清空内存
		delete[]	pSrcBuf;
		delete[]	pDstBuf;

	}
	catch (CMemoryException* e)
	{

	}
	catch (CFileException* e)
	{
	}
	catch (CException* e)
	{
	}


	return 0;
}





/*---------------------------------------*/
//	函数说明：
//		解密文件
//
//
//	参数：
//
//
//
//
//	返回值:
//
//
/*---------------------------------------*/
int decrypt_base64(char* src_path, char* dst_path)
{
	int src_file_len;
	CFile src_file, dst_file;
	char* pSrcBuf = NULL;
	char* pDstBuf = NULL;

	// 将源文件读到缓冲区
	src_file.Open((LPCTSTR)src_path, CFile::modeRead);
	src_file_len = src_file.GetLength();
	pSrcBuf = new char[src_file_len];
	src_file.Read(pSrcBuf, src_file_len);
	src_file.Close();

	// 将缓冲区的内容解密
	pDstBuf = new char[src_file_len];	// 解密长度一定比加密后的短

	memset(pDstBuf, 0, src_file_len);

	int dst_file_len ;
	base64_decode((const unsigned char*)pSrcBuf, (unsigned char *)pDstBuf);

	CString tmp_str = pDstBuf;

	dst_file_len = tmp_str.GetLength();


	// 写解密文件文件
	DeleteFile((LPCTSTR)dst_path);


	dst_file.Open((LPCTSTR)dst_path, CFile::modeReadWrite | CFile::modeCreate);
	dst_file.Write(pDstBuf, dst_file_len);
 	dst_file.Close();

	// 清空内存
	delete[]	pSrcBuf;
	delete[]	pDstBuf;

	return 0;
}







void CTestBase64Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	

	CDialogEx::OnOK();
}


void CTestBase64Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	




	CDialogEx::OnCancel();
}





void CTestBase64Dlg::OnBnClickedButtonFindSrcPath()
{
	// TODO: 在此添加控件通知处理程序代码

	CString filter = "hge 文件(*.hge)|*.hge|xml 文件(*.xml)|*.xml|所有文件 (*.*)|*.*||";

	CFileDialog fileDlg (TRUE, _T("xml"), _T("*.xml"), OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, filter, NULL);
	if ( fileDlg.DoModal() == IDOK)
	{
		m_valSrcFilePath = fileDlg.GetPathName();
		UpdateData(FALSE);
	}

}


void CTestBase64Dlg::OnBnClickedButtonEncrypt()
{
	// TODO: 在此添加控件通知处理程序代码

	m_valDstFilePath = m_valSrcFilePath.Left(m_valSrcFilePath.ReverseFind('.')) + ".hge";


	//encrypt_base64(m_valSrcFilePath.GetBuffer(), m_valDstFilePath.GetBuffer());

	func_drawing0(m_valSrcFilePath.GetBuffer(), m_valDstFilePath.GetBuffer());


	AfxMessageBox("加密完成！");

}


void CTestBase64Dlg::OnBnClickedButtonDecrypt()
{
	// TODO: 在此添加控件通知处理程序代码


	m_valDstFilePath = m_valSrcFilePath.Left(m_valSrcFilePath.ReverseFind('.')) + ".xml";

	//decrypt_base64(m_valSrcFilePath.GetBuffer(), m_valDstFilePath.GetBuffer());

	func_drawing1(m_valSrcFilePath.GetBuffer(), m_valDstFilePath.GetBuffer());

	AfxMessageBox("解密完成！");

}



void CTestBase64Dlg::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码

	char* pSrc = "123456789";
	char Dst[20] = {0};
	char buf[20] = {0};

	//base64_encode((const  char * )pSrc, buf, 10);
	//base64_decode(buf, ( char*)Dst);


	int a = 0;

}


void CTestBase64Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int DropCount=DragQueryFile(hDropInfo,-1,NULL,0);//取得被拖动文件的数目  
	for(int i=0;i< DropCount;i++)  
	{  
		char Str[MAX_PATH];  
		DragQueryFile(hDropInfo,i,Str,MAX_PATH);//获得拖曳的第i个文件的文件名  
		
		m_valSrcFilePath.SetString(Str);
		UpdateData(FALSE);
	}  


	DragFinish(hDropInfo);  //拖放结束后,释放内存  

	CDialogEx::OnDropFiles(hDropInfo);
}
