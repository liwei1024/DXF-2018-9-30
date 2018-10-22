#include "pch.h"
#include "Role.h"
#include "Utils.h"
#include "Game.h"


Role::Role()
{
}


Role::~Role()
{
}


DWORD Role::GetFatigueValue()
{
	return (DWORD)Game::decrypt(__最大疲劳) - Game::decrypt(__当前疲劳);
}

int Role::GetLevel()
{
	return _Process.ReadInteger(__角色等级);
}

Pos Role::GetPos()
{
	Pos _Pos;
	//DWORD pos_pointer = readInteger(readInteger(__人物基址) + __人物坐标偏移);
	_Pos.x = (int)_Process.ReadFloat(__角色坐标 - 4);
	_Pos.y = (int)_Process.ReadFloat(__角色坐标);
	_Pos.z = (int)_Process.ReadFloat(__角色坐标 + 4);
	return _Pos;
}