// DXF 2018-9-30.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "Message.h"
#include "Utils.h"

Process _Process;

int main()
{
	EnableDebugPrivilege(true);

	删除自身();

	窗口初始化();

	_Process.Run();

	SetGlobalKeyboardHook();

	MSG msg;//消息指针
	while (GetMessage(&msg, NULL, 0, 0))
	{
		ThreadMessage(msg.message, msg.wParam, msg.lParam);//线程消息处理
		TranslateMessage(&msg);//等待信号
		DispatchMessage(&msg);//处理信号
	}
	UnsetGlobalKeyboardHook();
	return 0;
}

