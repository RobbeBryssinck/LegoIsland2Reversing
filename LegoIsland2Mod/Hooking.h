#pragma once

#include <windows.h>

void Hook(void* targetAddress, void* customCode, int len);
