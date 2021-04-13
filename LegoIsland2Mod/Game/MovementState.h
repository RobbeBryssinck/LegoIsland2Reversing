#pragma once

enum MovementState : unsigned char
{
	Jumping = 0x1,
	StartJumpWindUp = 0x2,
	IdleKick = 0x3,
	PizzaThrow = 0xB,
	Still = 0x1B,
	DoubleJumping = 0x1F,
	FlyingInHelicopter = 0x4C,
	GroundedAfterJump = 0x57,
};
