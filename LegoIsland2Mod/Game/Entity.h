#pragma once

#include "../pch.h"
#include "EntFnChainHead.h"

struct Entity
{
	char name[4];
	char pad_0004[56];
	char coords[3][4];
	char pad_0048[20];
	EntFnChainHead* entFnChainHead;
	uint8_t isModelVisible;
	char pad_0061[7];
};
