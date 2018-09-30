#include "pch.h"
#include "AutoThread.h"
#include "Utils.h"


AutoThread::AutoThread()
{

}


AutoThread::~AutoThread()
{
}

int AutoThread::GetGameStatus()
{
	return _Process.ReadInteger(__ÓÎÏ·×´Ì¬);
}

int AutoThread::GetMaxRoleCount()
{

}

int AutoThread::GetCurrentRoleIndex()
{

}


bool AutoThread::SelectRole()
{
	int CurrentRoleIndex = GetCurrentRoleIndex();
	while (GetGameStatus() == 0)
	{
		doKeyPress(VK_LEFT);
		Sleep(1000);
		if ((CurrentRoleIndex + 1) == GetCurrentRoleIndex())
		{
			doKeyPress(VK_RETURN);
			Sleep(3000);
		}
	}
}

void AutoThread::GameStatus_0()
{
	SelectRole();
}

void AutoThread::GameStatus_1()
{

}

void AutoThread::GameStatus_2()
{

}

void AutoThread::GameStatus_3()
{

}

void AutoThread::Thread(void* arg)
{
	AutoThread * _AutoThread = ((AutoThread*)arg);
	while (true)
	{
		switch (_AutoThread->GetGameStatus())
		{
		case 0:
			break;
		default:
			break;
		}
	}
	return;
}

void AutoThread::Start()
{
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)this, NULL, NULL);
}

