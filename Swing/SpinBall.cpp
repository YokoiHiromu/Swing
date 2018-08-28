#include "SpinBall.h"
#include "GameTask.h"
#include "Player.h"

SpinBall::SpinBall()
{
	size = 16;
	ID = CHIP_SPIN;
}

SpinBall::~SpinBall()
{
}

bool SpinBall::CollisionProcessing(void)
{
	ReverseMove();
	return false;
}
