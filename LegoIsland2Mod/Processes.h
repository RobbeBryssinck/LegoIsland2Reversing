#pragma once

#include <vector>
#include <windows.h>
#include <TlHelp32.h>

DWORD GetProcId(const wchar_t* procName);
