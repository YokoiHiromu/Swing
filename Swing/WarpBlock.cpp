#include "WarpBlock.h"
#include "GameTask.h"

WarpBlock::WarpBlock()
{
	size = 16;
}

WarpBlock::~WarpBlock()
{
}

bool WarpBlock::CollisionProcessing(void)
{
	VECTOR2 Pos = {80, 480};		//���ɍ쐬�����i�K�A������z���g�Ɏ�������Ȃ痐��
	lpGameTask.player->WarpPos(Pos);
	return true;
}