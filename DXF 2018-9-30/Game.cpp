#include "pch.h"
#include "Game.h"
#include "Role.h"
#include "Utils.h"
#include "Map.h"

using namespace std;

Game::Game()
{
}


Game::~Game()
{
}

int Game::decrypt(int address)
{
	int eax, esi, edx, i;
	eax = _Process.ReadInteger(address);
	esi = _Process.ReadInteger(__解密基址);
	edx = eax >> 16;
	edx = _Process.ReadInteger(esi + edx * 4 + 36);
	eax = eax & 65535;
	eax = _Process.ReadInteger(edx + eax * 4 + 8468);
	edx = eax & 65535;
	esi = edx << 16;
	esi = esi | edx;
	i = _Process.ReadInteger(address + 4);
	esi = esi ^ i;
	return esi;
}

void Game::encrypt(INT32 Address, INT32 Value)
{
	INT32 EncryptId = 0;
	INT32 OffsetParam = 0;
	INT32 OffsetAddress = 0;
	INT32 Data = 0;
	INT32 AddressMask = 0;
	INT16 ax = 0;
	INT16 si = 0;
	EncryptId = _Process.ReadInteger(Address);
	OffsetParam = _Process.ReadInteger(_Process.ReadInteger(__解密基址) + (EncryptId >> 16) * 4 + 36);
	OffsetAddress = OffsetParam + (EncryptId & 0xFFFF) * 4 + 8468;
	OffsetParam = _Process.ReadInteger(OffsetAddress);
	Data = OffsetParam & 0xFFFF;
	Data += Data << 16;
	ax = OffsetParam & 0xFFFF;
	AddressMask = Address & 0xF;
	if (AddressMask == 0x0)
	{
		si = Value >> 16;
		si -= ax;
		si += Value;
	}
	else if (AddressMask == 0x4)
	{
		si = (Value & 0xFFFF) - (Value >> 16);
	}
	else if (AddressMask == 0x8)
	{
		si = Value >> 16;
		si *= Value;
	}
	else if (AddressMask == 0xC)
	{
		si = Value >> 16;
		si += Value;
		si += ax;
	}
	else
	{
		return;
	}
	ax ^= si;
	_Process.WriteByte(OffsetAddress + 2, (BYTE)ax);
	_Process.WriteByte(OffsetAddress + 3, (BYTE)(ax >> 8));
	_Process.WriteInteger(Address + 4, Data ^ Value);
}


void Game::SelectCopy(int mode)
{
	if (mode == 搬砖)
	{

	}
	else {

	}
}

int Game::Status()
{
	return _Process.ReadInteger(__游戏状态);
}




