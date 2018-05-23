#include "stdafx.h"
#include "Misc.h"
#include <math.h>

CString GetFloatString(float fNum, UCHAR uDecimals)
{
	CString strRet;
	CString strTmp;
	strTmp.Format("%%.%df", uDecimals);
	strRet.Format(strTmp, fNum);
	return strRet;
}

bool IsFloatEqual(float f1, float f2)
{
	if(fabs(f1 - f2) <= 0.01)
		return TRUE;
	return FALSE;
}

float GetScale(float fPanelWidth, float fPanelHeight, float fDrawAreaWidth, float fDrawAreaHeight)
{
	float scale = 1;
	scale = (fDrawAreaWidth / fPanelWidth) > (fDrawAreaHeight / fPanelHeight) ? (fDrawAreaHeight / fPanelHeight) : (fDrawAreaWidth / fPanelWidth);//获取缩放系数
	return scale;
}