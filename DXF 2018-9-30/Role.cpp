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
	return (DWORD)Game::decrypt(__���ƣ��) - Game::decrypt(__��ǰƣ��);
}

int Role::GetLevel()
{
	return _Process.ReadInteger(__��ɫ�ȼ�);
}

Pos Role::GetPos()
{
	Pos _Pos;
	//DWORD pos_pointer = readInteger(readInteger(__�����ַ) + __��������ƫ��);
	_Pos.x = (int)_Process.ReadFloat(__��ɫ���� - 4);
	_Pos.y = (int)_Process.ReadFloat(__��ɫ����);
	_Pos.z = (int)_Process.ReadFloat(__��ɫ���� + 4);
	return _Pos;
}