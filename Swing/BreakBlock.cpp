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
	//‚±‚±‚ÅplayerBall‚Ì ‚ð‘‚â‚·‚æ‚¤‚É‚·‚é
	lpGameTask.player->SizeUp();
	return true;
}