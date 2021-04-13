#pragma once

#include "Coordinates.h"
#include "UnkStruct4.h"
#include "UnkStruct1.h"

struct PlayerObject
{
	char pad_0000[8];
	UnkStruct4* unkPtr4;
	char pad_000C[48];
	Coordinates playerFeetPos;
	char pad_0048[20];
	UnkStruct1* unkPtr1;
	char pad_0060[5];
	float unk1;
	char pad_0069[103];
};
