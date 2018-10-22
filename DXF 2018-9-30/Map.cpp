#include "pch.h"
#include "Map.h"
#include "Utils.h"
#include "Knapsac.h"
#include "AutoThread.h"
#include "Role.h"
#include "Game.h"

using namespace std;
Map::Map()
{
}


Map::~Map()
{
}

DWORD Map::GetMapStartAddress()
{
	return  _Process.ReadInteger(_Process.ReadOfset(__人物基址, { __地图偏移 }) + __首地址);
}

DWORD Map::GetMapObjectCount(DWORD MapStartAddress)
{
	return  (_Process.ReadInteger(_Process.ReadOfset(__人物基址, { __地图偏移 }) + __尾地址) - MapStartAddress) / 4;
}

ObjectInfo Map::GetObjectInfo(DWORD ObjectPointer)
{
	ObjectInfo _ObjectInfo;
	DWORD PosPointer;
	_ObjectInfo.address = ObjectPointer;
	_ObjectInfo.type = _Process.ReadInteger(ObjectPointer + __类型偏移);
	_ObjectInfo.camp = _Process.ReadInteger(ObjectPointer + __阵营偏移);
	_ObjectInfo.health_point = _Process.ReadLong(ObjectPointer + __血量偏移);
	_ObjectInfo.code = _Process.ReadInteger(ObjectPointer + __代码偏移);
	_ObjectInfo.name = _Process.ReadString(_Process.ReadInteger(ObjectPointer + __名称偏移), 100);
	if (_ObjectInfo.type == 273)
	{
		PosPointer = _Process.ReadInteger(ObjectPointer + __人物坐标偏移);
		_ObjectInfo.pos.x = (int)_Process.ReadFloat(PosPointer + 0);
		_ObjectInfo.pos.y = (int)_Process.ReadFloat(PosPointer + 4);
		_ObjectInfo.pos.z = (int)_Process.ReadFloat(PosPointer + 8);
	}
	else {
		PosPointer = _Process.ReadInteger(ObjectPointer + __坐标偏移);
		_ObjectInfo.pos.x = (int)_Process.ReadFloat(PosPointer + 0x10);
		_ObjectInfo.pos.y = (int)_Process.ReadFloat(PosPointer + 0x14);
		_ObjectInfo.pos.z = (int)_Process.ReadFloat(PosPointer + 0x18);
	}
	return _ObjectInfo;
}

VOID Map::OutputMapObjectsInfo()
{
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	string str;
	ObjectInfo _ObjectInfo;
	粉色打印("count %d", MapObjectCount);
	粉色打印("name %s", GetMapName());
	str += "=================================================================================================================================\n";
	for (size_t i = 0; i < MapObjectCount; i++)
	{
		_ObjectInfo = GetObjectInfo(_Process.ReadInteger(MapStartAddress + i * 4));
		str += "地址:" + FormatString("0x%8x", _ObjectInfo.address);
		str += "\t代码:" + FormatString("%5d", _ObjectInfo.code);
		str += "\t类型:" + FormatString("%5d", _ObjectInfo.type);
		str += "\t阵营:" + FormatString("%3d", _ObjectInfo.camp);
		str += "\t血量:" + FormatString("%12d", _ObjectInfo.health_point);
		str += "\t位置:" + FormatString("%d,%d,%d", _ObjectInfo.pos.x, _ObjectInfo.pos.y, _ObjectInfo.pos.z);
		str += "\t名称:" + FormatString("%s", _ObjectInfo.name);
		str += "\n";
		青色打印("%s", str.c_str());
		str.clear();
	}
	
}

const char * Map::GetMapName()
{
	return _Process.ReadString(__地图名称,100);
}

VOID Map::PickUpAllLoot(int mode)
{
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	ObjectInfo _ObjectInfo;
	for (size_t i = 0; i < MapObjectCount; i++) {
		_ObjectInfo = GetObjectInfo(MapStartAddress + i * 4);
		if (_ObjectInfo.type == 289 && _ObjectInfo.camp == 200)
		{
			//PickUpFunction(_ObjectInfo);
		}
	}
}

void Map::SortByDistance(vector<ObjectInfo> &Objects)
{
	ObjectInfo temp_var;
	ObjectInfo RolePos = GetObjectInfo(_Process.ReadInteger(__人物基址));
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (size_t j = 0; j < Objects.size() - i; j++)
		{
			if (abs(Objects[j].pos.x - RolePos.pos.x) + abs(Objects[j].pos.y - RolePos.pos.y) > abs(Objects[j+1].pos.x - RolePos.pos.x) + abs(Objects[j+1].pos.y - RolePos.pos.y))
			{
				temp_var = Objects[j];
				Objects[j + 1] = Objects[j];
				Objects[j] = temp_var;
			}
		}
	}
}

VOID Map::AttackMonster(int mode)
{
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	vector<ObjectInfo> Objects;
	ObjectInfo _ObjectInfo;
	for (size_t i = 0; i < MapObjectCount; i++) {
		_ObjectInfo = GetObjectInfo(MapStartAddress + i * 4);
		if (_ObjectInfo.code == 258 || _ObjectInfo.code == 818 || _ObjectInfo.code == 63821)
		{
			continue;
		}
		if (
			_ObjectInfo.type == 529 ||
			_ObjectInfo.type == 273 ||
			_ObjectInfo.type == 545
			)
		{
			if (_ObjectInfo.camp > 0)
			{
				if (_ObjectInfo.health_point > 0 || _ObjectInfo.code == 8104 || _ObjectInfo.code == 817)
				{
					Objects.insert(Objects.end(), _ObjectInfo);
				}
			}
		}
	}
	SortByDistance(Objects);
	for (size_t i = 0; i < Objects.size(); i++)
	{
		//AttackFunction(Objects[i]);
		if (mode == 搬砖)
		{

		}
		else {

		}
	}
}