void Game::MoveToPos(PosObject PosObj)
{
	// 游戏状态
	int GameStatus = Status();
	// 时间变量
	int t1 = GetTime();
	int t2 = GetTime();
	// 卡点列表;
	//map<const char *,bool> 卡点列表;
	vector<string> 卡点列表;
	string flag;
	// 位置变量
	PosObject CurPosObj, StickingPos;
	GetPosObject(StickingPos);
	while (true)
	{
		GetPosObject(CurPosObj);
		t2 = GetTime();
		if (
			CurPosObj.RoomPos.x != PosObj.RoomPos.x ||
			CurPosObj.RoomPos.y != PosObj.RoomPos.y ||
			(abs(CurPosObj.RolePos.x - PosObj.RolePos.x) <= 10 && abs(CurPosObj.RolePos.y - PosObj.RolePos.y) <= 10)
		)
		{
			还原键状态();
			break;
		}
		else {
			if (CurPosObj.RolePos.x - PosObj.RolePos.x >= 10)
			{
				if (getKeyStatus(VK_NUMPAD1) == false)
				{
					if (GameStatus == 3)
					{
						doKeyPress(VK_NUMPAD1);
						keyDown(VK_NUMPAD1);
					}
					else {
						keyDown(VK_NUMPAD1);
					}
				}
			}
			else {
				if (getKeyStatus(VK_NUMPAD1) == true) keyUp(VK_NUMPAD1);
			}

			if (CurPosObj.RolePos.x - PosObj.RolePos.x <= 10)
			{
				if (getKeyStatus(VK_NUMPAD3) == false)
				{
					if (GameStatus == 3)
					{
						doKeyPress(VK_NUMPAD3);
						keyDown(VK_NUMPAD3);
					}
					else {
						keyDown(VK_NUMPAD3);
					}
				}
			}
			else {
				if (getKeyStatus(VK_NUMPAD3) == true) keyUp(VK_NUMPAD3);
			}

			if (CurPosObj.RolePos.y - PosObj.RolePos.y >= 10)
			{
				if (getKeyStatus(VK_NUMPAD5) == false)
				{
					keyDown(VK_NUMPAD5);
				}
			}
			else {
				if (getKeyStatus(VK_NUMPAD5) == true) keyUp(VK_NUMPAD5);
			}

			if (CurPosObj.RolePos.y - PosObj.RolePos.y <= 10)
			{
				if (getKeyStatus(VK_NUMPAD2) == false)
				{
					keyDown(VK_NUMPAD2);
				}
			}
			else {
				if (getKeyStatus(VK_NUMPAD2) == true) keyUp(VK_NUMPAD2);
			}
		}
		if (t2 - t1 >= 3) {
			t1 = GetTime();
			if ((abs(CurPosObj.RolePos.x - StickingPos.RolePos.x) + abs(CurPosObj.RolePos.y - StickingPos.RolePos.y)) <= 30)
			{
				还原键状态();
				if (VectorFindString(卡点列表,FormatString("%d-%d-%d", CurPosObj.RolePos.x, CurPosObj.RolePos.y,2)) == false)
				{
					keyDown(VK_NUMPAD5);
					Sleep(500);
					keyUp(VK_NUMPAD5);
					卡点列表.insert(卡点列表.end(),FormatString("%d-%d-%d", CurPosObj.RolePos.x, CurPosObj.RolePos.y,2));	
				}
				else if (VectorFindString(卡点列表, FormatString("%d-%d-%d", CurPosObj.RolePos.x, CurPosObj.RolePos.y, 3)) == false) {
					keyDown(VK_NUMPAD2);
					Sleep(500);
					keyUp(VK_NUMPAD2);
					卡点列表.insert(卡点列表.end(), FormatString("%d-%d-%d", CurPosObj.RolePos.x, CurPosObj.RolePos.y, 3));
				}
				else if (VectorFindString(卡点列表, FormatString("%d-%d-%d", CurPosObj.RolePos.x, CurPosObj.RolePos.y, 0)) == false) {
					keyDown(VK_NUMPAD1);
					Sleep(500);
					keyUp(VK_NUMPAD1);
					卡点列表.insert(卡点列表.end(), FormatString("%d-%d-%d", CurPosObj.RolePos.x, CurPosObj.RolePos.y, 0));
				}
				else if (VectorFindString(卡点列表, FormatString("%d-%d-%d", CurPosObj.RolePos.x, CurPosObj.RolePos.y, 1)) == false) {
					keyDown(VK_NUMPAD3);
					Sleep(500);
					keyUp(VK_NUMPAD3);
					卡点列表.insert(卡点列表.end(), FormatString("%d-%d-%d", CurPosObj.RolePos.x, CurPosObj.RolePos.y, 1));
				}
				else {
					红色打印("处理卡点失败");
				}
				
			}
			GetPosObject(StickingPos);
		}

		if (卡点列表.size() >= 10)
		{
			红色打印("寻路失败");
			system("pause");
		}
	}
	
	
}

VOID Game::GetPosObject(PosObject &_PosObject)
{
	_PosObject.RoomPos = Map::GetCurrentRoomPos();
	_PosObject.RolePos = Role::GetPos();
}
void Game::GoToCopyByCopyId(int copy_id)
{
	PosObject PosObj;
	while (Status() != 2)
	{
		GetPosObject(PosObj);
		//printf("MaxMapId %d , MinMapId %d , x %d , y %d\n", _CityInfo.MaxMapId, _CityInfo.MinMapId, _CityInfo.x, _CityInfo.y);
		if (PosObj.RoomPos.x == 38 && PosObj.RoomPos.y == 1)
		{
			PosObj.RolePos.x = 450;
			PosObj.RolePos.y = 400;
			
		}
		if (PosObj.RoomPos.x == 14 && PosObj.RoomPos.y == 0)
		{
			PosObj.RolePos.x = 830;
			PosObj.RolePos.y = 200;
		}
		if (PosObj.RoomPos.x == 14 && PosObj.RoomPos.y == 1)
		{
			PosObj.RolePos.x = 2248;
			PosObj.RolePos.y = 279;
		}
		if (PosObj.RoomPos.x == 14 && PosObj.RoomPos.y == 2)
		{
			PosObj.RolePos.x = 811;
			PosObj.RolePos.y = 253;
		}
		MoveToPos(PosObj);
	}
}