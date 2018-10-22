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
		红色打印("取窗口句柄失败 Error Code - < %d >", GetLastError());
		return false;
	}
	GetWindowThreadProcessId(hWnd, &ProcessId);
	if (ProcessId == NULL)
	{
		红色打印("获取进程ID失败 Error Code - < %d >", GetLastError());
		return false;
	}
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessId);
	if (hProcess == NULL)
	{
		红色打印("打开进程失败 Error Code - < %d >", GetLastError());
		return false;
	}
	绿色打印("hWnd			< %d >", hWnd);
	红色打印("hProcess		< %d >", hProcess);
	黄色打印("ProcessId		< %d >", ProcessId);
	return true;
}

void Process::Clear()
{
	::CloseHandle(hProcess);
	OutputDebugString(L"123456789");
}

//=====================================读======================================//
BOOL Process::ReadMemory(INT baseAddress, LPVOID lpBuffer, INT nSize)
{
	SIZE_T lpNumberOfBytesRead;
	if (ReadProcessMemory(hProcess, (LPCVOID)baseAddress, lpBuffer, (SIZE_T)nSize, &lpNumberOfBytesRead) == FALSE) {
		//printf("读取 %x 内存时失败！\n", baseAddress);
		//system("pause");
		return false;
	}
	if (lpNumberOfBytesRead != nSize) {
		//printf("读取 %x 内存时实际读取的长度与要读取的长度不一致！\n", baseAddress);
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

//=====================================写======================================//

BOOL Process::WriteMemory(INT lpBaseAddress, LPCVOID lpBuffer, INT nSize)
{
	SIZE_T lpNumberOfBytesRead;
	if (WriteProcessMemory(hProcess, (LPVOID)lpBaseAddress, lpBuffer, (SIZE_T)(nSize), &lpNumberOfBytesRead) == false) {
		printf("写入 %x 内存时失败！\n", lpBaseAddress);
		return false;
	}
	if (lpNumberOfBytesRead != nSize) {
		printf("写入 %x 内存时实际写入的长度与要写入的长度不一致！\n", lpBaseAddress);
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

