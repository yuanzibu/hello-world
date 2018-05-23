
// ElectricSawDlg.h : 头文件
//

#pragma once

#include "../../include/DataManager/BaseDataType/CommonData/CommonData.h"

class CPanelListDlg;
class CResultDlg;
// CElectricSawDlg 对话框
class CElectricSawDlg : public CDialogEx
{
// 构造
public:
	CElectricSawDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ELECTRICSAW_DIALOG };
	enum ViewType{VIEW_PANEL_LIST, VIEW_RESULT};
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

	CRect GetViewRect();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonOptimize();

protected:
	CString m_strPanelInfoFile;
	CPanelListDlg* m_pPanelListDlg;
	CResultDlg* m_pResultDlg;
	ViewType m_eCurViewType;

	vector<ComponentInputItem> m_vComponentInputItem;
	//CSingleon m_data;
public:
	afx_msg void OnBnClickedButtonPanelList();
	afx_msg void OnBnClickedButtonResult();
	void SwitchView(ViewType eViewType);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int m_valFirstSectionOPTimes;
	CComboBox m_cbxFirstSectionOPMethod;
	float m_valPanelLength;
	float m_valPanelWidth;
	float m_valKerfWidth;
	int m_valThirdSectionOPTimes;
	int m_valSecondSectionOPTimes;
	float m_valThirdSectionAcceptableUtilization;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonOutputNc();
};
