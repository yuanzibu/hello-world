
// TestBase64Dlg.h : 头文件
//

#pragma once


// CTestBase64Dlg 对话框
class CTestBase64Dlg : public CDialogEx
{
// 构造
public:
	CTestBase64Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTBASE64_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	CString m_valSrcFilePath;
	CString m_valDstFilePath;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonFindSrcPath();
	afx_msg void OnBnClickedButtonEncrypt();
	afx_msg void OnBnClickedButtonDecrypt();
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
