// ResultDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "../ElectricSaw.h"
#include "ResultDlg.h"
#include "TotalResultDlg.h"
#include "../Misc/Misc.h"
#include "../../../include/DataManager/BaseDataType/CommonData/CommonData.h"
#include "../../../include/DataManager/BaseDataType/Component/Component.h"
#include "../../../include/DataManager/BaseDataType/Panel/Panel.h"


// CResultDlg 对话框

IMPLEMENT_DYNAMIC(CResultDlg, CDialog)

CResultDlg::CResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResultDlg::IDD, pParent)
	, m_pTotalResultDlg(NULL)
	, m_bDrawPanel(false)
	, m_pImg(NULL)
{

}

CResultDlg::~CResultDlg()
{
	::delete m_pImg;
}

void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_MESSAGE(WM_REFRESH_PANEL_VIEW, &CResultDlg::OnRefreshPanelVeiw)
END_MESSAGE_MAP()


// CResultDlg 消息处理程序


BOOL CResultDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_pTotalResultDlg = new CTotalResultDlg(this);
	m_pTotalResultDlg->Create(CTotalResultDlg::IDD, this);
	m_pTotalResultDlg->MoveWindow(100, 100, 100, 500);
	m_pTotalResultDlg->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CResultDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CRect rcClient;
	GetClientRect(rcClient);
	//dc.FillSolidRect(rcClient, RGB(255, 100, 100));

	CRect rcDrawArea;
	rcDrawArea = GetPanelViewRect();

	Graphics g(dc.m_hDC);

	if(m_bDrawPanel && m_pImg)
	{
		RectF rfDes((REAL)rcDrawArea.left, (REAL)rcDrawArea.top, (REAL)rcDrawArea.Width(), (REAL)rcDrawArea.Height());
		g.DrawImage(m_pImg, rfDes, 0, 0, m_pImg->GetWidth(), m_pImg->GetHeight(), UnitPixel);
	}
}


void CResultDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_pTotalResultDlg->GetSafeHwnd())
	{
		CRect rcTotalResult(cx-300, 0, cx, cy);
		m_pTotalResultDlg->MoveWindow(rcTotalResult);

		Invalidate();
		//InvalidateRect(GetPanelViewRect());
	}
}

void CResultDlg::RefreshOptimizeResult()
{
	m_pTotalResultDlg->RefreshOptimizeResult();
}

CRect CResultDlg::GetPanelViewRect()
{
	CRect rcRet;

	CRect rcClient, rcTotalResultDlg;
	GetClientRect(rcClient);
	m_pTotalResultDlg->GetWindowRect(rcTotalResultDlg);
	ScreenToClient(rcTotalResultDlg);

	rcRet.left = rcClient.left + 10;
	rcRet.top = rcClient.top + 10;
	rcRet.right = rcTotalResultDlg.left - 10;
	rcRet.bottom = rcClient.bottom - 50;

	return rcRet;
}

LRESULT CResultDlg::OnRefreshPanelVeiw(WPARAM wparam, LPARAM lparam)
{
	m_bDrawPanel = true;
	DrawDiagram((PanelViewingParam*)wparam);
	return 0;
}

void CResultDlg::StopDrawing()
{
	m_bDrawPanel = false;
}

void CResultDlg::DrawDiagram(PanelViewingParam* param)
{
	CRect rcDrawArea;
	rcDrawArea = GetPanelViewRect();

	if (param == NULL)
	{
		AfxMessageBox("函数：DrawDiagram 的 param  为空指针");
		return;
	}


	if(m_pImg)
	{
		::delete m_pImg;
		m_pImg = NULL;
	}
	m_pImg = ::new Bitmap(rcDrawArea.Width(), rcDrawArea.Height());
	Graphics* g = Graphics::FromImage(m_pImg);

	g->SetCompositingMode(CompositingModeSourceOver);
	g->SetCompositingQuality(CompositingQualityHighQuality);
	g->SetPixelOffsetMode(PixelOffsetModeHighQuality);
	g->SetInterpolationMode(InterpolationModeHighQualityBicubic);
	g->SetTextContrast(12);
	g->SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	g->SetSmoothingMode(SmoothingModeAntiAlias);

	//g->FillRectangle(&SolidBrush(Color::Blue), (INT)rcDrawArea.left, (INT)rcDrawArea.top, (INT)rcDrawArea.Width(), (INT)rcDrawArea.Height());


	Panel& thePanel = *(param->m_pPanel);
	float fScale = GetScale(thePanel.m_RealLength, thePanel.m_RealWidth, rcDrawArea.Width()-50, rcDrawArea.Height()-50);
	CRect rcPanelArea(50/2, 50/2, rcDrawArea.Width()-50/2, rcDrawArea.Height()-50/2);

	CRect rcPanel((rcDrawArea.Width()-thePanel.m_RealLength*fScale)/2, \
		(rcDrawArea.Height()-thePanel.m_RealWidth*fScale)/2, \
		(rcDrawArea.Width()-thePanel.m_RealLength*fScale)/2 + thePanel.m_RealLength*fScale, \
		(rcDrawArea.Height()-thePanel.m_RealWidth*fScale)/2 + thePanel.m_RealWidth*fScale);

	g->DrawRectangle(&Pen(Color::Red, 2), (INT)rcPanel.left, (INT)rcPanel.top, (INT)rcPanel.Width(), (INT)rcPanel.Height());

	vector<Component*> vAllComponent;
	FindAllcomponentFromPanel(thePanel, vAllComponent);

	for(int i = 0; i < vAllComponent.size(); i++)
	{
		Component& theComponent = *(vAllComponent[i]);
		CRect rcComponent(theComponent.m_x*fScale, (thePanel.m_RealWidth - (theComponent.m_y + theComponent.m_RealWidth))*fScale, (theComponent.m_x + theComponent.m_RealLength)*fScale, (thePanel.m_RealWidth - theComponent.m_y)*fScale);
		rcComponent.OffsetRect(rcPanel.left, rcPanel.top);
		g->DrawRectangle(&Pen(Color::Red, 2), (INT)rcComponent.left, (INT)rcComponent.top, (INT)rcComponent.Width(), (INT)rcComponent.Height());
	}

	delete g;

	InvalidateRect(rcDrawArea);
}

void CResultDlg::DrawDiagram()
{

}

void CResultDlg::FindAllcomponentFromPanel(Component& thePanel, vector<Component*>& vAllComponent)
{
	for(int i = 0; i < thePanel.m_ChildrenList.size(); i++)
	{		
		try
		{

			if(((Component*)(thePanel.m_ChildrenList[i]))->m_type == NodeType_NeededComponent)
			{
				vAllComponent.push_back((Component*)(thePanel.m_ChildrenList[i]));
			}
			else if(((Component*)(thePanel.m_ChildrenList[i]))->m_type == NodeType_CombinePanel)
			{
				FindAllcomponentFromPanel(*(static_cast<Component*>(thePanel.m_ChildrenList[i])), vAllComponent);
			}
		
		}
		catch(CException* e)
		{
			int j = 0;
		}

	}
}
