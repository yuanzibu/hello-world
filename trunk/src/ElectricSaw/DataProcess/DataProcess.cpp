#include "stdafx.h"
#include "DataProcess.h"
#include "../Misc/Misc.h"
#include "../../../include/DataManager/BaseDataType/CommonData/CommonData.h"
#include "../../../include/DataManager/Algorithm/Algorithm.h"
#include "../../../include/DataManager/BaseDataType/CSingleton/CSingleon.h"





/*--------------------------------------------------------------------------------------*/
//	purpose:
//		将读入的EXCEL小板结构体（ComponentInputItem）转换为小板类（Component）链表
//	
//	param：
//		vector<ComponentInputItem>& vComponentInputItem -- 读入的EXCEL小板数组
//		ComponentList& componentList -- 小板链表
//
//	return:
//		void
/*--------------------------------------------------------------------------------------*/
void ConvertInputInfoToComponentList(vector<ComponentInputItem>& vComponentInputItem, ComponentList& componentList)
{
	componentList.clear();

	int nID = 0;
	for(int i = 0; i < vComponentInputItem.size(); i++)
	{
		ComponentInputItem& theInputItem = vComponentInputItem[i];
		for(int j = 0; j < theInputItem.m_nCount; j++)
		{
			Component *pCpn = new Component;
			pCpn->m_CpnID = nID;
			pCpn->m_BarCode = theInputItem.m_strBarcode;
			pCpn->m_strCabinetName = theInputItem.m_strCabinetName;
			pCpn->m_strComponentName = theInputItem.m_strPanelName;
			pCpn->m_RealLength = theInputItem.m_fLength;
			pCpn->m_RealWidth = theInputItem.m_fWidth;
			pCpn->m_Thickness = theInputItem.m_fThickness;
			pCpn->m_Material = theInputItem.m_strMaterial;

			if(theInputItem.m_strTexture.CompareNoCase("横纹") == 0)
				pCpn->m_Texture = TextureType_H_TEXTURE;
			else if(theInputItem.m_strTexture.CompareNoCase("竖纹") == 0)
				pCpn->m_Texture = TextureType_V_TEXTURE;
			else if(theInputItem.m_strTexture.CompareNoCase("无纹理") == 0)
				pCpn->m_Texture = TextureType_NO_TEXTURE;
			else
				pCpn->m_Texture = TextureType_H_TEXTURE;

			pCpn->m_type = NodeType_NeededComponent;
			pCpn->m_x = 0;
			pCpn->m_y = 0;
			componentList.push_back(pCpn);

			nID++;
		}
	}
}

/*--------------------------------------------------------------------------------------*/
//	purpose:
//		将小板根据材质和厚度分组，同材质、通厚度的为一组
//	
//	param：
//		ComponentList& SrcComponentList -- 所有的小板链表
//		vector<ComponentList>& SplitComponentGroup -- 分好组的小板链表
//
//	return:
//		void
/*--------------------------------------------------------------------------------------*/
void SplitComponentList(ComponentList& SrcComponentList, vector<ComponentList>& SplitComponentGroup)
{
	int nSrcCompSize = SrcComponentList.size();

	// 遍历
	for(int i = 0; i < nSrcCompSize; i++)
	{
		int nListToInsertItemID = -1;
		int nSplitCompGroupSize = SplitComponentGroup.size();
		Component* pSrcComponent = SrcComponentList[i];

		// 查看板件分组中是否已有同材质、厚度的分组
		for(int j = 0; j < nSplitCompGroupSize; j++)
		{
			if(SplitComponentGroup[j].size() > 0 )		// 存在分组
			{
				Component* pSplitComponent = SplitComponentGroup[j][0];

				// 判断材质、厚度是否相同
				if (pSplitComponent->m_Material.Compare(pSrcComponent->m_Material) == 0 
					&& IsFloatEqual(pSplitComponent->m_Thickness, pSrcComponent->m_Thickness) == TRUE)
				{
					nListToInsertItemID = j;
					break;
				}
			}
		}

		if(nListToInsertItemID != -1)	// 找到已有分组
		{
			SplitComponentGroup[nListToInsertItemID].push_back(pSrcComponent);
		}
		else							// 未找到分组，新建分组并插入
		{
			ComponentList componentList;
			componentList.push_back(pSrcComponent);
			SplitComponentGroup.push_back(componentList);
		}
	}
}

void ProcessOptimize(/*CSingleon& data*/)
{
	CSingleon* pSingleton = CSingleon::GetSingleton();

	//pSingleton->Layout();
	//pSingleton->BackupBestSolution();

	CString str;
	
	str.Format("%d", pSingleton->GetBackupSolutionPanelNum());
	str += "块大板,";
	str = "目前最优:" + str;

	MessageBox(NULL, str, "", MB_OK);

}