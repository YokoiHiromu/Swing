#include "BreakBlock.h"
#include "GameTask.h"

BreakBlock::BreakBlock()
{
	size = 16;
	ID = CHIP_BREAK;
}

BreakBlock::~BreakBlock()
{
}

bool BreakBlock::CollisionProcessing(void)
{
	//ここでplayerBallの を増やすようにする
	lpGameTask.player->SizeUp();
	return true;
}