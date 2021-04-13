#pragma once

#include "EntFnTable.h"

struct EntFnEntry
{
	uint32_t dict1Key0;
	EntFnTable* entVtable;
	char pad_0008[8];
	EntFnEntry* nextEntFnEntry;
	char pad_0014[48];
};
