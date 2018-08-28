#include "DamageBlock.h"

DamageBlock::DamageBlock()
{
	size = 16;
	ID = CHIP_DAMAGE;
}

DamageBlock::~DamageBlock()
{
}

bool DamageBlock::CollisionProcessing(void)
{
	DamageProcessing();
	ReverseMove();
	return false;
}