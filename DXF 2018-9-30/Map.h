#pragma once
class Map
{
public:
	Map();
	~Map();
	DWORD GetMapStartAddress();
	DWORD GetMapObjectCount(DWORD MapStartAddress);
	ObjectInfo GetObjectInfo(DWORD ObjectPointer);
	VOID OutputMapObjectsInfo();
	const char * GetMapName();
	VOID PickUpAllLoot(void(*PickUpFunction)(ObjectInfo));
	std::vector<ObjectInfo> SortByDistance(std::vector<ObjectInfo> Objects);
	VOID AttackMonster(void(*AttackFunction)(ObjectInfo));
};

