#include "pch.h"
#include "AutoThread.h"
#include "Utils.h"
#include "Role.h"
#include "Map.h"
#include "Game.h"


AutoThread::AutoThread()
{

}


AutoThread::~AutoThread()
{
}

int AutoThread::GetGameStatus()
{
	return _Process.ReadInteger(__游戏状态);
}

int AutoThread::GetMaxRoleCount()
{

}

int AutoThread::GetCurrentRoleIndex()
{
	return _Process.ReadOfset(__遍历取值, {__角色下标偏移});
}


VOID AutoThread::SelectRole()
{
	int CurrentRoleIndex = GetCurrentRoleIndex();
	while (GetGameStatus() == 0)
	{
		doKeyPress(VK_RIGHT);
		Sleep(1000);
		if ((CurrentRoleIndex + 1) == GetCurrentRoleIndex())
		{
			doKeyPress(VK_RETURN);
			Sleep(3000);
		}
	}
}

VOID AutoThread::OutputPlayerLog(int mode) 
{

}



void AutoThread::GameStatus_0()
{
	SelectRole();
}

void AutoThread::GameStatus_1()
{

	Game().GoToCopyByCopyId(104);
}

void AutoThread::GameStatus_2()
{
	Sleep(1000);
	if (Role().GetFatigueValue() == 0)
	{
		doKeyPress(VK_ESCAPE);
		Sleep(1000);
	}
	else {
		Game::SelectCopy(mode);
	}

}

void AutoThread::GameStatus_3()
{
	Map _Map;
	if (_Map.IsOpenDoor() == true)
	{
		_Map.PickUpAllLoot(mode);
		if (_Map.IsBossRoom() == true && _Map.IsHaveMonster() == false)
		{
			_Map.PlayerDispose(mode);
		}
		else {
			_Map.MoveToNextRoom(mode);
		}
	}
	else {
		_Map.Follow(mode);
	}
}

void AutoThread::Thread(void* arg)
{
	AutoThread * _AutoThread = ((AutoThread*)arg);
	while (true)
	{
		switch (_AutoThread->GetGameStatus())
		{
		case 0:
			_AutoThread->GameStatus_0();
			break;
		case 1:
			_AutoThread->GameStatus_1();
			break;
		case 2:
			_AutoThread->GameStatus_2();
			break;
		case 3:
			_AutoThread->GameStatus_3();
			break;
		default:
			break;
		}
	}
	return;
}

// mode 1=搬砖 2=剧情 3=深渊 4=黄龙 
void AutoThread::Start(int mode)
{
	mode = mode;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)this, NULL, NULL);
}

