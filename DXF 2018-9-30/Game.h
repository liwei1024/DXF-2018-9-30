#pragma once
class Game
{
public:
	Game();
	~Game();
	int static decrypt(int address);
	void static encrypt(INT32 Address, INT32 Value);
	void static SelectCopy(int mode);
	int static Status();
	void  MoveToPos(PosObject PosObj);
	VOID GetPosObject(PosObject & _PosObject);
	//void static MoveToPos(PosObject end_pos, int type);
	void GoToCopyByCopyId(int copy_id);
};