bool Map::IsOpenDoor()
{
	if (Game::decrypt(_Process.ReadOfset(__人物基址, {__地图偏移 }) + __开门偏移) == 0)
	{
		return true;
	}
	else {
		return false;
	}
		
}

Pos Map::GetCurrentRoomPos()
{
	Pos CurrentRoomPos;
	if (Game::Status() == 1)
	{
		CurrentRoomPos.x = _Process.ReadOfset(__遍历取值, { __大区域偏移 });
		CurrentRoomPos.y = _Process.ReadOfset(__遍历取值, { __小区域偏移 });
	}
	else {
		DWORD OffsetAddress = _Process.ReadOfset(__房间编号, { __时间基址 ,__门型偏移 });
		CurrentRoomPos.x = _Process.ReadInteger(OffsetAddress + __当前房间X);
		CurrentRoomPos.y = _Process.ReadInteger(OffsetAddress + __当前房间Y);
	}
	
	return CurrentRoomPos;
}

Pos Map::GetBossRoomPos()
{
	Pos BossRoomPos;
	DWORD OffsetAddress = _Process.ReadOfset(__房间编号, { __时间基址 ,__门型偏移 });
	BossRoomPos.x = Game::decrypt(OffsetAddress + __BOSS房间X);
	BossRoomPos.y = Game::decrypt(OffsetAddress + __BOSS房间Y);
	return BossRoomPos;
}

bool Map::IsBossRoom()
{
	Pos CurrentRoomPos;
	Pos BossRoomPos;

	CurrentRoomPos = GetCurrentRoomPos();
	BossRoomPos = GetBossRoomPos();

	if (CurrentRoomPos.x == BossRoomPos.x && CurrentRoomPos.y == BossRoomPos.y)
	{
		return true;
	}
	return false;
}

bool Map::IsHaveMonster()
{
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	ObjectInfo _ObjectInfo;
	for (DWORD i = 0; i < MapObjectCount; i++) {
		_ObjectInfo = GetObjectInfo(MapStartAddress + i * 4);
		if (_ObjectInfo.code == 258 || _ObjectInfo.code == 818 || _ObjectInfo.code == 63821)
		{
			continue;
		}
		if (
			_ObjectInfo.type == 529 ||
			_ObjectInfo.type == 273 ||
			_ObjectInfo.type == 545
			)
		{
			if (_ObjectInfo.camp > 0)
			{
				if (_ObjectInfo.health_point > 0 || _ObjectInfo.code == 8104 || _ObjectInfo.code == 817)
				{
					return true;
				}
			}
		}
	}
	return false;
}

VOID Map::MoveToNextRoom(int mode)
{

}

bool Map::GetPlayerNpc()
{
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	ObjectInfo _ObjectInfo;
	for (size_t i = 0; i < MapObjectCount; i++)
	{
		_ObjectInfo = GetObjectInfo(MapStartAddress + i * 4);
		if (_ObjectInfo.type == 33 && _ObjectInfo.camp == 200 && _ObjectInfo.code == 48026)
		{
			return true;
		}
	}
	return false;
}

void Map::Flop() 
{
	while (GetPlayerNpc() == false)
	{
		doKeyPress(VK_ESCAPE);
		Sleep(500);
	}
}

void Map::StarNextChallenge(int mode)
{
	Pos CurrentRoomPos;
	AutoThread _AutoThread;
	CurrentRoomPos = GetCurrentRoomPos();
	DWORD CurrentGameStatus = _AutoThread.GetGameStatus();
	while (true)
	{

		if (CurrentRoomPos.x != GetCurrentRoomPos().x || CurrentRoomPos.y != GetCurrentRoomPos().y || CurrentGameStatus != _AutoThread.GetGameStatus())
		{
			_AutoThread.OutputPlayerLog(mode);
			break;
		}

		if (mode == 搬砖)
		{
			if (Role().GetFatigueValue() == 0) {
				doKeyPress(VK_F12);
			}
			else {
				doKeyPress(VK_F10);
			}
			Sleep(1000);
		}
		else if (mode == 剧情) {
			doKeyPress(VK_ESCAPE);
			doKeyPress(VK_SPACE);
			Sleep(300);
		}
	}
}

VOID Map::PlayerDispose(int mode)
{
	Flop(); //翻牌
	Knapsac().Clear(mode);//卖物
	StarNextChallenge(mode);//下次挑战
}

VOID Map::Follow(int mode) {
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	vector<ObjectInfo> Objects;
	ObjectInfo _ObjectInfo;
	for (DWORD i = 0; i < MapObjectCount; i++) {
		_ObjectInfo = GetObjectInfo(MapStartAddress + i * 4);
		if (_ObjectInfo.code == 258 || _ObjectInfo.code == 818 || _ObjectInfo.code == 63821)
		{
			continue;
		}
		if (
			_ObjectInfo.type == 529 ||
			_ObjectInfo.type == 273 ||
			_ObjectInfo.type == 545
			)
		{
			if (_ObjectInfo.camp > 0)
			{
				if (_ObjectInfo.health_point > 0 || _ObjectInfo.code == 8104 || _ObjectInfo.code == 817)
				{
					Objects.insert(Objects.end(), _ObjectInfo);
				}
			}
		}
	}
	SortByDistance(Objects);
	for (DWORD i = 0; i < Objects.size(); i++)
	{
		//AttackFunction(Objects[i]);
		if (mode == 搬砖)
		{
			//Game::MoveToPos(Objects[i].pos);
			return;
		}
		else {

		}
	}
}