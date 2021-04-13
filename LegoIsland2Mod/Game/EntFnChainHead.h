#pragma once

#include "../pch.h"
#include "EntFnEntry.h"

struct EntFnChainHead
{
	EntFnEntry* entFnEntry;
	uint32_t unkFlag0;
	uint32_t functionCount;
	uint32_t unkFlag2;
	char pad_0010[8];
	float distanceToPlayer;
	char pad_001C[4];
};
