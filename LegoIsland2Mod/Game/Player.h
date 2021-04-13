#pragma once

#include "PlayerObject.h"
#include "Coordinates.h"

struct Player
{
	PlayerObject* playerObject;
	char pad_0004[4];
	void* playerObject_C;
	char pad_000C[12];
	Coordinates globalPlayerCamPos;
	Coordinates globalPlayerHeadPos;
	char pad_0030[96];
};
