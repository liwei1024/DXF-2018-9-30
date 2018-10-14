#include "pch.h"
#include "Message.h"
#include "Utils.h"
#include "Map.h"
#include "Task.h"
#include "AStar.h"
#include "Game.h"
#include "AutoThread.h"


HHOOK g_hHook;
DWORD g_dwMainThreadId;
PosObject _PosObject;

VOID ThreadMessage(
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	青色打印("message %d", message);
	青色打印("wParam %d", wParam);
	青色打印("lParam %d", lParam);
}

void test() {
	while (true)
	{

		青色打印("当前游戏状态 %d",_Process.ReadInteger(0x400000));
		Sleep(10);
	}
}


LRESULT CALLBACK Keypress(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* p = (CWPSTRUCT*)lParam;
	if (nCode == HC_ACTION)
	{
		switch (wParam) //wParam中是消息ID
		{
			// 键盘消息
		case WM_KEYDOWN:
		{
			switch (p->lParam)
			{
			case VK_HOME:
				PostThreadMessage(g_dwMainThreadId, 10024, 0, 0);
				/*Map().OutputMapObjectsInfo();
				Task().OutputTaskInfo(0);
				AStar().GetDirection(1);*/
				//AutoThread().Start(搬砖);
				/*Game().GetPosObject(_PosObject);
				_PosObject.RolePos.x = 1000;
				_PosObject.RolePos.y = 200;
				Game().MoveToPos(_PosObject);*/
				Game().GoToCopyByCopyId(104);
				//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)test, NULL, NULL, NULL);
				break;

			default:
				break;
			}
		}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

BOOL WINAPI ConsoleCtrlhandler(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)//退出事件
	{
		UnhookWindowsHookEx(g_hHook);
		//OutputDebugString(L"exit 1");
		还原键状态();
		_Process.Clear();
		PostThreadMessage(g_dwMainThreadId, WM_QUIT, 0, 0);
	}

	return TRUE;
}

VOID SetGlobalKeyboardHook()
{
	g_dwMainThreadId = GetCurrentThreadId();
	SetConsoleCtrlHandler(ConsoleCtrlhandler, TRUE);
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, Keypress, GetModuleHandle(NULL), NULL);
	if (g_hHook == NULL)
		红色打印("hook failure!");
}

VOID UnsetGlobalKeyboardHook()
{
	SetConsoleCtrlHandler(ConsoleCtrlhandler, FALSE);
}