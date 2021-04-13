#pragma once

#include "../pch.h"
#include "JumpData.h"

struct MovementData
{
	char pad_0000[24];
	uint8_t movementStateFlag;
	char pad_0019[39];
	float idleKickTimer;
	char pad_0044[12];
	JumpData jumpData;
	char pad_0064[16];
};
