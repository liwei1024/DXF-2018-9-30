#pragma once
class AutoThread
{
public:
	int game_status;
	AutoThread();
	~AutoThread();
	int GetGameStatus();
	int GetMaxRoleCount();
	int GetCurrentRoleIndex();
	bool SelectRole();
	void GameStatus_0();
	void GameStatus_1();
	void GameStatus_2();
	void GameStatus_3();
	static void Thread(void* arg);
	void Start();
};

