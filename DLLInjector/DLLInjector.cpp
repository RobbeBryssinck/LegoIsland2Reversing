#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

DWORD GetProcId(const wchar_t* processName)
{
	DWORD processId = 0;

	HANDLE procSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (procSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(procEntry);

	if (Process32First(procSnapshot, &procEntry))
	{
		do
		{
			if (!_wcsicmp(procEntry.szExeFile, processName))
			{
				processId = procEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(procSnapshot, &procEntry));
	}

	CloseHandle(procSnapshot);
	return processId;
}

int main()
{
	const char* dllPath = "C:\\Users\\robbe\\source\\repos\\LegoIsland2Mod\\Debug\\LegoIsland2Mod.dll";
	const wchar_t* processName = L"LEGO Island 2.exe";
	DWORD processId = 0;

	while (!processId)
	{
		processId = GetProcId(processName);
		if (!processId)
		{
			std::cout << "Process not found. Retrying in 5 seconds..." << std::endl;
			Sleep(5000);
		}
	}

	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);

	if (process && process != INVALID_HANDLE_VALUE)
	{
		void* dllSpace = VirtualAllocEx(process, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (!dllSpace)
		{
			std::cout << "Error: could not allocate dll space." << std::endl;
			return 0;
		}

		WriteProcessMemory(process, dllSpace, dllPath, strlen(dllPath) + 1, 0);

		HANDLE remoteThread = CreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, dllSpace, 0, 0);

		if (remoteThread)
			CloseHandle(remoteThread);
	}

	if (process)
		CloseHandle(process);

	return 0;
}

