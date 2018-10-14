#include "pch.h"
#include "Process.h"
#include "Utils.h"


using namespace std;

//ProcessInfo _ProcessInfo;

Process::Process()
{
	
}


Process::~Process()
{

	
}

BOOL Process::Run(LPCWSTR lpClass, LPCWSTR lpName)
{
	hWnd = FindWindow(lpClass, lpName);
	if (hWnd == NULL)
	{
		��ɫ��ӡ("ȡ���ھ��ʧ�� Error Code - < %d >", GetLastError());
		return false;
	}
	GetWindowThreadProcessId(hWnd, &ProcessId);
	if (ProcessId == NULL)
	{
		��ɫ��ӡ("��ȡ����IDʧ�� Error Code - < %d >", GetLastError());
		return false;
	}
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessId);
	if (hProcess == NULL)
	{
		��ɫ��ӡ("�򿪽���ʧ�� Error Code - < %d >", GetLastError());
		return false;
	}
	��ɫ��ӡ("hWnd			< %d >", hWnd);
	��ɫ��ӡ("hProcess		< %d >", hProcess);
	��ɫ��ӡ("ProcessId		< %d >", ProcessId);
	return true;
}

void Process::Clear()
{
	::CloseHandle(hProcess);
	OutputDebugString(L"123456789");
}

//=====================================��======================================//
BOOL Process::ReadMemory(INT baseAddress, LPVOID lpBuffer, INT nSize)
{
	SIZE_T lpNumberOfBytesRead;
	if (ReadProcessMemory(hProcess, (LPCVOID)baseAddress, lpBuffer, (SIZE_T)nSize, &lpNumberOfBytesRead) == FALSE) {
		//printf("��ȡ %x �ڴ�ʱʧ�ܣ�\n", baseAddress);
		//system("pause");
		return false;
	}
	if (lpNumberOfBytesRead != nSize) {
		//printf("��ȡ %x �ڴ�ʱʵ�ʶ�ȡ�ĳ�����Ҫ��ȡ�ĳ��Ȳ�һ�£�\n", baseAddress);
		//system("pause");
		return false;
	}
	return true;
}

byte Process::ReadByte(INT address)
{
	byte lpBuffer;
	ReadMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

short Process::ReadShort(INT address)
{
	short lpBuffer;
	ReadMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

int Process::ReadInteger(INT address)
{
	int lpBuffer;
	ReadMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

LONGLONG Process::ReadLong(INT address)
{
	LONGLONG lpBuffer;
	ReadMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

float Process::ReadFloat(INT lpBaseAddress)
{
	float lpBuffer;
	ReadMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

double Process::ReadDouble(INT lpBaseAddress)
{
	double lpBuffer;
	ReadMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

vector<byte> Process::ReadBytes(INT lpBaseAddress, INT len)
{
	byte * lpBuffer;
	lpBuffer = new byte[len];
	memset(lpBuffer, 0, len);
	ReadMemory(lpBaseAddress, lpBuffer, len);
	vector<byte>  result;
	result.resize(len);
	for (INT i = 0; i < len; i++)
	{
		result[i] = lpBuffer[i];
	}
	delete[]lpBuffer;
	return result;
}

CHAR* Process::ReadString(INT lpBaseAddress, INT len)
{
	TCHAR *lpBuffer;
	len = len * 2 + 2;
	lpBuffer = new TCHAR[len];
	ReadMemory(lpBaseAddress, lpBuffer, len);
	CHAR * str = unicodeToAnsi(lpBuffer);
	return str;
}

DWORD Process::ReadOfset(DWORD lpBaseAddress,vector<int> Ofsets)
{
	DWORD OfsetAddress = ReadInteger(lpBaseAddress);
	for (size_t i = 0; i < Ofsets.size(); i++)
	{
		OfsetAddress = ReadInteger(OfsetAddress + Ofsets[i]);
	}
	return OfsetAddress;
}

//=====================================д======================================//

BOOL Process::WriteMemory(INT lpBaseAddress, LPCVOID lpBuffer, INT nSize)
{
	SIZE_T lpNumberOfBytesRead;
	if (WriteProcessMemory(hProcess, (LPVOID)lpBaseAddress, lpBuffer, (SIZE_T)(nSize), &lpNumberOfBytesRead) == false) {
		printf("д�� %x �ڴ�ʱʧ�ܣ�\n", lpBaseAddress);
		return false;
	}
	if (lpNumberOfBytesRead != nSize) {
		printf("д�� %x �ڴ�ʱʵ��д��ĳ�����Ҫд��ĳ��Ȳ�һ�£�\n", lpBaseAddress);
		return false;
	}
	return true;
}

BOOL Process::WriteByte(INT lpBaseAddress, byte lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteShort(INT lpBaseAddress, short lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteInteger(INT lpBaseAddress, int lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteLong(INT lpBaseAddress, LONGLONG lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteFloat(INT lpBaseAddress, float lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteDouble(INT lpBaseAddress, double lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteBytes(INT lpBaseAddress, vector<int> bytes)
{
	INT size = bytes.size();
	byte *lpBuffer = new byte[size];
	for (INT i = 0; i < size; i++)
	{
		lpBuffer[i] = bytes[i];
	}
	bool result = WriteMemory(lpBaseAddress, lpBuffer, size);
	delete[]lpBuffer;
	return result;
}

BOOL Process::WriteString(INT lpBaseAddress, LPCWSTR lpBuffer)
{
	INT len = wcslen(lpBuffer) * 2 + 2;
	return WriteMemory(lpBaseAddress, (LPCVOID)lpBuffer, len);
}

