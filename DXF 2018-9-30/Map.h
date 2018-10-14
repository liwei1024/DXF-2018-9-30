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
	VOID PickUpAllLoot(int mode);
	void SortByDistance(std::vector<ObjectInfo>& Objects);
	VOID AttackMonster(int mode);
	bool IsOpenDoor();
	Pos static GetCurrentRoomPos();
	Pos static GetBossRoomPos();
	bool IsBossRoom();
	bool IsHaveMonster();
	VOID MoveToNextRoom(int mode);
	bool GetPlayerNpc();
	void Flop();
	void StarNextChallenge(int mode);
	VOID PlayerDispose(int mode);
	VOID Follow(int mode);
};

