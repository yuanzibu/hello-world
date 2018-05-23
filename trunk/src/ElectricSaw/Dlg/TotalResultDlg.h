#pragma once
#include "..\resource.h"
#include "afxcmn.h"

// CTotalResultDlg 对话框

class CTotalResultDlg : public CDialog
{
	DECLARE_DYNAMIC(CTotalResultDlg)

public:
	CTotalResultDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTotalResultDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_TOTAL_RESULT };

	void RefreshOptimizeResult();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListTotalSolutionPanel(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

	void RefreshTotalSolutionPanel();
public:
	afx_msg void OnPaint();
protected:
	CListCtrl m_lcTotalSolutionPanel;
};
