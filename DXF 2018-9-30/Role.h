#pragma once
class Role
{
public:
	Role();
	~Role();
	DWORD GetFatigueValue();
	int GetLevel();
	Pos static GetPos();
};

