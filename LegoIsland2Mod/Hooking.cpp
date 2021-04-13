#include "Hooking.h"
#include "pch.h"

void Hook(void* targetAddress, void* customCode, int len)
{
	if (len < 5)
	{
		std::cout << "The length of the hook is too short!" << std::endl;
		return;
	}

	DWORD oldProtection;
	VirtualProtect(targetAddress, len, PAGE_EXECUTE_READWRITE, &oldProtection);

	memset(targetAddress, 0x90, len);

	DWORD relativeAddress = ((DWORD)customCode - (DWORD)targetAddress) - 5;
	*(BYTE*)targetAddress = 0xE9;
	*(DWORD*)((DWORD)targetAddress + 1) = relativeAddress;

	VirtualProtect(targetAddress, len, oldProtection, &oldProtection);

	std::cout << "Hook installed correctly!" << std::endl;
}
