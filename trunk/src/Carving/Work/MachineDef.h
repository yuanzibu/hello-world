#pragma once
#include <map>

using namespace std;

enum LabelMachine
{
	SyntecCycle = 14,
	XiaoFeng = 16
};

class CoordinateHandler;

class IDToCoordinateMap
{
public:
	IDToCoordinateMap();
	~IDToCoordinateMap();

	map<int, CoordinateHandler*> m_mapIDToCoordinate;
};

extern IDToCoordinateMap g_IDToCoordinateMap;