#pragma once
std::string FormatString(const char *lpcszFormat, ...);

std::wstring FormatWstring(const wchar_t *lpcwszFormat, ...);

bool ɾ������();

void ��ɫ��ӡ(const char *����, ...);

void ��ɫ��ӡ(const char *����, ...);

void ��ɫ��ӡ(const char *����, ...);

void ��ɫ��ӡ(const char *����, ...);

void ��ɫ��ӡ(const char *����, ...);

void ���ڳ�ʼ��();

bool EnableDebugPrivilege(bool bEnable);

int createRandom(int min, int max);
char * unicodeToAnsi(const wchar_t * wstr);
INT getTime();
VOID keyDown(INT keyCode);
VOID keyUp(INT keyCode);
VOID doKeyPress(INT keyCode, INT s = 100);
bool Զ��CALL(int CALL_Address, bool async = true);

std::string PosToString(Pos pos);

DWORD GetSystemTime();