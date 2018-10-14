#pragma once
class AutoThread
{
public:
	int game_status;
	int mode;
	AutoThread();
	~AutoThread();
	int GetGameStatus();
	int GetMaxRoleCount();
	int GetCurrentRoleIndex();
	VOID SelectRole();
	VOID OutputPlayerLog(int mode);
	void GoToCopy();
	void GameStatus_0();
	void GameStatus_1();
	void GameStatus_2();
	void GameStatus_3();
	static void Thread(void* arg);
	void Start(int mode);
};

