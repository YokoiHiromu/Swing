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
	//������playerBall�� �𑝂₷�悤�ɂ���
	lpGameTask.player->SizeUp();
	return true;
}