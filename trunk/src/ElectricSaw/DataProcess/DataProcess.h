#pragma once
#include "../../../include/DataManager/BaseDataType/CommonData/CommonData.h"
#include "../../../include/DataManager/BaseDataType/Component/Component.h"
#include "../../../include/DataManager/BaseDataType/Panel/Panel.h"
#include "../Misc/Misc.h"

void ConvertInputInfoToComponentList(vector<ComponentInputItem>& vComponentInputItem, ComponentList& componentList);

void SplitComponentList(ComponentList& componentList, vector<ComponentList>& vComponentList);

void ProcessOptimize(/*CSingleon& data*/);